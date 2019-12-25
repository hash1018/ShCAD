
#include "ShTemporaryMoveAxisAction.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Command\ShAvailableCommands.h"
#include "Base\ShCursorShape.h"
#include <qpainter.h>
#include "Interface\Private\ShAxis.h"
#include "Data\ShScrollPosition.h"
#include "Entity\Private\Algorithm\ShMover.h"
#include "UnRedo\ShCADWidgetTransaction.h"
#include "Base\ShGlobal.h"

ShTemporaryMoveAxisAction::ShTemporaryMoveAxisAction(ShCADWidget *widget)
	:ShTemporaryAction(widget), createdPreview(false) {

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowKey(KeyType::Enter).
		allowKey(KeyType::Return).
		allowKey(KeyType::EscBackToPrevious).
		allowInput().
		build();

	this->availableCommands = ShAvailableCommands::ShBuilder(this->widget, this).
		addAvailableCommand(CommandType::AbsoluteCoordinate).
		addAvailableCommand(CommandType::Empty_CancelBackToPrevious).
		addAvailableCommand(CommandType::RelativeCoordinate).
		addAvailableCommand(CommandType::PolarCoordinate).
		addAvailableCommand(CommandType::DistanceFromBase).
		build();
}

ShTemporaryMoveAxisAction::~ShTemporaryMoveAxisAction() {

	this->widget->getRubberBand().clear();
}

void ShTemporaryMoveAxisAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShTemporaryMoveAxisAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShTemporaryMoveAxisAction::getType() {

	return ActionType::ActionMoveAxis;
}

QCursor ShTemporaryMoveAxisAction::getCursorShape() {

	return ShCursorShape::getCursor(ShCursorShape::CursorType::Drawing);
}

void ShTemporaryMoveAxisAction::draw(QPainter *painter) {

	int dx, dy;
	this->widget->convertEntityToDevice(0, 0, dx, dy);

	if (painter->isActive() == false)
		painter->begin(this->widget);

	painter->fillRect(dx - 4, dy - 4, 8, 8, QColor(255, 000, 000));

	this->widget->convertEntityToDevice(this->widget->getRubberBand().getEnd().x, this->widget->getRubberBand().getEnd().y, dx, dy);

	painter->setPen(QColor(204, 204, 204));
	painter->drawLine(dx, dy, dx + 100, dy);
	painter->drawLine(dx, dy, dx, dy - 100);

	painter->drawText(dx + 90, dy + 15, "X");
	painter->drawText(dx - 15, dy - 90, "Y");
	painter->drawText(dx - 15, dy + 15, "O");
	painter->setPen(QColor(0, 0, 0));

	painter->end();
}

QString ShTemporaryMoveAxisAction::getHeadTitle() {

	return shGetLanValue_command("Command/Specify origin point") + ": ";
}

void ShTemporaryMoveAxisAction::invalidate(ShPoint3d &point) {

	if (this->createdPreview == false) {
	
		this->widget->getRubberBand().create(ShLineData(ShPoint3d(), ShPoint3d()));
	}

	this->widget->getRubberBand().setEnd(point);

	this->widget->update((DrawType)(DrawType::DrawCaptureImage |
		DrawType::DrawPreviewEntities | DrawType::DrawActionHandler));
}

ShAvailableDraft ShTemporaryMoveAxisAction::getAvailableDraft() {

	ShAvailableDraft draft;

	draft.setAvailableOrthogonal(true);
	draft.setAvailableSnap(true);
	draft.setOrthogonalBasePoint(ShPoint3d(0,0,0));
	draft.setSnapBasePoint(ShPoint3d(0, 0, 0));

	return draft;
}

void ShTemporaryMoveAxisAction::trigger(const ShPoint3d &point) {

	ShPoint3d prevCenter = this->widget->getAxis().getCenter();
	ShPoint3d currentCenter;

	currentCenter.x = point.x - this->widget->getScrollPosition().horizontal + prevCenter.x;
	currentCenter.y = -1 * (point.y + this->widget->getScrollPosition().vertical - prevCenter.y);

	currentCenter.x += this->widget->getScrollPosition().horizontal;
	currentCenter.y += this->widget->getScrollPosition().vertical;

	this->widget->getAxis().setCenter(currentCenter);

	ShMoverByAxis visitor(this->widget->getScrollPosition(), prevCenter, currentCenter, this->widget->getZoomRate());

	auto itr = this->widget->getEntityTable().begin();

	for (itr; itr != this->widget->getEntityTable().end(); ++itr)
		(*itr)->accept(&visitor);

	ShGlobal::pushNewTransaction(this->widget, new ShChangeAxisPositionTransaction(this->widget, prevCenter, currentCenter));


	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();

	this->setLastBasePoint(point);
	this->actionFinished();
}
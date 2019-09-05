
#include "ShTemporaryStretchAction.h"
#include <qpainter.h>
#include "KeyHandler\ShKeyHandler.h"
#include "Command\ShAvailableCommands.h"
#include "Entity\Private\ShStretchVisitor.h"


ShTemporaryStretchAction::ShTemporaryStretchAction(ShCADWidget *widget, const ShPoint3d &vertexPoint, const QLinkedList<ShEntity*> &possibleStretchEntities,
	const QLinkedList<ShStretchData*> &stretchDatas)
	:ShTemporaryAction(widget), vertexPoint(vertexPoint), possibleStretchEntities(possibleStretchEntities), stretchDatas(stretchDatas),
	createdPreview(false) {

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

ShTemporaryStretchAction::~ShTemporaryStretchAction() {

	this->widget->getPreview().clear();
	this->widget->getRubberBand().clear();
	while (!this->stretchDatas.isEmpty())
		delete this->stretchDatas.takeFirst();
}

void ShTemporaryStretchAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShTemporaryStretchAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShTemporaryStretchAction::getType() {

	return ActionType::ActionTempStretch;
}

QCursor ShTemporaryStretchAction::getCursorShape() {

	return QCursor(Qt::CursorShape::CrossCursor);
}

void ShTemporaryStretchAction::draw(QPainter *painter) {

	if (painter->isActive() == false)
		painter->begin(this->widget);

	int dx, dy;
	this->widget->convertEntityToDevice(this->vertexPoint.x, this->vertexPoint.y, dx, dy);

	painter->fillRect(dx - 3, dy - 3, 6, 6, QColor(255, 000, 000));
}

QString ShTemporaryStretchAction::getHeadTitle() {

	return shGetLanValue_command("Command/Specify stretch point") + ": ";
}

void ShTemporaryStretchAction::invalidate(ShPoint3d &point) {

	if (this->createdPreview == false) {
	
		auto itr = this->possibleStretchEntities.begin();

		for (itr; itr != this->possibleStretchEntities.end(); ++itr)
			this->widget->getPreview().add((*itr)->clone());

		this->widget->getRubberBand().setData(ShLineData(this->vertexPoint, this->vertexPoint));

		this->createdPreview = true;
	}
	else {
	
		this->widget->getRubberBand().setEnd(point);

		ShStretchVisitor visitor(this->vertexPoint, point);

		auto itr = this->widget->getPreview().begin();
		auto originalItr = this->possibleStretchEntities.begin();
		auto dataItr = this->stretchDatas.begin();

		for (itr; itr != this->widget->getPreview().end(); ++itr) {
		
			visitor.setOriginal(*originalItr);
			visitor.setStretchData(*dataItr);
			(*itr)->accept(&visitor);
			++originalItr;
			++dataItr;
		}

	}
	
	this->widget->update((DrawType)(DrawType::DrawCaptureImage |
		DrawType::DrawPreviewEntities | DrawType::DrawActionHandler));
}

ShAvailableDraft ShTemporaryStretchAction::getAvailableDraft() {

	ShAvailableDraft draft;

	draft.setAvailableOrthogonal(true);
	draft.setAvailableSnap(true);
	draft.setOrthogonalBasePoint(this->vertexPoint);
	draft.setSnapBasePoint(this->vertexPoint);

	return draft;
}

ShPoint3d ShTemporaryStretchAction::getLastBasePoint() {

	return this->vertexPoint;
}

ShPoint3d ShTemporaryStretchAction::getCurrentAboutToPickPoint() {

	return this->widget->getRubberBand().getEnd();
}

void ShTemporaryStretchAction::trigger(const ShPoint3d &point) {

}
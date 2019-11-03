
#include "ShDrawXLineAction.h"
#include <QMouseEvent>
#include "KeyHandler\ShKeyHandler.h"
#include "KeyHandler\ShCustomKey.h"
#include "Command\ShAvailableCommands.h"
#include "Command\ShCustomCommand.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShConstructionLine.h"

ShDrawXLineAction::ShDrawXLineAction(ShCADWidget *widget)
	:ShDrawAction(widget), status(Status::PickedNothing) {

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowKey(KeyType::Enter).
		allowKey(KeyType::Return).
		allowKey(KeyType::EscCancelCurrent).
		allowInput().
		build();

	this->availableCommands = ShAvailableCommands::ShBuilder(this->widget, this).
		addAvailableCommand(CommandType::Empty_Cancel).
		addAvailableCommand(CommandType::AbsoluteCoordinate).
		addAvailableCommand(CommandType::RelativeCoordinate).
		addAvailableCommand(CommandType::PolarCoordinate).
		addAvailableCommand(CommandType::DistanceFromBase).
		build();
}

ShDrawXLineAction::~ShDrawXLineAction() {

}

void ShDrawXLineAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShDrawXLineAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShDrawXLineAction::getType() {

	return ActionType::ActionDrawContructionLine;
}

QString ShDrawXLineAction::getHeadTitle() {

	QString text;

	if (this->status == Status::PickedNothing)
		text = "XLine >> " + shGetLanValue_command("Command/Specify a point") + ": ";
	else
		text = "XLine >> " + shGetLanValue_command("Command/Specify through point") + ": ";

	return text;
}

ShAvailableDraft ShDrawXLineAction::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->status == Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else {

		ShConstructionLine *prevLine = dynamic_cast<ShConstructionLine*>((*this->widget->getPreview().begin()));
		
		draft.setAvailableOrthogonal(true);
		draft.setOrthogonalBasePoint(prevLine->getMid());
		draft.setAvailableSnap(true);
		draft.setSnapBasePoint(prevLine->getMid());
	}

	return draft;
}

void ShDrawXLineAction::invalidate(ShPoint3d &point) {

	if (this->status == Status::PickedMid) {
	
		ShConstructionLine *prevLine = dynamic_cast<ShConstructionLine*>((*this->widget->getPreview().begin()));
		
		ShLineData data;
		this->getData(prevLine->getMid(), point, data);
		prevLine->setData(data);

		this->widget->getRubberBand().setEnd(point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

void ShDrawXLineAction::trigger(const ShPoint3d &point) {

	if (this->status == Status::PickedNothing) {
	
		this->status = Status::PickedMid;

		ShLineData data;
		this->getData(point, point, data);
		this->widget->getPreview().add(new ShConstructionLine(this->widget->getPropertyData(), data, this->widget->getCurrentLayer()));
		this->widget->getRubberBand().create(ShLineData(point, point));

		this->setLastBasePoint(point);
		this->triggerSucceeded();
	}
	else if (this->status == Status::PickedMid) {
	
		ShConstructionLine *prevLine = dynamic_cast<ShConstructionLine*>((*this->widget->getPreview().begin()));

		if (math::compare(prevLine->getMid().x, point.x) == 0 &&
			math::compare(prevLine->getMid().y, point.y) == 0) {

			this->triggerFailed(ValueMustBeGreaterThanZero);
			return;
		}

		ShLineData data;
		this->getData(prevLine->getMid(), point, data);

		prevLine->setData(data);
		this->addEntity(prevLine->clone(), "XLine");

		this->triggerSucceeded();
	}
}

void ShDrawXLineAction::getData(const ShPoint3d &mid, const ShPoint3d &point, ShLineData &data) {

	double angle = math::getAbsAngle(mid.x, mid.y, point.x, point.y);
	math::rotate(angle, mid.x, mid.y, mid.x + 100, mid.y, data.start.x, data.start.y);
	math::rotate(angle + 180, mid.x, mid.y, mid.x + 100, mid.y, data.end.x, data.end.y);
}


#include "ShDrawDimAlignedAction.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Command\ShAvailableCommands.h"
#include "Base\ShMath.h"
#include "Entity\Composite\Dim\ShDimAligned.h"

ShDrawDimAlignedAction::ShDrawDimAlignedAction(ShCADWidget *widget)
	:ShDrawDimAction(widget), status(Status::PickedNothing) {

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

ShDrawDimAlignedAction::~ShDrawDimAlignedAction() {

}

void ShDrawDimAlignedAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShDrawDimAlignedAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShDrawDimAlignedAction::getType() {

	return ActionType::ActionDrawDimAligned;
}

QString ShDrawDimAlignedAction::getHeadTitle() {

	QString text;

	if (this->status == Status::PickedNothing)
		text = "DimAligned >> " + shGetLanValue_command("Command/Specify first extension line origin") + ": ";
	else if (this->status == Status::PickedFirst)
		text = "DimAligned >> " + shGetLanValue_command("Command/Specify second extension line origin") + ": ";
	else if (this->status == Status::PickedSecond)
		text = "DimAligned >> " + shGetLanValue_command("Command/Specify dimension line location") + ": ";

	return text;
}

ShAvailableDraft ShDrawDimAlignedAction::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->status == Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->status == Status::PickedFirst) {

		draft.setAvailableOrthogonal(true);
		draft.setOrthogonalBasePoint(this->first);
		draft.setAvailableSnap(true);
		draft.setSnapBasePoint(this->first);
	}
	else if (this->status == Status::PickedSecond) {

		draft.setAvailableSnap(true);
		draft.setSnapBasePoint(this->second);
	}

	return draft;
}

void ShDrawDimAlignedAction::invalidate(ShPoint3d &point) {

	if (this->status == Status::PickedFirst) {

		this->widget->getRubberBand().setEnd(point);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->status == Status::PickedSecond) {

		ShDimAlignedData data;
		this->getDimAlignedData(this->first, this->second, point, data);

		ShDimAligned *prevDimAligned = dynamic_cast<ShDimAligned*>(*this->widget->getPreview().begin());
		prevDimAligned->setData(data);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

void ShDrawDimAlignedAction::trigger(const ShPoint3d &point) {

	if (this->status == Status::PickedNothing) {

		this->status = Status::PickedFirst;
		this->first = point;

		this->widget->getRubberBand().setData(ShLineData(point, point));

		this->setLastBasePoint(point);
		this->triggerSucceeded();
	}
	else if (this->status == Status::PickedFirst) {

		this->status = Status::PickedSecond;
		this->second = point;

		this->widget->getRubberBand().clear();

		ShDimAlignedData data;
		this->getDimAlignedData(this->first, this->second, point, data);

		this->widget->getPreview().add(new ShDimAligned(data, this->widget->getPropertyData(), this->widget->getCurrentLayer(),
			this->widget->getCurrentDimensionStyle()));

		this->setLastBasePoint(point);
		this->triggerSucceeded();
	}
	else if (this->status == Status::PickedSecond) {

		ShDimAlignedData data;
		this->getDimAlignedData(this->first, this->second, point, data);

		ShDimAligned *prevDimAligned = dynamic_cast<ShDimAligned*>(*this->widget->getPreview().begin());
		prevDimAligned->setData(data);

		this->addEntity(prevDimAligned->clone(), "DimAligned");

		this->setLastBasePoint(point);
		this->actionFinished();
	}
}


void ShDrawDimAlignedAction::getDimAlignedData(const ShPoint3d &first, const ShPoint3d &second, const ShPoint3d &point, ShDimAlignedData &data) {

	data.firstOrigin = first;
	data.secondOrigin = second;
	data.firstDim = first;
	data.secondDim = second;

	double angle = math::getAbsAngle(first.x, first.y, second.x, second.y);

	ShPoint3d temp, temp2;
	math::rotate(angle + 90, first.x, first.y, first.x + 10, first.y, temp.x, temp.y);
	math::rotate(angle, point.x, point.y, point.x + 10, point.y, temp2.x, temp2.y);
	math::checkLineLineIntersect(first, temp, point, temp2, data.firstDim);

	math::rotate(angle + 90, second.x, second.y, second.x + 10, second.y, temp.x, temp.y);
	math::checkLineLineIntersect(second, temp, point, temp2, data.secondDim);

	double distance = math::getDistance(data.firstDim.x, data.firstDim.y, data.secondDim.x, data.secondDim.y);
	math::rotate(angle, data.firstDim.x, data.firstDim.y, data.firstDim.x + distance / 2.0, data.firstDim.y,
		data.text.x, data.text.y);
}
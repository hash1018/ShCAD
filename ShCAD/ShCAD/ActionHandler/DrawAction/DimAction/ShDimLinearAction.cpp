

#include "ShDimLinearAction.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Command\ShAvailableCommands.h"

ShDimLinearAction::ShDimLinearAction(ShCADWidget *widget)
	:ShDimAction(widget), status(Status::PickedNothing), direction(Direction::Nothing) {

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

ShDimLinearAction::~ShDimLinearAction() {

}

void ShDimLinearAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShDimLinearAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShDimLinearAction::getType() {

	return ActionType::ActionDrawDimLinear;
}

QString ShDimLinearAction::getHeadTitle() {

	QString text;

	if (this->status == Status::PickedNothing)
		text = "DimLinear >> " + shGetLanValue_command("Command/Specify first point") + ": ";
	else if(this->status == Status::PickedFirst)
		text = "DimLinear >> " + shGetLanValue_command("Command/Specify second point") + ": ";
	else if(this->status==Status::PickedSecond)
		text = "DimLinear >> " + shGetLanValue_command("Command/Specify third point") + ": ";

	return text;
}

ShAvailableDraft ShDimLinearAction::getAvailableDraft() {

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
	
		draft.setAvailableOrthogonal(true);
		draft.setOrthogonalBasePoint(this->second);
		draft.setAvailableSnap(true);
		draft.setSnapBasePoint(this->second);
	}

	return draft;
}

void ShDimLinearAction::invalidate(ShPoint3d &point) {

}

void ShDimLinearAction::trigger(const ShPoint3d &point) {

}
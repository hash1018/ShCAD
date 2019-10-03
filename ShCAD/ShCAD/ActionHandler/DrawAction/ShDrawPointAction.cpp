
#include "ShDrawPointAction.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Command\ShAvailableCommands.h"
#include "Entity\Leaf\ShPoint.h"

ShDrawPointAction::ShDrawPointAction(ShCADWidget *widget)
	:ShDrawAction(widget) {

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

ShDrawPointAction::~ShDrawPointAction() {

}

void ShDrawPointAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShDrawPointAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShDrawPointAction::getType() {

	return ActionType::ActionDrawPoint;
}

QString ShDrawPointAction::getHeadTitle() {

	QString text;

	text = "Point >> " + shGetLanValue_command("Command/Specify a point") + ": ";

	return text;
}

ShAvailableDraft ShDrawPointAction::getAvailableDraft() {

	ShAvailableDraft draft;

	draft.setAvailableSnap(true);
	ShPoint3d mouse = this->widget->getMousePoint();
	draft.setSnapBasePoint(mouse);

	return draft;
}

void ShDrawPointAction::invalidate(ShPoint3d &point) {

}

void ShDrawPointAction::trigger(const ShPoint3d &point) {

	ShPoint *newPoint = new ShPoint(point, this->widget->getPropertyData(), this->widget->getCurrentLayer());

	this->addEntity(newPoint, "Point");

	this->triggerSucceeded();
}


#include "ShDrawLineAction.h"
#include <QMouseEvent>
#include "Manager\ShLanguageManager.h"

ShDrawLineAction::ShDrawLineAction(ShCADWidget *widget)
	:ShDrawAction(widget), status(PickedNothing), drawMethod(Default) {


}

ShDrawLineAction::~ShDrawLineAction() {

}

void ShDrawLineAction::mouseLeftPressEvent(ShActionData &data) {

}

void ShDrawLineAction::mouseMoveEvent(ShActionData &data) {

}

void ShDrawLineAction::keyPressEvent(ShActionData &data) {


}

ActionType ShDrawLineAction::getType() {

	return ActionType::ActionDrawLine;
}

QString ShDrawLineAction::getHeadTitle() {

	QString text;

	if (this->status == Status::PickedNothing)
		text = "Line >> " + shGetLanValue_command("Command/Specify first point");
	else
		text = "Line >> " + shGetLanValue_command("Command/Specify next point");

	return text;
}
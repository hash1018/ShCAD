

#include "ShDrawLineAction.h"
#include <QMouseEvent>
#include "Manager\ShLanguageManager.h"
#include "KeyHandler\ShKeyHandler.h"
#include "KeyHandler\ShCustomKey.h"

ShDrawLineAction::ShDrawLineAction(ShCADWidget *widget)
	:ShDrawAction(widget), status(PickedNothing), drawMethod(Default) {

	//this->keyHandler = new ShKeyHandler<ShDrawLineAction>(this, &ShDrawLineAction::temp);

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowEnter().
		allowEsc().
		allowInput().
		allowCustom(new ShCustomKey<ShDrawLineAction>(Qt::Key::Key_I, Qt::KeyboardModifier::ControlModifier, this, &ShDrawLineAction::temp)).
		build();

}

ShDrawLineAction::~ShDrawLineAction() {

	
}

void ShDrawLineAction::mouseLeftPressEvent(ShActionData &data) {

}

void ShDrawLineAction::mouseMoveEvent(ShActionData &data) {

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

#include <qmessagebox.h>
void ShDrawLineAction::temp() {

	QMessageBox box;
	box.setText("Tem");
	box.exec();
}
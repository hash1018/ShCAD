

#include "ShDrawLineAction.h"
#include <QMouseEvent>
#include "Manager\ShLanguageManager.h"
#include "KeyHandler\ShKeyHandler.h"
#include "KeyHandler\ShCustomKey.h"

ShDrawLineAction::ShDrawLineAction(ShCADWidget *widget)
	:ShDrawAction(widget), status(PickedNothing), drawMethod(Default) {

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowKey(KeyType::Enter).
		allowKey(KeyType::Return).
		allowKey(KeyType::EscCancelCurrent).
		allowInput().
		allowCustom(new ShCustomKey<ShDrawLineAction>(Qt::Key::Key_I, Qt::KeyboardModifier::ControlModifier, this, &ShDrawLineAction::temp)).
		build();

}

ShDrawLineAction::~ShDrawLineAction() {

	
}

void ShDrawLineAction::mouseLeftPressEvent(ShActionData &data) {

	if (this->status == PickedNothing) {
	
		this->status = PickedStart;
		this->widget->getRubberBand().create(ShLineData(data.point, data.nextPoint));
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->status == PickedStart) {
	
	}

}

void ShDrawLineAction::mouseMoveEvent(ShActionData &data) {

	if (this->status == PickedStart) {
	
		this->widget->getRubberBand().setEnd(data.point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
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
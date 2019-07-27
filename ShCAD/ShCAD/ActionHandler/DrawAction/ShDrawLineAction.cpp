

#include "ShDrawLineAction.h"
#include <QMouseEvent>
#include "Manager\ShLanguageManager.h"
#include "KeyHandler\ShKeyHandler.h"
#include "KeyHandler\ShCustomKey.h"
#include "Event\ShNotifyEvent.h"

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

	this->takeNextStep(data.point, data.nextPoint);

}

void ShDrawLineAction::mouseMoveEvent(ShActionData &data) {

	if (this->status == PickedStart) {
	
		ShLine *prevLine = dynamic_cast<ShLine*>((*this->widget->getPreview().begin()));
		prevLine->setEnd(data.point);
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

void ShDrawLineAction::takeNextStep(const ShPoint3d &point, const ShPoint3d &nextPoint) {

	if (this->status == PickedNothing) {
	
		this->status = PickedStart;
		
		this->widget->getPreview().add(new ShLine(point, nextPoint));
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		ShUpdateTextToCommandListEvent notifyEvent("");
		this->widget->notify(&notifyEvent);

		this->updateCommandEditHeadTitle();
	}
	else if (this->status == PickedStart) {
	
		ShLine *preview = dynamic_cast<ShLine*>((*this->widget->getPreview().begin()));
		ShLineData data = preview->getData();
		data.end = point;

		preview->setData(data);

		this->addEntity(preview->clone(), "Line");

		data = ShLineData(point, nextPoint);
		preview->setData(data);

		ShUpdateTextToCommandListEvent notifyEvent("");
		this->widget->notify(&notifyEvent);

		this->updateCommandEditHeadTitle();

	}

}

#include <qmessagebox.h>
void ShDrawLineAction::temp() {

	QMessageBox box;
	box.setText("Tem");
	box.exec();
}
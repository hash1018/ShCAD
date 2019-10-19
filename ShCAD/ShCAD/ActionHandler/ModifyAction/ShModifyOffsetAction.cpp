
#include "ShModifyOffsetAction.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "Command\ShAvailableCommands.h"
#include "KeyHandler\ShKeyHandler.h"


ShModifyOffsetAction::ShModifyOffsetAction(ShCADWidget *widget)
	:ShModifyAction(widget) {

	this->status = Status::InputtingNumber;
	
	if (this->widget->getSelectedEntities()->getSize() != 0)
		this->widget->getSelectedEntities()->unSelectAll();

	this->keyHandler->disAllowKey(KeyType::Control_A);

	this->command = new ShOnlyNumberCommand<ShModifyOffsetAction>(this, &ShModifyOffsetAction::inputNumber);

	this->availableCommands = ShAvailableCommands::ShBuilder(this->widget, this).
		addAvailableCommand(this->command).
		build();

}

ShModifyOffsetAction::~ShModifyOffsetAction() {

}

void ShModifyOffsetAction::mouseLeftPressEvent(ShActionData &data) {

}

void ShModifyOffsetAction::mouseMoveEvent(ShActionData &data) {

}

ActionType ShModifyOffsetAction::getType() {

	return ActionType::ActionModifyOffset;
}

QString ShModifyOffsetAction::getHeadTitle() {

	return QString();
}

void ShModifyOffsetAction::finishSelectingEntities() {


}

void ShModifyOffsetAction::invalidate(ShPoint3d &point) {

}

void ShModifyOffsetAction::trigger(const ShPoint3d &point) {


}

#include <qmessagebox.h>
void ShModifyOffsetAction::inputNumber(void *number) {

	double num = *(double*)(number);

	QMessageBox box;
	box.setText(QString::number(num));
	box.exec();
}
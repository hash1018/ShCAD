
#include "ShActionHandler.h"
#include <qpainter.h>
#include "KeyHandler\ShKeyHandler.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "Manager\ShCommandLogManager.h"
#include "Command\ShAvailableCommands.h"

ShActionHandler::ShActionHandler(ShCADWidget *widget)
	:widget(widget), keyHandler(nullptr), availableCommands(nullptr) {

}

ShActionHandler::~ShActionHandler() {

	if (this->keyHandler != nullptr)
		delete this->keyHandler;

	if (this->availableCommands != nullptr)
		delete this->availableCommands;
}

void ShActionHandler::mouseLeftPressEvent(ShActionData &data) {

}

void ShActionHandler::mouseMidPressEvent(ShActionData &data) {

}

void ShActionHandler::mouseRightPressEvent(ShActionData &data) {

}

void ShActionHandler::mouseMoveEvent(ShActionData &data) {

}

void ShActionHandler::mouseReleaseEvent(ShActionData &data) {

}


void ShActionHandler::keyPressEvent(ShActionData &data) {

	if (this->keyHandler != nullptr)
		this->keyHandler->keyPressEvent(data.keyEvent);
}

void ShActionHandler::draw(QPainter *painter) {

}

ActionType ShActionHandler::getTypeIgnoringTemp() {

	return this->getType();
}

QCursor ShActionHandler::getCursorShape() {

	QPixmap pix(48, 48);
	pix.fill(Qt::transparent);
	QPainter painter(&pix);
	painter.setPen(QColor(255, 255, 255));

	painter.drawLine(24, 0, 24, 48);
	painter.drawLine(0, 24, 48, 24);

	painter.drawRect(21, 21, 6, 6);

	return QCursor(pix);
}

//*Template method pattern.
void ShActionHandler::updateCommandEditHeadTitle() {

	shCommandLogManager->replaceHeadTitle(this->getHeadTitle());
}

ShAvailableDraft ShActionHandler::getAvailableDraft() {

	return ShAvailableDraft();
}

void ShActionHandler::invalidate(ShPoint3d &point) {

}

void ShActionHandler::temporaryActionFinished() {


}

void ShActionHandler::interpret(const QString &command) {

	if (this->availableCommands != nullptr)
		this->availableCommands->interpret(command);
}

ShPoint3d ShActionHandler::getLastBasePoint() {

	return ShPoint3d();
}

void ShActionHandler::triggerSucceeded() {

	shCommandLogManager->appendListEditTextWith("");
	this->updateCommandEditHeadTitle();
}

void ShActionHandler::triggerFailed(ShActionTriggerFailureReason reason) {

	if (reason == ShActionTriggerFailureReason::ValueMustBeGreaterThanZero) {
	
		shCommandLogManager->appendListEditTextWith("");
		shCommandLogManager->appendList(shGetLanValue_command("Command/Value must be greater than zero") + ".");
		this->updateCommandEditHeadTitle();
	}
	else if (reason == ShActionTriggerFailureReason::InvalidPoint) {
	
		shCommandLogManager->appendListEditTextWith("");
		shCommandLogManager->appendList(shGetLanValue_command("Command/Invalid point") + ".");
		this->updateCommandEditHeadTitle();
	}
}

void ShActionHandler::trigger(const ShPoint3d &point) {

}

void ShActionHandler::actionCanceled() {

	ShChangeDefaultAfterCancelingCurrentStrategy strategy;
	this->widget->changeAction(strategy);
}

void ShActionHandler::actionFinished() {

	ShChangeDefaultAfterFinishingCurrentStrategy strategy;
	this->widget->changeAction(strategy);
}
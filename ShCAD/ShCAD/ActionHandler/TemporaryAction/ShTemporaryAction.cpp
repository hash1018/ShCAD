
#include "ShTemporaryAction.h"

ShTemporaryAction::ShTemporaryAction(ShCADWidget *widget, ShActionHandler *previousAction)
	:ShActionHandler(widget), previousAction(previousAction) {

}

ShTemporaryAction::~ShTemporaryAction() {

	if (this->previousAction != nullptr)
		delete this->previousAction;
}

void ShTemporaryAction::returnToPrevious() {

	this->widget->setCursor(this->previousAction->getCursorShape());
	this->widget->replaceAction(this->previousAction);
	this->previousAction = nullptr;
	delete this;
}
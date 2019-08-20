
#include "ShTemporaryAction.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"


ShTemporaryAction::ShTemporaryAction(ShCADWidget *widget)
	:ShActionHandler(widget), previousAction(nullptr) {

	
}

ShTemporaryAction::~ShTemporaryAction() {

	if (this->previousAction != nullptr)
		delete this->previousAction;
}

void ShTemporaryAction::setPreviousAction(ShActionHandler *previousAction) {

	this->previousAction = previousAction;
}


void ShTemporaryAction::returnToPrevious() {

	ShReturnToPreviousFromTemporaryStrategy strategy(this);
	this->widget->changeAction(strategy);
}

ActionType ShTemporaryAction::getTypeIgnoringTemp() {

	return this->previousAction->getTypeIgnoringTemp();
}
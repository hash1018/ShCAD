
#include "ShChangeActionStrategy.h"
#include <qdebug.h>
#include "ActionHandler\TemporaryAction\ShTemporaryAction.h"
#include "ActionHandler\ShActionHandlerProxy.h"

ShChangeActionStrategy::ShChangeActionStrategy()
	:widget(nullptr) {

}

ShChangeActionStrategy::~ShChangeActionStrategy() {

}

////////////////////////////////////////////////////////////


ShChangeActionAfterCancelingCurrentStrategy::ShChangeActionAfterCancelingCurrentStrategy(ActionType typeToChange)
{

}

ShChangeActionAfterCancelingCurrentStrategy::~ShChangeActionAfterCancelingCurrentStrategy() {

}

void ShChangeActionAfterCancelingCurrentStrategy::change() {

}

//////////////////////////////////////////////////////////////


ShChangeDefaultAfterFinishingCurrentStrategy::ShChangeDefaultAfterFinishingCurrentStrategy() {

}

ShChangeDefaultAfterFinishingCurrentStrategy::~ShChangeDefaultAfterFinishingCurrentStrategy() {

}

void ShChangeDefaultAfterFinishingCurrentStrategy::change() {

}

///////////////////////////////////////////////////////////////

ShChangeTemporaryStrategy::ShChangeTemporaryStrategy(ShTemporaryAction *temporaryAction, ShActionHandler *previousAction)
	:temporaryAction(temporaryAction), previousAction(previousAction) {

	
}

ShChangeTemporaryStrategy::~ShChangeTemporaryStrategy() {

}

void ShChangeTemporaryStrategy::change() {

	if (this->widget == nullptr)
		Q_ASSERT("ShChangeTemporaryStrategy::change() >> widget is null ptr");

	this->temporaryAction->setPreviousAction(this->previousAction);

	this->widget->getActionHandlerProxy()->setCurrentAction(temporaryAction);
	this->widget->setCursor(this->widget->getActionHandlerProxy()->getCursorShape());

}

/////////////////////////////////////////////////////////////////

ShReturnToPreviousFromTemporaryStrategy::ShReturnToPreviousFromTemporaryStrategy(ShTemporaryAction *temporaryAction)
	:temporaryAction(temporaryAction) {

}

ShReturnToPreviousFromTemporaryStrategy::~ShReturnToPreviousFromTemporaryStrategy() {


}

void ShReturnToPreviousFromTemporaryStrategy::change() {

	if(this->widget==nullptr)
		Q_ASSERT("ShChangeTemporaryStrategy::change() >> widget is null ptr");

	ShActionHandler *previous = this->temporaryAction->getPreviousAction();

	this->temporaryAction->setPreviousAction(nullptr);
	delete this->temporaryAction;

	this->widget->getActionHandlerProxy()->setCurrentAction(previous);
	this->widget->setCursor(this->widget->getActionHandlerProxy()->getCursorShape());
}
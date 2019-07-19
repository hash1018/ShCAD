
#include "ShChangeActionStrategy.h"
#include <qdebug.h>
#include "ActionHandler\TemporaryAction\ShTemporaryAction.h"
#include "ActionHandler\ShActionHandlerProxy.h"
#include "ActionHandler\Private\ShActionHandlerFactory.h"
#include "Event\ShNotifyEvent.h"
#include "Manager\ShLanguageManager.h"

ShChangeActionStrategy::ShChangeActionStrategy()
	:widget(nullptr) {

}

ShChangeActionStrategy::~ShChangeActionStrategy() {

}

////////////////////////////////////////////////////////////


ShChangeActionAfterCancelingCurrentStrategy::ShChangeActionAfterCancelingCurrentStrategy(ActionType typeToChange)
	:typeToChange(typeToChange) {

	
}

ShChangeActionAfterCancelingCurrentStrategy::~ShChangeActionAfterCancelingCurrentStrategy() {

}

void ShChangeActionAfterCancelingCurrentStrategy::change() {

	if (this->widget == nullptr)
		Q_ASSERT("ShChangeActionAfterCancelingCurrentStrategy::change() >> widget is null ptr");

	DrawType drawType = DrawType::DrawCaptureImage;

	if ((drawType & DrawType::DrawAll) == DrawType::DrawAll) {
		this->widget->update(DrawType::DrawAll);
		this->widget->captureImage();
	}
	else if ((drawType & DrawType::DrawCaptureImage) == DrawType::DrawCaptureImage)
		this->widget->update(DrawType::DrawCaptureImage);

	ShActionHandler *newAction = ShActionHandlerFactory::create(this->typeToChange, this->widget);

	if (this->widget->getActionHandlerProxy()->getCurrentAction() == nullptr)
		Q_ASSERT("ShChangeActionAfterCancelingCurrentStrategy::change() >> currentAction is null ptr");
		

	if (this->widget->getActionHandlerProxy()->getCurrentAction()->getType() != ActionType::ActionDefault) {
		ShUpdateTextToCommandListEvent notifyEvent(shGetLanValue_command("Command/<Cancel>"));
		this->widget->notify(&notifyEvent);
	}

	delete this->widget->getActionHandlerProxy()->getCurrentAction();

	this->widget->getActionHandlerProxy()->setCurrentAction(newAction);
	this->widget->setCursor(newAction->getCursorShape());
	shReplaceCommandHeadTitle(this->widget, newAction->getHeadTitle());

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

	this->widget->getActionHandlerProxy()->setCurrentAction(this->temporaryAction);
	this->widget->setCursor(this->temporaryAction->getCursorShape());
	shReplaceCommandHeadTitle(this->widget, this->temporaryAction->getHeadTitle());

}

/////////////////////////////////////////////////////////////////

ShReturnToPreviousFromTemporaryStrategy::ShReturnToPreviousFromTemporaryStrategy(ShTemporaryAction *temporaryAction)
	:temporaryAction(temporaryAction) {

}

ShReturnToPreviousFromTemporaryStrategy::~ShReturnToPreviousFromTemporaryStrategy() {


}

void ShReturnToPreviousFromTemporaryStrategy::change() {

	if(this->widget==nullptr)
		Q_ASSERT("ShReturnToPreviousFromTemporaryStrategy::change() >> widget is null ptr");

	ShActionHandler *previous = this->temporaryAction->getPreviousAction();

	this->temporaryAction->setPreviousAction(nullptr);
	delete this->temporaryAction;

	this->widget->getActionHandlerProxy()->setCurrentAction(previous);
	this->widget->setCursor(previous->getCursorShape());
	shReplaceCommandHeadTitle(this->widget, previous->getHeadTitle());
}

#include "ShCommandDockEventFilter.h"
#include "Interface\Dock\ShCommandDock.h"
#include "ShNotifyEvent.h"

ShCommandDockEventFilter::ShCommandDockEventFilter(ShCommandDock *commandDock, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::KeyPressed)
		this->strategy = new ShCommandDockKeyPressedEventFilterStrategy(commandDock, event);
	else if (event->getType() == ShNotifyEvent::UpdateTextToCommandList)
		this->strategy = new ShCommandDockUpdateTextToCommandListEventFilterStrategy(commandDock, event);

}

ShCommandDockEventFilter::~ShCommandDockEventFilter() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShCommandDockEventFilter::update() {

	if (this->strategy != nullptr)
		this->strategy->update();
}

///////////////////////////////////////////////////////////////

ShCommandDockEventFilterStrategy::ShCommandDockEventFilterStrategy(ShCommandDock *commandDock, ShNotifyEvent *event)
	:commandDock(commandDock), event(event) {

}

ShCommandDockEventFilterStrategy::~ShCommandDockEventFilterStrategy() {

}

/////////////////////////////////////////////////////////////////

ShCommandDockKeyPressedEventFilterStrategy::ShCommandDockKeyPressedEventFilterStrategy(ShCommandDock *commandDock, ShNotifyEvent *event)
	:ShCommandDockEventFilterStrategy(commandDock, event) {

}

ShCommandDockKeyPressedEventFilterStrategy::~ShCommandDockKeyPressedEventFilterStrategy() {

}

void ShCommandDockKeyPressedEventFilterStrategy::update() {

	this->commandDock->setCalledKeyPressedEventByNotify(true);
	this->commandDock->keyPressEvent(dynamic_cast<ShKeyPressedEvent*>(this->event)->getEvent());
	this->commandDock->setCalledKeyPressedEventByNotify(false);
}

///////////////////////////////////////////////////////////////////


ShCommandDockUpdateTextToCommandListEventFilterStrategy::ShCommandDockUpdateTextToCommandListEventFilterStrategy(ShCommandDock *commandDock, ShNotifyEvent *event)
	:ShCommandDockEventFilterStrategy(commandDock, event) {

}

ShCommandDockUpdateTextToCommandListEventFilterStrategy::~ShCommandDockUpdateTextToCommandListEventFilterStrategy() {

}

void ShCommandDockUpdateTextToCommandListEventFilterStrategy::update() {

	ShUpdateTextToCommandListEvent *event = dynamic_cast<ShUpdateTextToCommandListEvent*>(this->event);
	
	if (event->getUpdateType() == ShUpdateTextToCommandListEvent::UpdateType::EditTextWithText) {

		QString currentText = this->commandDock->getHeadTitle() + this->commandDock->getEditText() + event->getText();
		this->commandDock->appendTextToList(currentText);
		this->commandDock->clearEditText();

	}
	else if (event->getUpdateType() == ShUpdateTextToCommandListEvent::UpdateType::EditTextAndNewLineHeadTitleWithText) {

		QString currentText = this->commandDock->getHeadTitle() + this->commandDock->getEditText();
		this->commandDock->appendTextToList(currentText);
		this->commandDock->appendTextToList(this->commandDock->getHeadTitle() + event->getText());
		this->commandDock->clearEditText();
	}
	else if (event->getUpdateType() == ShUpdateTextToCommandListEvent::UpdateType::OnlyText) {

		this->commandDock->appendTextToList(event->getText());
	}

}
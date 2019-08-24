
#include "ShCommandDockEventFilter.h"
#include "Interface\Dock\ShCommandDock.h"
#include "ShNotifyEvent.h"
#include "Interface\ShCADWidget.h"

ShCommandDockEventFilter::ShCommandDockEventFilter(ShCommandDock *commandDock, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::KeyPressed)
		this->strategy = new ShCommandDockKeyPressedEventFilterStrategy(commandDock, event);
	else if (event->getType() == ShNotifyEvent::ActivatedWidgetChanged)
		this->strategy = new ShCommandDockActivatedWidgetChangedEventFilterStrategy(commandDock, event);

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

//////////////////////////////////////////////////////////////////////////////

ShCommandDockActivatedWidgetChangedEventFilterStrategy::ShCommandDockActivatedWidgetChangedEventFilterStrategy(ShCommandDock *commandDock, ShNotifyEvent *event)
	:ShCommandDockEventFilterStrategy(commandDock, event) {

}

ShCommandDockActivatedWidgetChangedEventFilterStrategy::~ShCommandDockActivatedWidgetChangedEventFilterStrategy() {

}


void ShCommandDockActivatedWidgetChangedEventFilterStrategy::update() {

	ShActivatedWidgetChangedEvent *event = dynamic_cast<ShActivatedWidgetChangedEvent*>(this->event);

	ShCADWidget *newWidget = event->getNewWidget();
	ShCADWidget *previousWidget = event->getPreviousWidget();

	if (previousWidget != nullptr) {
		previousWidget->getCommandLog().headTitle = this->commandDock->getHeadTitle();
		previousWidget->getCommandLog().edit = this->commandDock->getEditText();
		previousWidget->getCommandLog().list = this->commandDock->getListText();
	}

	this->commandDock->setHeadTitle(newWidget->getCommandLog().headTitle);
	this->commandDock->setEditText(newWidget->getCommandLog().edit);
	this->commandDock->setListText(newWidget->getCommandLog().list);

}

////////////////////////////////////////////////////////////////////////////////

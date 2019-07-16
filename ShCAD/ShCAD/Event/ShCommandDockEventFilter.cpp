
#include "ShCommandDockEventFilter.h"
#include "Interface\Dock\ShCommandDock.h"
#include "ShNotifyEvent.h"

ShCommandDockEventFilter::ShCommandDockEventFilter(ShCommandDock *commandDock, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::KeyPressed)
		this->strategy = new ShCommandDockKeyPressedEventFilterStrategy(commandDock, event);

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
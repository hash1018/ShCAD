
#include "ShCADWidgetEventFilter.h"
#include "Event\ShNotifyEvent.h"
#include "Interface\ShCADWidget.h"
#include "ActionHandler\ShActionHandlerProxy.h"

ShCADWidgetEventFilter::ShCADWidgetEventFilter(ShCADWidget *widget, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::KeyPressed)
		this->strategy = new ShCADWidgetKeyPressedEventFilterStrategy(widget, event);
}

ShCADWidgetEventFilter::~ShCADWidgetEventFilter() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShCADWidgetEventFilter::update() {

	if (this->strategy != nullptr)
		this->strategy->update();
}


////////////////////////////////////////////////////////////////////


ShCADWidgetEventFilterStrategy::ShCADWidgetEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event)
	:widget(widget), event(event) {

}

ShCADWidgetEventFilterStrategy::~ShCADWidgetEventFilterStrategy() {

}

////////////////////////////////////////////////////////////////////

ShCADWidgetKeyPressedEventFilterStrategy::ShCADWidgetKeyPressedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event)
	:ShCADWidgetEventFilterStrategy(widget, event) {

}

ShCADWidgetKeyPressedEventFilterStrategy::~ShCADWidgetKeyPressedEventFilterStrategy() {

}

void ShCADWidgetKeyPressedEventFilterStrategy::update() {

	ShKeyPressedEvent *event = dynamic_cast<ShKeyPressedEvent*>(this->event);

	this->widget->getActionHandlerProxy()->keyPressEvent(event->getEvent());
}
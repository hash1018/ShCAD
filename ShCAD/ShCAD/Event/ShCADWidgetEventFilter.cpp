
#include "ShCADWidgetEventFilter.h"
#include "Event\ShNotifyEvent.h"
#include "Interface\ShCADWidget.h"
#include "ActionHandler\ShActionHandlerProxy.h"
#include "UnRedo\ShCADWidgetTransaction.h"
#include "Base\ShGlobal.h"

ShCADWidgetEventFilter::ShCADWidgetEventFilter(ShCADWidget *widget, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::KeyPressed)
		this->strategy = new ShCADWidgetKeyPressedEventFilterStrategy(widget, event);
	else if (event->getType() == ShNotifyEvent::CurrentColorChanged)
		this->strategy = new ShCADWidgetCurrentColorChangedEventFilterStrategy(widget, event);
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

/////////////////////////////////////////////////////////////////////

ShCADWidgetCurrentColorChangedEventFilterStrategy::ShCADWidgetCurrentColorChangedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event)
	:ShCADWidgetEventFilterStrategy(widget, event) {

}

ShCADWidgetCurrentColorChangedEventFilterStrategy::~ShCADWidgetCurrentColorChangedEventFilterStrategy() {

}

void ShCADWidgetCurrentColorChangedEventFilterStrategy::update() {

	ShCurrentColorChangedEvent *event = dynamic_cast<ShCurrentColorChangedEvent*>(this->event);

	ShPropertyData prev = this->widget->getPropertyData();
	ShPropertyData current = prev;
	current.setColor(event->getColor());
	this->widget->setPropertyData(current);

	ShCurrentColorChangedEvent notifyEvent(event->getColor());
	this->widget->notify(&notifyEvent);

	ShChangeColorTransaction *transaction = new ShChangeColorTransaction(this->widget, prev.getColor(), event->getColor());
	ShGlobal::pushNewTransaction(this->widget, transaction);
	
}
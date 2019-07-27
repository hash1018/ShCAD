
#include "ShStatusBarEventFilter.h"
#include "ShNotifyEvent.h"
#include "Interface\StatusBar\ShStatusBar.h"

ShStatusBarEventFilter::ShStatusBarEventFilter(ShStatusBar *statusBar, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::MousePositionChanged)
		this->strategy = new ShStatusBarMousePositionChangedEventFilterStrategy(statusBar, event);
	else if (event->getType() == ShNotifyEvent::ZoomRateChanged)
		this->strategy = new ShStatusBarZoomRateChangedEventFilterStrategy(statusBar, event);
	else if (event->getType() == ShNotifyEvent::ActivatedWidgetChanged)
		this->strategy = new ShStatusBarActivatedWidgetChangedEventFilterStrategy(statusBar, event);

}

ShStatusBarEventFilter::~ShStatusBarEventFilter() {

}

void ShStatusBarEventFilter::update() {

	if (this->strategy != nullptr)
		this->strategy->update();

}

//////////////////////////////////////////////////////////


ShStatusBarEventFilterStrategy::ShStatusBarEventFilterStrategy(ShStatusBar *statusBar, ShNotifyEvent *event)
	:statusBar(statusBar), event(event) {

}

ShStatusBarEventFilterStrategy::~ShStatusBarEventFilterStrategy() {

}

//////////////////////////////////////////////////////////

ShStatusBarMousePositionChangedEventFilterStrategy::ShStatusBarMousePositionChangedEventFilterStrategy(ShStatusBar *statusBar, ShNotifyEvent *event)
	:ShStatusBarEventFilterStrategy(statusBar, event) {

}

ShStatusBarMousePositionChangedEventFilterStrategy::~ShStatusBarMousePositionChangedEventFilterStrategy() {

}

void ShStatusBarMousePositionChangedEventFilterStrategy::update() {

	this->statusBar->setPoint(dynamic_cast<ShMousePositionChangedEvent*>(this->event)->getPoint());
	this->statusBar->updateCoordiLabel();
}

///////////////////////////////////////////////////////////////


ShStatusBarZoomRateChangedEventFilterStrategy::ShStatusBarZoomRateChangedEventFilterStrategy(ShStatusBar *statusBar, ShNotifyEvent *event)
	:ShStatusBarEventFilterStrategy(statusBar, event) {

}

ShStatusBarZoomRateChangedEventFilterStrategy::~ShStatusBarZoomRateChangedEventFilterStrategy() {

}

void ShStatusBarZoomRateChangedEventFilterStrategy::update() {

	this->statusBar->setZoomRate(dynamic_cast<ShZoomRateChangedEvent*>(this->event)->getZoomRate());
	this->statusBar->updateCoordiLabel();
}

////////////////////////////////////////////////////////////////


ShStatusBarActivatedWidgetChangedEventFilterStrategy::ShStatusBarActivatedWidgetChangedEventFilterStrategy(ShStatusBar *statusBar, ShNotifyEvent *event)
	:ShStatusBarEventFilterStrategy(statusBar, event) {

}

ShStatusBarActivatedWidgetChangedEventFilterStrategy::~ShStatusBarActivatedWidgetChangedEventFilterStrategy() {

}

void ShStatusBarActivatedWidgetChangedEventFilterStrategy::update() {


}

#include "ShNotifyEvent.h"

ShNotifyEvent::ShNotifyEvent(Type type)
	:type(type) {

}

ShNotifyEvent::~ShNotifyEvent() {

}

////////////////////////////////////////////

ShZoomRateChangedEvent::ShZoomRateChangedEvent()
	:ShNotifyEvent(Type::ZoomRateChanged) {

}

ShZoomRateChangedEvent::~ShZoomRateChangedEvent() {


}

////////////////////////////////////////////

ShMousePositionChangedEvent::ShMousePositionChangedEvent()
	:ShNotifyEvent(Type::MousePositionChanged) {

}

ShMousePositionChangedEvent::~ShMousePositionChangedEvent() {


}

/////////////////////////////////////////////////////////////////////

ShKeyPressedEvent::ShKeyPressedEvent(QKeyEvent *event)
	:ShNotifyEvent(Type::KeyPressed), event(event) {


}

ShKeyPressedEvent::~ShKeyPressedEvent() {

}

///////////////////////////////////////////////////////////////////////

ShActivatedWidgetChangedEvent::ShActivatedWidgetChangedEvent(ShCADWidget *newWidget, ShCADWidget *previousWidget)
	:ShNotifyEvent(Type::ActivatedWidgetChanged), newWidget(newWidget), previousWidget(previousWidget) {

}

ShActivatedWidgetChangedEvent::~ShActivatedWidgetChangedEvent() {

}

#include "ShNotifyEvent.h"

ShNotifyEvent::ShNotifyEvent(Type type)
	:type(type) {

}

ShNotifyEvent::~ShNotifyEvent() {

}

////////////////////////////////////////////

ShZoomRateChangedEvent::ShZoomRateChangedEvent(const double &zoomRate)
	:ShNotifyEvent(Type::ZoomRateChanged), zoomRate(zoomRate) {

}

ShZoomRateChangedEvent::~ShZoomRateChangedEvent() {


}

////////////////////////////////////////////

ShMousePositionChangedEvent::ShMousePositionChangedEvent(const ShPoint3d &point)
	:ShNotifyEvent(Type::MousePositionChanged), point(point) {

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

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


///////////////////////////////////////////////////////////////////////

ShCurrentColorChangedEvent::ShCurrentColorChangedEvent(const ShColor &color)
	:ShNotifyEvent(Type::CurrentColorChanged), color(color) {

}

ShCurrentColorChangedEvent::~ShCurrentColorChangedEvent() {

}

////////////////////////////////////////////////////////////////////////

ShCurrentLineStyleChangedEvent::ShCurrentLineStyleChangedEvent(const ShLineStyle &lineStyle)
	:ShNotifyEvent(Type::CurrentLineStyleChanged), lineStyle(lineStyle) {

}

ShCurrentLineStyleChangedEvent::~ShCurrentLineStyleChangedEvent() {

}

////////////////////////////////////////////////////////////////////////

ShTransactionStackSizeChangedEvent::ShTransactionStackSizeChangedEvent(const int &undoSize, const int &redoSize)
	:ShNotifyEvent(Type::TransactionStackSizeChanged), undoSize(undoSize), redoSize(redoSize) {

}

ShTransactionStackSizeChangedEvent::~ShTransactionStackSizeChangedEvent() {

}

////////////////////////////////////////////////////////////////////////

ShCurrentLayerChangedEvent::ShCurrentLayerChangedEvent(ShLayer *currentLayer)
	:ShNotifyEvent(Type::CurrentLayerChanged), currentLayer(currentLayer) {

}

ShCurrentLayerChangedEvent::~ShCurrentLayerChangedEvent() {

}

////////////////////////////////////////////////////////////////////////

ShLayerDataChangedEvent::ShLayerDataChangedEvent(ShLayer *layer, const ShColor &color, bool current)
	:ShNotifyEvent(Type::LayerDataChanged), layer(layer), current(current), color(&color), lineStyle(nullptr), name(nullptr),
	turn(false), changedType(ChangedType::Color) {

}

ShLayerDataChangedEvent::ShLayerDataChangedEvent(ShLayer *layer, const ShLineStyle &lineStyle, bool current)
	: ShNotifyEvent(Type::LayerDataChanged), layer(layer), current(current), color(nullptr), lineStyle(&lineStyle), name(nullptr),
	turn(false), changedType(ChangedType::LineStyle) {

}

ShLayerDataChangedEvent::ShLayerDataChangedEvent(ShLayer *layer, const QString &name, bool current)
	: ShNotifyEvent(Type::LayerDataChanged), layer(layer), current(current), color(nullptr), lineStyle(nullptr), name(&name),
	turn(false), changedType(ChangedType::Name) {

}

ShLayerDataChangedEvent::ShLayerDataChangedEvent(ShLayer *layer, bool turn, bool current)
	: ShNotifyEvent(Type::LayerDataChanged), layer(layer), current(current), color(nullptr), lineStyle(nullptr), name(nullptr),
	turn(turn), changedType(ChangedType::Turn) {

}

ShLayerDataChangedEvent::~ShLayerDataChangedEvent() {

}

/////////////////////////////////////////////////////////////////////////

ShLayerCreatedEvent::ShLayerCreatedEvent(ShLayer *createdLayer)
	:ShNotifyEvent(Type::LayerCreated), createdLayer(createdLayer) {

}

ShLayerCreatedEvent::~ShLayerCreatedEvent() {

}

/////////////////////////////////////////////////////////////////////////

ShLayerDeletedEvent::ShLayerDeletedEvent(ShLayer *deletedLayer)
	:ShNotifyEvent(Type::LayerDeleted), deletedLayer(deletedLayer) {

}

ShLayerDeletedEvent::~ShLayerDeletedEvent() {

}

//////////////////////////////////////////////////////////////////////////

ShActionChangedEvent::ShActionChangedEvent(ActionType newType)
	:ShNotifyEvent(Type::ActionChanged), newType(newType) {

}

ShActionChangedEvent::~ShActionChangedEvent() {

}

//////////////////////////////////////////////////////////////////////////


ShSelectedEntityCountChangedEvent::ShSelectedEntityCountChangedEvent(ShCADWidget *widget, const QLinkedList<ShEntity*> &selectedList)
	:ShNotifyEvent(Type::SelectedEntityCountChanged), widget(widget), selectedList(selectedList) {

}

ShSelectedEntityCountChangedEvent::~ShSelectedEntityCountChangedEvent() {

}


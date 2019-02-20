
/*--
**
**   This file is part of the ShCAD project, a 2D CAD Program
**
**    Copyright (C) 2019, Seungho Ha  (sh.ha1018@gmail.com)
**
**
**   This program is free software; you can redistribute it and/or modify it
**   under the terms of the GNU Lesser General Public License as published by
**   the Free Software Foundation; either version 2.1 of the License, or (at
**   your option) any later version.
**
**   This program is distributed in the hope that it will be useful, but
**   WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
**   General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
**
**
--*/

#include "ShNotifyEvent.h"


ShNotifyEvent::ShNotifyEvent(Type type)
	:type(type) {

}

ShNotifyEvent::~ShNotifyEvent() {

}

/////////////////////////////////////////////////////////////

ShZoomRateChangedEvent::ShZoomRateChangedEvent(double x, double y, double z, double zoomRate)
	:ShNotifyEvent(Type::ZoomRateChanged), x(x), y(y), z(z), zoomRate(zoomRate) {


}

ShZoomRateChangedEvent::~ShZoomRateChangedEvent() {

}

////////////////////////////////////////////////////////////////

ShMousePositionChangedEvent::ShMousePositionChangedEvent(double x, double y, double z, double zoomRate)
	:ShNotifyEvent(Type::MousePositionChanged), x(x), y(y), z(z), zoomRate(zoomRate) {


}

ShMousePositionChangedEvent::~ShMousePositionChangedEvent() {

}

/////////////////////////////////////////////////////////////////

ShKeyPressedEvent::ShKeyPressedEvent(QKeyEvent *event)
	:ShNotifyEvent(Type::KeyPressed), event(event) {

	
}

ShKeyPressedEvent::~ShKeyPressedEvent() {

}

///////////////////////////////////////////////////////////////////


ShUpdateListTextEvent::ShUpdateListTextEvent(const QString& text, ShUpdateListTextEvent::UpdateType type)
	:ShNotifyEvent(Type::UpdateListText), text(text), updateType(type) {


}

ShUpdateListTextEvent::~ShUpdateListTextEvent() {

}


/////////////////////////////////////////////////////////////////


ShActivatedWidgetChangedEvent::ShActivatedWidgetChangedEvent(ShGraphicView *newWidget, ShGraphicView *previousWidget)
	:ShNotifyEvent(Type::ActivatedWidgetChanged), newWidget(newWidget), previousWidget(previousWidget) {


}

ShActivatedWidgetChangedEvent::~ShActivatedWidgetChangedEvent() {

}

/////////////////////////////////////////////////////////////////////////////////

ShPropertyColorComboSelChangedEvent::ShPropertyColorComboSelChangedEvent(const ShColor& color)
	:ShNotifyEvent(Type::PropertyColorComboSelChanged), color(color) {


}

ShPropertyColorComboSelChangedEvent::~ShPropertyColorComboSelChangedEvent() {


}

//////////////////////////////////////////////////////////////////////////////////

ShPropertyLineStyleComboSelChangedEvent::ShPropertyLineStyleComboSelChangedEvent(const ShLineStyle& lineStyle)
	:ShNotifyEvent(Type::PropertyLineStyleComboSelChanged), lineStyle(lineStyle) {

}

ShPropertyLineStyleComboSelChangedEvent::~ShPropertyLineStyleComboSelChangedEvent() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

ShLayerComboSelChangedEvent::ShLayerComboSelChangedEvent(int index)
	:index(index), ShNotifyEvent(ShNotifyEvent::Type::LayerComboSelChanged) {

}

ShLayerComboSelChangedEvent::~ShLayerComboSelChangedEvent() {


}

////////////////////////////////////////////////////////////////////////////////////////////////////////

ShCurrentLayerChangedEvent::ShCurrentLayerChangedEvent(ShLayer *previousLayer, ShLayer *currentLayer)
	:ShNotifyEvent(Type::CurrentLayerChanged), previousLayer(previousLayer), currentLayer(currentLayer) {


}

ShCurrentLayerChangedEvent::~ShCurrentLayerChangedEvent() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

ShLayerDataChangedEvent::ShLayerDataChangedEvent(ShLayer *changedLayer, const ShLayerData& previousData,
	ShLayerDataChangedEvent::ChangedType changedType)
	:ShNotifyEvent(Type::LayerDataChanged), changedLayer(changedLayer), changedType(changedType), currentLayer(0),
	previousData(previousData) {


}

ShLayerDataChangedEvent::~ShLayerDataChangedEvent() {

}


////////////////////////////////////////////////////////////////////////////////////

ShLayerCreatedEvent::ShLayerCreatedEvent(ShLayer *newLayer)
	:ShNotifyEvent(Type::LayerCreated), newLayer(newLayer) {


}

ShLayerCreatedEvent::~ShLayerCreatedEvent() {


}

//////////////////////////////////////////////////////////////////////////////////

ShLayerDeletedEvent::ShLayerDeletedEvent(ShLayer *deletedLayer)
	:ShNotifyEvent(Type::LayerDeleted), deletedLayer(deletedLayer) {

}

ShLayerDeletedEvent::~ShLayerDeletedEvent() {

}

////////////////////////////////////////////////////////////////////////////////////


ShCurrentActionChangedEvent::ShCurrentActionChangedEvent(ActionType type)
	:ShNotifyEvent(Type::CurrentActionChanged), type(type) {

}

ShCurrentActionChangedEvent::~ShCurrentActionChangedEvent() {


}

//////////////////////////////////////////////////////////////////////////////////

ShSelectedEntityCountChangedEvent::ShSelectedEntityCountChangedEvent(ShGraphicView *view, const ShPropertyData& data,
	const ShPropertyData& layerData, const ShPropertyData& blockData, ShLayer *layer,
	bool isAllSameColor, bool isAllSameLineStyle, bool isAllSameLayer, int count)
	:view(view), data(data), layerData(layerData), blockData(blockData), layer(layer),
	isAllSameColor(isAllSameColor), isAllSameLineStyle(isAllSameLineStyle), isAllSameLayer(isAllSameLayer),
	count(count), ShNotifyEvent(ShNotifyEvent::Type::SelectedEntityCountChanged) {


}

ShSelectedEntityCountChangedEvent::~ShSelectedEntityCountChangedEvent() {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////

ShUpdateCommandEditHeadTitle::ShUpdateCommandEditHeadTitle(const QString& headTitle, UpdateType updateType)
	:headTitle(headTitle), updateType(updateType), ShNotifyEvent(ShNotifyEvent::Type::UpdateCommandEditHeadTitle) {

}

ShUpdateCommandEditHeadTitle::~ShUpdateCommandEditHeadTitle() {

}
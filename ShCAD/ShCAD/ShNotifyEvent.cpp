
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


ShNotifyEvent::ShNotifyEvent()
	:type(Type::Nothing) {

}

ShNotifyEvent::~ShNotifyEvent() {

}

/////////////////////////////////////////////////////////////

ShZoomRateChangedEvent::ShZoomRateChangedEvent(double x, double y, double z, double zoomRate)
	:x(x), y(y), z(z), zoomRate(zoomRate) {

	this->type = Type::ZoomRateChanged;
}

ShZoomRateChangedEvent::~ShZoomRateChangedEvent() {

}

////////////////////////////////////////////////////////////////

ShMousePositionChangedEvent::ShMousePositionChangedEvent(double x, double y, double z, double zoomRate)
	:x(x), y(y), z(z), zoomRate(zoomRate) {

	this->type = Type::MousePositionChanged;
}

ShMousePositionChangedEvent::~ShMousePositionChangedEvent() {

}

/////////////////////////////////////////////////////////////////

ShKeyPressedEvent::ShKeyPressedEvent(QKeyEvent *event)
	:event(event) {

	this->type = Type::KeyPressed;
}

ShKeyPressedEvent::~ShKeyPressedEvent() {

}

///////////////////////////////////////////////////////////////////


ShUpdateListTextEvent::ShUpdateListTextEvent(const QString& text, ShUpdateListTextEvent::UpdateType type)
	:text(text),updateType(type) {

	this->type = Type::UpdateListText;
}

ShUpdateListTextEvent::~ShUpdateListTextEvent() {

}


/////////////////////////////////////////////////////////////////


ShActivatedWidgetChangedEvent::ShActivatedWidgetChangedEvent(ShGraphicView *newWidget, ShGraphicView *previousWidget)
	:newWidget(newWidget), previousWidget(previousWidget) {

	this->type = Type::ActivatedWidgetChanged;
}

ShActivatedWidgetChangedEvent::~ShActivatedWidgetChangedEvent() {

}

/////////////////////////////////////////////////////////////////////////////////

ShPropertyColorComboSelChangedEvent::ShPropertyColorComboSelChangedEvent(const ShColor& color)
	:color(color) {

	this->type = Type::PropertyColorComboSelChanged;
}

ShPropertyColorComboSelChangedEvent::~ShPropertyColorComboSelChangedEvent() {


}
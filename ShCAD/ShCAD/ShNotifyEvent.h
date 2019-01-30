
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

#ifndef _SHNOTIFYEVENT_H
#define _SHNOTIFYEVENT_H

class ShNotifyEvent {

public:
	enum Type {
		Nothing = 0,
		ZoomRateChanged = 1,
		MousePositionChanged = 2,
		KeyPressed = 3,
		UpdateListText = 4,
		ActivatedWidgetChanged = 5,
		PropertyColorComboSelChanged = 6,
		PropertyLineStyleComboSelChanged = 7,
		CurrentLayerChanged = 8,
		LayerDataChanged = 9,
		LayerCreated = 10,
		LayerDeleted = 11,
	
	};

public:
	ShNotifyEvent(Type type);
	virtual ~ShNotifyEvent() = 0;

	inline Type GetType() const { return this->type; }

protected:
	Type type;
};

class ShZoomRateChangedEvent : public ShNotifyEvent {
	
public:
	ShZoomRateChangedEvent(double x, double y, double z, double zoomRate);
	~ShZoomRateChangedEvent();

	inline double GetX() const { return this->x; }
	inline double GetY() const { return this->y; }
	inline double GetZ() const { return this->z; }
	inline double GetZoomRate() const { return this->zoomRate; }

protected:
	double x;
	double y;
	double z;
	double zoomRate;
};

class ShMousePositionChangedEvent : public ShNotifyEvent {

public:
	ShMousePositionChangedEvent(double x, double y, double z, double zoomRate);
	~ShMousePositionChangedEvent();

	inline double GetX() const { return this->x; }
	inline double GetY() const { return this->y; }
	inline double GetZ() const { return this->z; }
	inline double GetZoomRate() const { return this->zoomRate; }

protected:
	double x;
	double y;
	double z;
	double zoomRate;

};

class QKeyEvent;
class ShKeyPressedEvent : public ShNotifyEvent {

public:
	ShKeyPressedEvent(QKeyEvent *event);
	~ShKeyPressedEvent();

	inline QKeyEvent* GetEvent() const { return this->event; }

protected:
	QKeyEvent *event;
};

#include <qstring.h>
class ShUpdateListTextEvent : public ShNotifyEvent {
public:
	enum UpdateType {
		editTextWithText=1,
		editTextAndNewLineHeadTitleWithText=2,
		TextWithoutAnything=3,
		
	};

public:
	ShUpdateListTextEvent(const QString& text, ShUpdateListTextEvent::UpdateType type = UpdateType::editTextWithText);
	~ShUpdateListTextEvent();

	inline const QString& GetText() const { return this->text; }
	inline UpdateType GetUpdateType() const { return this->updateType; }

private:
	QString text;
	UpdateType updateType;


};

class ShGraphicView;
class ShActivatedWidgetChangedEvent : public ShNotifyEvent {

public:
	ShActivatedWidgetChangedEvent(ShGraphicView *newWidget, ShGraphicView *previousWidget);
	~ShActivatedWidgetChangedEvent();

	inline ShGraphicView* GetNewWidget() const { return this->newWidget; }
	inline ShGraphicView* GetPreviousWidget() const { return this->previousWidget; }

private:
	ShGraphicView *newWidget;
	ShGraphicView *previousWidget;
};

#include "ShPropertyData.h"
class ShPropertyColorComboSelChangedEvent : public ShNotifyEvent {

public:
	ShPropertyColorComboSelChangedEvent(const ShColor& color);
	~ShPropertyColorComboSelChangedEvent();

	inline ShColor GetColor() const { return this->color; }

private:
	ShColor color;

};

class ShPropertyLineStyleComboSelChangedEvent : public ShNotifyEvent {

public:
	ShPropertyLineStyleComboSelChangedEvent(const ShLineStyle& lineStyle);
	~ShPropertyLineStyleComboSelChangedEvent();

	inline ShLineStyle GetLineStyle() const { return this->lineStyle; }

private:
	ShLineStyle lineStyle;

};
class ShLayer;
class ShCurrentLayerChangedEvent : public ShNotifyEvent {

public:
	ShCurrentLayerChangedEvent(ShLayer *previousLayer, ShLayer *currentLayer);
	~ShCurrentLayerChangedEvent();

	inline ShLayer* GetPreviousLayer() const { return this->previousLayer; }
	inline ShLayer* GetCurrentLayer() const { return this->currentLayer; }

private:
	ShLayer *previousLayer;
	ShLayer *currentLayer;
};

class ShLayerMemento;
class ShLayerDataChangedEvent : public ShNotifyEvent {

public:
	enum ChangedType {
		State = 0,
		Name = 1,
		TurnOnOff = 2,
		Color = 3,
		LineStyle = 4
	};

public:
	ShLayerDataChangedEvent(ShLayer *changedLayer, ShLayerMemento *previousMemento,
		ShLayerDataChangedEvent::ChangedType changedType);

	~ShLayerDataChangedEvent();

	inline ShLayer* GetChangedLayer() const { return this->changedLayer; }
	inline ChangedType GetChangedType() const { return this->changedType; }
	void SetCurrentLayer(ShLayer *currentLayer) { this->currentLayer = currentLayer; }
	inline ShLayer* GetCurrentLayer() const { return this->currentLayer; }
	inline ShLayerMemento* GetPreviousMemento() const { return this->previousMemento; }

private:
	ShLayer *changedLayer;
	ChangedType changedType;
	ShLayer *currentLayer;
	ShLayerMemento *previousMemento;
};

class ShLayerCreatedEvent : public ShNotifyEvent {

public:
	ShLayerCreatedEvent(ShLayer *newLayer);
	~ShLayerCreatedEvent();

	inline ShLayer* GetNewLayer() const { return this->newLayer; }

private:
	ShLayer *newLayer;

};

class ShLayerDeletedEvent : public ShNotifyEvent {

public:
	ShLayerDeletedEvent(ShLayer *deletedLayer);
	~ShLayerDeletedEvent();

	inline ShLayer* GetDeletedLayer() const { return this->deletedLayer; }

private:
	ShLayer *deletedLayer;
};


#endif //_SHNOTIFYEVENT_H
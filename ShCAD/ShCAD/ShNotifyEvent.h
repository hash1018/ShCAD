
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
		NotifyNothing = 0,
		NotifyZoomRateChanged = 1,
		NotifyMousePositionChanged = 2,
		NotifyKeyPressed = 3,
		
		


	};

public:
	ShNotifyEvent();
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


#endif //_SHNOTIFYEVENT_H
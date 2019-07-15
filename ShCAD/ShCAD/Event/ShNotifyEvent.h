
#ifndef _SHNOTIFYEVENT_H
#define _SHNOTIFYEVENT_H

#include "Data\ShPoint.h"

class QKeyEvent;
class ShCADWidget;

class ShNotifyEvent {

public:
	enum Type {
		Nothing,
		ZoomRateChanged,
		MousePositionChanged,
		KeyPressed,
		ActivatedWidgetChanged,
	};

	ShNotifyEvent(Type type);
	virtual ~ShNotifyEvent() = 0;

	inline Type getType() const { return this->type; }

protected:
	Type type;

};

/////////////////////////////////////////////////////////////////////

class ShZoomRateChangedEvent : public ShNotifyEvent {

public:
	ShZoomRateChangedEvent(const double &zoomRate);
	~ShZoomRateChangedEvent();

	inline double getZoomRate() const { return this->zoomRate; }

private:
	double zoomRate;
};

//////////////////////////////////////////////////////////////////////

class ShMousePositionChangedEvent : public ShNotifyEvent {

public:
	ShMousePositionChangedEvent(const ShPoint3d &point);
	~ShMousePositionChangedEvent();

	inline ShPoint3d getPoint() const { return this->point; }
private:
	ShPoint3d point;
};

///////////////////////////////////////////////////////////////////////


class ShKeyPressedEvent : public ShNotifyEvent {

public:
	ShKeyPressedEvent(QKeyEvent *event);
	~ShKeyPressedEvent();

	inline QKeyEvent* getEvent() const { return this->event; }

protected:
	QKeyEvent *event;
};


//////////////////////////////////////////////////////////////////////

class ShActivatedWidgetChangedEvent : public ShNotifyEvent {

public:
	ShActivatedWidgetChangedEvent(ShCADWidget *newWidget, ShCADWidget *previousWidget);
	~ShActivatedWidgetChangedEvent();

	inline ShCADWidget* GetNewView() const { return this->newWidget; }
	inline ShCADWidget* GetPreviousView() const { return this->previousWidget; }

private:
	ShCADWidget *newWidget;
	ShCADWidget *previousWidget;
};

#endif //_NOTIFYEVENT_H
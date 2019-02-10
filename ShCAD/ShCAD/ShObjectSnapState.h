

#ifndef _SHOBJECTSNAPSTATE_H
#define _SHOBJECTSNAPSTATE_H

#include "ShVariable.h"

class QMouseEvent;
class ShGraphicView;
class QPainter;
class ShObjectSnapState {

protected:
	ShGraphicView *view;
	double snapX;
	double snapY;
	bool isValid;

public:
	ShObjectSnapState(ShGraphicView *view);
	virtual ~ShObjectSnapState() = 0;

	virtual void MousePressEvent(QMouseEvent *event) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event, DrawType &drawType) = 0;

	virtual ObjectSnap GetType() = 0;
	virtual void Draw(QPainter *painter) = 0;
};


class ShObjectSnapState_Nothing : public ShObjectSnapState {

public:
	ShObjectSnapState_Nothing(ShGraphicView *view);
	~ShObjectSnapState_Nothing();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event, DrawType &drawType);

	virtual ObjectSnap GetType() { return ObjectSnap::ObjectSnapNothing; }
	virtual void Draw(QPainter *painter) {}
};

class ShObjectSnapState_EndPoint : public ShObjectSnapState {

public:
	ShObjectSnapState_EndPoint(ShGraphicView *view);
	~ShObjectSnapState_EndPoint();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event, DrawType &drawType);

	virtual ObjectSnap GetType() { return ObjectSnap::ObjectSnapEndPoint; }
	virtual void Draw(QPainter *painter);
};

class ShObjectSnapState_MidPoint : public ShObjectSnapState {

public:
	ShObjectSnapState_MidPoint(ShGraphicView *view);
	~ShObjectSnapState_MidPoint();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event, DrawType &drawType);

	virtual ObjectSnap GetType() { return ObjectSnap::ObjectSnapMidPoint; }
	virtual void Draw(QPainter *painter);

};

#endif //_SHOBJECTSNAPSTATE_H


#ifndef _SHOBJECTSNAPSTATE_H
#define _SHOBJECTSNAPSTATE_H

#include "ShVariable.h"

class QMouseEvent;
class ShGraphicView;
class QPainter;
class ShEntity;
class ShObjectSnapState {

protected:
	ShGraphicView *view;
	double snapX;
	double snapY;
	bool isValid;

public:
	ShObjectSnapState(ShGraphicView *view);
	virtual ~ShObjectSnapState() = 0;

	virtual bool FindSnapPoint(QMouseEvent *event) = 0;

	virtual ObjectSnap GetType() = 0;
	virtual void Draw(QPainter *painter) = 0;

	inline double GetSnapX() const { return this->snapX; }
	inline double GetSnapY() const { return this->snapY; }
};

class ShObjectSnapState_Nothing : public ShObjectSnapState {

public:
	ShObjectSnapState_Nothing(ShGraphicView *view);
	~ShObjectSnapState_Nothing();

	virtual bool FindSnapPoint(QMouseEvent *event);

	virtual ObjectSnap GetType() { return ObjectSnap::ObjectSnapNothing; }
	virtual void Draw(QPainter *painter) {}
};


class ShObjectSnapState_EndPoint : public ShObjectSnapState {

public:
	ShObjectSnapState_EndPoint(ShGraphicView *view);
	~ShObjectSnapState_EndPoint();

	virtual bool FindSnapPoint(QMouseEvent *event);

	virtual ObjectSnap GetType() { return ObjectSnap::ObjectSnapEndPoint; }
	virtual void Draw(QPainter *painter);
};

class ShObjectSnapState_MidPoint : public ShObjectSnapState {

public:
	ShObjectSnapState_MidPoint(ShGraphicView *view);
	~ShObjectSnapState_MidPoint();

	virtual bool FindSnapPoint(QMouseEvent *event);

	virtual ObjectSnap GetType() { return ObjectSnap::ObjectSnapMidPoint; }
	virtual void Draw(QPainter *painter);

};

class ShObjectSnapState_Perpendicular : public ShObjectSnapState {

private:
	ShEntity *perpendicularBaseEntity;

public:
	ShObjectSnapState_Perpendicular(ShGraphicView *view);
	~ShObjectSnapState_Perpendicular();

	virtual bool FindSnapPoint(QMouseEvent *event);
	virtual bool FindSnapPoint(QMouseEvent *event, double perpendicularX, double perpendicularY);

	virtual ObjectSnap GetType() { return ObjectSnap::ObjectSnapPerpendicular; }
	virtual void Draw(QPainter *painter);
	inline ShEntity* PerpendicularBaseEntity() const { return this->perpendicularBaseEntity; }
};

#endif //_SHOBJECTSNAPSTATE_H
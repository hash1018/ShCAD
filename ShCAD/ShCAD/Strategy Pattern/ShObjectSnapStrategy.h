

#ifndef _SHOBJECTSNAPSTATE_H
#define _SHOBJECTSNAPSTATE_H

#include "ShVariable.h"
class QMouseEvent;
class ShGraphicView;
class QPainter;
class ShEntity;
class ShObjectSnapStrategy {

protected:
	ShGraphicView *view;
	double snapX;
	double snapY;
	bool isValid;

public:
	ShObjectSnapStrategy(ShGraphicView *view);
	virtual ~ShObjectSnapStrategy() = 0;

	virtual bool FindSnapPoint(QMouseEvent *event) = 0;

	virtual ObjectSnap GetType() = 0;
	virtual void Draw(QPainter *painter) = 0;

	inline double GetSnapX() const { return this->snapX; }
	inline double GetSnapY() const { return this->snapY; }
};

////////////////////////////////////////////////////////////////////////////////////

class ShObjectSnapStrategy_Nothing : public ShObjectSnapStrategy {

public:
	ShObjectSnapStrategy_Nothing(ShGraphicView *view);
	~ShObjectSnapStrategy_Nothing();

	virtual bool FindSnapPoint(QMouseEvent *event);

	virtual ObjectSnap GetType() { return ObjectSnap::ObjectSnapNothing; }
	virtual void Draw(QPainter *painter) {}
};


/////////////////////////////////////////////////////////////////////////////////////

class ShObjectSnapStrategy_EndPoint : public ShObjectSnapStrategy {

public:
	ShObjectSnapStrategy_EndPoint(ShGraphicView *view);
	~ShObjectSnapStrategy_EndPoint();

	virtual bool FindSnapPoint(QMouseEvent *event);

	virtual ObjectSnap GetType() { return ObjectSnap::ObjectSnapEndPoint; }
	virtual void Draw(QPainter *painter);
};

//////////////////////////////////////////////////////////////////////////////////////

class ShObjectSnapStrategy_MidPoint : public ShObjectSnapStrategy {

public:
	ShObjectSnapStrategy_MidPoint(ShGraphicView *view);
	~ShObjectSnapStrategy_MidPoint();

	virtual bool FindSnapPoint(QMouseEvent *event);

	virtual ObjectSnap GetType() { return ObjectSnap::ObjectSnapMidPoint; }
	virtual void Draw(QPainter *painter);

};

///////////////////////////////////////////////////////////////////////////////////////

class ShObjectSnapStrategy_Center : public ShObjectSnapStrategy {

public:
	ShObjectSnapStrategy_Center(ShGraphicView *view);
	~ShObjectSnapStrategy_Center();

	virtual bool FindSnapPoint(QMouseEvent *event);

	virtual ObjectSnap GetType() { return ObjectSnap::ObjectSnapCenter; }
	virtual void Draw(QPainter *painter);

};

////////////////////////////////////////////////////////////////////////////////////////

class ShObjectSnapStrategy_Quadrant : public ShObjectSnapStrategy {

public:
	ShObjectSnapStrategy_Quadrant(ShGraphicView *view);
	~ShObjectSnapStrategy_Quadrant();

	virtual bool FindSnapPoint(QMouseEvent *event);

	virtual ObjectSnap GetType() { return ObjectSnap::ObjectSnapCenter; }
	virtual void Draw(QPainter *painter);

};

////////////////////////////////////////////////////////////////////////////////////////

class ShObjectSnapStrategy_Perpendicular : public ShObjectSnapStrategy {

private:
	ShEntity *perpendicularBaseEntity;

public:
	ShObjectSnapStrategy_Perpendicular(ShGraphicView *view);
	~ShObjectSnapStrategy_Perpendicular();

	virtual bool FindSnapPoint(QMouseEvent *event);
	virtual bool FindSnapPoint(QMouseEvent *event, double perpendicularX, double perpendicularY);

	virtual ObjectSnap GetType() { return ObjectSnap::ObjectSnapPerpendicular; }
	virtual void Draw(QPainter *painter);
	inline ShEntity* PerpendicularBaseEntity() const { return this->perpendicularBaseEntity; }
};

///////////////////////////////////////////////////////////////////////////////////////////

#endif //_SHOBJECTSNAPSTATE_H
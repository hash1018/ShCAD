
#ifndef _SHSEARCHSNAPPOINTSTRATEGY_H
#define _SHSEARCHSNAPPOINTSTRATEGY_H

#include "Base\ShVariable.h"
#include "Data\ShPoint.h"

class QPainter;
class ShCADWidget;
class ShEntity;

class ShSearchSnapPointStrategy {

protected:
	ShCADWidget *widget;
	ShPoint3d snap;
	bool isValid;

public:
	ShSearchSnapPointStrategy(ShCADWidget *widget);
	virtual ~ShSearchSnapPointStrategy() = 0;

	virtual bool search(const ShPoint3d &point) = 0;
	virtual ObjectSnap getType() = 0;
	virtual void draw(QPainter *painter) = 0;

	inline ShPoint3d getSnap() const { return this->snap; }

};

/////////////////////////////////////////////////////////

class ShSearchSnapPointStrategy_Nothing : public ShSearchSnapPointStrategy {

public:
	ShSearchSnapPointStrategy_Nothing(ShCADWidget *widget);
	~ShSearchSnapPointStrategy_Nothing();

	virtual bool search(const ShPoint3d &point);
	virtual ObjectSnap getType();
	virtual void draw(QPainter *painter);

};

////////////////////////////////////////////////////////

class ShSearchSnapPointStrategy_End : public ShSearchSnapPointStrategy {

public:
	ShSearchSnapPointStrategy_End(ShCADWidget *widget);
	~ShSearchSnapPointStrategy_End();

	virtual bool search(const ShPoint3d &point);
	virtual ObjectSnap getType();
	virtual void draw(QPainter *painter);

};

////////////////////////////////////////////////////////

class ShSearchSnapPointStrategy_Mid : public ShSearchSnapPointStrategy {

public:
	ShSearchSnapPointStrategy_Mid(ShCADWidget *widget);
	~ShSearchSnapPointStrategy_Mid();

	virtual bool search(const ShPoint3d &point);
	virtual ObjectSnap getType();
	virtual void draw(QPainter *painter);

};

/////////////////////////////////////////////////////////

class ShSearchSnapPointStrategy_Center : public ShSearchSnapPointStrategy {

public:
	ShSearchSnapPointStrategy_Center(ShCADWidget *widget);
	~ShSearchSnapPointStrategy_Center();

	virtual bool search(const ShPoint3d &point);
	virtual ObjectSnap getType();
	virtual void draw(QPainter *painter);

};

//////////////////////////////////////////////////////////

class ShSearchSnapPointStrategy_Quadrant : public ShSearchSnapPointStrategy {

public:
	ShSearchSnapPointStrategy_Quadrant(ShCADWidget *widget);
	~ShSearchSnapPointStrategy_Quadrant();

	virtual bool search(const ShPoint3d &point);
	virtual ObjectSnap getType();
	virtual void draw(QPainter *painter);

};

//////////////////////////////////////////////////////////

class ShSearchSnapPointStrategy_Perpendicular : public ShSearchSnapPointStrategy {

private:
	ShEntity *perpendicularBaseEntity;

public:
	ShSearchSnapPointStrategy_Perpendicular(ShCADWidget *widget);
	~ShSearchSnapPointStrategy_Perpendicular();

	virtual bool search(const ShPoint3d &point);
	virtual bool search(const ShPoint3d &point, double perpendicularX, double perpendicularY);
	virtual ObjectSnap getType();
	virtual void draw(QPainter *painter);


	inline ShEntity* getPerpendicularBase() const { return this->perpendicularBaseEntity; }

};


/////////////////////////////////////////////////////////////

class ShSearchSnapPointStrategy_Intersecion : public ShSearchSnapPointStrategy {

private:
	ShEntity *firstBaseEntity;

public:
	ShSearchSnapPointStrategy_Intersecion(ShCADWidget *widget);
	~ShSearchSnapPointStrategy_Intersecion();

	virtual bool search(const ShPoint3d &point);
	virtual ObjectSnap getType();
	virtual void draw(QPainter *painter);
};

#endif //_SHSEARCHSNAPPOINTSTRATEGY_H
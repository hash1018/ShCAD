
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

class ShSearchSnapPointStrategy_Nothing : public ShSearchSnapPointStrategy {

public:
	ShSearchSnapPointStrategy_Nothing(ShCADWidget *widget);
	~ShSearchSnapPointStrategy_Nothing();

	virtual bool search(const ShPoint3d &point);
	virtual ObjectSnap getType();
	virtual void draw(QPainter *painter);

};

class ShSearchSnapPointStrategy_End : public ShSearchSnapPointStrategy {

public:
	ShSearchSnapPointStrategy_End(ShCADWidget *widget);
	~ShSearchSnapPointStrategy_End();

	virtual bool search(const ShPoint3d &point);
	virtual ObjectSnap getType();
	virtual void draw(QPainter *painter);

};

#endif //_SHSEARCHSNAPPOINTSTRATEGY_H
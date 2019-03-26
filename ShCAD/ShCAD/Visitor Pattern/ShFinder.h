

#ifndef _SHFINDER_H
#define _SHFINDER_H

#include "ShVisitor.h"
#include "ShPoint.h"

class ShEntity;
class ShLine;
class ShCircle;
class ShArc;
class ShFinder : public ShVisitor {

private:
	double x;
	double y;
	double zoomRate;
	ShEntity* *foundEntity;

public:
	ShFinder(double x, double y, double zoomRate, ShEntity* *foundEntity);
	~ShFinder();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);
	virtual void Visit(ShPolyLine *polyLine);

};

class ShRectFinder : public ShVisitor {

public:
	enum FindMethod {
		OnePartLiesInsideRect,
		AllPartLiesInsideRect,
	};

private:
	ShPoint3d topLeft;
	ShPoint3d bottomRight;
	ShEntity* *foundEntity;
	FindMethod findMethod;

public:
	ShRectFinder(const ShPoint3d& topLeft, const ShPoint3d& bottomRight, ShEntity* *foundEntity, FindMethod findMethod = AllPartLiesInsideRect);
	~ShRectFinder();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);
	virtual void Visit(ShPolyLine *polyLine);

};

#endif //_SHFINDER_H
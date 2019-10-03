
#ifndef _SHFINDER_H
#define _SHFINDER_H

#include "ShVisitor.h"
#include "Data\ShPoint3d.h"
#include "Base\ShVariable.h"

class ShEntity;

class ShFinder : public ShVisitor {

private:
	double x;
	double y;
	double zoomRate;
	double tolerance;
	ShEntity* *foundEntity;

public:
	ShFinder(double x, double y, double zoomRate, ShEntity* *foundEntity, double tolerance = 6.0);
	~ShFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);

};

//////////////////////////////////////////

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
	ShRectFinder(const ShPoint3d &topLeft, const ShPoint3d &bottomRight, ShEntity* *foundEntity, FindMethod findMethod);
	~ShRectFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);

};


//////////////////////////////////////////


#endif //_SHFINDER_H
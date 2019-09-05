
#ifndef _SHFINDER_H
#define _SHFINDER_H

#include "ShVisitor.h"
#include "Data\ShPoint.h"
#include "Base\ShVariable.h"

class ShEntity;

class ShFinder : public ShVisitor {

private:
	double x;
	double y;
	double zoomRate;
	ShEntity* *foundEntity;

public:
	ShFinder(double x, double y, double zoomRate, ShEntity* *foundEntity);
	~ShFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

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

};


//////////////////////////////////////////

class ShNearestVertexFinder : public ShVisitor {

private:
	double x;
	double y;
	double zoomRate;
	VertexType &vertexType;
	ShPoint3d &vertexPoint;
	double tolerance;

public:
	ShNearestVertexFinder(double x, double y, double zoomRate, VertexType &vertexType, ShPoint3d &vertexPoint, double tolerance = 6.0);
	~ShNearestVertexFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

};

#endif //_SHFINDER_H
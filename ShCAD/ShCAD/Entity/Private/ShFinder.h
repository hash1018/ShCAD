
#ifndef _SHFINDER_H
#define _SHFINDER_H

#include "ShVisitor.h"
#include "Data\ShPoint3d.h"
#include "Base\ShVariable.h"

class ShEntity;
class ShDim;

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
	virtual void visit(ShDot *dot);
	virtual void visit(ShDimLinear *dimLinear);
	virtual void visit(ShDimAligned *dimAligned);
	virtual void visit(ShDimRadius *dimRadius);
	virtual void visit(ShDimDiameter *dimDiameter);
	virtual void visit(ShDimArcLength *dimArcLength);
	virtual void visit(ShDimAngular *dimAngular);

private:
	void visitDim(ShDim *dim);

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
	virtual void visit(ShDot *dot);
	virtual void visit(ShDimLinear *dimLinear);
	virtual void visit(ShDimAligned *dimAligned);
	virtual void visit(ShDimRadius *dimRadius);
	virtual void visit(ShDimDiameter *dimDiameter);
	virtual void visit(ShDimArcLength *dimArcLength);
	virtual void visit(ShDimAngular *dimAngular);

private:
	void visitDim(ShDim *dim);

};


//////////////////////////////////////////


#endif //_SHFINDER_H
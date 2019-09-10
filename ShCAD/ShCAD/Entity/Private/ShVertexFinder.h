

#ifndef _SHVERTEXFINDER_H
#define _SHVERTEXFINDER_H

#include "ShVisitor.h"
#include "Base\ShVariable.h"
#include "Data\ShPoint.h"

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

/////////////////////////////////////////////

class PointAndVertexTypeMathchedEntityFinder : public ShVisitor {

private:
	ShPoint3d mustMatchPoint;
	VertexType vertexType;
	bool &matched;

public:
	PointAndVertexTypeMathchedEntityFinder(const ShPoint3d &mustMatchPoint, VertexType vertexType, bool &matched);
	~PointAndVertexTypeMathchedEntityFinder();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
};


#endif //_SHVERTEXFINDER_H
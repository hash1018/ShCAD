
#ifndef _SHMOVER_H
#define _SHMOVER_H

#include "ShVisitor.h"
#include "Data\ShScrollPosition.h"
#include "Data\ShPoint3d.h"

class ShMover : public ShVisitor {

private:
	double disX;
	double disY;

public:
	ShMover(double disX, double disY);
	~ShMover();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);
	virtual void visit(ShDot *dot);
	virtual void visit(ShDimLinear *dimLinear);
	virtual void visit(ShDimAligned *dimAligned);
	virtual void visit(ShDimRadius *dimRadius);
	virtual void visit(ShDimDiameter *dimDiameter);

};

class ShMoverByAxis : public ShVisitor {

private:
	const ShScrollPosition scroll;
	const ShPoint3d prevCenter;
	const ShPoint3d currentCenter;
	double zoomRate;
	
public:
	ShMoverByAxis(const ShScrollPosition &scroll, const ShPoint3d &prevCenter, const ShPoint3d &currentCenter, double zoomRate);
	~ShMoverByAxis();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);
	virtual void visit(ShDot *dot);
	virtual void visit(ShDimLinear *dimLinear);
	virtual void visit(ShDimAligned *dimAligned);
	virtual void visit(ShDimRadius *dimRadius);
	virtual void visit(ShDimDiameter *dimDiameter);

private:
	void convert(const ShPoint3d &point, ShPoint3d &converted);
};

#endif //_SHMOVER_H
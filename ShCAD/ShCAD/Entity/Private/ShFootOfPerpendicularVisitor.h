

#ifndef _SHFOOTOFPERPENDICULARVISITOR_H
#define _SHFOOTOFPERPENDICULARVISITOR_H

#include "ShVisitor.h"
#include "Data\ShPoint.h"

class ShEntity;

class ShFootOfPerpendicularVisitor : public ShVisitor {

private:
	double &perpendicularX;
	double &perpendicularY;
	ShPoint3d point;

public:
	ShFootOfPerpendicularVisitor(double &perpendicularX, double &perpendicularY, const ShPoint3d& point);
	~ShFootOfPerpendicularVisitor();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);

};

#endif //_SHFOOTOFPERPENDICULARVISITOR_H
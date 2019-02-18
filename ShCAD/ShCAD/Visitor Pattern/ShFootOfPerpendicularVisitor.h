

#ifndef _SHFOOTOFPERPENDICULARVISITOR_H
#define _SHFOOTOFPERPENDICULARVISITOR_H

#include "ShVisitor.h"
#include "ShPoint.h"
class ShEntity;
class ShFootOfPerpendicularVisitor : public ShVisitor {

private:
	double &perpendicularX;
	double &perpendicularY;
	ShPoint3d point;

public:
	ShFootOfPerpendicularVisitor(double &perpendicularX, double &perpendicularY, const ShPoint3d& point);
	~ShFootOfPerpendicularVisitor();

	virtual void Visit(ShLine *perpendicularBaseLine);
	virtual void Visit(ShCircle *perpendicularBaseCircle);
	virtual void Visit(ShArc *perpendicularBaseArc);


};

#endif //_SHFOOTOFPERPENDICULARVISITOR_H
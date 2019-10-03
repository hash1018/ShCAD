

#ifndef _SHFOOTOFPERPENDICULARVISITOR_H
#define _SHFOOTOFPERPENDICULARVISITOR_H

#include "ShVisitor.h"
#include "Data\ShPoint3d.h"

class ShEntity;

class ShFootOfPerpendicularForLinePerpendicularVisitor : public ShVisitor {

private:
	double &perpendicularX;
	double &perpendicularY;
	ShPoint3d point;

public:
	ShFootOfPerpendicularForLinePerpendicularVisitor(double &perpendicularX, double &perpendicularY, const ShPoint3d& point);
	~ShFootOfPerpendicularForLinePerpendicularVisitor();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

};

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
	virtual void visit(ShArc *arc);

};

#endif //_SHFOOTOFPERPENDICULARVISITOR_H
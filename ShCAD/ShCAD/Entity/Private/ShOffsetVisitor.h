
#ifndef _SHOFFSETVISITOR_H
#define _SHOFFSETVISITOR_H

#include "ShVisitor.h"
#include "Data\ShPoint3d.h"

class ShEntity;

class ShOffsetVisitor : public ShVisitor {

private:
	double offsetDistance;
	const ShPoint3d mouse;
	ShEntity *original;

public:
	ShOffsetVisitor(double offsetDistance, const ShPoint3d &mouse, ShEntity *original);
	~ShOffsetVisitor();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

};

#endif //_SHOFFSETVISITOR_H

#ifndef _SHROTATER_H
#define _SHROTATER_H

#include "ShVisitor.h"
#include "Data\ShPoint3d.h"

class ShRotater : public ShVisitor {

private:
	ShPoint3d center;
	double angle;

public:
	ShRotater(const ShPoint3d &center, double angle);
	~ShRotater();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);
	virtual void visit(ShDot *dot);
	virtual void visit(ShDimLinear *dimLinear);

};

#endif //_SHROTATER_H
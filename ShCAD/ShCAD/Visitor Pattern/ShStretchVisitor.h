

#ifndef _SHSELECTIONMOVER_H
#define _SHSELECTIONMOVER_H

#include "ShVisitor.h"
#include "ShVariable.h"
class ShStretchVisitor : public ShVisitor {

private:
	double x;
	double y;
	HitPoint hitPoint;

public:
	ShStretchVisitor(double x, double y);
	~ShStretchVisitor();
	
	void Visit(ShLine *line);
	void Visit(ShCircle *circle);
	void Visit(ShArc *arc);

	void SetHitPoint(HitPoint point);


};

#endif //_SHSELECTIONMOVER_H
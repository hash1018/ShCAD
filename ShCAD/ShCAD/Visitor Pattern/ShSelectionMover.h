

#ifndef _SHSELECTIONMOVER_H
#define _SHSELECTIONMOVER_H

#include "ShVisitor.h"
#include "ShVariable.h"
class ShSelectionMover : public ShVisitor {

private:
	double x;
	double y;
	HitPoint hitPoint;

public:
	ShSelectionMover(double x, double y);
	~ShSelectionMover();
	
	void Visit(ShLine *line);
	void Visit(ShCircle *circle);
	void Visit(ShArc *arc);

	void SetHitPoint(HitPoint point);


};

#endif //_SHSELECTIONMOVER_H
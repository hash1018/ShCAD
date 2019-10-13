
#ifndef _SHMOVER_H
#define _SHMOVER_H

#include "ShVisitor.h"

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

};

#endif //_SHMOVER_H
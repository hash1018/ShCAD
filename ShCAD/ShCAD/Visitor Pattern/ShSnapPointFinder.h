

#ifndef _SHSNAPPOINTFINDER_H
#define _SHSNAPPOINTFINDER_H

#include "ShVisitor.h"
#include "ShVariable.h"

class ShSnapPointFinder : public ShVisitor {

private:
	ObjectSnap objectSnap;
	double x;
	double y;
	double &snapX;
	double &snapY;
	bool &isValid;

public:
	ShSnapPointFinder(ObjectSnap objectSnap, double x, double y, double &snapX, double &snapY, bool &isValid);
	~ShSnapPointFinder();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);



};

#endif //_SHSNAPPOINTFINDER_H


#ifndef _SHSNAPPOINTFINDER_H
#define _SHSNAPPOINTFINDER_H

#include "Base\ShVariable.h"
#include "ShVisitor.h"

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

	virtual void visit(ShLine *line);

};

#endif //_SHSNAPPOINTFINDER_H
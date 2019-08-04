

#ifndef _SHSNAPPOINTFINDER_H
#define _SHSNAPPOINTFINDER_H

#include "Base\ShVariable.h"
#include "ShVisitor.h"

class ShSnapPointFinder : public ShVisitor {

public:
	enum Mode {
		Normal,
		FootOfPerpendicular,
	};

private:
	ObjectSnap objectSnap;
	double x;
	double y;
	double &snapX;
	double &snapY;
	bool &isValid;
	double perpendicularX;
	double perpendicularY;
	Mode mode;

public:
	ShSnapPointFinder(ObjectSnap objectSnap, double x, double y, double &snapX, double &snapY, bool &isValid);
	ShSnapPointFinder(ObjectSnap objectSnap, double x, double y, double &snapX, double &snapY, bool &isValid,
		double perpendicularX, double perpendicularY);
	~ShSnapPointFinder();

	virtual void visit(ShLine *line);

};

#endif //_SHSNAPPOINTFINDER_H
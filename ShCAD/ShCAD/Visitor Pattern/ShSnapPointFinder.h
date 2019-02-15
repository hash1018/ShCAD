

#ifndef _SHSNAPPOINTFINDER_H
#define _SHSNAPPOINTFINDER_H

#include "ShVisitor.h"
#include "ShVariable.h"

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

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);



};

#endif //_SHSNAPPOINTFINDER_H
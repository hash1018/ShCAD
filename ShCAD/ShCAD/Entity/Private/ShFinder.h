
#ifndef _SHFINDER_H
#define _SHFINDER_H

#include "ShVisitor.h"
class ShEntity;

class ShFinder : public ShVisitor {

private:
	double x;
	double y;
	double zoomRate;
	ShEntity* *foundEntity;

public:
	ShFinder(double x, double y, double zoomRate, ShEntity* *foundEntity);
	~ShFinder();

	virtual void visit(ShLine *line);

};

#endif //_SHFINDER_H
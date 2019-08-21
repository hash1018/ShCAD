
#ifndef _SHROTATER_H
#define _SHROTATER_H

#include "ShVisitor.h"
#include "Data\ShPoint.h"

class ShRotater : public ShVisitor {

private:
	ShPoint3d center;
	double angle;

public:
	ShRotater(const ShPoint3d &center, double angle);
	~ShRotater();

	virtual void visit(ShLine *line);

};

#endif //_SHROTATER_H


#ifndef _SHROTATER_H
#define _SHROTATER_H

#include "ShVisitor.h"
#include "ShPoint.h"
class ShRotater : public ShVisitor {

private:
	ShPoint3d center;
	double angle;

public:
	ShRotater(const ShPoint3d& center, double angle);
	~ShRotater();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);

};

#endif //_SHROTATER_H
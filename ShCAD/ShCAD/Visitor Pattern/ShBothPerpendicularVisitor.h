
#ifndef _SHBOTHPERPENDICULARVISITOR_H
#define _SHBOTHPERPENDICULARVISITOR_H

#include "ShVisitor.h"
#include "ShPoint.h"
class ShEntity;
class ShBothPerpendicularVisitor : public ShVisitor {

private:
	ShPoint3d &perpendicular;
	bool &isValid;

	// **this object is the one that perpendicular point needs to be known.
	ShEntity* perpendicularEntity;

public:
	ShBothPerpendicularVisitor(ShEntity *perpendicularEntity, ShPoint3d &perpendicular, bool &isValid);
	~ShBothPerpendicularVisitor();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);



};


class ShLinePerpendicularVisitor : public ShVisitor {

	friend class ShBothPerpendicularVisitor;

private:
	ShPoint3d &perpendicular;
	ShLine *baseLine;
	bool &isValid;

	ShLinePerpendicularVisitor(ShLine *baseLine, ShPoint3d &perpendicular, bool &isValid);
	~ShLinePerpendicularVisitor();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);

};


#endif //_SHBOTHPERPENDICULARVISITOR_H
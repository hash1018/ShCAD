
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

	virtual void Visit(ShLine *firstPerpendicularLine);
	virtual void Visit(ShCircle *firstPerpendicularCircle);
	virtual void Visit(ShArc *firstPerpendicularArc);



};


class ShFirstLinePerpendicularVisitor : public ShVisitor {

	friend class ShBothPerpendicularVisitor;

private:
	ShPoint3d &perpendicular;
	ShLine *firstLine;
	bool &isValid;

	ShFirstLinePerpendicularVisitor(ShLine *firstLine, ShPoint3d &perpendicular, bool &isValid);
	~ShFirstLinePerpendicularVisitor();

	virtual void Visit(ShLine *secondPerpendicularLine);
	virtual void Visit(ShCircle *secondPerpendicularCircle);
	virtual void Visit(ShArc *secondPerpendicularArc);

};


#endif //_SHBOTHPERPENDICULARVISITOR_H
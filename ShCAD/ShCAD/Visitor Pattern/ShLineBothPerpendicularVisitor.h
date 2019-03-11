
#ifndef _SHLINEBOTHPERPENDICULARVISITOR_H
#define _SHLINEBOTHPERPENDICULARVISITOR_H

#include "ShVisitor.h"
#include "ShPoint.h"
class ShEntity;
class ShLineBothPerpendicularVisitor : public ShVisitor {

private:
	ShPoint3d &perpendicular;
	bool &isValid;

	// **this object is the one that perpendicular point needs to be known.
	ShEntity* secondPerpendicularEntity;

public:
	ShLineBothPerpendicularVisitor(ShEntity *secondPerpendicularEntity, ShPoint3d &perpendicular, bool &isValid);
	~ShLineBothPerpendicularVisitor();

	virtual void Visit(ShLine *firstPerpendicularLine);
	virtual void Visit(ShCircle *firstPerpendicularCircle);
	virtual void Visit(ShArc *firstPerpendicularArc);



};


class ShFirstLinePerpendicularVisitor : public ShVisitor {

	friend class ShLineBothPerpendicularVisitor;

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

class ShFirstCirclePerpendicularVisitor : public ShVisitor {

	friend class ShLineBothPerpendicularVisitor;

private:
	ShPoint3d &perpendicular;
	ShCircle *firstCircle;
	bool &isValid;

	ShFirstCirclePerpendicularVisitor(ShCircle *firstCircle, ShPoint3d &perpendicular, bool &isValid);
	~ShFirstCirclePerpendicularVisitor();

	virtual void Visit(ShLine *secondPerpendicularLine);
	virtual void Visit(ShCircle *secondPerpendicularCircle);
	virtual void Visit(ShArc *secondPerpendicularArc);

};

class ShFirstArcPerpendicularVisitor : public ShVisitor {

	friend class ShLineBothPerpendicularVisitor;

private:
	ShPoint3d &perpendicular;
	ShArc *firstArc;
	bool &isValid;

	ShFirstArcPerpendicularVisitor(ShArc *firstArc, ShPoint3d &perpendicular, bool &isValid);
	~ShFirstArcPerpendicularVisitor();

	virtual void Visit(ShLine *secondPerpendicularLine);
	virtual void Visit(ShCircle *secondPerpendicularCircle);
	virtual void Visit(ShArc *secondPerpendicularArc);
};


#endif //_SHLINEBOTHPERPENDICULARVISITOR_H
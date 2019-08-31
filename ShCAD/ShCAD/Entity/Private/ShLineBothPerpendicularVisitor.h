
#ifndef _SHLINEBOTHPERPENDICULARVISITOR_H
#define _SHLINEBOTHPERPENDICULARVISITOR_H

#include "ShVisitor.h"
#include "Data\ShPoint.h"

class ShEntity;

class ShLineBothPerpendicularVisitor : public ShVisitor {

private:
	ShPoint3d &perpendicular;
	bool &isValid;

	ShEntity *secondPerpendicularBase;

public:
	ShLineBothPerpendicularVisitor(ShEntity *secondPerpendicularBase, ShPoint3d &perpendicular, bool &isValid);
	~ShLineBothPerpendicularVisitor();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

};

//////////////////////////////////////////////////////////////

class ShFirstLinePerpendicularVisitor : public ShVisitor {

	friend class ShLineBothPerpendicularVisitor;

private:
	ShPoint3d &perpendicular;
	ShLine *firstLine;
	bool &isValid;

private:
	ShFirstLinePerpendicularVisitor(ShLine *firstLine, ShPoint3d &perpendicular, bool &isValid);
	~ShFirstLinePerpendicularVisitor();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

};

///////////////////////////////////////////////////////////////

class ShFirstCirclePerpendicularVisitor : public ShVisitor {

	friend class ShLineBothPerpendicularVisitor;

private:
	ShPoint3d &perpendicular;
	ShCircle *firstCircle;
	bool &isValid;

private:
	ShFirstCirclePerpendicularVisitor(ShCircle *firstCircle, ShPoint3d &perpendicular, bool &isValid);
	~ShFirstCirclePerpendicularVisitor();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	
};


//////////////////////////////////////////////////////////////////

class ShFirstArcPerpendicularVisitor : public ShVisitor {

	friend class ShLineBothPerpendicularVisitor;

private:
	ShPoint3d &perpendicular;
	ShArc *firstArc;
	bool &isValid;

private:
	ShFirstArcPerpendicularVisitor(ShArc *firstArc, ShPoint3d &perpendicular, bool &isValid);
	~ShFirstArcPerpendicularVisitor();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

};

#endif //_SHLINEBOTHPERPENDICULARVISITOR_H
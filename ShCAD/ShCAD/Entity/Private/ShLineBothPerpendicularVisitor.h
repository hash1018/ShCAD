
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

};

#endif //_SHLINEBOTHPERPENDICULARVISITOR_H
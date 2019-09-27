
#ifndef _SHVISITOR_H
#define _SHVISITOR_H

// Visitor Pattern

class ShLine;
class ShRubberBand;
class ShCircle;
class ShArc;
class ShDimLinear;

class ShVisitor {

public:
	ShVisitor();
	virtual ~ShVisitor() = 0;

	virtual void visit(ShLine *line) = 0;
	virtual void visit(ShRubberBand *rubberBand) {}
	virtual void visit(ShCircle *circle) {}
	virtual void visit(ShArc *arc) {}
	virtual void visit(ShDimLinear *dimLinear) {}

};


#endif //_SHVISITOR_H
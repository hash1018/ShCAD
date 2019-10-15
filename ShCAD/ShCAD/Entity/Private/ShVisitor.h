
#ifndef _SHVISITOR_H
#define _SHVISITOR_H

// Visitor Pattern

class ShLine;
class ShRubberBand;
class ShCircle;
class ShArc;
class ShDimLinear;
class ShPoint;
class ShDot;
class ShDimAligned;

class ShVisitor {

public:
	ShVisitor();
	virtual ~ShVisitor() = 0;

	virtual void visit(ShLine *line) {}
	virtual void visit(ShRubberBand *rubberBand) {}
	virtual void visit(ShCircle *circle) {}
	virtual void visit(ShArc *arc) {}
	virtual void visit(ShPoint *point) {}
	virtual void visit(ShDot *dot) {}
	virtual void visit(ShDimLinear *dimLinear) {}
	virtual void visit(ShDimAligned *dimAligned) {}


};


#endif //_SHVISITOR_H
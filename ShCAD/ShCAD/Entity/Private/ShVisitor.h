
#ifndef _SHVISITOR_H
#define _SHVISITOR_H

class ShLine;
class ShRubberBand;
class ShCircle;
class ShArc;

class ShVisitor {

public:
	ShVisitor();
	virtual ~ShVisitor() = 0;

	virtual void visit(ShLine *line) = 0;
	virtual void visit(ShRubberBand *rubberBand) {}
	virtual void visit(ShCircle *circle) {}
	virtual void visit(ShArc *arc) {}

};


#endif //_SHVISITOR_H

#ifndef _SHVISITOR_H
#define _SHVISITOR_H

class ShLine;
class ShRubberBand;
class ShVisitor {

public:
	ShVisitor();
	virtual ~ShVisitor() = 0;

	virtual void visit(ShLine *line) = 0;
	virtual void visit(ShRubberBand *rubberBand) = 0;

};


#endif //_SHVISITOR_H
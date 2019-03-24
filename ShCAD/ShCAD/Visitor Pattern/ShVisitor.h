

#ifndef _SHVISITOR_H
#define _SHVISITOR_H


class ShLine;
class ShEntityTable;
class ShCircle;
class ShArc;
class ShRubberBand;
class ShPolyLine;
class ShVisitor {

public:
	ShVisitor();
	virtual ~ShVisitor() = 0;

	virtual void Visit(ShLine* shLine) = 0;
	virtual void Visit(ShEntityTable *shEntityTable) {}
	virtual void Visit(ShCircle *shCircle) = 0;
	virtual void Visit(ShArc *shArc) = 0;
	virtual void Visit(ShRubberBand *rubberBand) {}
	virtual void Visit(ShPolyLine *polyLine) {}

};


#endif //_SHVISITOR_H
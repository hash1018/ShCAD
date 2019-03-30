
#ifndef _SHPRINTVISITOR_H
#define _SHPRINTVISITOR_H

#include "ShVisitor.h"

class ShGraphicView;
class QColor;
class QPainter;
class ShEntity;
class QString;
class ShPrintVisitor : public ShVisitor {

private:
	ShGraphicView *view;
	QPainter *painter;
	double scale;

public:
	ShPrintVisitor(ShGraphicView *view, QPainter *painter, double scale);
	~ShPrintVisitor();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);
	virtual void Visit(ShPolyLine *polyLine);


private:
	void GetColor(ShEntity *entity, QColor &color);
	
};

#endif //_SHPRINTVISITOR_H
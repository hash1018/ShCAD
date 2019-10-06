

#ifndef _SHPLOTER_H
#define _SHPLOTER_H

#include "ShVisitor.h"

class ShCADWidget;
class QPainter;
class ShEntity;
class QColor;


class ShPloter : public ShVisitor {

private:
	ShCADWidget *widget;
	QPainter *painter;
	double scale;

public:
	ShPloter(ShCADWidget *widget, QPainter *painter, double scale);
	~ShPloter();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);
	virtual void visit(ShDot *dot);


private:
	void getColor(ShEntity *entity, QColor &color);
};

#endif //_SHPLOTER_H



#ifndef _SHPLOTER_H
#define _SHPLOTER_H

#include "ShVisitor.h"

class ShCADWidget;
class QPainter;
class ShEntity;
class QColor;
class QString;


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
	virtual void visit(ShDimLinear *dimLinear);
	virtual void visit(ShDimAligned *dimAligned);
	virtual void visit(ShDimRadius *dimRadius);
	virtual void visit(ShDimDiameter *dimDiameter);
	virtual void visit(ShDimArcLength *dimArcLength);
	virtual void visit(ShDimAngular *dimAngular);
	virtual void visit(ShConstructionLine *constructionLine);


private:
	void getColor(ShEntity *entity, QColor &color);
	void plotLine(int startX, int startY, int endX, int endY, QColor &color);
	void plotText(QPainter *painter, int dx, int dy, double angle, const QString &text, double textHeight, const QColor &color);
	void plotCircle(int centerX, int centerY, int radius, const QColor &color);
	void plotArc(int centerX, int centerY, int radius, double startAngle, double endAngle, const QColor &color);
	void plotFilledTriangle(int x, int y, int x2, int y2, int x3, int y3, const QColor &color);
	void plotPoint(int x, int y, const QColor &color);

	
};

#endif //_SHPLOTER_H

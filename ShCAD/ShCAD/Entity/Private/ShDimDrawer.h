

#ifndef _SHDIMDRAWER_H
#define _SHDIMDRAWER_H

#include "ShDrawer.h"

class QPainter;
class QString;
class ShColor;

class ShDimDrawer : public ShDrawer {

public:
	ShDimDrawer(ShCADWidget *widget, QPainter *painter);
	~ShDimDrawer();

	virtual void visit(ShDimLinear *dimLinear);

private:
	void drawArrow(const ShPoint3d &start, const ShPoint3d &end, const GLColor &color);
	void drawText(QPainter *painter, const ShPoint3d &point, double angle, const QString &text, const ShColor &color);
};

#endif //_SHDIMDRAWER_H
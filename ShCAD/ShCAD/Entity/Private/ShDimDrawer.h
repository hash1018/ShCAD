

#ifndef _SHDIMDRAWER_H
#define _SHDIMDRAWER_H

#include "ShDrawer.h"

class QPainter;
class QString;
class ShColor;

class ShDrawerUnSelectedDim : public ShDrawer {

	friend class ShDrawerUnSelectedEntity;

private:
	ShDrawerUnSelectedDim(ShCADWidget *widget, QPainter *painter);
	~ShDrawerUnSelectedDim();

	virtual void visit(ShDimLinear *dimLinear);

protected:
	void drawArrow(const ShPoint3d &start, const ShPoint3d &end, const GLColor &color);
	void drawText(QPainter *painter, const ShPoint3d &point, double angle, const QString &text, const ShColor &color);
};


#endif //_SHDIMDRAWER_H


#ifndef _SHDRAWER_H
#define _SHDRAWER_H

#include "ShVisitor.h"
#include <qopenglfunctions.h>

class ShLine;
class ShCircle;
class ShArc;
class ShRubberBand;
class ShGraphicView;
class ShDrawer : public ShVisitor {

private:
	ShGraphicView *view;

public:
	ShDrawer(ShGraphicView *view);
	~ShDrawer();

	void Visit(ShLine *shLine);
	void Visit(ShCircle *shCircle);
	void Visit(ShArc *shArc);
	void Visit(ShRubberBand *shRubberBand);

private:
	void ConvertDeviceToOpenGL(int x, int y, double  &ox, double  &oy);
	void ConvertEntityToOpenGL(double x, double y, double &ox, double &oy);
};

#endif //_SHDRAWER_H
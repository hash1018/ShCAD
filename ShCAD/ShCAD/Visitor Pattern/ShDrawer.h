

#ifndef _SHDRAWER_H
#define _SHDRAWER_H

#include "ShVisitor.h"
#include <qopenglfunctions.h>

class ShSelectedEntityDrawer;
class ShLine;
class ShCircle;
class ShArc;
class ShRubberBand;
class ShGraphicView;
class ShDrawer : public ShVisitor {

protected:
	ShGraphicView *view;

public:
	ShDrawer(ShGraphicView *view);
	~ShDrawer();

	virtual void Visit(ShLine *shLine);
	virtual void Visit(ShCircle *shCircle);
	virtual void Visit(ShArc *shArc);
	void Visit(ShRubberBand *shRubberBand);

protected:
	void ConvertDeviceToOpenGL(int x, int y, double  &ox, double  &oy);
	void ConvertEntityToOpenGL(double x, double y, double &ox, double &oy);
};

class ShSelectedEntityDrawer : public ShDrawer {

public:
	ShSelectedEntityDrawer(ShGraphicView *view);
	~ShSelectedEntityDrawer();

	void Visit(ShLine *shLine);
	void Visit(ShCircle *shCircle);
	void Visit(ShArc *shArc);
	


};

#endif //_SHDRAWER_H
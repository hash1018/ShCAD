

#ifndef _SHDRAWER_H
#define _SHDRAWER_H

#include "ShVisitor.h"
#include <qopenglfunctions.h>

class ShLine;
class ShCircle;
class ShArc;
class ShRubberBand;
class ShDrawer : public ShVisitor {

private:
	int glWidth;
	int glHeight;


public:
	ShDrawer(int glWidth, int glHeight);
	~ShDrawer();

	void Visit(ShLine *shLine);
	void Visit(ShCircle *shCircle);
	void Visit(ShArc *shArc);
	void Visit(ShRubberBand *shRubberBand);

private:
	void ConvertDeviceXY2OpenglXY(int x, int y, double  &ox, double  &oy);
};

#endif //_SHDRAWER_H
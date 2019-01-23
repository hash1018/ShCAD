

#ifndef _SHDRAWER_H
#define _SHDRAWER_H

#include "ShVisitor.h"
#include <qopenglfunctions.h>
#include "ShVariable.h"

typedef struct GLPoint {
	double x;
	double y;
}GLPoint;

typedef struct GLColor {
	GLfloat red;
	GLfloat green;
	GLfloat blue;

	GLColor(GLfloat red, GLfloat green, GLfloat blue)
		:red(red), green(green), blue(blue) {
	
	}

}GLColor;


class ShSelectedEntityDrawer;
class ShLine;
class ShCircle;
class ShArc;
class ShRubberBand;
class ShGraphicView;
class ShDrawer : public ShVisitor {

protected:
	ShGraphicView *view;
	DrawType drawType;

public:
	ShDrawer(ShGraphicView *view, DrawType drawType);
	~ShDrawer();

	virtual void Visit(ShLine *shLine);
	virtual void Visit(ShCircle *shCircle);
	virtual void Visit(ShArc *shArc);
	void Visit(ShRubberBand *shRubberBand);

protected:
	void ConvertDeviceToOpenGL(int x, int y, double  &ox, double  &oy);
	void ConvertEntityToOpenGL(double x, double y, double &ox, double &oy);

	void DrawLine(const GLPoint& start, const GLPoint& end, const GLColor& color);
};

class ShSelectedEntityDrawer : public ShDrawer {

public:
	ShSelectedEntityDrawer(ShGraphicView *view, DrawType drawType);
	~ShSelectedEntityDrawer();

	void Visit(ShLine *shLine);
	void Visit(ShCircle *shCircle);
	void Visit(ShArc *shArc);
	
};

class ShJustUnSelectedEntitiesDrawer : public ShDrawer {

public:
	ShJustUnSelectedEntitiesDrawer(ShGraphicView *view);
	~ShJustUnSelectedEntitiesDrawer();

	void Visit(ShLine *shLine);
	void Visit(ShCircle *shCircle);
	void Visit(ShArc *shArc);

};

#endif //_SHDRAWER_H
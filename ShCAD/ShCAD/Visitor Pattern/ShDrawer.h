

#ifndef _SHDRAWER_H
#define _SHDRAWER_H

#include "ShVisitor.h"
#include <qopenglfunctions.h>
#include "ShVariable.h"
#include "ShPoint.h"
typedef struct GLPoint {
	double x;
	double y;
	
	GLPoint() :x(0), y(0) {}

	GLPoint(double x, double y) :x(x), y(y) {}

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

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);
	virtual void Visit(ShRubberBand *rubberBand);
	virtual void Visit(ShPolyLine *polyLine);

protected:
	void ConvertDeviceToOpenGL(int x, int y, double  &ox, double  &oy);
	void ConvertEntityToOpenGL(double x, double y, double &ox, double &oy);
	void ConvertEntityToDevice(double x, double y, int &dx, int &dy);

	void DrawLine(const GLPoint& start, const GLPoint& end, const GLColor& color);
	void DrawFilledRect(const GLPoint& topLeft, const GLPoint& bottomRight, const GLColor& color);
	void DrawCircle(const ShPoint3d& center, double radius, const GLColor& color, int segments = 360);
	void DrawArc(const ShPoint3d& center, double radius, double startAngle, double endAngle, const GLColor& color, int segments = 360);
};

class ShSelectedEntityDrawer : public ShDrawer {

public:
	ShSelectedEntityDrawer(ShGraphicView *view, DrawType drawType);
	~ShSelectedEntityDrawer();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);
	virtual void Visit(ShPolyLine *polyLine);
};

#endif //_SHDRAWER_H
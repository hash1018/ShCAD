
#ifndef _SHDRAWER_H
#define _SHDRAWER_H

#include "ShVisitor.h"
#include <qopenglfunctions.h>
#include "Data\ShPoint.h"

class ShCADWidget;


typedef struct GLPoint {

	double x;
	double y;

	GLPoint();
	GLPoint(double x, double y);
	~GLPoint();

}GLPoint;

/////////////////////////////////////////////

typedef struct GLColor {
	
	GLfloat red;
	GLfloat green;
	GLfloat blue;

	GLColor(GLfloat red, GLfloat green, GLfloat blue);
	~GLColor();

}GLColor;

//////////////////////////////////////////////

class ShDrawerFunctions {

private:
	ShCADWidget *widget;

public:
	ShDrawerFunctions(ShCADWidget *widget);
	~ShDrawerFunctions();

	void convertDeviceToOpenGL(int x, int y, double &ox, double &oy);
	void convertEntityToOpenGL(double x, double y, double &ox, double &oy);
	void convertEntityToDevice(double x, double y, int &dx, int &dy);
	void drawLine(const GLPoint& start, const GLPoint& end, const GLColor& color);
	void drawFilledRect(const GLPoint& topLeft, const GLPoint& bottomRight, const GLColor& color);
	void drawFilledPolygon(GLPoint(*array), int length, const GLColor& color);
	void drawCircle(const ShPoint3d& center, double radius, const GLColor& color, int segments = 360);
	void drawArc(const ShPoint3d& center, double radius, double startAngle, double endAngle, const GLColor& color, int segments = 360);
};

////////////////////////////////////////////////

class ShDrawer : public ShVisitor {

protected:
	ShCADWidget *widget;

public:
	ShDrawer(ShCADWidget *widget);
	virtual ~ShDrawer() = 0;

};

class ShDrawerUnSelectedEntity : public ShDrawer {

public:
	ShDrawerUnSelectedEntity(ShCADWidget *widget);
	~ShDrawerUnSelectedEntity();

	virtual void visit(ShLine *line);
	virtual void visit(ShRubberBand *rubberBand);


};

class ShDrawerSelectedEntityVertex : public ShDrawer {

public:
	ShDrawerSelectedEntityVertex(ShCADWidget *widget);
	~ShDrawerSelectedEntityVertex();

	virtual void visit(ShLine *line);

};

class ShDrawerSelectedEntity : public ShDrawer {

public:
	ShDrawerSelectedEntity(ShCADWidget *widget);
	~ShDrawerSelectedEntity();

	virtual void visit(ShLine *line);
};

#endif //_SHDRAWER_H

#ifndef _SHDRAWER_H
#define _SHDRAWER_H

#include "ShVisitor.h"
#include <qopenglfunctions.h>
#include "Data\ShPoint3d.h"
#include "Base\ShVariable.h"

class ShCADWidget;
class ShDrawerSelectedEntity;
class QPainter;

class ShDrawerSelectedEntityFactory {

public:
	ShDrawerSelectedEntityFactory();
	~ShDrawerSelectedEntityFactory();

	static ShDrawerSelectedEntity* create(ShCADWidget *widget, QPainter *painter, ActionType actionType);

};


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
	void drawDot(const GLPoint &point, const GLColor &color);
	void drawFilledTriangle(const GLPoint &p1, const GLPoint &p2, const GLPoint &p3, const GLColor &color);
	void drawTriangle(const GLPoint &p1, const GLPoint &p2, const GLPoint &p3, const GLColor &color);
	
};

////////////////////////////////////////////////

class ShDrawer : public ShVisitor {

protected:
	ShCADWidget *widget;
	QPainter *painter;

public:
	ShDrawer(ShCADWidget *widget, QPainter *painter);
	virtual ~ShDrawer() = 0;

};

//////////////////////////////////////////////

class ShDrawerUnSelectedEntity : public ShDrawer {

public:
	ShDrawerUnSelectedEntity(ShCADWidget *widget, QPainter *painter);
	~ShDrawerUnSelectedEntity();

	virtual void visit(ShLine *line);
	virtual void visit(ShRubberBand *rubberBand);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);
	virtual void visit(ShDot *dot);
	virtual void visit(ShDimLinear *dimLinear);
	virtual void visit(ShDimAligned *dimAligned);
	virtual void visit(ShDimRadius *dimRadius);
	


};

//////////////////////////////////////////////

class ShDrawerSelectedEntity : public ShDrawer {

public:
	ShDrawerSelectedEntity(ShCADWidget *widget, QPainter *painter);
	virtual ~ShDrawerSelectedEntity() = 0;

};

//////////////////////////////////////////////

class ShDrawerSelectedEntityVertex : public ShDrawerSelectedEntity {

public:
	ShDrawerSelectedEntityVertex(ShCADWidget *widget, QPainter *painter);
	~ShDrawerSelectedEntityVertex();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);
	virtual void visit(ShDot *dot);
	virtual void visit(ShDimLinear *dimLinear);
	virtual void visit(ShDimAligned *dimAligned);
	
};

///////////////////////////////////////////////


class ShDrawerSelectedEntityNoVertex : public ShDrawerSelectedEntity {

public:
	ShDrawerSelectedEntityNoVertex(ShCADWidget *widget, QPainter *painter);
	~ShDrawerSelectedEntityNoVertex();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);
	virtual void visit(ShDot *dot);
	virtual void visit(ShDimLinear *dimLinear);
	virtual void visit(ShDimAligned *dimAligned);

};

///////////////////////////////////////////////

class ShDrawerEraseBackGround : public ShDrawer {

public:
	ShDrawerEraseBackGround(ShCADWidget *widget, QPainter *painter);
	~ShDrawerEraseBackGround();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);
	virtual void visit(ShPoint *point);
	virtual void visit(ShDot *dot);
	virtual void visit(ShDimLinear *dimLinear);
	virtual void visit(ShDimAligned *dimAligned);

};

class ShApparentExtensionDrawer : public ShDrawer {

private:
	ShPoint3d start;
	ShPoint3d end;

public:
	ShApparentExtensionDrawer(ShCADWidget *widget, QPainter *painter);
	~ShApparentExtensionDrawer();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);
	virtual void visit(ShArc *arc);

public:
	void setStart(const ShPoint3d &start) { this->start = start; }
	void setEnd(const ShPoint3d &end) { this->end = end; }
};

#endif //_SHDRAWER_H
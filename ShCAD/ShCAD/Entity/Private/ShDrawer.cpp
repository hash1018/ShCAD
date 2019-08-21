
#include "ShDrawer.h"
#include "Interface\ShCADWidget.h"
#include "Base\ShMath.h"
#include <qdebug.h>
ShDrawerSelectedEntityFactory::ShDrawerSelectedEntityFactory() {

}

ShDrawerSelectedEntityFactory::~ShDrawerSelectedEntityFactory() {

}

ShDrawerSelectedEntity* ShDrawerSelectedEntityFactory::create(ShCADWidget *widget,ActionType actionType) {
	qDebug() << "create" << actionType;

	if (actionType == ActionType::ActionModifyMove ||
		actionType == ActionType::ActionModifyCopy ||
		actionType == ActionType::ActionModifyRotate ||
		actionType == ActionType::ActionModifyMirror ||
		actionType == ActionType::ActionModifyExtend ||
		actionType == ActionType::ActionModifyStretch ||
		actionType == ActionType::ActionModifyTrim) {

		return new ShDrawerSelectedEntityNoVertex(widget);
	}

	return new ShDrawerSelectedEntityVertex(widget);
}



///////////////////////////////////////


GLPoint::GLPoint()
	:x(0), y(0) {

}

GLPoint::GLPoint(double x, double y)
	: x(x), y(y) {

}

GLPoint::~GLPoint() {

}

////////////////////////////////////////

GLColor::GLColor(GLfloat red, GLfloat green, GLfloat blue)
	:red(red), green(green), blue(blue) {

}

GLColor::~GLColor() {

}

////////////////////////////////////////

ShDrawerFunctions::ShDrawerFunctions(ShCADWidget *widget)
	:widget(widget) {

}

ShDrawerFunctions::~ShDrawerFunctions() {

}

void ShDrawerFunctions::convertDeviceToOpenGL(int x, int y, double &ox, double &oy) {

	int w = this->widget->width();
	int h = this->widget->height();
	ox = (double)((x - (double)w / 2.0)*(double)(1.0 / (double)(w / 2.0)));
	oy = -(double)((y - (double)h / 2.0)*(double)(1.0 / (double)(h / 2.0)));
}

void ShDrawerFunctions::convertEntityToOpenGL(double x, double y, double &ox, double &oy) {

	double zoomRate = this->widget->getZoomRate();
	double hPos = this->widget->getScrollPosition().horizontal;
	double vPos = this->widget->getScrollPosition().vertical;
	double centerX = this->widget->getAxis().getCenter().x;
	double centerY = this->widget->getAxis().getCenter().y;


	double tempX = (x*zoomRate) - hPos + (centerX*zoomRate);
	double tempY = -1 * ((y*zoomRate) + vPos - (centerY*zoomRate));


	int w = this->widget->width();
	int h = this->widget->height();
	ox = ((tempX - (double)w / 2.0)*(1.0 / ((double)w / 2.0)));
	oy = -((tempY - (double)h / 2.0)*(1.0 / ((double)h / 2.0)));
}

void ShDrawerFunctions::convertEntityToDevice(double x, double y, int &dx, int &dy) {

	double zoomRate = this->widget->getZoomRate();
	double hPos = this->widget->getScrollPosition().horizontal;
	double vPos = this->widget->getScrollPosition().vertical;
	ShPoint3d center = this->widget->getAxis().getCenter();

	double tempX = ((x*zoomRate) - hPos + (center.x*zoomRate));
	double tempY = (-1 * ((y*zoomRate) + vPos - (center.y*zoomRate)));

	dx = math::toInt(tempX);
	dy = math::toInt(tempY);
}

void ShDrawerFunctions::drawLine(const GLPoint& start, const GLPoint& end, const GLColor& color) {

	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_LINES);
	glVertex2f(start.x, start.y);
	glVertex2f(end.x, end.y);
	glEnd();
}

void ShDrawerFunctions::drawFilledRect(const GLPoint& topLeft, const GLPoint& bottomRight, const GLColor& color) {

	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_QUADS);
	glVertex2f(topLeft.x, topLeft.y);
	glVertex2f(bottomRight.x, topLeft.y);
	glVertex2f(bottomRight.x, bottomRight.y);
	glVertex2f(topLeft.x, bottomRight.y);
	glEnd();
}

void ShDrawerFunctions::drawFilledPolygon(GLPoint(*array), int length, const GLColor& color) {

	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_POLYGON);

	for (int i = 0; i < length; i++) {
		glVertex2f(array[i].x, array[i].y);
	}

	glEnd();
}

void ShDrawerFunctions::drawCircle(const ShPoint3d& center, double radius, const GLColor& color, int segments) {

	glColor3f(color.red, color.green, color.blue);

	double theta, x, y;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < segments; i++) {

		theta = 2.0 * 3.1415926 * double(i) / double(segments);
		x = radius*cosf(theta);
		y = radius*sinf(theta);

		this->convertEntityToOpenGL(center.x + x, center.y + y, x, y);
		glVertex2f(x, y);
	}

	glEnd();
}

void ShDrawerFunctions::drawArc(const ShPoint3d& center, double radius, double startAngle, double endAngle, const GLColor& color, int segments) {

	glColor3f(color.red, color.green, color.blue);

	double theta, x, y;

	glBegin(GL_LINE_STRIP);

	theta = 2.0 * 3.1415926 * double(startAngle) / double(segments);
	x = radius*cosf(theta);
	y = radius*sinf(theta);

	this->convertEntityToOpenGL(center.x + x, center.y + y, x, y);
	glVertex2f(x, y);

	for (int i = math::toInt(startAngle + 1); i <= math::toInt(endAngle - 1); i++) {

		theta = 2.0 * 3.1415926 * double(i) / double(segments);
		x = radius*cosf(theta);
		y = radius*sinf(theta);
		this->convertEntityToOpenGL(center.x + x, center.y + y, x, y);
		glVertex2f(x, y);
	}

	theta = 2.0 * 3.1415926 * double(endAngle) / double(segments);
	x = radius*cosf(theta);
	y = radius*sinf(theta);
	this->convertEntityToOpenGL(center.x + x, center.y + y, x, y);
	glVertex2f(x, y);

	glEnd();
}

/////////////////////////////////////////////////////////

ShDrawer::ShDrawer(ShCADWidget *widget)
	:widget(widget) {

}

ShDrawer::~ShDrawer() {

}

/////////////////////////////////////////////////////////

ShDrawerUnSelectedEntity::ShDrawerUnSelectedEntity(ShCADWidget *widget)
	:ShDrawer(widget) {

}

ShDrawerUnSelectedEntity::~ShDrawerUnSelectedEntity() {

}

void ShDrawerUnSelectedEntity::visit(ShLine *line) {

	ShDrawerFunctions f(this->widget);

	ShLineData data = line->getData();
	ShPropertyData propertyData = line->getPropertyData();

	GLPoint start, end;
	f.convertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
	f.convertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);

	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);

	glLineStipple(1, propertyData.getLineStyle().getPattern());
	glEnable(GL_LINE_STIPPLE);
	f.drawLine(start, end, color);
	glDisable(GL_LINE_STIPPLE);
	
}

void ShDrawerUnSelectedEntity::visit(ShRubberBand *rubberBand) {

	if (rubberBand->isExist() == true) {
	
		ShDrawerFunctions f(this->widget);

		ShLineData data = rubberBand->getData();

		GLPoint start, end;
		f.convertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
		f.convertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);

		GLColor color(1.0, 153 / 255.0, 51 / 255.0);

		glLineStipple(1, 0x07FF);
		glEnable(GL_LINE_STIPPLE);
		f.drawLine(start, end, color);
		glDisable(GL_LINE_STIPPLE);
		
	}

}

///////////////////////////////////////////////////////////////

ShDrawerSelectedEntity::ShDrawerSelectedEntity(ShCADWidget *widget)
	:ShDrawer(widget) {

}

ShDrawerSelectedEntity::~ShDrawerSelectedEntity() {

}
///////////////////////////////////////////////////////////////

ShDrawerSelectedEntityVertex::ShDrawerSelectedEntityVertex(ShCADWidget *widget)
	:ShDrawerSelectedEntity(widget) {

}

ShDrawerSelectedEntityVertex::~ShDrawerSelectedEntityVertex() {

}

void ShDrawerSelectedEntityVertex::visit(ShLine *line) {

	ShDrawerFunctions f(this->widget);

	ShLineData data = line->getData();

	GLPoint start, end;

	f.convertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
	f.convertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);

	f.drawLine(start, end, GLColor(0, 0, 0));

	glLineStipple(1, 0xF1F1);
	glEnable(GL_LINE_STIPPLE);

	f.drawLine(start, end, GLColor(153.f / 255, 153.f / 155, 1.f));
	glDisable(GL_LINE_STIPPLE);

	int startX, startY, midX, midY, endX, endY;
	f.convertEntityToDevice(data.start.x, data.start.y, startX, startY);
	f.convertEntityToDevice(data.end.x, data.end.y, endX, endY);
	f.convertEntityToDevice(line->getMid().x, line->getMid().y, midX, midY);

	GLPoint topLeft, bottomRight;
	f.convertDeviceToOpenGL(startX - 3, startY - 3, topLeft.x, topLeft.y);
	f.convertDeviceToOpenGL(startX + 3, startY + 3, bottomRight.x, bottomRight.y);
	f.drawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

	f.convertDeviceToOpenGL(midX - 3, midY - 3, topLeft.x, topLeft.y);
	f.convertDeviceToOpenGL(midX + 3, midY + 3, bottomRight.x, bottomRight.y);
	f.drawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

	f.convertDeviceToOpenGL(endX - 3, endY - 3, topLeft.x, topLeft.y);
	f.convertDeviceToOpenGL(endX + 3, endY + 3, bottomRight.x, bottomRight.y);
	f.drawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));
}




ShDrawerSelectedEntityNoVertex::ShDrawerSelectedEntityNoVertex(ShCADWidget *widget)
	:ShDrawerSelectedEntity(widget) {

}

ShDrawerSelectedEntityNoVertex::~ShDrawerSelectedEntityNoVertex() {

}

void ShDrawerSelectedEntityNoVertex::visit(ShLine *line) {

	ShDrawerFunctions f(this->widget);

	ShLineData data = line->getData();

	GLPoint start, end;

	f.convertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
	f.convertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);

	f.drawLine(start, end, GLColor(0, 0, 0));

	glLineStipple(1, 0xF1F1);
	glEnable(GL_LINE_STIPPLE);

	f.drawLine(start, end, GLColor(153.f / 255, 153.f / 155, 1.f));
	glDisable(GL_LINE_STIPPLE);

}

#include "ShDrawer.h"
#include "Interface\ShCADWidget.h"
#include "Base\ShMath.h"
#include <qdebug.h>
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Entity\Composite\Dim\ShDimLinear.h"
#include <qpainter.h>
#include "Data\ShScrollPosition.h"
#include "Interface\Private\ShAxis.h"
#include "Entity\Private\ShDimDrawer.h"

ShDrawerSelectedEntityFactory::ShDrawerSelectedEntityFactory() {

}

ShDrawerSelectedEntityFactory::~ShDrawerSelectedEntityFactory() {

}

ShDrawerSelectedEntity* ShDrawerSelectedEntityFactory::create(ShCADWidget *widget, QPainter *painter, ActionType actionType) {
	qDebug() << "create" << actionType;

	if (actionType == ActionType::ActionModifyMove ||
		actionType == ActionType::ActionModifyCopy ||
		actionType == ActionType::ActionModifyRotate ||
		actionType == ActionType::ActionModifyMirror ||
		actionType == ActionType::ActionModifyExtend ||
		actionType == ActionType::ActionModifyStretch ||
		actionType == ActionType::ActionModifyTrim ||
		actionType == ActionType::ActionModifyErase ||
		actionType == ActionType::ActionModifyScale) {

		return new ShDrawerSelectedEntityNoVertex(widget, painter);
	}

	return new ShDrawerSelectedEntityVertex(widget, painter);
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

void ShDrawerFunctions::drawDot(const GLPoint &point, const GLColor &color) {

	glColor3f(color.red, color.green, color.blue);

	glBegin(GL_POINTS);
	glVertex2f(point.x, point.y);
	glEnd();
}

void ShDrawerFunctions::drawFilledTriangle(const GLPoint &p1, const GLPoint &p2, const GLPoint &p3, const GLColor &color) {

	glColor3f(color.red, color.green, color.blue);

	glBegin(GL_POLYGON);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glVertex2f(p3.x, p3.y);
	glEnd();
}

/////////////////////////////////////////////////////////

ShDrawer::ShDrawer(ShCADWidget *widget, QPainter *painter)
	:widget(widget), painter(painter) {

}

ShDrawer::~ShDrawer() {

}

/////////////////////////////////////////////////////////

ShDrawerUnSelectedEntity::ShDrawerUnSelectedEntity(ShCADWidget *widget, QPainter *painter)
	:ShDrawer(widget, painter) {

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

void ShDrawerUnSelectedEntity::visit(ShCircle *circle) {

	ShDrawerFunctions f(this->widget);

	ShCircleData data = circle->getData();
	ShPropertyData propertyData = circle->getPropertyData();

	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);

	glLineStipple(1, propertyData.getLineStyle().getPattern());
	glEnable(GL_LINE_STIPPLE);
	f.drawCircle(data.center, data.radius, color);
	glDisable(GL_LINE_STIPPLE);
}

void ShDrawerUnSelectedEntity::visit(ShArc *arc) {

	ShDrawerFunctions f(this->widget);

	ShArcData data = arc->getData();
	ShPropertyData propertyData = arc->getPropertyData();

	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);

	glLineStipple(1, propertyData.getLineStyle().getPattern());
	glEnable(GL_LINE_STIPPLE);

	if (math::compare(data.startAngle, data.endAngle) == 1) {
		f.drawArc(data.center, data.radius, data.startAngle, 360, color);
		f.drawArc(data.center, data.radius, 0, data.endAngle, color);
	}
	else {
	
		f.drawArc(data.center, data.radius, data.startAngle, data.endAngle, color);
	}

	glDisable(GL_LINE_STIPPLE);
}

void ShDrawerUnSelectedEntity::visit(ShDimLinear *dimLinear) {

	ShDimDrawer visitor(this->widget, this->painter);

	dimLinear->accept(&visitor);
}


///////////////////////////////////////////////////////////////

ShDrawerSelectedEntity::ShDrawerSelectedEntity(ShCADWidget *widget, QPainter *painter)
	:ShDrawer(widget, painter) {

}

ShDrawerSelectedEntity::~ShDrawerSelectedEntity() {

}
///////////////////////////////////////////////////////////////

ShDrawerSelectedEntityVertex::ShDrawerSelectedEntityVertex(ShCADWidget *widget, QPainter *painter)
	:ShDrawerSelectedEntity(widget, painter) {

}

ShDrawerSelectedEntityVertex::~ShDrawerSelectedEntityVertex() {

}

void ShDrawerSelectedEntityVertex::visit(ShLine *line) {

	ShDrawerFunctions f(this->widget);

	ShLineData data = line->getData();

	GLPoint start, end;

	f.convertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
	f.convertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);


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

void ShDrawerSelectedEntityVertex::visit(ShCircle *circle) {

	ShDrawerFunctions f(this->widget);

	ShCircleData data = circle->getData();
	
	glLineStipple(1, 0xF1F1);
	glEnable(GL_LINE_STIPPLE);

	f.drawCircle(data.center, data.radius, GLColor(153.f / 255, 153.f / 155, 1.f));
	glDisable(GL_LINE_STIPPLE);

	int centerX, centerY, centerPlusRadiusX, centerPlusRadiusY;
	f.convertEntityToDevice(data.center.x, data.center.y, centerX, centerY);
	f.convertEntityToDevice(data.center.x + data.radius, data.center.y, centerPlusRadiusX, centerPlusRadiusY);

	int deviceRadius = (int)math::getDistance(centerX, centerY, centerPlusRadiusX, centerPlusRadiusY);

	GLPoint topLeft, bottomRight;
	f.convertDeviceToOpenGL(centerX - 3, centerY - 3, topLeft.x, topLeft.y);
	f.convertDeviceToOpenGL(centerX + 3, centerY + 3, bottomRight.x, bottomRight.y);
	f.drawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

	f.convertDeviceToOpenGL(centerX + deviceRadius - 3, centerY - 3, topLeft.x, topLeft.y);
	f.convertDeviceToOpenGL(centerX + deviceRadius + 3, centerY + 3, bottomRight.x, bottomRight.y);
	f.drawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

	f.convertDeviceToOpenGL(centerX - deviceRadius - 3, centerY - 3, topLeft.x, topLeft.y);
	f.convertDeviceToOpenGL(centerX - deviceRadius + 3, centerY + 3, bottomRight.x, bottomRight.y);
	f.drawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

	f.convertDeviceToOpenGL(centerX - 3, centerY + deviceRadius - 3, topLeft.x, topLeft.y);
	f.convertDeviceToOpenGL(centerX + 3, centerY + deviceRadius + 3, bottomRight.x, bottomRight.y);
	f.drawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

	f.convertDeviceToOpenGL(centerX - 3, centerY - deviceRadius - 3, topLeft.x, topLeft.y);
	f.convertDeviceToOpenGL(centerX + 3, centerY - deviceRadius + 3, bottomRight.x, bottomRight.y);
	f.drawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));
}


void ShDrawerSelectedEntityVertex::visit(ShArc *arc) {

	ShDrawerFunctions f(this->widget);

	ShArcData data = arc->getData();
	
	glLineStipple(1, 0xF1F1);
	glEnable(GL_LINE_STIPPLE);

	if (math::compare(data.startAngle, data.endAngle) == 1) {
		f.drawArc(data.center, data.radius, data.startAngle, 360, GLColor(153.f / 255, 153.f / 155, 1.f));
		f.drawArc(data.center, data.radius, 0, data.endAngle, GLColor(153.f / 255, 153.f / 155, 1.f));
	}
	else {
	
		f.drawArc(data.center, data.radius, data.startAngle, data.endAngle, GLColor(153.f / 255, 153.f / 155, 1.f));
	}

	glDisable(GL_LINE_STIPPLE);

	int x, y;
	GLPoint topLeft, bottomRight;

	f.convertEntityToDevice(data.center.x, data.center.y, x, y);
	f.convertDeviceToOpenGL(x - 3, y - 3, topLeft.x, topLeft.y);
	f.convertDeviceToOpenGL(x + 3, y + 3, bottomRight.x, bottomRight.y);
	f.drawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

	f.convertEntityToDevice(arc->getStart().x, arc->getStart().y, x, y);
	f.convertDeviceToOpenGL(x - 3, y - 3, topLeft.x, topLeft.y);
	f.convertDeviceToOpenGL(x + 3, y + 3, bottomRight.x, bottomRight.y);
	f.drawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

	f.convertEntityToDevice(arc->getEnd().x, arc->getEnd().y, x, y);
	f.convertDeviceToOpenGL(x - 3, y - 3, topLeft.x, topLeft.y);
	f.convertDeviceToOpenGL(x + 3, y + 3, bottomRight.x, bottomRight.y);
	f.drawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

	f.convertEntityToDevice(arc->getMid().x, arc->getMid().y, x, y);
	f.convertDeviceToOpenGL(x - 3, y - 3, topLeft.x, topLeft.y);
	f.convertDeviceToOpenGL(x + 3, y + 3, bottomRight.x, bottomRight.y);
	f.drawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

}

//////////////////////////////////////////////////////////////////////////////////////////

ShDrawerSelectedEntityNoVertex::ShDrawerSelectedEntityNoVertex(ShCADWidget *widget, QPainter *painter)
	:ShDrawerSelectedEntity(widget, painter) {

}

ShDrawerSelectedEntityNoVertex::~ShDrawerSelectedEntityNoVertex() {

}

void ShDrawerSelectedEntityNoVertex::visit(ShLine *line) {

	ShDrawerFunctions f(this->widget);

	ShLineData data = line->getData();

	GLPoint start, end;

	f.convertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
	f.convertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);


	glLineStipple(1, 0xF1F1);
	glEnable(GL_LINE_STIPPLE);

	f.drawLine(start, end, GLColor(153.f / 255, 153.f / 155, 1.f));
	glDisable(GL_LINE_STIPPLE);

}

void ShDrawerSelectedEntityNoVertex::visit(ShCircle *circle) {

	ShDrawerFunctions f(this->widget);

	ShCircleData data = circle->getData();
	
	glLineStipple(1, 0xF1F1);
	glEnable(GL_LINE_STIPPLE);

	f.drawCircle(data.center, data.radius, GLColor(153.f / 255, 153.f / 155, 1.f));
	glDisable(GL_LINE_STIPPLE);
}

void ShDrawerSelectedEntityNoVertex::visit(ShArc *arc) {

	ShDrawerFunctions f(this->widget);

	ShArcData data = arc->getData();

	glLineStipple(1, 0xF1F1);
	glEnable(GL_LINE_STIPPLE);

	if (math::compare(data.startAngle, data.endAngle) == 1) {
		f.drawArc(data.center, data.radius, data.startAngle, 360, GLColor(153.f / 255, 153.f / 155, 1.f));
		f.drawArc(data.center, data.radius, 0, data.endAngle, GLColor(153.f / 255, 153.f / 155, 1.f));
	}
	else {

		f.drawArc(data.center, data.radius, data.startAngle, data.endAngle, GLColor(153.f / 255, 153.f / 155, 1.f));
	}

	glDisable(GL_LINE_STIPPLE);
}

//////////////////////////////////////////////////////////////////////

ShDrawerEraseBackGround::ShDrawerEraseBackGround(ShCADWidget *widget, QPainter *painter)
	:ShDrawer(widget, painter) {

}

ShDrawerEraseBackGround::~ShDrawerEraseBackGround() {

}


void ShDrawerEraseBackGround::visit(ShLine *line) {

	ShDrawerFunctions f(this->widget);

	ShLineData data = line->getData();

	GLPoint start, end;

	f.convertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
	f.convertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);

	f.drawLine(start, end, GLColor(0, 0, 0));
}

void ShDrawerEraseBackGround::visit(ShCircle *circle) {

	ShDrawerFunctions f(this->widget);

	f.drawCircle(circle->getCenter(), circle->getRadius(), GLColor(0, 0, 0));
}

void ShDrawerEraseBackGround::visit(ShArc *arc) {

	ShDrawerFunctions f(this->widget);

	ShArcData data = arc->getData();

	if (math::compare(data.startAngle, data.endAngle) == 1) {
		f.drawArc(data.center, data.radius, data.startAngle, 360, GLColor(0, 0, 0));
		f.drawArc(data.center, data.radius, 0, data.endAngle, GLColor(0, 0, 0));
	}
	else {

		f.drawArc(data.center, data.radius, data.startAngle, data.endAngle, GLColor(0, 0, 0));
	}
}


//////////////////////////////////////////////////////////////////////////


ShApparentExtensionDrawer::ShApparentExtensionDrawer(ShCADWidget *widget, QPainter *painter)
	:ShDrawer(widget, painter) {

}


ShApparentExtensionDrawer::~ShApparentExtensionDrawer() {

}

void ShApparentExtensionDrawer::visit(ShLine *line) {

	if (painter->isActive() == false)
		painter->begin(this->widget);
	
	int dx, dy, dx2, dy2;

	QPen oldPen = painter->pen();
	QPen pen;
	pen.setWidth(2);
	pen.setStyle(Qt::PenStyle::DotLine);
	pen.setColor(QColor(000, 204, 000));
	painter->setPen(pen);

	this->widget->convertEntityToDevice(this->start.x, this->start.y, dx, dy);
	this->widget->convertEntityToDevice(this->end.x, this->end.y, dx2, dy2);

	painter->drawLine(dx, dy, dx2, dy2);

	painter->setPen(oldPen);
}

void ShApparentExtensionDrawer::visit(ShCircle *circle) {

}

void ShApparentExtensionDrawer::visit(ShArc *arc) {

	if (painter->isActive() == false)
		painter->begin(this->widget);

	int centerX, centerY, radiusX, radiusY, radius;

	this->widget->convertEntityToDevice(arc->getCenter().x, arc->getCenter().y, centerX, centerY);
	this->widget->convertEntityToDevice(arc->getCenter().x + arc->getRadius(), arc->getCenter().y, radiusX, radiusY);

	radius = math::toInt(math::getDistance(centerX, centerY, radiusX, radiusY));
	
	QRectF rect(centerX - radius, centerY - radius, radius * 2, radius * 2);
	
	double startAngle = math::getAbsAngle(arc->getCenter().x, arc->getCenter().y, this->start.x, this->start.y);
	double endAngle = math::getAbsAngle(arc->getCenter().x, arc->getCenter().y, this->end.x, this->end.y);
	double disAngle;

	if (this->start == arc->getStart())
		disAngle = math::getAngleDifference(endAngle, startAngle);
	else
		disAngle = math::getAngleDifference(startAngle, endAngle);

	QPen oldPen = painter->pen();
	QPen pen;
	pen.setWidth(2);
	pen.setStyle(Qt::PenStyle::DotLine);
	pen.setColor(QColor(000, 204, 000));
	painter->setPen(pen);

	if (this->start == arc->getStart())
		painter->drawArc(rect, math::toInt(endAngle * 16), math::toInt(disAngle * 16));
	else
		painter->drawArc(rect, math::toInt(startAngle * 16), math::toInt(disAngle * 16));

	painter->setPen(oldPen);

}
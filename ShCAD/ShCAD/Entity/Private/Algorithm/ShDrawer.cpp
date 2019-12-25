
#include "ShDrawer.h"
#include "Interface\ShCADWidget.h"
#include "Base\ShMath.h"
#include <qdebug.h>
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShConstructionLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Entity\Leaf\ShPoint.h"
#include "Entity\Leaf\ShDot.h"
#include "Entity\Composite\Dim\ShDimLinear.h"
#include "Entity\Composite\Dim\ShDimAligned.h"
#include "Entity\Composite\Dim\ShDimRadius.h"
#include "Entity\Composite\Dim\ShDimDiameter.h"
#include "Entity\Composite\Dim\ShDimArcLength.h"
#include "Entity\Composite\Dim\ShDimAngular.h"
#include <qpainter.h>
#include "Data\ShScrollPosition.h"
#include "Interface\Private\ShAxis.h"
#include "Base\ShPointStyle.h"
#include "Base\ShDimensionStyle.h"

ShDrawerSelectedEntityFactory::ShDrawerSelectedEntityFactory() {

}

ShDrawerSelectedEntityFactory::~ShDrawerSelectedEntityFactory() {

}

ShDrawerSelectedEntity* ShDrawerSelectedEntityFactory::create(ShCADWidget *widget, QPainter *painter, ActionType actionType) {
	qDebug() << "ShDrawerSelectedEntityFactory::create" << actionType;

	if (actionType == ActionType::ActionModifyMove ||
		actionType == ActionType::ActionModifyCopy ||
		actionType == ActionType::ActionModifyRotate ||
		actionType == ActionType::ActionModifyMirror ||
		actionType == ActionType::ActionModifyExtend ||
		actionType == ActionType::ActionModifyStretch ||
		actionType == ActionType::ActionModifyTrim ||
		actionType == ActionType::ActionModifyErase ||
		actionType == ActionType::ActionModifyScale ||
		actionType == ActionType::ActionModifyOffset) {

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

void ShDrawerFunctions::drawTriangle(const GLPoint &p1, const GLPoint &p2, const GLPoint &p3, const GLColor &color) {

	glColor3f(color.red, color.green, color.blue);

	glBegin(GL_LINES);
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

void ShDrawer::drawLine(ShLine *line, const GLColor &color, const GLushort &pattern) {

	ShDrawerFunctions f(this->widget);

	ShLineData data = line->getData();
	
	GLPoint start, end;
	f.convertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
	f.convertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);

	glLineStipple(1, pattern);
	glEnable(GL_LINE_STIPPLE);
	f.drawLine(start, end, color);
	glDisable(GL_LINE_STIPPLE);
}

void ShDrawer::drawCircle(ShCircle *circle, const GLColor &color, const GLushort &pattern) {

	ShDrawerFunctions f(this->widget);

	ShCircleData data = circle->getData();
	
	glLineStipple(1, pattern);
	glEnable(GL_LINE_STIPPLE);
	f.drawCircle(data.center, data.radius, color);
	glDisable(GL_LINE_STIPPLE);
}

void ShDrawer::drawArc(ShArc *arc, const GLColor &color, const GLushort &pattern) {

	ShDrawerFunctions f(this->widget);

	ShArcData data = arc->getData();
	
	glLineStipple(1, pattern);
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

void ShDrawer::drawDot(ShDot *dot, const GLColor &color, const GLushort &pattern) {

	ShDrawerFunctions f(this->widget);

	GLPoint glPoint;

	f.convertEntityToOpenGL(dot->getPosition().x, dot->getPosition().y, glPoint.x, glPoint.y);
	f.drawDot(glPoint, color);
}


void ShDrawer::drawConstructionLine(ShConstructionLine *constructionLine, const GLColor &color, const GLushort &pattern) {

	ShDrawerFunctions f(this->widget);

	ShLineData data = constructionLine->getData();
	
	ShPoint3d topLeft, bottomRight;
	this->widget->convertDeviceToEntity(0, 0, topLeft.x, topLeft.y);
	this->widget->convertDeviceToEntity(this->widget->width(), this->widget->height(), bottomRight.x, bottomRight.y);

	double slope, interceptY;
	math::getEquationLine(data.start, data.end, slope, interceptY);

	double y = slope*topLeft.x + interceptY;
	double y2 = slope*bottomRight.x + interceptY;

	GLPoint start, end;

	if (slope != 0) {
		f.convertEntityToOpenGL(topLeft.x, y, start.x, start.y);
		f.convertEntityToOpenGL(bottomRight.x, y2, end.x, end.y);
	}
	else {
		f.convertEntityToOpenGL(data.start.x, topLeft.y, start.x, start.y);
		f.convertEntityToOpenGL(data.end.x, bottomRight.y, end.x, end.y);
	}

	glLineStipple(1, pattern);
	glEnable(GL_LINE_STIPPLE);
	f.drawLine(start, end, color);
	glDisable(GL_LINE_STIPPLE);
}

void ShDrawer::drawDimLinearWithoutChild(ShDimLinear *dimLinear, const GLColor &color,const QColor &qColor, const GLushort &pattern) {

	ShDrawerFunctions f(this->widget);
	ShDimLinearData data = dimLinear->getData();
	ShPropertyData propertyData = dimLinear->getPropertyData();
	
	glLineStipple(1, pattern);
	glEnable(GL_LINE_STIPPLE);
	dimLinear->getDimensionStyle()->getDimensionArrowStyle().drawLineArrow(f, data.firstDim, data.secondDim, color);
	glDisable(GL_LINE_STIPPLE);
	

	int dx, dy;
	f.convertEntityToDevice(data.text.x, data.text.y, dx, dy);
	double angle = math::getAbsAngle(data.firstOrigin.x, data.firstOrigin.y, data.firstDim.x, data.firstDim.y);
	double distance = dimLinear->getDistance();
	
	if (this->painter->isActive() == false)
		painter->begin(this->widget);

	dimLinear->getDimensionStyle()->getDimensionTextStyle().drawDimensionDistanceText(this->painter,
		dx, dy, angle - 90, distance, qColor, this->widget->getZoomRate());
}

void ShDrawer::drawDimAlignedWithoutChild(ShDimAligned *dimAligned, const GLColor &color, const QColor &qColor, const GLushort &pattern) {

	ShDrawerFunctions f(this->widget);
	ShDimAlignedData data = dimAligned->getData();
	ShPropertyData propertyData = dimAligned->getPropertyData();
	
	glLineStipple(1, pattern);
	glEnable(GL_LINE_STIPPLE);
	dimAligned->getDimensionStyle()->getDimensionArrowStyle().drawLineArrow(f, data.firstDim, data.secondDim, color);
	glDisable(GL_LINE_STIPPLE);

	int dx, dy;
	f.convertEntityToDevice(data.text.x, data.text.y, dx, dy);
	double angle = math::getAbsAngle(data.firstOrigin.x, data.firstOrigin.y, data.firstDim.x, data.firstDim.y);
	double distance = dimAligned->getDistance();
	

	if (this->painter->isActive() == false)
		this->painter->begin(this->widget);

	dimAligned->getDimensionStyle()->getDimensionTextStyle().drawDimensionDistanceText(this->painter,
		dx, dy, angle - 90, distance, qColor, this->widget->getZoomRate());
}

void ShDrawer::drawDimRadiusWithoutChild(ShDimRadius *dimRadius, const GLColor &color, const QColor &qColor, const GLushort &pattern) {

	ShDrawerFunctions f(this->widget);
	ShDimRadiusData data = dimRadius->getData();
	ShPropertyData propertyData = dimRadius->getPropertyData();
	
	double angle = math::getAbsAngle(data.dim.x, data.dim.y, data.text.x, data.text.y);

	glLineStipple(1, pattern);
	glEnable(GL_LINE_STIPPLE);
	dimRadius->getDimensionStyle()->getDimensionArrowStyle().drawArrow(f, data.dim, angle, color);
	glDisable(GL_LINE_STIPPLE);

	int dx, dy;
	f.convertEntityToDevice(data.text.x, data.text.y, dx, dy);
	angle = math::getAbsAngle(data.center.x, data.center.y, data.text.x, data.text.y);
	

	if (this->painter->isActive() == false)
		this->painter->begin(this->widget);

	dimRadius->getDimensionStyle()->getDimensionTextStyle().drawDimensionRadiusText(this->painter,
		dx, dy, angle, dimRadius->getRadius(), qColor, this->widget->getZoomRate());
}

void ShDrawer::drawDimDiameterWithoutChild(ShDimDiameter *dimDiameter, const GLColor &color, const QColor &qColor, const GLushort &pattern) {

	ShDrawerFunctions f(this->widget);
	ShDimDiameterData data = dimDiameter->getData();
	ShPropertyData propertyData = dimDiameter->getPropertyData();

	double angle = math::getAbsAngle(data.firstDim.x, data.firstDim.y, data.text.x, data.text.y);

	glLineStipple(1, pattern);
	glEnable(GL_LINE_STIPPLE);
	dimDiameter->getDimensionStyle()->getDimensionArrowStyle().drawArrow(f, data.firstDim, angle, color);

	if (dimDiameter->isCenterToTextDistanceShorterThanRadius() == false) {
		angle = math::getAbsAngle(data.firstDim.x, data.firstDim.y, data.secondDim.x, data.secondDim.y);
		dimDiameter->getDimensionStyle()->getDimensionArrowStyle().drawArrow(f, data.secondDim, angle, color);
	}
	glDisable(GL_LINE_STIPPLE);

	int dx, dy;
	f.convertEntityToDevice(data.text.x, data.text.y, dx, dy);
	angle = math::getAbsAngle(data.center.x, data.center.y, data.text.x, data.text.y);
	

	if (this->painter->isActive() == false)
		this->painter->begin(this->widget);

	dimDiameter->getDimensionStyle()->getDimensionTextStyle().drawDimensionDiameterText(this->painter,
		dx, dy, angle, dimDiameter->getDiameter(), qColor, this->widget->getZoomRate());
}

void ShDrawer::drawDimArcLengthWithoutChild(ShDimArcLength *dimArcLength, const GLColor &color, const QColor &qColor, const GLushort &pattern) {

	ShDrawerFunctions f(this->widget);
	ShDimArcLengthData data = dimArcLength->getData();
	ShPropertyData propertyData = dimArcLength->getPropertyData();
	
	glLineStipple(1, pattern);
	glEnable(GL_LINE_STIPPLE);
	dimArcLength->getDimensionStyle()->getDimensionArrowStyle().drawArcArrow(f, data.center, dimArcLength->getArcRadius(),
		dimArcLength->getArcStart(), dimArcLength->getArcEnd(), color);
	glDisable(GL_LINE_STIPPLE);

	int dx, dy;
	f.convertEntityToDevice(data.text.x, data.text.y, dx, dy);
	double angle = math::getAbsAngle(data.center.x, data.center.y, data.text.x, data.text.y);


	if (this->painter->isActive() == false)
		this->painter->begin(this->widget);

	dimArcLength->getDimensionStyle()->getDimensionTextStyle().drawDimensionArcLengthText(this->painter,
		dx, dy, angle - 90, dimArcLength->getArcLength(), qColor, this->widget->getZoomRate());
}

void ShDrawer::drawDimAngularWithoutChild(ShDimAngular *dimAngular, const GLColor &color, const QColor &qColor, const GLushort &pattern) {

	ShDrawerFunctions f(this->widget);
	ShDimAngularData data = dimAngular->getData();
	ShPropertyData propertyData = dimAngular->getPropertyData();
	
	glLineStipple(1, pattern);
	glEnable(GL_LINE_STIPPLE);
	dimAngular->getDimensionStyle()->getDimensionArrowStyle().drawArcArrow(f, data.center, dimAngular->getArcRadius(),
		dimAngular->getArcStart(), dimAngular->getArcEnd(), color);
	glDisable(GL_LINE_STIPPLE);

	int dx, dy;
	f.convertEntityToDevice(data.text.x, data.text.y, dx, dy);
	double angle = math::getAbsAngle(data.center.x, data.center.y, data.text.x, data.text.y);

	if (this->painter->isActive() == false)
		this->painter->begin(this->widget);

	dimAngular->getDimensionStyle()->getDimensionTextStyle().drawDimensionAngleText(this->painter,
		dx, dy, angle - 90, dimAngular->getAngle(), qColor, this->widget->getZoomRate());
}


/////////////////////////////////////////////////////////

ShDrawerUnSelectedEntity::ShDrawerUnSelectedEntity(ShCADWidget *widget, QPainter *painter)
	:ShDrawer(widget, painter) {

}

ShDrawerUnSelectedEntity::~ShDrawerUnSelectedEntity() {

}

void ShDrawerUnSelectedEntity::visit(ShLine *line) {

	ShPropertyData propertyData = line->getPropertyData();

	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);

	this->drawLine(line, color, propertyData.getLineStyle().getPattern());

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

	ShPropertyData propertyData = circle->getPropertyData();

	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);

	this->drawCircle(circle, color, propertyData.getLineStyle().getPattern());
}

void ShDrawerUnSelectedEntity::visit(ShArc *arc) {

	ShPropertyData propertyData = arc->getPropertyData();

	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);

	this->drawArc(arc, color, propertyData.getLineStyle().getPattern());
}

void ShDrawerUnSelectedEntity::visit(ShPoint *point) {

	QList<ShEntity*> list;
	ShPointStyle::getComponentDependsOnStyle(list, point);

	ShDrawerUnSelectedEntity visitor(this->widget, this->painter);

	for (int i = 0; i < list.size(); i++) {
		list.at(i)->setPropertyData(point->getPropertyData());
		list.at(i)->accept(&visitor);
	}

	
	while (list.isEmpty() == false)
		delete list.takeFirst();
}

void ShDrawerUnSelectedEntity::visit(ShDot *dot) {

	ShPropertyData propertyData = dot->getPropertyData();
	
	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);

	this->drawDot(dot, color, 0xFFFF);
}

void ShDrawerUnSelectedEntity::visit(ShDimLinear *dimLinear) {

	ShDrawerUnSelectedEntity visitor(this->widget, this->painter);

	auto itr = dimLinear->begin();

	for (itr; itr != dimLinear->end(); ++itr)
		(*itr)->accept(&visitor);

	ShPropertyData propertyData = dimLinear->getPropertyData();
	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);
	QColor qColor(propertyData.getColor().getRed(), propertyData.getColor().getGreen(), propertyData.getColor().getBlue());

	this->drawDimLinearWithoutChild(dimLinear, color, qColor, 0xFFFF);
}

void ShDrawerUnSelectedEntity::visit(ShDimAligned *dimAligned) {

	ShDrawerUnSelectedEntity visitor(this->widget, this->painter);

	auto itr = dimAligned->begin();

	for (itr; itr != dimAligned->end(); ++itr)
		(*itr)->accept(&visitor);

	ShPropertyData propertyData = dimAligned->getPropertyData();
	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);
	QColor qColor(propertyData.getColor().getRed(), propertyData.getColor().getGreen(), propertyData.getColor().getBlue());

	this->drawDimAlignedWithoutChild(dimAligned, color, qColor, 0xFFFF);
}

void ShDrawerUnSelectedEntity::visit(ShDimRadius *dimRadius) {

	ShDrawerUnSelectedEntity visitor(this->widget, this->painter);
	
	auto itr = dimRadius->begin();

	for (itr; itr != dimRadius->end(); ++itr)
		(*itr)->accept(&visitor);

	ShPropertyData propertyData = dimRadius->getPropertyData();
	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);
	QColor qColor(propertyData.getColor().getRed(), propertyData.getColor().getGreen(), propertyData.getColor().getBlue());

	this->drawDimRadiusWithoutChild(dimRadius, color, qColor, 0xFFFF);
}

void ShDrawerUnSelectedEntity::visit(ShDimDiameter *dimDiameter) {

	ShDrawerUnSelectedEntity visitor(this->widget, this->painter);

	auto itr = dimDiameter->begin();

	for (itr; itr != dimDiameter->end(); ++itr)
		(*itr)->accept(&visitor);

	ShPropertyData propertyData = dimDiameter->getPropertyData();
	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);
	QColor qColor(propertyData.getColor().getRed(), propertyData.getColor().getGreen(), propertyData.getColor().getBlue());

	this->drawDimDiameterWithoutChild(dimDiameter, color, qColor, 0xFFFF);
}

void ShDrawerUnSelectedEntity::visit(ShDimArcLength *dimArcLength) {

	ShDrawerUnSelectedEntity visitor(this->widget, this->painter);

	auto itr = dimArcLength->begin();

	for (itr; itr != dimArcLength->end(); ++itr)
		(*itr)->accept(&visitor);

	ShPropertyData propertyData = dimArcLength->getPropertyData();
	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);
	QColor qColor(propertyData.getColor().getRed(), propertyData.getColor().getGreen(), propertyData.getColor().getBlue());

	this->drawDimArcLengthWithoutChild(dimArcLength, color, qColor, 0xFFFF);
}

void ShDrawerUnSelectedEntity::visit(ShDimAngular *dimAngular) {

	ShDrawerUnSelectedEntity visitor(this->widget, this->painter);

	auto itr = dimAngular->begin();

	for (itr; itr != dimAngular->end(); ++itr)
		(*itr)->accept(&visitor);

	ShPropertyData propertyData = dimAngular->getPropertyData();
	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);
	QColor qColor(propertyData.getColor().getRed(), propertyData.getColor().getGreen(), propertyData.getColor().getBlue());

	this->drawDimAngularWithoutChild(dimAngular, color, qColor, 0xFFFF);
}

void ShDrawerUnSelectedEntity::visit(ShConstructionLine *constructionLine) {

	ShPropertyData propertyData = constructionLine->getPropertyData();
	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);

	this->drawConstructionLine(constructionLine, color, propertyData.getLineStyle().getPattern());
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

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);
	line->accept(&visitor);

	ShLineData data = line->getData();

	QList<ShPoint3d> points;
	points.append(data.start);
	points.append(data.end);
	points.append(line->getMid());

	this->drawVertex(points);
}

void ShDrawerSelectedEntityVertex::visit(ShCircle *circle) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);
	circle->accept(&visitor);

	ShDrawerFunctions f(this->widget);
	ShCircleData data = circle->getData();
	
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

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);
	arc->accept(&visitor);

	ShArcData data = arc->getData();

	QList<ShPoint3d> points;
	points.append(data.center);
	points.append(arc->getStart());
	points.append(arc->getEnd());
	points.append(arc->getMid());

	this->drawVertex(points);
	
}

void ShDrawerSelectedEntityVertex::visit(ShPoint *point) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);
	point->accept(&visitor);

	QList<ShPoint3d> points;
	points.append(point->getPosition());

	this->drawVertex(points);
}

void ShDrawerSelectedEntityVertex::visit(ShDot *dot) {

	QList<ShPoint3d> points;
	points.append(dot->getPosition());

	this->drawVertex(points);
}

void ShDrawerSelectedEntityVertex::visit(ShDimLinear *dimLinear) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);
	dimLinear->accept(&visitor);

	ShDimLinearData data = dimLinear->getData();

	QList<ShPoint3d> points;
	points.append(data.firstOrigin);
	points.append(data.secondOrigin);
	points.append(data.firstDim);
	points.append(data.secondDim);
	points.append(data.text);

	this->drawVertex(points);

}

void ShDrawerSelectedEntityVertex::visit(ShDimAligned *dimAligned) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);
	dimAligned->accept(&visitor);

	ShDimAlignedData data = dimAligned->getData();

	QList<ShPoint3d> points;
	points.append(data.firstOrigin);
	points.append(data.secondOrigin);
	points.append(data.firstDim);
	points.append(data.secondDim);
	points.append(data.text);

	this->drawVertex(points);
}

void ShDrawerSelectedEntityVertex::visit(ShDimRadius *dimRadius) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);
	dimRadius->accept(&visitor);

	ShDimRadiusData data = dimRadius->getData();

	QList<ShPoint3d> points;
	points.append(data.center);
	points.append(data.dim);
	points.append(data.text);

	this->drawVertex(points);
}

void ShDrawerSelectedEntityVertex::visit(ShDimDiameter *dimDiameter) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);
	dimDiameter->accept(&visitor);

	ShDimDiameterData data = dimDiameter->getData();

	QList<ShPoint3d> points;
	points.append(data.firstDim);
	points.append(data.text);
	points.append(data.secondDim);

	this->drawVertex(points);

}

void ShDrawerSelectedEntityVertex::visit(ShDimArcLength *dimArcLength) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);
	dimArcLength->accept(&visitor);

	ShDimArcLengthData data = dimArcLength->getData();

	QList<ShPoint3d> points;
	points.append(data.start);
	points.append(data.end);
	points.append(data.boundary);
	points.append(data.text);

	this->drawVertex(points);
}

void ShDrawerSelectedEntityVertex::visit(ShDimAngular *dimAngular) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);
	dimAngular->accept(&visitor);

	ShDimAngularData data = dimAngular->getData();

	QList<ShPoint3d> points;
	points.append(data.center);
	points.append(data.start);
	points.append(data.end);
	points.append(data.boundary);
	points.append(data.text);

	this->drawVertex(points);
}

void ShDrawerSelectedEntityVertex::visit(ShConstructionLine *constructionLine) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);
	constructionLine->accept(&visitor);

	ShLineData data = constructionLine->getData();

	QList<ShPoint3d> points;
	points.append(data.start);
	points.append(data.end);
	points.append(constructionLine->getMid());

	this->drawVertex(points);
}

void ShDrawerSelectedEntityVertex::drawVertex(const QList<ShPoint3d> points) {

	ShDrawerFunctions f(this->widget);
	int dx, dy;
	GLPoint topLeft, bottomRight;

	for (int i = 0; i < points.size(); i++) {
	
		f.convertEntityToDevice(points.at(i).x, points.at(i).y, dx, dy);
		f.convertDeviceToOpenGL(dx - 3, dy - 3, topLeft.x, topLeft.y);
		f.convertDeviceToOpenGL(dx + 3, dy + 3, bottomRight.x, bottomRight.y);
		f.drawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));
	}

}

//////////////////////////////////////////////////////////////////////////////////////////

ShDrawerSelectedEntityNoVertex::ShDrawerSelectedEntityNoVertex(ShCADWidget *widget, QPainter *painter)
	:ShDrawerSelectedEntity(widget, painter) {

}

ShDrawerSelectedEntityNoVertex::~ShDrawerSelectedEntityNoVertex() {

}

void ShDrawerSelectedEntityNoVertex::visit(ShLine *line) {

	this->drawLine(line, GLColor(153.f / 255, 153.f / 155, 1.f), 0xF1F1);

}

void ShDrawerSelectedEntityNoVertex::visit(ShCircle *circle) {

	this->drawCircle(circle, GLColor(153.f / 255, 153.f / 155, 1.f), 0xF1F1);
}

void ShDrawerSelectedEntityNoVertex::visit(ShArc *arc) {

	this->drawArc(arc, GLColor(153.f / 255, 153.f / 155, 1.f), 0xF1F1);
}

void ShDrawerSelectedEntityNoVertex::visit(ShPoint *point) {
	
	QList<ShEntity*> list;
	ShPointStyle::getComponentDependsOnStyle(list, point);

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);

	for (int i = 0; i < list.size(); i++) {
		list.at(i)->accept(&visitor);
	}

	while (list.isEmpty() == false)
		delete list.takeFirst();
}

void ShDrawerSelectedEntityNoVertex::visit(ShDot *dot) {

	this->drawDot(dot, GLColor(153.f / 255, 153.f / 155, 1.f), 0xF1F1);
}

void ShDrawerSelectedEntityNoVertex::visit(ShDimLinear *dimLinear) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);

	auto itr = dimLinear->begin();
	for (itr; itr != dimLinear->end(); ++itr)
		(*itr)->accept(&visitor);

	this->drawDimLinearWithoutChild(dimLinear, GLColor(153.f / 255, 153.f / 155, 1.f), QColor(153, 153, 155), 0xF1F1);
}

void ShDrawerSelectedEntityNoVertex::visit(ShDimAligned *dimAligned) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);

	auto itr = dimAligned->begin();
	for (itr; itr != dimAligned->end(); ++itr)
		(*itr)->accept(&visitor);

	this->drawDimAlignedWithoutChild(dimAligned, GLColor(153.f / 255, 153.f / 155, 1.f), QColor(153, 153, 155), 0xF1F1);
}

void ShDrawerSelectedEntityNoVertex::visit(ShDimRadius *dimRadius) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);

	auto itr = dimRadius->begin();
	for (itr; itr != dimRadius->end(); ++itr)
		(*itr)->accept(&visitor);

	this->drawDimRadiusWithoutChild(dimRadius, GLColor(153.f / 255, 153.f / 155, 1.f), QColor(153, 153, 155), 0xF1F1);
}

void ShDrawerSelectedEntityNoVertex::visit(ShDimDiameter *dimDiameter) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);

	auto itr = dimDiameter->begin();
	for (itr; itr != dimDiameter->end(); ++itr)
		(*itr)->accept(&visitor);

	this->drawDimDiameterWithoutChild(dimDiameter, GLColor(153.f / 255, 153.f / 155, 1.f), QColor(153, 153, 155), 0xF1F1);
}

void ShDrawerSelectedEntityNoVertex::visit(ShDimArcLength *dimArcLength) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);

	auto itr = dimArcLength->begin();
	for (itr; itr != dimArcLength->end(); ++itr)
		(*itr)->accept(&visitor);

	this->drawDimArcLengthWithoutChild(dimArcLength, GLColor(153.f / 255, 153.f / 155, 1.f), QColor(153, 153, 155), 0xF1F1);
}

void ShDrawerSelectedEntityNoVertex::visit(ShDimAngular *dimAngular) {

	ShDrawerSelectedEntityNoVertex visitor(this->widget, this->painter);

	auto itr = dimAngular->begin();
	for (itr; itr != dimAngular->end(); ++itr)
		(*itr)->accept(&visitor);

	this->drawDimAngularWithoutChild(dimAngular, GLColor(153.f / 255, 153.f / 155, 1.f), QColor(153, 153, 155), 0xF1F1);
}


void ShDrawerSelectedEntityNoVertex::visit(ShConstructionLine *constructionLine) {

	this->drawConstructionLine(constructionLine, GLColor(153.f / 255, 153.f / 155, 1.f), 0xF1F1);
}


//////////////////////////////////////////////////////////////////////

ShDrawerEraseBackGround::ShDrawerEraseBackGround(ShCADWidget *widget, QPainter *painter)
	:ShDrawer(widget, painter) {

}

ShDrawerEraseBackGround::~ShDrawerEraseBackGround() {

}


void ShDrawerEraseBackGround::visit(ShLine *line) {

	this->drawLine(line, GLColor(0, 0, 0), 0xFFFF);
}

void ShDrawerEraseBackGround::visit(ShCircle *circle) {

	this->drawCircle(circle, GLColor(0, 0, 0), 0xFFFF);
}

void ShDrawerEraseBackGround::visit(ShArc *arc) {

	this->drawArc(arc, GLColor(0, 0, 0), 0xFFFF);
}

void ShDrawerEraseBackGround::visit(ShPoint *point) {

	QList<ShEntity*> list;
	ShPointStyle::getComponentDependsOnStyle(list, point);

	ShDrawerEraseBackGround visitor(this->widget, this->painter);

	for (int i = 0; i < list.size(); i++) {
		list.at(i)->accept(&visitor);
	}

	while (list.isEmpty() == false)
		delete list.takeFirst();
}

void ShDrawerEraseBackGround::visit(ShDot *dot) {

	this->drawDot(dot, GLColor(0, 0, 0), 0xFFFF);
}

void ShDrawerEraseBackGround::visit(ShDimLinear *dimLinear) {

	ShDrawerEraseBackGround visitor(this->widget, this->painter);

	auto itr = dimLinear->begin();
	for (itr; itr != dimLinear->end(); ++itr)
		(*itr)->accept(&visitor);

	this->drawDimLinearWithoutChild(dimLinear, GLColor(0, 0, 0), QColor(0, 0, 0), 0xFFFF);
}

void ShDrawerEraseBackGround::visit(ShDimAligned *dimAligned) {

	ShDrawerEraseBackGround visitor(this->widget, this->painter);

	auto itr = dimAligned->begin();
	for (itr; itr != dimAligned->end(); ++itr)
		(*itr)->accept(&visitor);

	this->drawDimAlignedWithoutChild(dimAligned, GLColor(0, 0, 0), QColor(0, 0, 0), 0xFFFF);
}

void ShDrawerEraseBackGround::visit(ShDimRadius *dimRadius) {

	ShDrawerEraseBackGround visitor(this->widget, this->painter);

	auto itr = dimRadius->begin();
	for (itr; itr != dimRadius->end(); ++itr)
		(*itr)->accept(&visitor);

	this->drawDimRadiusWithoutChild(dimRadius, GLColor(0, 0, 0), QColor(0, 0, 0), 0xFFFF);
}

void ShDrawerEraseBackGround::visit(ShDimDiameter *dimDiameter) {

	ShDrawerEraseBackGround visitor(this->widget, this->painter);

	auto itr = dimDiameter->begin();
	for (itr; itr != dimDiameter->end(); ++itr)
		(*itr)->accept(&visitor);

	this->drawDimDiameterWithoutChild(dimDiameter, GLColor(0, 0, 0), QColor(0, 0, 0), 0xFFFF);
}

void ShDrawerEraseBackGround::visit(ShDimArcLength *dimArcLength) {

	ShDrawerEraseBackGround visitor(this->widget, this->painter);

	auto itr = dimArcLength->begin();
	for (itr; itr != dimArcLength->end(); ++itr)
		(*itr)->accept(&visitor);

	this->drawDimArcLengthWithoutChild(dimArcLength, GLColor(0, 0, 0), QColor(0, 0, 0), 0xFFFF);
}

void ShDrawerEraseBackGround::visit(ShDimAngular *dimAngular) {

	ShDrawerEraseBackGround visitor(this->widget, this->painter);

	auto itr = dimAngular->begin();
	for (itr; itr != dimAngular->end(); ++itr)
		(*itr)->accept(&visitor);

	this->drawDimAngularWithoutChild(dimAngular, GLColor(0, 0, 0), QColor(0, 0, 0), 0xFFFF);
}

void ShDrawerEraseBackGround::visit(ShConstructionLine *constructionLine) {

	this->drawConstructionLine(constructionLine, GLColor(0, 0, 0), 0xFFFF);
}

//////////////////////////////////////////////////////////////////////////


ShApparentExtensionDrawer::ShApparentExtensionDrawer(ShCADWidget *widget, QPainter *painter)
	:widget(widget), painter(painter) {

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
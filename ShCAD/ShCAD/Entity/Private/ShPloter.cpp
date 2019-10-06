
#include "ShPloter.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Leaf\ShPoint.h"
#include "Entity\Leaf\ShDot.h"
#include "Interface\ShCADWidget.h"
#include "Base\ShMath.h"
#include <qpainter.h>
#include "Base\ShPointStyle.h"

ShPloter::ShPloter(ShCADWidget *widget, QPainter *painter, double scale)
	:widget(widget), painter(painter), scale(scale) {

}

ShPloter::~ShPloter() {

}

void ShPloter::visit(ShLine *line) {

	QColor color;
	this->getColor(line, color);

	int startX, startY, endX, endY;
	this->widget->convertEntityToDevice(line->getStart().x, line->getStart().y, startX, startY);
	this->widget->convertEntityToDevice(line->getEnd().x, line->getEnd().y, endX, endY);

	this->painter->setPen(color);
	startX = math::toInt((double)startX*this->scale);
	startY = math::toInt((double)startY*this->scale);
	endX = math::toInt((double)endX*this->scale);
	endY = math::toInt((double)endY*this->scale);

	this->painter->drawLine(startX, startY, endX, endY);
}

void ShPloter::visit(ShCircle *circle) {

	QColor color;
	this->getColor(circle, color);

	int centerX, centerY, radiusX, radiusY;
	this->widget->convertEntityToDevice(circle->getCenter().x, circle->getCenter().y, centerX, centerY);
	this->widget->convertEntityToDevice(circle->getCenter().x + circle->getRadius(), circle->getCenter().y,
		radiusX, radiusY);

	int radius = math::getDistance(centerX, centerY, radiusX, radiusY);
	radius = math::toInt((double)radius * this->scale);
	centerX = math::toInt((double)centerX*this->scale);
	centerY = math::toInt((double)centerY*this->scale);

	this->painter->setPen(color);
	this->painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
}

void ShPloter::visit(ShArc *arc) {

	QColor color;
	this->getColor(arc, color);

	ShArcData data = arc->getData();
	int centerX, centerY, radiusX, radiusY, radius;

	this->widget->convertEntityToDevice(data.center.x, data.center.y, centerX, centerY);
	this->widget->convertEntityToDevice(data.center.x + data.radius, data.center.y, radiusX, radiusY);


	radius = math::getDistance(centerX, centerY, radiusX, radiusY);
	radius = math::toInt((double)(radius)*this->scale);
	centerX = math::toInt((double)(centerX)*this->scale);
	centerY = math::toInt((double)(centerY)*this->scale);

	double angleDifference = math::getAngleDifference(data.startAngle, data.endAngle);

	QRect rect(centerX - radius, centerY - radius, radius * 2, radius * 2);

	this->painter->setPen(color);

	this->painter->drawArc(rect, math::toInt(data.startAngle * 16), math::toInt(angleDifference * 16));
}

void ShPloter::visit(ShPoint *point) {

	QList<ShEntity*> list;
	ShPointStyle::getComponentDependsOnStyle(list, point);

	ShPloter visitor(this->widget, this->painter, this->scale);

	for (int i = 0; i < list.size(); i++)
		list.at(i)->accept(&visitor);
	

	while (list.isEmpty() == false)
		delete list.takeFirst();
}

void ShPloter::visit(ShDot *dot) {

	QColor color;
	this->getColor(dot, color);

	int x, y;
	this->widget->convertEntityToDevice(dot->getPosition().x, dot->getPosition().y, x, y);

	x = math::toInt((double)x*this->scale);
	y = math::toInt((double)y*this->scale);

	this->painter->setPen(color);
	this->painter->drawPoint(x, y);
}

void ShPloter::getColor(ShEntity *entity, QColor &color) {

	ShPropertyData propertyData = entity->getPropertyData();
	color = QColor(propertyData.getColor().getRed(), propertyData.getColor().getGreen(),
		propertyData.getColor().getBlue());

	if (color.red() == 255 && color.green() == 255 && color.blue() == 255) {
		color.setRed(0);
		color.setGreen(0);
		color.setBlue(0);
	}
}
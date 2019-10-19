
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
#include "Entity\Composite\Dim\ShDimLinear.h"
#include "Base\ShDimensionStyle.h"
#include "Entity\Composite\Dim\ShDimAligned.h"
#include "Entity\Composite\Dim\ShDimRadius.h"
#include "Entity\Composite\Dim\ShDimDiameter.h"
#include "Entity\Composite\Dim\ShDimArcLength.h"

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

	this->plotLine(startX, startY, endX, endY, color);
}

void ShPloter::visit(ShCircle *circle) {

	QColor color;
	this->getColor(circle, color);

	int centerX, centerY, radiusX, radiusY;
	this->widget->convertEntityToDevice(circle->getCenter().x, circle->getCenter().y, centerX, centerY);
	this->widget->convertEntityToDevice(circle->getCenter().x + circle->getRadius(), circle->getCenter().y,
		radiusX, radiusY);

	int radius = math::getDistance(centerX, centerY, radiusX, radiusY);
	
	this->plotCircle(centerX, centerY, radius, color);
}

void ShPloter::visit(ShArc *arc) {

	QColor color;
	this->getColor(arc, color);

	ShArcData data = arc->getData();
	int centerX, centerY, radiusX, radiusY, radius;

	this->widget->convertEntityToDevice(data.center.x, data.center.y, centerX, centerY);
	this->widget->convertEntityToDevice(data.center.x + data.radius, data.center.y, radiusX, radiusY);

	radius = math::getDistance(centerX, centerY, radiusX, radiusY);
	
	this->plotArc(centerX, centerY, radius, data.startAngle, data.endAngle, color);
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

	this->plotPoint(x, y, color);
}


void ShPloter::visit(ShDimLinear *dimLinear) {

	ShPloter visitor(this->widget, this->painter, this->scale);
	
	auto itr = dimLinear->begin();
	for (itr; itr != dimLinear->end(); ++itr)
		(*itr)->accept(&visitor);

	ShDimLinearData data = dimLinear->getData();
	QColor color;
	this->getColor(dimLinear, color);

	int x, y, x2, y2, x3, y3;
	ShPoint3d vertex, vertex2, vertex3;

	dimLinear->getFirstArrowPoints(vertex, vertex2, vertex3);
	this->widget->convertEntityToDevice(vertex.x, vertex.y, x, y);
	this->widget->convertEntityToDevice(vertex2.x, vertex2.y, x2, y2);
	this->widget->convertEntityToDevice(vertex3.x, vertex3.y, x3, y3);

	this->plotFilledTriangle(x, y, x2, y2, x3, y3, color);


	dimLinear->getSecondArrowPoints(vertex, vertex2, vertex3);
	this->widget->convertEntityToDevice(vertex.x, vertex.y, x, y);
	this->widget->convertEntityToDevice(vertex2.x, vertex2.y, x2, y2);
	this->widget->convertEntityToDevice(vertex3.x, vertex3.y, x3, y3);
	
	this->plotFilledTriangle(x, y, x2, y2, x3, y3, color);


	this->widget->convertEntityToDevice(data.text.x, data.text.y, x, y);
	double angle = math::getAbsAngle(data.firstOrigin.x, data.firstOrigin.y, data.firstDim.x, data.firstDim.y);
	double distance = dimLinear->getDistance();
	this->plotText(this->painter, x, y, angle - 90, QString::number(distance, 'f', 4),
		dimLinear->getDimensionStyle()->getDimensionTextStyle().getTextHeight(), color);
	
}

void ShPloter::visit(ShDimAligned *dimAligned) {

	ShPloter visitor(this->widget, this->painter, this->scale);

	auto itr = dimAligned->begin();
	for (itr; itr != dimAligned->end(); ++itr)
		(*itr)->accept(&visitor);

	ShDimAlignedData data = dimAligned->getData();
	QColor color;
	this->getColor(dimAligned, color);

	int x, y, x2, y2, x3, y3;
	ShPoint3d vertex, vertex2, vertex3;

	dimAligned->getFirstArrowPoints(vertex, vertex2, vertex3);
	this->widget->convertEntityToDevice(vertex.x, vertex.y, x, y);
	this->widget->convertEntityToDevice(vertex2.x, vertex2.y, x2, y2);
	this->widget->convertEntityToDevice(vertex3.x, vertex3.y, x3, y3);
	
	this->plotFilledTriangle(x, y, x2, y2, x3, y3, color);


	dimAligned->getSecondArrowPoints(vertex, vertex2, vertex3);
	this->widget->convertEntityToDevice(vertex.x, vertex.y, x, y);
	this->widget->convertEntityToDevice(vertex2.x, vertex2.y, x2, y2);
	this->widget->convertEntityToDevice(vertex3.x, vertex3.y, x3, y3);

	this->plotFilledTriangle(x, y, x2, y2, x3, y3, color);


	this->widget->convertEntityToDevice(data.text.x, data.text.y, x, y);
	double angle = math::getAbsAngle(data.firstOrigin.x, data.firstOrigin.y, data.firstDim.x, data.firstDim.y);
	double distance = dimAligned->getDistance();
	this->plotText(this->painter, x, y, angle - 90, QString::number(distance, 'f', 4),
		dimAligned->getDimensionStyle()->getDimensionTextStyle().getTextHeight(), color);
}

void ShPloter::visit(ShDimRadius *dimRadius) {

	ShPloter visitor(this->widget, this->painter, this->scale);

	auto itr = dimRadius->begin();
	for (itr; itr != dimRadius->end(); ++itr)
		(*itr)->accept(&visitor);

	ShDimRadiusData data = dimRadius->getData();
	QColor color;
	this->getColor(dimRadius, color);

	int x, y, x2, y2, x3, y3;
	ShPoint3d vertex, vertex2, vertex3;

	dimRadius->getArrowPoints(vertex, vertex2, vertex3);

	this->widget->convertEntityToDevice(vertex.x, vertex.y, x, y);
	this->widget->convertEntityToDevice(vertex2.x, vertex2.y, x2, y2);
	this->widget->convertEntityToDevice(vertex3.x, vertex3.y, x3, y3);

	this->plotFilledTriangle(x, y, x2, y2, x3, y3, color);

	this->widget->convertEntityToDevice(data.text.x, data.text.y, x, y);
	double angle = math::getAbsAngle(data.center.x, data.center.y, data.text.x, data.text.y);
	this->plotText(this->painter, x, y, angle, QString("R") + QString::number(dimRadius->getRadius(), 'f', 4),
		dimRadius->getDimensionStyle()->getDimensionTextStyle().getTextHeight(), color);
}

void ShPloter::visit(ShDimDiameter *dimDiameter) {

	ShPloter visitor(this->widget, this->painter, this->scale);

	auto itr = dimDiameter->begin();
	for (itr; itr != dimDiameter->end(); ++itr)
		(*itr)->accept(&visitor);

	ShDimDiameterData data = dimDiameter->getData();
	QColor color;
	this->getColor(dimDiameter, color);

	int x, y, x2, y2, x3, y3;
	ShPoint3d vertex, vertex2, vertex3;

	dimDiameter->getFirstArrowPoints(vertex, vertex2, vertex3);
	this->widget->convertEntityToDevice(vertex.x, vertex.y, x, y);
	this->widget->convertEntityToDevice(vertex2.x, vertex2.y, x2, y2);
	this->widget->convertEntityToDevice(vertex3.x, vertex3.y, x3, y3);
	this->plotFilledTriangle(x, y, x2, y2, x3, y3, color);

	if (dimDiameter->isCenterToTextDistanceShorterThanRadius() == false) {
	
		dimDiameter->getSecondArrowPoints(vertex, vertex2, vertex3);
		this->widget->convertEntityToDevice(vertex.x, vertex.y, x, y);
		this->widget->convertEntityToDevice(vertex2.x, vertex2.y, x2, y2);
		this->widget->convertEntityToDevice(vertex3.x, vertex3.y, x3, y3);
		this->plotFilledTriangle(x, y, x2, y2, x3, y3, color);
	}

	this->widget->convertEntityToDevice(data.text.x, data.text.y, x, y);
	double angle = math::getAbsAngle(data.center.x, data.center.y, data.text.x, data.text.y);
	this->plotText(this->painter, x, y, angle, QString(QString::fromLocal8Bit("¤±")) + QString::number(dimDiameter->getDiameter(), 'f', 4),
		dimDiameter->getDimensionStyle()->getDimensionTextStyle().getTextHeight(), color);
}

void ShPloter::visit(ShDimArcLength *dimArcLength) {

	ShPloter visitor(this->widget, this->painter, this->scale);

	auto itr = dimArcLength->begin();
	for (itr; itr != dimArcLength->end(); ++itr)
		(*itr)->accept(&visitor);

	ShDimArcLengthData data = dimArcLength->getData();
	QColor color;
	this->getColor(dimArcLength, color);

	int x, y, x2, y2, x3, y3;
	ShPoint3d vertex, vertex2, vertex3;

	dimArcLength->getFirstArrowPoints(vertex, vertex2, vertex3);
	this->widget->convertEntityToDevice(vertex.x, vertex.y, x, y);
	this->widget->convertEntityToDevice(vertex2.x, vertex2.y, x2, y2);
	this->widget->convertEntityToDevice(vertex3.x, vertex3.y, x3, y3);
	this->plotFilledTriangle(x, y, x2, y2, x3, y3, color);
	

	dimArcLength->getSecondArrowPoints(vertex, vertex2, vertex3);
	this->widget->convertEntityToDevice(vertex.x, vertex.y, x, y);
	this->widget->convertEntityToDevice(vertex2.x, vertex2.y, x2, y2);
	this->widget->convertEntityToDevice(vertex3.x, vertex3.y, x3, y3);
	this->plotFilledTriangle(x, y, x2, y2, x3, y3, color);


	this->widget->convertEntityToDevice(data.text.x, data.text.y, x, y);
	double angle = math::getAbsAngle(data.center.x, data.center.y, data.text.x, data.text.y);
	this->plotText(this->painter, x, y, angle - 90, QString(QString::fromLocal8Bit("¡û")) + QString::number(dimArcLength->getArcLength(), 'f', 4),
		dimArcLength->getDimensionStyle()->getDimensionTextStyle().getTextHeight(), color);

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

void ShPloter::plotLine(int startX, int startY, int endX, int endY, QColor &color) {

	this->painter->setPen(color);
	startX = math::toInt((double)startX*this->scale);
	startY = math::toInt((double)startY*this->scale);
	endX = math::toInt((double)endX*this->scale);
	endY = math::toInt((double)endY*this->scale);

	this->painter->drawLine(startX, startY, endX, endY);
}

void ShPloter::plotText(QPainter *painter, int dx, int dy, double angle, const QString &text, double textHeight, const QColor &color) {

	textHeight = textHeight*this->widget->getZoomRate();
	double width = textHeight * 10;
	double height = textHeight * 2;

	QPen pen = painter->pen();
	painter->setPen(color);
	QFont oldFont = painter->font();
	QFont font = painter->font();
	font.setPointSize(math::toInt(textHeight*this->scale));
	painter->setFont(font);

	painter->rotate(-angle);
	double rotateX, rotateY;
	math::rotate(angle, 0, 0, dx, dy, rotateX, rotateY);

	painter->drawText(math::toInt((rotateX - width / 2.0) *this->scale), math::toInt((rotateY - height)*this->scale),
		math::toInt(width*this->scale), math::toInt(height*this->scale), Qt::AlignCenter, text);
	painter->rotate(angle);
}

void ShPloter::plotCircle(int centerX, int centerY, int radius, const QColor &color) {

	radius = math::toInt((double)radius * this->scale);
	centerX = math::toInt((double)centerX*this->scale);
	centerY = math::toInt((double)centerY*this->scale);

	this->painter->setPen(color);
	this->painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
}

void ShPloter::plotArc(int centerX, int centerY, int radius, double startAngle, double endAngle, const QColor &color) {

	radius = math::toInt((double)(radius)*this->scale);
	centerX = math::toInt((double)(centerX)*this->scale);
	centerY = math::toInt((double)(centerY)*this->scale);

	double angleDifference = math::getAngleDifference(startAngle, endAngle);

	QRect rect(centerX - radius, centerY - radius, radius * 2, radius * 2);

	this->painter->setPen(color);

	this->painter->drawArc(rect, math::toInt(startAngle * 16), math::toInt(angleDifference * 16));
}

void ShPloter::plotFilledTriangle(int x, int y, int x2, int y2, int x3, int y3, const QColor &color) {

	x = math::toInt((double)x*this->scale);
	y = math::toInt((double)y*this->scale);
	x2 = math::toInt((double)x2*this->scale);
	y2 = math::toInt((double)y2*this->scale);
	x3 = math::toInt((double)x3*this->scale);
	y3 = math::toInt((double)y3*this->scale);

	QPainterPath path;
	QPen oldPen = this->painter->pen();
	this->painter->setPen(Qt::NoPen);

	path.moveTo(x, y);
	path.lineTo(x2, y2);
	path.lineTo(x3, y3);

	this->painter->fillPath(path, QBrush(color));

	this->painter->setPen(oldPen);
}

void ShPloter::plotPoint(int x, int y, const QColor &color) {

	x = math::toInt((double)x*this->scale);
	y = math::toInt((double)y*this->scale);

	this->painter->setPen(color);
	this->painter->drawPoint(x, y);
}
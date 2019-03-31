
#include "ShPrintVisitor.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Composite\ShPolyLine.h"

#include "Interface\ShGraphicView.h"
#include <qpainter.h>
#include "ShMath.h"
ShPrintVisitor::ShPrintVisitor(ShGraphicView *view, QPainter *painter, double scale)
	:view(view), painter(painter), scale(scale) {


}

ShPrintVisitor::~ShPrintVisitor() {


}

void ShPrintVisitor::Visit(ShLine *line) {

	QColor color;
	this->GetColor(line, color);

	int startX, endX, startY, endY;
	this->view->ConvertEntityToDevice(line->GetStart().x, line->GetStart().y, startX, startY);
	this->view->ConvertEntityToDevice(line->GetEnd().x, line->GetEnd().y, endX, endY);

	this->painter->setPen(color);
	startX = Math::ToInt((double)startX*this->scale);
	startY = Math::ToInt((double)startY*this->scale);
	endX = Math::ToInt((double)endX*this->scale);
	endY = Math::ToInt((double)endY*this->scale);

	this->painter->drawLine(startX, startY, endX, endY);
	

}

void ShPrintVisitor::Visit(ShCircle *circle) {

	QColor color;
	this->GetColor(circle, color);

	int centerX, centerY, radiusX, radiusY;
	this->view->ConvertEntityToDevice(circle->GetCenter().x, circle->GetCenter().y, centerX, centerY);
	this->view->ConvertEntityToDevice(circle->GetCenter().x + circle->GetRadius(), circle->GetCenter().y, 
		radiusX, radiusY);

	int radius = Math::GetDistance(centerX, centerY, radiusX, radiusY);
	radius = Math::ToInt((double)radius * this->scale);
	centerX = Math::ToInt((double)centerX*this->scale);
	centerY = Math::ToInt((double)centerY*this->scale);

	this->painter->setPen(color);
	this->painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

}

void ShPrintVisitor::Visit(ShArc *arc) {

	QColor color;
	this->GetColor(arc, color);

	ShArcData data = arc->GetData();
	int centerX, centerY, radiusX, radiusY, radius;

	this->view->ConvertEntityToDevice(data.center.x, data.center.y, centerX, centerY);
	this->view->ConvertEntityToDevice(data.center.x + data.radius, data.center.y, radiusX, radiusY);


	radius =Math::GetDistance(centerX, centerY, radiusX, radiusY);
	radius = Math::ToInt((double)(radius)*this->scale);
	centerX = Math::ToInt((double)(centerX)*this->scale);
	centerY = Math::ToInt((double)(centerY)*this->scale);

	double angleDifference = Math::GetAngleDifference(data.startAngle, data.endAngle);

	QRect rect(centerX - radius, centerY - radius, radius * 2, radius * 2);

	this->painter->setPen(color);

	this->painter->drawArc(rect, Math::ToInt(data.startAngle * 16), Math::ToInt(angleDifference * 16));

}

void ShPrintVisitor::Visit(ShPolyLine *polyLine) {

	ShPrintVisitor visitor(this->view, this->painter, this->scale);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = polyLine->Begin(); itr != polyLine->End(); ++itr)
		(*itr)->Accept(&visitor);

}

void ShPrintVisitor::GetColor(ShEntity *entity, QColor &color) {

	ShPropertyData propertyData = entity->GetPropertyData();
	color = QColor(propertyData.GetColor().GetRed(), propertyData.GetColor().GetGreen(),
		propertyData.GetColor().GetBlue());

	if (color.red() == 255 && color.green() == 255 && color.blue() == 255) {
		color.setRed(0);
		color.setGreen(0);
		color.setBlue(0);
	}
}
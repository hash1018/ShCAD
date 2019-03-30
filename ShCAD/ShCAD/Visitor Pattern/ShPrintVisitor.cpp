
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

}

void ShPrintVisitor::Visit(ShArc *arc) {

}

void ShPrintVisitor::Visit(ShPolyLine *polyLine) {


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
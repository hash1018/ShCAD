
#include "ShDimDrawer.h"
#include "Entity\Composite\Dim\ShDimLinear.h"
#include "Manager\ShDimStyleManager.h"
#include "Base\ShMath.h"
#include <qpainter.h>
#include "Interface\ShCADWidget.h"

ShDimDrawer::ShDimDrawer(ShCADWidget *widget, QPainter *painter)
	:ShDrawer(widget, painter) {

}

ShDimDrawer::~ShDimDrawer() {

}

void ShDimDrawer::visit(ShDimLinear *dimLinear) {

	double intervalFromBase = ShDimStyleManager::getInstance()->getIntervalFromBase();

	ShDimLinearData data = dimLinear->getData();
	ShPropertyData propertyData = dimLinear->getPropertyData();
	GLColor color(propertyData.getColor().getRed() / 255., propertyData.getColor().getGreen() / 255.,
		propertyData.getColor().getBlue() / 255.);


	ShPoint3d first, second;
	math::rotate(data.angle, data.first.x, data.first.y, data.first.x + intervalFromBase, data.first.y, first.x, first.y);
	double angle = math::getAbsAngle(data.second.x, data.second.y, data.second2.x, data.second2.y);
	math::rotate(angle, data.second.x, data.second.y, data.second.x + intervalFromBase, data.second.y, second.x, second.y);

	ShDrawerFunctions f(this->widget);

	GLPoint start, end, start2, end2;
	f.convertEntityToOpenGL(first.x, first.y, start.x, start.y);
	f.convertEntityToOpenGL(data.first2.x, data.first2.y, end.x, end.y);

	f.convertEntityToOpenGL(second.x, second.y, start2.x, start2.y);
	f.convertEntityToOpenGL(data.second2.x, data.second2.y, end2.x, end2.y);

	glLineStipple(1, propertyData.getLineStyle().getPattern());
	glEnable(GL_LINE_STIPPLE);

	f.drawLine(start, end, color);
	f.drawLine(start2, end2, color);
	f.drawLine(end, end2, color);
	glDisable(GL_LINE_STIPPLE);

	GLPoint dot;
	f.convertEntityToOpenGL(data.first.x, data.first.y, dot.x, dot.y);
	f.drawDot(dot, color);
	f.convertEntityToOpenGL(data.second.x, data.second.y, dot.x, dot.y);
	f.drawDot(dot, color);

	this->drawArrow(data.first2, data.second2, color);

	
	this->drawText(this->painter, data.distancePosition, data.angle - 90, QString::number(data.distance, 'f', 4), propertyData.getColor());
}


void ShDimDrawer::drawArrow(const ShPoint3d &start, const ShPoint3d &end, const GLColor &color) {


	ShDrawerFunctions f(this->widget);

	double distance = math::getDistance(start.x, start.y, end.x, end.y);
	double arrowSize = ShDimStyleManager::getInstance()->getArrowSize();
	double angle = math::getAbsAngle(start.x, start.y, end.x, end.y);
	double arrowHeight = arrowSize;
	double arrowBaseSize = arrowSize * 0.4;

	if (arrowSize > distance *2.5) {

		ShPoint3d vertex1, vertex2, vertex3;

		math::rotate(angle, start.x, start.y, start.x, start.y, vertex1.x, vertex1.y);
		math::rotate(angle, start.x, start.y, start.x - arrowHeight, start.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(angle, start.x, start.y, start.x - arrowHeight, start.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);


		GLPoint p1, p2, p3;
		f.convertEntityToOpenGL(vertex1.x, vertex1.y, p1.x, p1.y);
		f.convertEntityToOpenGL(vertex2.x, vertex2.y, p2.x, p2.y);
		f.convertEntityToOpenGL(vertex3.x, vertex3.y, p3.x, p3.y);
		f.drawFilledTriangle(p1, p2, p3, color);


		math::rotate(angle, end.x, end.y, end.x, end.y, vertex1.x, vertex1.y);
		math::rotate(angle, end.x, end.y, end.x + arrowHeight, end.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(angle, end.x, end.y, end.x + arrowHeight, end.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);

		f.convertEntityToOpenGL(vertex1.x, vertex1.y, p1.x, p1.y);
		f.convertEntityToOpenGL(vertex2.x, vertex2.y, p2.x, p2.y);
		f.convertEntityToOpenGL(vertex3.x, vertex3.y, p3.x, p3.y);
		f.drawFilledTriangle(p1, p2, p3, color);
	}
	else {

		ShPoint3d vertex1, vertex2, vertex3;

		math::rotate(angle, start.x, start.y, start.x, start.y, vertex1.x, vertex1.y);
		math::rotate(angle, start.x, start.y, start.x + arrowHeight, start.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(angle, start.x, start.y, start.x + arrowHeight, start.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);

		GLPoint p1, p2, p3;
		f.convertEntityToOpenGL(vertex1.x, vertex1.y, p1.x, p1.y);
		f.convertEntityToOpenGL(vertex2.x, vertex2.y, p2.x, p2.y);
		f.convertEntityToOpenGL(vertex3.x, vertex3.y, p3.x, p3.y);
		f.drawFilledTriangle(p1, p2, p3, color);


		math::rotate(angle, end.x, end.y, end.x, end.y, vertex1.x, vertex1.y);
		math::rotate(angle, end.x, end.y, end.x - arrowHeight, end.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(angle, end.x, end.y, end.x - arrowHeight, end.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);

		f.convertEntityToOpenGL(vertex1.x, vertex1.y, p1.x, p1.y);
		f.convertEntityToOpenGL(vertex2.x, vertex2.y, p2.x, p2.y);
		f.convertEntityToOpenGL(vertex3.x, vertex3.y, p3.x, p3.y);
		f.drawFilledTriangle(p1, p2, p3, color);
	}
}

void ShDimDrawer::drawText(QPainter *painter, const ShPoint3d &point, double angle, const QString &text, const ShColor &color) {

	if (painter->isActive() == false)
		painter->begin(this->widget);

	ShDrawerFunctions f(this->widget);

	int dx, dy;
	f.convertEntityToDevice(point.x, point.y, dx, dy);

	double textHeight = ShDimStyleManager::getInstance()->getTextHeight() *this->widget->getZoomRate();
	double width = textHeight * 10;
	double height = textHeight * 2;

	QPen pen = painter->pen();
	painter->setPen(QColor(color.getRed(), color.getGreen(), color.getBlue()));
	QFont oldFont = painter->font();
	QFont font = painter->font();
	font.setPointSize(math::toInt(textHeight));
	painter->setFont(font);

	painter->rotate(angle);
	double rotateX, rotateY;
	math::rotate(-angle, 0, 0, dx, dy, rotateX, rotateY);


	painter->drawText(math::toInt(rotateX) - math::toInt(width / 2.0), math::toInt(rotateY) - math::toInt(height), width, height, Qt::AlignCenter, text);
	painter->setPen(pen);
	painter->setFont(oldFont);
	painter->rotate(-angle);
	painter->end();
}
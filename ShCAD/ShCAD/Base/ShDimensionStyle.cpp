
#include "ShDimensionStyle.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShMath.h"
#include "Entity\Private\ShDrawer.h"
#include <qpainter.h>
#include "Entity\Composite\Dim\ShDim.h"

ShDimensionExtensionLineStyle::ShDimensionExtensionLineStyle()
	:offsetFromOrigin(10.0), extendBeyondDimensionLine(5.0), suppressExtensionLine(false), suppressExtensionLine2(false) {

}

ShDimensionExtensionLineStyle::ShDimensionExtensionLineStyle(double offsetFromOrigin, double extendBeyondDimensionLine, 
	bool suppressExtensionLine, bool suppressExtensionLine2)
	: offsetFromOrigin(offsetFromOrigin), extendBeyondDimensionLine(extendBeyondDimensionLine), 
	suppressExtensionLine(suppressExtensionLine), suppressExtensionLine2(suppressExtensionLine2) {

}

ShDimensionExtensionLineStyle::ShDimensionExtensionLineStyle(const ShDimensionExtensionLineStyle &other)
	: offsetFromOrigin(other.offsetFromOrigin), extendBeyondDimensionLine(other.extendBeyondDimensionLine),
	suppressExtensionLine(other.suppressExtensionLine), suppressExtensionLine2(other.suppressExtensionLine2) {

}

ShDimensionExtensionLineStyle::~ShDimensionExtensionLineStyle() {

}

ShDimensionExtensionLineStyle& ShDimensionExtensionLineStyle::operator=(const ShDimensionExtensionLineStyle &other) {

	this->offsetFromOrigin = other.offsetFromOrigin;
	this->extendBeyondDimensionLine = other.extendBeyondDimensionLine;
	this->suppressExtensionLine = other.suppressExtensionLine;
	this->suppressExtensionLine2 = other.suppressExtensionLine2;

	return *this;
}

ShLine* ShDimensionExtensionLineStyle::createExtensionLine(const ShPoint3d &origin, const ShPoint3d &dim, const ShPropertyData &propertyData, ShLayer *layer) const {

	if (this->suppressExtensionLine == true)
		return nullptr;

	ShPoint3d start, end;
	double angle = math::getAbsAngle(origin.x, origin.y, dim.x, dim.y);
	math::rotate(angle, origin.x, origin.y, origin.x + this->offsetFromOrigin, origin.y, start.x, start.y);
	math::rotate(angle, dim.x, dim.y, dim.x + this->extendBeyondDimensionLine, dim.y, end.x, end.y);

	return new ShLine(propertyData, ShLineData(start, end), layer);
}

ShLine* ShDimensionExtensionLineStyle::createExtensionLine2(const ShPoint3d &origin, const ShPoint3d &dim, const ShPropertyData &propertyData, ShLayer *layer) const {

	if (this->suppressExtensionLine2 == true)
		return nullptr;

	ShPoint3d start, end;
	double angle = math::getAbsAngle(origin.x, origin.y, dim.x, dim.y);
	math::rotate(angle, origin.x, origin.y, origin.x + this->offsetFromOrigin, origin.y, start.x, start.y);
	math::rotate(angle, dim.x, dim.y, dim.x + this->extendBeyondDimensionLine, dim.y, end.x, end.y);

	return new ShLine(propertyData, ShLineData(start, end), layer);
}

////////////////////////////////////////////////////////

ShDimensionLineStyle::ShDimensionLineStyle() {

}

ShDimensionLineStyle::~ShDimensionLineStyle() {

}

////////////////////////////////////////////////////////

ShDimensionArrowStyle::ShDimensionArrowStyle()
	:first(Arrowheads::ClosedFilled), second(Arrowheads::ClosedFilled), arrowSize(10.0) {

}

ShDimensionArrowStyle::ShDimensionArrowStyle(Arrowheads first, Arrowheads second, double arrowSize)
	: first(first), second(second), arrowSize(arrowSize) {

}

ShDimensionArrowStyle::ShDimensionArrowStyle(const ShDimensionArrowStyle &other)
	: first(other.first), second(other.second), arrowSize(other.arrowSize) {

}

ShDimensionArrowStyle::~ShDimensionArrowStyle() {

}

ShDimensionArrowStyle& ShDimensionArrowStyle::operator=(const ShDimensionArrowStyle &other) {

	this->first = other.first;
	this->second = other.second;
	this->arrowSize = other.arrowSize;

	return *this;
}

void ShDimensionArrowStyle::drawLineArrow(ShDrawerFunctions &drawerFunctions, const ShPoint3d &start, const ShPoint3d &end, const GLColor &color) const {

	ShPoint3d vertex1, vertex2, vertex3, vertex4, vertex5, vertex6;
	GLPoint first1, first2, first3, second1, second2, second3;

	this->getFirstLineArrowPoints(start, end, vertex1, vertex2, vertex3);
	this->getSecondLineArrowPoints(start, end, vertex4, vertex5, vertex6);

	drawerFunctions.convertEntityToOpenGL(vertex1.x, vertex1.y, first1.x, first1.y);
	drawerFunctions.convertEntityToOpenGL(vertex2.x, vertex2.y, first2.x, first2.y);
	drawerFunctions.convertEntityToOpenGL(vertex3.x, vertex3.y, first3.x, first3.y);
	drawerFunctions.convertEntityToOpenGL(vertex4.x, vertex4.y, second1.x, second1.y);
	drawerFunctions.convertEntityToOpenGL(vertex5.x, vertex5.y, second2.x, second2.y);
	drawerFunctions.convertEntityToOpenGL(vertex6.x, vertex6.y, second3.x, second3.y);

	if (this->first == Arrowheads::ClosedFilled) {
		drawerFunctions.drawFilledTriangle(first1, first2, first3, color);
		drawerFunctions.drawFilledTriangle(second1, second2, second3, color);
	}

	else if (this->first == Arrowheads::ClosedBlank) {
		drawerFunctions.drawTriangle(first1, first2, first3, color);
		drawerFunctions.drawTriangle(second1, second2, second3, color);
	}

}

void ShDimensionArrowStyle::drawArrow(ShDrawerFunctions &drawerFunctions, const ShPoint3d &point, double angle, const GLColor &color) const {

	ShPoint3d vertex1, vertex2, vertex3;

	this->getArrowPoints(point, angle, vertex1, vertex2, vertex3);

	GLPoint p1, p2, p3;
	drawerFunctions.convertEntityToOpenGL(vertex1.x, vertex1.y, p1.x, p1.y);
	drawerFunctions.convertEntityToOpenGL(vertex2.x, vertex2.y, p2.x, p2.y);
	drawerFunctions.convertEntityToOpenGL(vertex3.x, vertex3.y, p3.x, p3.y);

	if (this->first == Arrowheads::ClosedFilled) 
		drawerFunctions.drawFilledTriangle(p1, p2, p3, color);
	else if (this->first == Arrowheads::ClosedBlank) 
		drawerFunctions.drawTriangle(p1, p2, p3, color);
	
}

void ShDimensionArrowStyle::drawArcArrow(ShDrawerFunctions &drawerFunctions, const ShPoint3d &center, double radius,
	const ShPoint3d &start, const ShPoint3d &end, const GLColor &color) const {

	ShPoint3d vertex1, vertex2, vertex3, vertex4, vertex5, vertex6;
	GLPoint first1, first2, first3, second1, second2, second3;

	this->getFirstArcArrowPoints(center, radius, start, end, vertex1, vertex2, vertex3);
	this->getSecondArcArrowPoints(center, radius, start, end, vertex4, vertex5, vertex6);

	drawerFunctions.convertEntityToOpenGL(vertex1.x, vertex1.y, first1.x, first1.y);
	drawerFunctions.convertEntityToOpenGL(vertex2.x, vertex2.y, first2.x, first2.y);
	drawerFunctions.convertEntityToOpenGL(vertex3.x, vertex3.y, first3.x, first3.y);
	drawerFunctions.convertEntityToOpenGL(vertex4.x, vertex4.y, second1.x, second1.y);
	drawerFunctions.convertEntityToOpenGL(vertex5.x, vertex5.y, second2.x, second2.y);
	drawerFunctions.convertEntityToOpenGL(vertex6.x, vertex6.y, second3.x, second3.y);

	if (this->first == Arrowheads::ClosedFilled) {
		drawerFunctions.drawFilledTriangle(first1, first2, first3, color);
		drawerFunctions.drawFilledTriangle(second1, second2, second3, color);
	}

	else if (this->first == Arrowheads::ClosedBlank) {
		drawerFunctions.drawTriangle(first1, first2, first3, color);
		drawerFunctions.drawTriangle(second1, second2, second3, color);
	}
}


void ShDimensionArrowStyle::getFirstLineArrowPoints(const ShPoint3d &start, const ShPoint3d &end, ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) const {

	double distance = math::getDistance(start.x, start.y, end.x, end.y);
	double angle = math::getAbsAngle(start.x, start.y, end.x, end.y);
	double arrowHeight = this->arrowSize;
	double arrowBaseSize = arrowSize*0.4;

	if (this->arrowSize * 2 > distance) {

		math::rotate(angle, start.x, start.y, start.x, start.y, vertex.x, vertex.y);
		math::rotate(angle, start.x, start.y, start.x - arrowHeight, start.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(angle, start.x, start.y, start.x - arrowHeight, start.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);
	}
	else {
	
		math::rotate(angle, start.x, start.y, start.x, start.y, vertex.x, vertex.y);
		math::rotate(angle, start.x, start.y, start.x + arrowHeight, start.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(angle, start.x, start.y, start.x + arrowHeight, start.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);
	}
}

void ShDimensionArrowStyle::getSecondLineArrowPoints(const ShPoint3d &start, const ShPoint3d &end, ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) const {

	double distance = math::getDistance(start.x, start.y, end.x, end.y);
	double angle = math::getAbsAngle(start.x, start.y, end.x, end.y);
	double arrowHeight = this->arrowSize;
	double arrowBaseSize = arrowSize*0.4;

	if (this->arrowSize * 2 > distance) {

		math::rotate(angle, end.x, end.y, end.x, end.y, vertex.x, vertex.y);
		math::rotate(angle, end.x, end.y, end.x + arrowHeight, end.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(angle, end.x, end.y, end.x + arrowHeight, end.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);
	}
	else {

		math::rotate(angle, end.x, end.y, end.x, end.y, vertex.x, vertex.y);
		math::rotate(angle, end.x, end.y, end.x - arrowHeight, end.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(angle, end.x, end.y, end.x - arrowHeight, end.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);
	}
}

void ShDimensionArrowStyle::getArrowPoints(const ShPoint3d &point, double angle, ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) const {

	double arrowHeight = this->arrowSize;
	double arrowBaseSize = this->arrowSize * 0.4;

	math::rotate(angle, point.x, point.y, point.x, point.y, vertex.x, vertex.y);
	math::rotate(angle, point.x, point.y, point.x + arrowHeight, point.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
	math::rotate(angle, point.x, point.y, point.x + arrowHeight, point.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);
}

void ShDimensionArrowStyle::getFirstArcArrowPoints(const ShPoint3d &center, double radius, const ShPoint3d &start, const ShPoint3d &end,
	ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) const {

	double startAngle = math::getAbsAngle(center.x, center.y, start.x, start.y);
	double endAngle = math::getAbsAngle(center.x, center.y, end.x, end.y);
	double angleDifference = math::getAngleDifference(startAngle, endAngle);

	double arcLength = (2 * 3.1415926535897*radius)*(angleDifference / 360);
	double arrowHeight = this->arrowSize;
	double arrowBaseSize = this->arrowSize * 0.4;

	if (this->arrowSize * 2 > arcLength) {
	
		math::rotate(startAngle + 90, start.x, start.y, start.x, start.y, vertex.x, vertex.y);
		math::rotate(startAngle + 90, start.x, start.y, start.x - arrowHeight, start.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(startAngle + 90, start.x, start.y, start.x - arrowHeight, start.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);
	}
	else {

		math::rotate(startAngle + 90, start.x, start.y, start.x, start.y, vertex.x, vertex.y);
		math::rotate(startAngle + 90, start.x, start.y, start.x + arrowHeight, start.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(startAngle + 90, start.x, start.y, start.x + arrowHeight, start.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);
	}
}

void ShDimensionArrowStyle::getSecondArcArrowPoints(const ShPoint3d &center, double radius, const ShPoint3d &start, const ShPoint3d &end,
	ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) const {

	double startAngle = math::getAbsAngle(center.x, center.y, start.x, start.y);
	double endAngle = math::getAbsAngle(center.x, center.y, end.x, end.y);
	double angleDifference = math::getAngleDifference(startAngle, endAngle);

	double arcLength = (2 * 3.1415926535897*radius)*(angleDifference / 360);
	double arrowHeight = this->arrowSize;
	double arrowBaseSize = this->arrowSize * 0.4;

	if (this->arrowSize * 2 > arcLength) {
	
		math::rotate(endAngle + 90, end.x, end.y, end.x, end.y, vertex.x, vertex.y);
		math::rotate(endAngle + 90, end.x, end.y, end.x + arrowHeight, end.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(endAngle + 90, end.x, end.y, end.x + arrowHeight, end.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);
	}
	else {
	
		math::rotate(endAngle + 90, end.x, end.y, end.x, end.y, vertex.x, vertex.y);
		math::rotate(endAngle + 90, end.x, end.y, end.x - arrowHeight, end.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(endAngle + 90, end.x, end.y, end.x - arrowHeight, end.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);
	}
}

/////////////////////////////////////////////////////////////////

ShDimensionTextStyle::ShDimensionTextStyle()
	:textHeight(10.0), textAlignment(AlignedWithDimensionLine) {

}

ShDimensionTextStyle::ShDimensionTextStyle(double textHeight, TextAlignment textAlignment)
	: textHeight(textHeight), textAlignment(textAlignment) {

}

ShDimensionTextStyle::ShDimensionTextStyle(const ShDimensionTextStyle &other)
	: textHeight(other.textHeight), textAlignment(other.textAlignment) {

}

ShDimensionTextStyle::~ShDimensionTextStyle() {

}

ShDimensionTextStyle& ShDimensionTextStyle::operator=(const ShDimensionTextStyle &other) {

	this->textHeight = other.textHeight;
	this->textAlignment = other.textAlignment;

	return *this;
}

void ShDimensionTextStyle::drawDimensionDistanceText(QPainter *painter, int dx, int dy, double angle, double distance, const QColor &color, double zoomRate) const {

	this->drawDimensionText(painter, dx, dy, angle, QString::number(distance, 'f', 4), color, zoomRate);
}

void ShDimensionTextStyle::drawDimensionRadiusText(QPainter *painter, int dx, int dy, double angle, double radius, const QColor &color, double zoomRate) const {

	this->drawDimensionText(painter, dx, dy, angle, QString("R") + QString::number(radius, 'f', 4), color, zoomRate);
}

void ShDimensionTextStyle::drawDimensionDiameterText(QPainter *painter, int dx, int dy, double angle, double diameter, const QColor &color, double zoomRate) const {

	this->drawDimensionText(painter, dx, dy, angle, QString(QString::fromLocal8Bit("¤±")) + QString::number(diameter, 'f', 4), color, zoomRate);
}

void ShDimensionTextStyle::drawDimensionArcLengthText(QPainter *painter, int dx, int dy, double angle, double arcLength, const QColor &color, double zoomRate) const {

	this->drawDimensionText(painter, dx, dy, angle, QString(QString::fromLocal8Bit("¡û")) + QString::number(arcLength, 'f', 4), color, zoomRate);
}

void ShDimensionTextStyle::drawDimensionAngleText(QPainter *painter, int dx, int dy, double angle, double arcLength, const QColor &color, double zoomRate) const {

	this->drawDimensionText(painter, dx, dy, angle, QString::number(arcLength, 'f', 4) + QString::fromLocal8Bit("¢ª"), color, zoomRate);
}

void ShDimensionTextStyle::drawDimensionText(QPainter *painter, int dx, int dy, double angle, const QString &text, const QColor &color, double zoomRate) const {

	double textHeight = this->textHeight*zoomRate;
	double width = textHeight * 10;
	double height = textHeight * 2;

	QPen pen = painter->pen();
	painter->setPen(color);
	QFont oldFont = painter->font();
	QFont font = painter->font();
	font.setPointSize(math::toInt(textHeight));
	painter->setFont(font);


	if (this->textAlignment == TextAlignment::AlignedWithDimensionLine) {

		painter->rotate(-angle);
		double rotateX, rotateY;
		math::rotate(angle, 0, 0, dx, dy, rotateX, rotateY);

		painter->drawText(math::toInt(rotateX) - math::toInt(width / 2.0), math::toInt(rotateY) - math::toInt(height), width, height,
			Qt::AlignCenter, text);
		painter->rotate(angle);
	}
	else if (this->textAlignment == TextAlignment::Horizontal) {


	}

	painter->setPen(pen);
	painter->setFont(oldFont);

	painter->end();
}

////////////////////////////////////////////////////////////////////

ShDimensionStyle::ShDimensionStyle(const QString &name)
	:name(name) {

}

ShDimensionStyle::~ShDimensionStyle() {

}

void ShDimensionStyle::add(ShDim *dim) {

	this->list.append(dim);
}

void ShDimensionStyle::remove(ShDim *dim) {

	this->list.removeOne(dim);
}

void ShDimensionStyle::updateDimension() {

	auto itr = this->begin();

	for (itr; itr != this->end(); ++itr)
		(*itr)->updateChild();
}
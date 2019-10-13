
#include "ShDimensionStyle.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShMath.h"
#include "Entity\Private\ShDrawer.h"
#include <qpainter.h>

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

	double distance = math::getDistance(start.x, start.y, end.x, end.y);
	double angle = math::getAbsAngle(start.x, start.y, end.x, end.y);
	double arrowHeight = this->arrowSize;
	double arrowBaseSize = arrowSize*0.4;

	ShPoint3d vertex1, vertex2, vertex3, vertex4, vertex5, vertex6;
	GLPoint first1, first2, first3, second1, second2, second3;

	if (arrowSize * 2 > distance) {

		math::rotate(angle, start.x, start.y, start.x, start.y, vertex1.x, vertex1.y);
		math::rotate(angle, start.x, start.y, start.x - arrowHeight, start.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(angle, start.x, start.y, start.x - arrowHeight, start.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);

		math::rotate(angle, end.x, end.y, end.x, end.y, vertex4.x, vertex4.y);
		math::rotate(angle, end.x, end.y, end.x + arrowHeight, end.y + arrowBaseSize / 2.0, vertex5.x, vertex5.y);
		math::rotate(angle, end.x, end.y, end.x + arrowHeight, end.y - arrowBaseSize / 2.0, vertex6.x, vertex6.y);
	}
	else {

		math::rotate(angle, start.x, start.y, start.x, start.y, vertex1.x, vertex1.y);
		math::rotate(angle, start.x, start.y, start.x + arrowHeight, start.y + arrowBaseSize / 2.0, vertex2.x, vertex2.y);
		math::rotate(angle, start.x, start.y, start.x + arrowHeight, start.y - arrowBaseSize / 2.0, vertex3.x, vertex3.y);

		math::rotate(angle, end.x, end.y, end.x, end.y, vertex4.x, vertex4.y);
		math::rotate(angle, end.x, end.y, end.x - arrowHeight, end.y + arrowBaseSize / 2.0, vertex5.x, vertex5.y);
		math::rotate(angle, end.x, end.y, end.x - arrowHeight, end.y - arrowBaseSize / 2.0, vertex6.x, vertex6.y);
	}

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

	if (arrowSize * 2 > distance) {

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

	if (arrowSize * 2 > distance) {

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
			Qt::AlignCenter, QString::number(distance, 'f', 4));
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

#include "ShDimensionStyle.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShMath.h"

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

ShLine* ShDimensionExtensionLineStyle::createExtensionLine(const ShPoint3d &origin, const ShPoint3d &dim, const ShPropertyData &propertyData, ShLayer *layer) {

	if (this->suppressExtensionLine == true)
		return nullptr;

	ShPoint3d start, end;
	double angle = math::getAbsAngle(origin.x, origin.y, dim.x, dim.y);
	math::rotate(angle, origin.x, origin.y, origin.x + this->offsetFromOrigin, origin.y, start.x, start.y);
	math::rotate(angle, dim.x, dim.y, dim.x + this->extendBeyondDimensionLine, dim.y, end.x, end.y);

	return new ShLine(propertyData, ShLineData(start, end), layer);
}

ShLine* ShDimensionExtensionLineStyle::createExtensionLine2(const ShPoint3d &origin, const ShPoint3d &dim, const ShPropertyData &propertyData, ShLayer *layer) {

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

/////////////////////////////////////////////////////////////////

ShDimensionTextStyle::ShDimensionTextStyle()
	:textHeight(10.0) {

}

ShDimensionTextStyle::ShDimensionTextStyle(double textHeight)
	: textHeight(textHeight) {

}

ShDimensionTextStyle::ShDimensionTextStyle(const ShDimensionTextStyle &other)
	: textHeight(other.textHeight) {

}

ShDimensionTextStyle::~ShDimensionTextStyle() {

}

ShDimensionTextStyle& ShDimensionTextStyle::operator=(const ShDimensionTextStyle &other) {

	this->textHeight = other.textHeight;

	return *this;
}

ShDimensionStyle::ShDimensionStyle(const QString &name)
	:name(name) {

}

ShDimensionStyle::~ShDimensionStyle() {

}
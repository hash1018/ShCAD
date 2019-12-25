
#include "ShDimArcLength.h"
#include "Entity\Private\Algorithm\ShVisitor.h"
#include "Entity\Leaf\ShDot.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShArc.h"
#include "Base\ShMath.h"
#include "Base\ShDimensionStyle.h"

ShDimArcLength::ShDimArcLength(const ShDimArcLengthData &data, const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle)
	:ShDim(propertyData, layer, dimensionStyle), data(data) {

	this->updateChild();
}

ShDimArcLength::ShDimArcLength(const ShDimArcLength &other)
	: ShDim(other), data(other.data) {

	this->updateChild();
}

ShDimArcLength::~ShDimArcLength() {

}

ShDimArcLength& ShDimArcLength::operator=(const ShDimArcLength &other) {

	ShDim::operator=(other);
	this->data = other.data;
	this->updateChild();
	return *this;
}

ShDimArcLength* ShDimArcLength::clone() {

	return new ShDimArcLength(*this);
}

void ShDimArcLength::accept(ShVisitor *visitor) {

	visitor->visit(this);
}

void ShDimArcLength::updateChild() {

	while (!this->list.isEmpty())
		delete this->list.takeFirst();

	this->list.append(new ShDot(this->data.center, this->propertyData, this->layer));
	this->list.append(new ShDot(this->data.start, this->propertyData, this->layer));
	this->list.append(new ShDot(this->data.end, this->propertyData, this->layer));

	ShLine *extensionLine = const_cast<ShDimensionExtensionLineStyle&>(this->dimensionStyle->getDimensionExtensionLineStyle()).
		createExtensionLine(this->data.start, this->getArcStart(), this->propertyData, this->layer);

	if (extensionLine != nullptr)
		this->list.append(extensionLine);

	extensionLine = const_cast<ShDimensionExtensionLineStyle&>(this->dimensionStyle->getDimensionExtensionLineStyle()).
		createExtensionLine(this->data.end, this->getArcEnd(), this->propertyData, this->layer);

	if (extensionLine != nullptr)
		this->list.append(extensionLine);

	this->list.append(new ShArc(this->propertyData, ShArcData(this->data.center, this->getArcRadius(), this->getStartAngle(), this->getEndAngle()), this->layer));

}

void ShDimArcLength::setData(const ShDimArcLengthData &data) {

	this->data = data;
	this->updateChild();
}

double ShDimArcLength::getArcRadius() {

	return math::getDistance(this->data.center.x, this->data.center.y, this->data.boundary.x, this->data.boundary.y);
}

ShPoint3d ShDimArcLength::getArcStart() {

	ShPoint3d start;
	double radius = this->getArcRadius();
	math::rotate(this->getStartAngle(), this->data.center.x, this->data.center.y,
		this->data.center.x + radius, this->data.center.y, start.x, start.y);

	return start;
}

ShPoint3d ShDimArcLength::getArcEnd() {

	ShPoint3d end;
	double radius = this->getArcRadius();
	math::rotate(this->getEndAngle(), this->data.center.x, this->data.center.y,
		this->data.center.x + radius, this->data.center.y, end.x, end.y);

	return end;
}

double ShDimArcLength::getStartAngle() {

	return math::getAbsAngle(this->data.center.x, this->data.center.y, this->data.start.x, this->data.start.y);
}

double ShDimArcLength::getEndAngle() {

	return math::getAbsAngle(this->data.center.x, this->data.center.y, this->data.end.x, this->data.end.y);
}

double ShDimArcLength::getArcLength() {

	double angle = math::getAngleDifference(this->getStartAngle(), this->getEndAngle());

	return  (2 * 3.1415926535897*this->data.radius)*(angle / 360);
}

void ShDimArcLength::getFirstArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) {

	this->dimensionStyle->getDimensionArrowStyle().getFirstArcArrowPoints(this->data.center, this->getArcRadius(),
		this->getArcStart(), this->getArcEnd(), vertex, vertex2, vertex3);
}

void ShDimArcLength::getSecondArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) {

	this->dimensionStyle->getDimensionArrowStyle().getSecondArcArrowPoints(this->data.center, this->getArcRadius(),
		this->getArcStart(), this->getArcEnd(), vertex, vertex2, vertex3);
}
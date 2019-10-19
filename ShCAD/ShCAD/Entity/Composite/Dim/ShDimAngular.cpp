
#include "ShDimAngular.h"
#include "Entity\Private\ShVisitor.h"
#include "Entity\Leaf\ShDot.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShArc.h"
#include "Base\ShMath.h"
#include "Base\ShDimensionStyle.h"

ShDimAngular::ShDimAngular(const ShDimAngularData &data, const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle)
	:ShDim(propertyData, layer, dimensionStyle), data(data) {

	this->updateChild();
}

ShDimAngular::ShDimAngular(const ShDimAngular &other)
	: ShDim(other), data(other.data) {

	this->updateChild();
}

ShDimAngular::~ShDimAngular() {

}

ShDimAngular& ShDimAngular::operator=(const ShDimAngular &other) {

	ShDim::operator=(other);
	this->data = other.data;
	this->updateChild();
	return *this;
}

ShDimAngular* ShDimAngular::clone() {

	return new ShDimAngular(*this);
}

void ShDimAngular::accept(ShVisitor *visitor) {

	visitor->visit(this);
}

void ShDimAngular::updateChild() {

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

void ShDimAngular::setData(const ShDimAngularData &data) {

	this->data = data;
	this->updateChild();
}

double ShDimAngular::getArcRadius() {

	return math::getDistance(this->data.center.x, this->data.center.y, this->data.boundary.x, this->data.boundary.y);
}

ShPoint3d ShDimAngular::getArcStart() {

	ShPoint3d start;
	double radius = this->getArcRadius();
	math::rotate(this->getStartAngle(), this->data.center.x, this->data.center.y,
		this->data.center.x + radius, this->data.center.y, start.x, start.y);

	return start;
}

ShPoint3d ShDimAngular::getArcEnd() {

	ShPoint3d end;
	double radius = this->getArcRadius();
	math::rotate(this->getEndAngle(), this->data.center.x, this->data.center.y,
		this->data.center.x + radius, this->data.center.y, end.x, end.y);

	return end;
}

double ShDimAngular::getStartAngle() {

	return math::getAbsAngle(this->data.center.x, this->data.center.y, this->data.start.x, this->data.start.y);
}

double ShDimAngular::getEndAngle() {

	return math::getAbsAngle(this->data.center.x, this->data.center.y, this->data.end.x, this->data.end.y);
}

double ShDimAngular::getAngle() {

	return math::getAngleDifference(this->getStartAngle(), this->getEndAngle());
}

void ShDimAngular::getFirstArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) {

	this->dimensionStyle->getDimensionArrowStyle().getFirstArcArrowPoints(this->data.center, this->getArcRadius(),
		this->getArcStart(), this->getArcEnd(), vertex, vertex2, vertex3);
}

void ShDimAngular::getSecondArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) {

	this->dimensionStyle->getDimensionArrowStyle().getSecondArcArrowPoints(this->data.center, this->getArcRadius(),
		this->getArcStart(), this->getArcEnd(), vertex, vertex2, vertex3);
}
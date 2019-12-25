

#include "ShDimDiameter.h"
#include "Entity\Private\Algorithm\ShVisitor.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShDimensionStyle.h"

ShDimDiameter::ShDimDiameter(const ShDimDiameterData &data, const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle)
	:ShDim(propertyData, layer, dimensionStyle), data(data) {

	this->updateChild();
}

ShDimDiameter::ShDimDiameter(const ShDimDiameter &other)
	: ShDim(other), data(other.data) {

	this->updateChild();
}

ShDimDiameter::~ShDimDiameter() {

}

ShDimDiameter& ShDimDiameter::operator=(const ShDimDiameter &other) {

	ShDim::operator=(other);
	this->data = other.data;
	this->updateChild();
	return *this;
}

ShDimDiameter* ShDimDiameter::clone() {

	return new ShDimDiameter(*this);
}

void ShDimDiameter::accept(ShVisitor *visitor) {

	visitor->visit(this);
}

void ShDimDiameter::updateChild() {

	while (!this->list.isEmpty())
		delete this->list.takeFirst();

	if (this->isCenterToTextDistanceShorterThanRadius() == false)
		this->list.append(new ShLine(this->propertyData, ShLineData(this->data.secondDim, this->data.firstDim), this->layer));

	this->list.append(new ShLine(this->propertyData, ShLineData(this->data.firstDim, this->data.text), this->layer));

}

void ShDimDiameter::setData(const ShDimDiameterData &data) {

	this->data = data;
	this->updateChild();
}

double ShDimDiameter::getRadius() {

	return math::getDistance(this->data.center.x, this->data.center.y, this->data.firstDim.x, this->data.firstDim.y);
}

double ShDimDiameter::getDiameter() {

	return this->getRadius() * 2;
}

void ShDimDiameter::getFirstArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) {

	double angle = math::getAbsAngle(data.firstDim.x, data.firstDim.y, data.text.x, data.text.y);
	this->dimensionStyle->getDimensionArrowStyle().getArrowPoints(this->data.firstDim, angle, vertex, vertex2, vertex3);
}

void ShDimDiameter::getSecondArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) {

	double angle = math::getAbsAngle(data.firstDim.x, data.firstDim.y, data.secondDim.x, data.secondDim.y);
	this->dimensionStyle->getDimensionArrowStyle().getArrowPoints(this->data.secondDim, angle, vertex, vertex2, vertex3);
}

bool ShDimDiameter::isCenterToTextDistanceShorterThanRadius() {

	double radius = this->getRadius();
	double distance = math::getDistance(this->data.center.x, this->data.center.y, this->data.text.x, this->data.text.y);

	if (distance > radius)
		return false;

	return true;
}
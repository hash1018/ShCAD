
#include "ShDimRadius.h"
#include "Entity\Private\Algorithm\ShVisitor.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShDot.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShDimensionStyle.h"

ShDimRadius::ShDimRadius(const ShDimRadiusData &data, const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle)
	:ShDim(propertyData, layer, dimensionStyle), data(data) {

	this->updateChild();
}

ShDimRadius::ShDimRadius(const ShDimRadius &other)
	: ShDim(other), data(other.data) {

	this->updateChild();
}

ShDimRadius::~ShDimRadius() {

}

ShDimRadius& ShDimRadius::operator=(const ShDimRadius &other) {

	ShDim::operator=(other);
	this->data = other.data;
	this->updateChild();
	return *this;
}

ShDimRadius* ShDimRadius::clone() {

	return new ShDimRadius(*this);
}

void ShDimRadius::accept(ShVisitor *visitor) {

	visitor->visit(this);
}

void ShDimRadius::updateChild() {

	while (!this->list.isEmpty())
		delete this->list.takeFirst();

	this->list.append(new ShDot(this->data.center, this->propertyData, this->layer));

	double radius = this->getRadius();
	double distance = math::getDistance(this->data.center.x, this->data.center.y, this->data.text.x, this->data.text.y);

	if (distance > radius)
		this->list.append(new ShLine(this->propertyData, ShLineData(this->data.center, this->data.dim), this->layer));

	this->list.append(new ShLine(this->propertyData, ShLineData(this->data.dim, this->data.text), this->layer));

}

void ShDimRadius::setData(const ShDimRadiusData &data) {

	this->data = data;
	this->updateChild();
}
	
double ShDimRadius::getRadius() {

	return math::getDistance(this->data.center.x, this->data.center.y, this->data.dim.x, this->data.dim.y);
}

void ShDimRadius::getArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) {

	double angle = math::getAbsAngle(data.dim.x, data.dim.y, data.text.x, data.text.y);
	this->dimensionStyle->getDimensionArrowStyle().getArrowPoints(this->data.dim, angle, vertex, vertex2, vertex3);
}
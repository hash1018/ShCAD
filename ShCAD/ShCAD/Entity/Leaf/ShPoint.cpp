
#include "ShPoint.h"
#include "Entity\Private\ShVisitor.h"

ShPoint::ShPoint()
	:pointStyle(nullptr) {

}

ShPoint::ShPoint(const ShPoint3d &position, const ShPropertyData &propertyData, ShLayer *layer, const ShPointStyle *pointStyle)
	: ShLeaf(propertyData, layer), position(position), pointStyle(pointStyle) {

}

ShPoint::ShPoint(const ShPoint &other)
	: ShLeaf(other), position(other.position), pointStyle(other.pointStyle) {

}

ShPoint::~ShPoint() {

}

ShPoint& ShPoint::operator=(const ShPoint &other) {

	ShLeaf::operator=(other);
	this->position = other.position;
	this->pointStyle = other.pointStyle;

	return *this;
}

ShPoint* ShPoint::clone() {

	return new ShPoint(*this);
}

void ShPoint::accept(ShVisitor *visitor) {

	visitor->visit(this);
}
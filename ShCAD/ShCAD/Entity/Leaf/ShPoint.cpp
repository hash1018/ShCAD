
#include "ShPoint.h"
#include "Entity\Private\ShVisitor.h"

ShPoint::ShPoint() {

}

ShPoint::ShPoint(const ShPoint3d &position, const ShPropertyData &propertyData, ShLayer *layer)
	:ShLeaf(propertyData, layer), position(position) {

}

ShPoint::ShPoint(const ShPoint &other)
	: ShLeaf(other), position(other.position) {


}

ShPoint::~ShPoint() {

}

ShPoint& ShPoint::operator=(const ShPoint &other) {

	ShLeaf::operator=(other);
	this->position = other.position;

	return *this;
}

ShPoint* ShPoint::clone() {

	return new ShPoint(*this);
}

void ShPoint::accept(ShVisitor *visitor) {

	visitor->visit(this);
}
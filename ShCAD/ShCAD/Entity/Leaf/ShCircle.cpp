
#include "ShCircle.h"
#include "Entity\Private\Algorithm\ShVisitor.h"

ShCircle::ShCircle() {

}

ShCircle::ShCircle(const ShPropertyData &propertyData, const ShCircleData &data, ShLayer *layer)
	:ShLeaf(propertyData, layer), data(data) {

}

ShCircle::ShCircle(const ShCircleData &data)
	: data(data) {

}

ShCircle::ShCircle(const ShPoint3d &center, double radius)
	: data(ShCircleData(center, radius)) {

}

ShCircle::ShCircle(const ShCircle &other)
	: ShLeaf(other), data(other.data) {

}

ShCircle::~ShCircle() {

}

ShCircle& ShCircle::operator=(const ShCircle &other) {

	ShLeaf::operator=(other);
	this->data = other.data;

	return *this;
}


ShCircle* ShCircle::clone() {

	return new ShCircle(*this);
}

void ShCircle::accept(ShVisitor *visitor) {

	visitor->visit(this);
}
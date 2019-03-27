
#include "ShCircle.h"
#include "Visitor Pattern\ShVisitor.h"



ShCircle::ShCircle() {


}

ShCircle::ShCircle(const ShCircleData &data)
	:data(data) {


}

ShCircle::ShCircle(const ShPropertyData& propertyData, const ShCircleData &data, ShLayer *layer)
	: ShLeaf(propertyData, layer), data(data) {

}

ShCircle::ShCircle(const ShCircle& other)
	: ShLeaf(other), data(other.data) {

}

ShCircle& ShCircle::operator=(const ShCircle& other) {

	ShLeaf::operator=(other);

	this->data = other.data;

	return *this;
}

ShCircle::~ShCircle() {


}

ShCircle* ShCircle::Clone() {

	return new ShCircle(*this);
}

void ShCircle::Accept(ShVisitor *shVisitor) {

	shVisitor->Visit(this);

}


void ShCircle::Move(double cx, double cy) {

	this->data.center.x += cx;
	this->data.center.y += cy;
}

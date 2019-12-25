

#include "ShDot.h"
#include "Entity\Private\Algorithm\ShVisitor.h"

ShDot::ShDot() {

}

ShDot::ShDot(const ShPoint3d &position)
	:position(position) {

}

ShDot::ShDot(const ShPoint3d &position, const ShPropertyData &propertyData, ShLayer *layer)
	:ShLeaf(propertyData, layer), position(position) {

}

ShDot::ShDot(const ShDot &other)
	: ShLeaf(other), position(position) {

}

ShDot::~ShDot() {

}


ShDot& ShDot::operator=(const ShDot &other) {

	ShLeaf::operator=(other);
	this->position = other.position;

	return *this;
}

ShDot* ShDot::clone() {

	return new ShDot(*this);
}

void ShDot::accept(ShVisitor *visitor) {

	visitor->visit(this);
}
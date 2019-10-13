
#include "ShDim.h"

ShDim::ShDim()
	:dimensionStyle(nullptr) {

}

ShDim::ShDim(const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle)
	:ShComposite(propertyData, layer), dimensionStyle(dimensionStyle) {

}

ShDim::ShDim(const ShDim &other)
	: ShComposite(other), dimensionStyle(other.dimensionStyle) {

}

ShDim::~ShDim() {

}

ShDim& ShDim::operator=(const ShDim &other) {

	ShComposite::operator=(other);
	this->dimensionStyle = other.dimensionStyle;

	return *this;
}
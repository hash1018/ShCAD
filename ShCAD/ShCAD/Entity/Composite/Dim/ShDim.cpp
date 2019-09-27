
#include "ShDim.h"

ShDim::ShDim() {

}

ShDim::ShDim(const ShPropertyData &propertyData, ShLayer *layer)
	:ShComposite(propertyData, layer) {

}

ShDim::ShDim(const ShDim &other)
	: ShComposite(other) {

}

ShDim::~ShDim() {

}

ShDim& ShDim::operator=(const ShDim &other) {

	ShComposite::operator=(other);

	return *this;
}
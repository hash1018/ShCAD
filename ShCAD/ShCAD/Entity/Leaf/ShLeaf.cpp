
#include "ShLeaf.h"

ShLeaf::ShLeaf() {

}

ShLeaf::ShLeaf(const ShPropertyData &propertyData, ShLayer *layer)
	:ShEntity(propertyData, layer) {

}

ShLeaf::ShLeaf(const ShLeaf &other)
	:ShEntity(other) {

}

ShLeaf::~ShLeaf() {

}

ShLeaf& ShLeaf::operator=(const ShLeaf &other) {

	ShEntity::operator=(other);

	return *this;
}

#include "ShLeaf.h"

ShLeaf::ShLeaf() {

}

ShLeaf::ShLeaf(const ShPropertyData &propertyData)
	:ShEntity(propertyData) {

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

#include "ShEntity.h"

ShEntity::ShEntity()
	:selected(false) {

}

ShEntity::ShEntity(const ShPropertyData &propertyData)
	: propertyData(propertyData) {

}

ShEntity::ShEntity(const ShEntity &other)
	: propertyData(other.propertyData), selected(false) {

}

ShEntity::~ShEntity() {

}

ShEntity& ShEntity::operator=(const ShEntity &other) {

	this->propertyData = other.propertyData;
	this->selected = other.selected;

	return *this;
}

void ShEntity::select() {

	this->selected = true;
}

void ShEntity::unSelect() {

	this->selected = false;
}
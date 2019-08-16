
#include "ShEntity.h"

ShEntity::ShEntity()
	:selected(false), layer(nullptr) {

}

ShEntity::ShEntity(const ShPropertyData &propertyData, ShLayer *layer)
	: propertyData(propertyData), layer(layer), selected(false) {

}

ShEntity::ShEntity(const ShEntity &other)
	: propertyData(other.propertyData), layer(other.layer), selected(false) {

}

ShEntity::~ShEntity() {

}

ShEntity& ShEntity::operator=(const ShEntity &other) {

	this->propertyData = other.propertyData;
	this->selected = other.selected;
	this->layer = other.layer;

	return *this;
}

void ShEntity::select() {

	this->selected = true;
}

void ShEntity::unSelect() {

	this->selected = false;
}
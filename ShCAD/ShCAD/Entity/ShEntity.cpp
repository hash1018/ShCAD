

#include "ShEntity.h"

ShEntity::ShEntity()
	:isSelected(false),layer(0) {

}

ShEntity::ShEntity(const ShPropertyData &propertyData, ShLayer *layer)
	: propertyData(propertyData), layer(layer), isSelected(false) {

}

ShEntity::ShEntity(const ShPropertyData &propertyData)
	: propertyData(propertyData), isSelected(false), layer(0) {

}


ShEntity::ShEntity(ShLayer *layer)
	: isSelected(false), layer(layer) {

}


ShEntity::~ShEntity() {

}

ShEntity::ShEntity(const ShEntity& other)
	:propertyData(other.propertyData), layer(other.layer), isSelected(false) {

}

ShEntity& ShEntity::operator=(const ShEntity& other) {

	this->propertyData = other.propertyData;
	this->layer = other.layer;
	this->isSelected = other.isSelected;

	return *this;
}


void ShEntity::Select() {
	this->isSelected = true;
}
void ShEntity::UnSelect() {
	this->isSelected = false;
}


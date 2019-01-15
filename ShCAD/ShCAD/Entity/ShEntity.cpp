

#include "ShEntity.h"

ShEntity::ShEntity()
	:isSelected(false) {

}

ShEntity::~ShEntity() {

}

ShEntity::ShEntity(const ShEntity& other) {

}

ShEntity& ShEntity::operator=(const ShEntity& other) {

	return *this;
}

void ShEntity::Select() {
	this->isSelected = true;
}
void ShEntity::UnSelect() {
	this->isSelected = false;
}
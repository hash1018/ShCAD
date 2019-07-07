
#include "ShEntity.h"

ShEntity::ShEntity()
	:selected(false) {

}

ShEntity::ShEntity(const ShEntity &other)
	: selected(false) {

}

ShEntity::~ShEntity() {

}

ShEntity& ShEntity::operator=(const ShEntity &other) {

	this->selected = other.selected;

	return *this;
}

void ShEntity::select() {

	this->selected = true;
}

void ShEntity::unSelect() {

	this->selected = false;
}
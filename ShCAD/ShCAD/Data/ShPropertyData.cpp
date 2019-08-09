
#include "ShPropertyData.h"

ShPropertyData::ShPropertyData() {

}

ShPropertyData::ShPropertyData(const ShPropertyData &other)
	:color(other.color) {

}

ShPropertyData::~ShPropertyData() {

}

ShPropertyData& ShPropertyData::operator=(const ShPropertyData &other) {

	this->color = other.color;

	return *this;
}
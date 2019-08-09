
#include "ShPropertyData.h"

ShPropertyData::ShPropertyData() {

}

ShPropertyData::ShPropertyData(const ShPropertyData &other)
	:color(other.color), lineStyle(other.lineStyle) {

}

ShPropertyData::~ShPropertyData() {

}

ShPropertyData& ShPropertyData::operator=(const ShPropertyData &other) {

	this->color = other.color;
	this->lineStyle = other.lineStyle;

	return *this;
}
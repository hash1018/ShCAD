

#include "ShPropertyData.h"

ShColor::ShColor()
	:r(255), g(255), b(255), type(Type::Normal) {

}

ShColor::ShColor(unsigned char r, unsigned char g, unsigned b, ShColor::Type type)
	: r(r), g(g), b(b), type(type) {

}

ShColor::ShColor(const ShColor& other)
	: r(other.r), g(other.g), b(other.b), type(other.type) {

}

ShColor& ShColor::operator=(const ShColor& other) {

	this->r = other.r;
	this->g = other.g;
	this->b = other.b;
	this->type = other.type;

	return *this;

}

ShColor::~ShColor() {

}

bool ShColor::operator==(const ShColor& other) {

	if (this->r != other.r)
		return false;

	if (this->g != other.g)
		return false;

	if (this->b != other.b)
		return false;

	if (this->type != other.type)
		return false;

	return true;
}

bool ShColor::operator!=(const ShColor& other) {

	if (this->r != other.r)
		return true;
	if (this->g != other.g)
		return true;
	if (this->b != other.b)
		return true;
	if (this->type != other.type)
		return true;

	return false;
}


ShLineStyle::ShLineStyle()
	:pattern(0xFFFF),type(ShLineStyle::Type::Normal) {

}

ShLineStyle::ShLineStyle(unsigned short pattern, ShLineStyle::Type type)
	: pattern(pattern), type(type) {

}

ShLineStyle::ShLineStyle(const ShLineStyle& other)
	: pattern(other.pattern), type(other.type) {

}

ShLineStyle& ShLineStyle::operator=(const ShLineStyle& other) {

	this->pattern = other.pattern;
	this->type = other.type;

	return *this;
}

ShLineStyle::~ShLineStyle() {

}


bool ShLineStyle::operator==(const ShLineStyle& other) {

	if (this->pattern != other.pattern)
		return false;

	if (this->type != other.type)
		return false;

	return true;
}

bool ShLineStyle::operator!=(const ShLineStyle& other) {

	if (this->pattern != other.pattern)
		return true;

	if (this->type != other.type)
		return true;

	return false;
}


ShPropertyData::ShPropertyData() {

}

ShPropertyData::ShPropertyData(const ShPropertyData& other)
	:color(other.color),lineStyle(other.lineStyle) {

}

ShPropertyData& ShPropertyData::operator=(const ShPropertyData& other) {

	this->color = other.color;
	this->lineStyle = other.lineStyle;

	return *this;
}

ShPropertyData::~ShPropertyData() {

}
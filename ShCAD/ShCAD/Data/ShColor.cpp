
#include "ShColor.h"

ShColor::ShColor()
	:r(255), g(255), b(255), type(Type::Normal) {

}

ShColor::ShColor(unsigned char r, unsigned char g, unsigned char b, ShColor::Type type)
	: r(r), g(g), b(b), type(type) {

}

ShColor::ShColor(const ShColor &other)
	: r(other.r), g(other.g), b(other.b), type(other.type) {

}

ShColor::~ShColor() {

}

ShColor& ShColor::operator=(const ShColor &other) {

	this->r = other.r;
	this->g = other.g;
	this->b = other.b;
	this->type = other.type;

	return *this;
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

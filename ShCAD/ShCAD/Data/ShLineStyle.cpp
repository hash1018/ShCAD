
#include "ShLineStyle.h"

ShLineStyle::ShLineStyle()
	:pattern(0xFFFF), type(Type::Normal) {

}

ShLineStyle::ShLineStyle(unsigned short pattern, Type type)
	: pattern(pattern), type(type) {

}

ShLineStyle::ShLineStyle(const ShLineStyle &other)
	: pattern(other.pattern), type(other.type) {

}

ShLineStyle::~ShLineStyle() {

}

ShLineStyle& ShLineStyle::operator=(const ShLineStyle &other) {

	this->pattern = other.pattern;
	this->type = other.type;

	return *this;
}

bool ShLineStyle::operator==(const ShLineStyle &other) {

	if (this->pattern != other.pattern)
		return false;

	if (this->type != other.type)
		return false;

	return true;
}

bool ShLineStyle::operator!=(const ShLineStyle &other) {

	if (this->pattern != other.pattern)
		return true;

	if (this->type != other.type)
		return true;

	return false;
}
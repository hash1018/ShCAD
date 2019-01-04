

#include "ShVector.h"


ShVector::ShVector()
	:x(0), y(0), z(0) {


}

ShVector::ShVector(double x, double y, double z)
	: x(x), y(y), z(z) {

}

ShVector::ShVector(const ShVector& other)
	: x(other.x), y(other.y), z(other.z) {

}

ShVector& ShVector::operator=(const ShVector& other) {

	this->x = other.x;
	this->y = other.y;
	this->z = other.z;

	return *this;
}

ShVector::~ShVector() {

}

bool ShVector::operator==(const ShVector& other) {

	if (this->x == other.x && this->y == other.y && this->z == other.z)
		return true;

	return false;
}
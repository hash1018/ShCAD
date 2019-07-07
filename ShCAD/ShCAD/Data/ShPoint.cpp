
#include "ShPoint.h"

ShPoint3d::ShPoint3d()
	:x(0), y(0), z(0) {

}

ShPoint3d::ShPoint3d(double x, double y, double z)
	: x(x), y(y), z(z) {

}

ShPoint3d::ShPoint3d(const ShPoint3d &other)
	: x(other.x), y(other.y), z(other.z) {

}

ShPoint3d::~ShPoint3d() {

}

ShPoint3d& ShPoint3d::operator=(const ShPoint3d &other) {

	this->x = other.x;
	this->y = other.y;
	this->z = other.z;

	return *this;
}

bool ShPoint3d::operator==(const ShPoint3d& other) {

	if (this->x == other.x && this->y == other.y && this->z == other.z)
		return true;

	return false;
}
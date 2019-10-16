
#include "ShPoint3d.h"
#include "Base\ShMath.h"

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

bool ShPoint3d::isEqual(const ShPoint3d &other, double epsilon) {

	if (math::compare(this->x, other.x, epsilon) != 0)
		return false;

	if (math::compare(this->y, other.y, epsilon) != 0)
		return false;

	if (math::compare(this->z, other.z, epsilon) != 0)
		return false;

	return true;
}

void ShPoint3d::move(double dx, double dy, double dz) {

	this->x += dx;
	this->y += dy;
	this->z += dz;
}
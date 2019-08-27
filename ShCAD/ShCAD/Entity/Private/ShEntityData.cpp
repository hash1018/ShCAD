
#include "ShEntityData.h"

ShEntityData::ShEntityData() {

}

ShEntityData::ShEntityData(const ShEntityData &other) {

}

ShEntityData::~ShEntityData() {

}

ShEntityData& ShEntityData::operator=(const ShEntityData &other) {

	return *this;
}

////////////////////////////////////////////////////////////

ShLineData::ShLineData() {

}

ShLineData::ShLineData(const ShPoint3d &start, const ShPoint3d &end)
	:start(start), end(end) {

}

ShLineData::ShLineData(const ShLineData &other)
	: start(other.start), end(other.end) {

}

ShLineData::~ShLineData() {

}

ShLineData& ShLineData::operator=(const ShLineData &other) {

	this->start = other.start;
	this->end = other.end;

	return *this;
}

/////////////////////////////////////////////////////////////////

ShCircleData::ShCircleData()
	:radius(0) {

}

ShCircleData::ShCircleData(const ShPoint3d &center, double radius)
	: center(center), radius(radius) {

}

ShCircleData::ShCircleData(const ShCircleData &other)
	: center(other.center), radius(other.radius) {

}

ShCircleData::~ShCircleData() {

}

ShCircleData& ShCircleData::operator=(const ShCircleData &other) {

	this->center = other.center;
	this->radius = other.radius;

	return *this;
}

//////////////////////////////////////////////////////////////////

ShArcData::ShArcData()
	:radius(0), startAngle(0), endAngle(0) {

}

ShArcData::ShArcData(const ShPoint3d &center, double radius, double startAngle, double endAngle)
	: center(center), radius(radius), startAngle(startAngle), endAngle(endAngle) {

}

ShArcData::ShArcData(const ShArcData &other)
	: center(other.center), radius(other.radius), startAngle(other.startAngle), endAngle(other.endAngle) {

}

ShArcData::~ShArcData() {

}

ShArcData& ShArcData::operator=(const ShArcData &other) {

	this->center = other.center;
	this->radius = other.radius;
	this->startAngle = other.startAngle;
	this->endAngle = other.endAngle;

	return *this;
}

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


////////////////////////////////////////////////////////////////////////

ShDimLinearData::ShDimLinearData() {

}

ShDimLinearData::ShDimLinearData(const ShPoint3d &first, const ShPoint3d &first2, const ShPoint3d &second, const ShPoint3d &second2,
	double angle, double distance, const ShPoint3d &distancePosition)
	:first(first), first2(first2), second(second), second2(second2), angle(angle), distance(distance), distancePosition(distancePosition) {

}

ShDimLinearData::ShDimLinearData(const ShDimLinearData &other)
	: first(other.first), first2(other.first2), second(other.second), second2(other.second2), angle(other.angle),
	distance(other.distance), distancePosition(other.distancePosition) {

}

ShDimLinearData::~ShDimLinearData() {

}

ShDimLinearData& ShDimLinearData::operator=(const ShDimLinearData &other) {

	this->first = other.first;
	this->first2 = other.first2;
	this->second = other.second;
	this->second2 = other.second2;
	this->angle = other.angle;
	this->distance = other.distance;
	this->distancePosition = other.distancePosition;

	return *this;
}

#include "ShEntityData.h"



ShLineData::ShLineData() {

}

ShLineData::ShLineData(const ShPoint3d &start, const ShPoint3d &end)
	:start(start), end(end) {


}

ShLineData::ShLineData(const ShLineData &data)
	: start(data.start), end(data.end) {


}

bool ShLineData::operator==(const ShLineData& data) {

	if (this->start == data.start && this->end == data.end)
		return true;

	return false;

}

ShLineData& ShLineData::operator=(const ShLineData& data) {


	this->start = data.start;
	this->end = data.end;

	return *this;
}

//////////////////////////////////////////////////////////////////////////


ShCircleData::ShCircleData() {

}

ShCircleData::ShCircleData(ShPoint3d &center, double radius)
	:center(center), radius(radius) {

}

ShCircleData::ShCircleData(const ShCircleData &data)
	: center(data.center), radius(data.radius) {


}

bool ShCircleData::operator==(const ShCircleData& data) {

	if (this->center == data.center && this->radius == data.radius)
		return true;

	return false;

}

ShCircleData& ShCircleData::operator=(const ShCircleData& data) {

	this->center = data.center;
	this->radius = data.radius;

	return *this;
}

//////////////////////////////////////////////////////////////////////////////



ShArcData::ShArcData() {

}

ShArcData::ShArcData(ShPoint3d &center, double radius, double startAngle, double endAngle)
	:center(center), radius(radius), startAngle(startAngle), endAngle(endAngle) {

}

ShArcData::ShArcData(const ShArcData &data)
	: center(data.center), radius(data.radius), startAngle(data.startAngle), endAngle(data.endAngle) {


}

bool ShArcData::operator==(const ShArcData& data) {

	if (this->center == data.center && this->radius == data.radius &&
		this->startAngle == data.startAngle && this->endAngle == data.endAngle)
		return true;

	return false;

}

ShArcData& ShArcData::operator=(const ShArcData& data) {

	this->center = data.center;
	this->radius = data.radius;
	this->startAngle = data.startAngle;
	this->endAngle = data.endAngle;

	return *this;
}

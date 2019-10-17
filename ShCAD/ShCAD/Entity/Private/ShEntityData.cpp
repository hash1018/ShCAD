
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

ShDimLinearData::ShDimLinearData(const ShPoint3d &firstOrigin, const ShPoint3d &secondOrigin, const ShPoint3d &firstDim, const ShPoint3d &secondDim,
	const ShPoint3d &text)
	:firstOrigin(firstOrigin), secondOrigin(secondOrigin), firstDim(firstDim), secondDim(secondDim), text(text) {

}

ShDimLinearData::ShDimLinearData(const ShDimLinearData &other)
	: firstOrigin(other.firstOrigin), secondOrigin(other.secondOrigin), firstDim(other.firstDim), secondDim(other.secondDim), text(other.text) {

}

ShDimLinearData::~ShDimLinearData() {

}

ShDimLinearData& ShDimLinearData::operator=(const ShDimLinearData &other) {

	this->firstOrigin = other.firstOrigin;
	this->secondOrigin = other.secondOrigin;
	this->firstDim = other.firstDim;
	this->secondDim = other.secondDim;
	this->text = other.text;

	return *this;
}

//////////////////////////////////////////////////////////////////////////////

ShDimAlignedData::ShDimAlignedData() {

}

ShDimAlignedData::ShDimAlignedData(const ShPoint3d &firstOrigin, const ShPoint3d &secondOrigin, const ShPoint3d &firstDim, const ShPoint3d &secondDim,
	const ShPoint3d &text)
	:firstOrigin(firstOrigin), secondOrigin(secondOrigin), firstDim(firstDim), secondDim(secondDim), text(text) {

}

ShDimAlignedData::ShDimAlignedData(const ShDimAlignedData &other)
	: firstOrigin(other.firstOrigin), secondOrigin(other.secondOrigin), firstDim(other.firstDim), secondDim(other.secondDim), text(other.text) {

}

ShDimAlignedData::~ShDimAlignedData() {

}

ShDimAlignedData& ShDimAlignedData::operator=(const ShDimAlignedData &other) {

	this->firstOrigin = other.firstOrigin;
	this->secondOrigin = other.secondOrigin;
	this->firstDim = other.firstDim;
	this->secondDim = other.secondDim;
	this->text = other.text;

	return *this;
}

////////////////////////////////////////////////////////////////

ShDimRadiusData::ShDimRadiusData() {

}

ShDimRadiusData::ShDimRadiusData(const ShPoint3d &center, const ShPoint3d &dim, const ShPoint3d &text)
	:center(center), dim(dim), text(text) {

}

ShDimRadiusData::ShDimRadiusData(const ShDimRadiusData &other)
	: center(other.center), dim(other.dim), text(other.text) {

}

ShDimRadiusData::~ShDimRadiusData() {

}

ShDimRadiusData& ShDimRadiusData::operator=(const ShDimRadiusData &other) {

	this->center = other.center;
	this->dim = other.dim;
	this->text = other.text;

	return *this;
}

//////////////////////////////////////////////////////////////

ShDimDiameterData::ShDimDiameterData() {

}

ShDimDiameterData::ShDimDiameterData(const ShPoint3d &center, const ShPoint3d &firstDim, const ShPoint3d &secondDim, const ShPoint3d &text)
	:center(center), firstDim(firstDim), secondDim(secondDim), text(text) {

}

ShDimDiameterData::ShDimDiameterData(const ShDimDiameterData &other)
	: center(other.center), firstDim(other.firstDim), secondDim(other.secondDim), text(other.text) {

}

ShDimDiameterData::~ShDimDiameterData() {

}

ShDimDiameterData& ShDimDiameterData::operator=(const ShDimDiameterData &other) {

	this->center = other.center;
	this->firstDim = other.firstDim;
	this->secondDim = other.secondDim;
	this->text = other.text;
	
	return *this;
}
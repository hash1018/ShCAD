
#include "ShArc.h"
#include "Visitor Pattern\ShVisitor.h"


ShArcData::ShArcData() {

}

ShArcData::ShArcData(ShVector &center, double radius, double startAngle, double endAngle)
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


ShArc::ShArc() {


}

ShArc::ShArc(const ShArcData &data)
	:data(data) {


}

ShArc::ShArc(const ShArc& other)
	: data(other.data) {


}

ShArc& ShArc::operator=(const ShArc& other) {

	ShLeaf::operator=(other);

	this->data = other.data;

	return *this;
}

ShArc::~ShArc() {


}

ShArc* ShArc::Clone() {

	return new ShArc(*this);
}

void ShArc::Accept(ShVisitor *shVisitor) {

	shVisitor->Visit(this);

}

void ShArc::SetData(const ShArcData &data) {

	this->data = data;

}

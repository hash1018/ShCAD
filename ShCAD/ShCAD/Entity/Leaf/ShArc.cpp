
#include "ShArc.h"
#include "Entity\Private\Algorithm\ShVisitor.h"
#include "Base\ShMath.h"

ShArc::ShArc() {

}

ShArc::ShArc(const ShPropertyData &propertyData, const ShArcData &data, ShLayer *layer)
	:ShLeaf(propertyData, layer), data(data) {

}

ShArc::ShArc(const ShArcData &data)
	: data(data) {

}

ShArc::ShArc(const ShPoint3d &center, double radius, double startAngle, double endAngle)
	: data(ShArcData(center, radius, startAngle, endAngle)) {

}

ShArc::ShArc(const ShArc &other)
	: ShLeaf(other), data(other.data) {

}

ShArc::~ShArc() {

}

ShArc& ShArc::operator=(const ShArc &other) {

	ShLeaf::operator=(other);
	this->data = other.data;

	return *this;
}

ShArc* ShArc::clone() {

	return new ShArc(*this);
}

void ShArc::accept(ShVisitor *visitor) {

	visitor->visit(this);
}

ShPoint3d ShArc::getStart() const {

	ShPoint3d start;
	ShPoint3d center = this->data.center;
	double radius = this->data.radius;
	double startAngle = this->data.startAngle;

	math::rotate(startAngle, center.x, center.y, center.x + radius, center.y, start.x, start.y);

	return start;
}

ShPoint3d ShArc::getEnd() const {

	ShPoint3d end;
	ShPoint3d center = this->data.center;
	double radius = this->data.radius;
	double endAngle = this->data.endAngle;

	math::rotate(endAngle, center.x, center.y, center.x + radius, center.y, end.x, end.y);

	return end;
}

ShPoint3d ShArc::getMid() const {

	ShPoint3d mid;
	ShPoint3d center = this->data.center;
	double radius = this->data.radius;
	double difference = math::getAngleDifference(this->data.startAngle, this->data.endAngle);

	math::rotate(this->data.startAngle + (difference / 2.0), center.x, center.y, center.x + radius, center.y, mid.x, mid.y);

	return mid;
}
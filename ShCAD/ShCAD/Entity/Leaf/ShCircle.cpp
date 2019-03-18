
#include "ShCircle.h"
#include "Visitor Pattern\ShVisitor.h"


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


ShCircle::ShCircle() {


}

ShCircle::ShCircle(const ShCircleData &data)
	:data(data) {


}

ShCircle::ShCircle(const ShPropertyData& propertyData, const ShCircleData &data, ShLayer *layer)
	: ShLeaf(propertyData, layer), data(data) {

}

ShCircle::ShCircle(const ShCircle& other)
	: ShLeaf(other), data(other.data) {

}

ShCircle& ShCircle::operator=(const ShCircle& other) {

	ShLeaf::operator=(other);

	this->data = other.data;

	return *this;
}

ShCircle::~ShCircle() {


}

ShCircle* ShCircle::Clone() {

	return new ShCircle(*this);
}

void ShCircle::Accept(ShVisitor *shVisitor) {

	shVisitor->Visit(this);

}


void ShCircle::GetHitPoint(HitPoint hitPoint, ShPoint3d &point) {

	if (hitPoint == HitPoint::HitCenter) {
		point = this->data.center;
	}
	else if (hitPoint == HitPoint::HitTop) {
		point.x = this->data.center.x;
		point.y = this->data.center.y + this->data.radius;
	}
	else if (hitPoint == HitPoint::HitLeft) {
		point.x = this->data.center.x - this->data.radius;
		point.y = this->data.center.y;
	}
	else if (hitPoint == HitPoint::HitBottom) {
		point.x = this->data.center.x;
		point.y = this->data.center.y - this->data.radius;
	}
	else if (hitPoint == HitPoint::HitRight) {
		point.x = this->data.center.x + this->data.radius;
		point.y = this->data.center.y;
	}

}

void ShCircle::Move(double cx, double cy) {

	this->data.center.x += cx;
	this->data.center.y += cy;
}
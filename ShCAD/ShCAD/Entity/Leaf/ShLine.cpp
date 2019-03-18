

#include "ShLine.h"
#include "Visitor Pattern\ShVisitor.h"

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


ShLine::ShLine() {


}

ShLine::ShLine(const ShLineData& data)
	:data(data) {

}

ShLine::ShLine(const ShPropertyData& propertyData, const ShLineData &data, ShLayer *layer)
	: ShLeaf(propertyData, layer), data(data) {


}

ShLine::ShLine(const ShLine& other)
	: ShLeaf(other), data(other.data) {


}

ShLine& ShLine::operator=(const ShLine& other) {

	ShLeaf::operator=(other);

	this->data = other.data;

	return *this;
}

ShLine::~ShLine() {


}

ShLine* ShLine::Clone() {

	return new ShLine(*this);
}

void ShLine::Accept(ShVisitor *shVisitor) {

	shVisitor->Visit(this);

}

void ShLine::GetHitPoint(HitPoint hitPoint, ShPoint3d &point) {

	if (hitPoint == HitPoint::HitStart) {

		point.x = this->data.start.x;
		point.y = this->data.start.y;
	}
	else if (hitPoint == HitPoint::HitEnd) {
	
		point.x = this->data.end.x;
		point.y = this->data.end.y;
	}
	else if (hitPoint == HitPoint::HitMid) {
	
		point = this->GetMid();
	}


}

void ShLine::Move(double cx, double cy) {

	this->data.start.x += cx;
	this->data.start.y += cy;
	this->data.end.x += cx;
	this->data.end.y += cy;
}


#include <math.h>
ShPoint3d ShLine::GetMid() {

	double distanceX = fabs(this->data.end.x - this->data.start.x);
	double midX = distanceX / 2.0;

	if (this->data.start.x > this->data.end.x)
		midX = this->data.start.x - midX;
	else if (this->data.start.x < this->data.end.x)
		midX = this->data.start.x + midX;
	else if (this->data.start.x == this->data.end.x)
		midX = this->data.start.x;
	

	double distanceY = fabs(this->data.end.y - this->data.start.y);
	double midY = distanceY / 2.0;

	if (this->data.start.y > this->data.end.y)
		midY = this->data.start.y - midY;
	else if (this->data.start.y < this->data.end.y)
		midY = this->data.start.y + midY;
	else if (this->data.start.y == this->data.end.y) 
		midY = this->data.start.y;
	

	return ShPoint3d(midX, midY);

}
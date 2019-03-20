

#include "ShLine.h"
#include "Visitor Pattern\ShVisitor.h"


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

void ShLine::GetVertexPoint(VertexPoint vertexPoint, ShPoint3d &point) {

	if (vertexPoint == VertexPoint::VertexStart) {

		point.x = this->data.start.x;
		point.y = this->data.start.y;
	}
	else if (vertexPoint == VertexPoint::VertexEnd) {
	
		point.x = this->data.end.x;
		point.y = this->data.end.y;
	}
	else if (vertexPoint == VertexPoint::VertexMid) {
	
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

ShLineData* ShLine::CreateData() {
	
	return new ShLineData(this->data);
}

void ShLine::SetData(ShEntityData *data) {
	
	if (dynamic_cast<ShLineData*>(data))
		this->data = *(dynamic_cast<ShLineData*>(data));

}
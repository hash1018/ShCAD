
#include "ShCircle.h"
#include "Visitor Pattern\ShVisitor.h"



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


void ShCircle::GetVertexPoint(VertexPoint vertexPoint, ShPoint3d &point) {

	if (vertexPoint == VertexPoint::VertexCenter) {
		point = this->data.center;
	}
	else if (vertexPoint == VertexPoint::VertexTop) {
		point.x = this->data.center.x;
		point.y = this->data.center.y + this->data.radius;
	}
	else if (vertexPoint == VertexPoint::VertexLeft) {
		point.x = this->data.center.x - this->data.radius;
		point.y = this->data.center.y;
	}
	else if (vertexPoint == VertexPoint::VertexBottom) {
		point.x = this->data.center.x;
		point.y = this->data.center.y - this->data.radius;
	}
	else if (vertexPoint == VertexPoint::VertexRight) {
		point.x = this->data.center.x + this->data.radius;
		point.y = this->data.center.y;
	}

}

void ShCircle::Move(double cx, double cy) {

	this->data.center.x += cx;
	this->data.center.y += cy;
}

ShCircleData* ShCircle::CreateData() {

	return new ShCircleData(this->data);
}

void ShCircle::SetData(ShEntityData *data) {

	if (dynamic_cast<ShCircleData*>(data))
		this->data = *(dynamic_cast<ShCircleData*>(data));
}
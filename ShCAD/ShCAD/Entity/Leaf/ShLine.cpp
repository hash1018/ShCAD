
#include "ShLine.h"
#include "Entity\Private\ShVisitor.h"
#include <math.h>

ShLine::ShLine() {

}

ShLine::ShLine(const ShLineData &data)
	:data(data) {

}

ShLine::ShLine(const ShPoint3d &start, const ShPoint3d &end)
	: data(start, end) {

}

ShLine::ShLine(const ShLine &other)
	: ShLeaf(other), data(other.data) {

}

ShLine::~ShLine() {

}

ShLine& ShLine::operator=(const ShLine &other) {

	ShLeaf::operator=(other);

	this->data = other.data;

	return *this;
}

ShLine* ShLine::clone() {

	return new ShLine(*this);
}

void ShLine::accept(ShVisitor *visitor) {

	visitor->visit(this);
}

ShPoint3d ShLine::getMid() {

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
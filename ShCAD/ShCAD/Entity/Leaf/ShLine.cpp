
#include "ShLine.h"
#include "Entity\Visitor Algorithm\ShVisitor.h"

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
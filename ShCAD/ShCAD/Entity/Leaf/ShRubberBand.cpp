

#include "ShRubberBand.h"
#include "Visitor Pattern\ShVisitor.h"

ShRubberBand::ShRubberBand() {

}

ShRubberBand::ShRubberBand(const ShLineData &data)
	:ShLine(data) {

}

ShRubberBand::ShRubberBand(const ShRubberBand& other)
	: ShLine(other) {

}

ShRubberBand& ShRubberBand::operator=(const ShRubberBand& other) {

	ShLine::operator=(other);

	return *this;
}

ShRubberBand::~ShRubberBand() {

}

ShRubberBand* ShRubberBand::Clone() {

	return new ShRubberBand(*this);
}

void ShRubberBand::Accept(ShVisitor *shVisitor) {

	shVisitor->Visit(this);
}
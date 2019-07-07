
#include "ShRubberBand.h"
#include "Entity\Visitor Algorithm\ShVisitor.h"

ShRubberBand::ShRubberBand() {

}

ShRubberBand::ShRubberBand(const ShLineData &data)
	:ShLine(data) {

}

ShRubberBand::ShRubberBand(const ShRubberBand &other)
	: ShLine(other) {

}

ShRubberBand::~ShRubberBand() {

}

ShRubberBand& ShRubberBand::operator=(const ShRubberBand &other) {

	ShLine::operator=(other);

	return *this;
}

ShRubberBand* ShRubberBand::clone() {

	return new ShRubberBand(*this);
}

void ShRubberBand::accept(ShVisitor *visitor) {

	visitor->visit(this);
}
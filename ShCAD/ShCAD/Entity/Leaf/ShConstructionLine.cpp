
#include "ShConstructionLine.h"
#include "Entity\Private\ShVisitor.h"

ShConstructionLine::ShConstructionLine() {

}

ShConstructionLine::ShConstructionLine(const ShPropertyData &propertyData, const ShLineData &data, ShLayer *layer)
	:ShLine(propertyData, data, layer) {

}

ShConstructionLine::ShConstructionLine(const ShLineData &data)
	: ShLine(data) {

}

ShConstructionLine::ShConstructionLine(const ShPoint3d &start, const ShPoint3d &end)
	: ShLine(start, end) {

}

ShConstructionLine::ShConstructionLine(const ShConstructionLine &other)
	: ShLine(other) {

}

ShConstructionLine::~ShConstructionLine() {

}

ShConstructionLine& ShConstructionLine::operator=(const ShConstructionLine &other) {

	ShLine::operator=(other);

	return *this;
}

ShConstructionLine* ShConstructionLine::clone() {

	return new ShConstructionLine(*this);
}

void ShConstructionLine::accept(ShVisitor *visitor) {

	visitor->visit(this);
}
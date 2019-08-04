
#include "ShLineBothPerpendicularVisitor.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShMath.h"

ShLineBothPerpendicularVisitor::ShLineBothPerpendicularVisitor(ShEntity *secondPerpendicularBase, ShPoint3d &perpendicular, bool &isValid)
	:secondPerpendicularBase(secondPerpendicularBase), perpendicular(perpendicular), isValid(isValid) {

}

ShLineBothPerpendicularVisitor::~ShLineBothPerpendicularVisitor() {

}

void ShLineBothPerpendicularVisitor::visit(ShLine *line) {

	ShFirstLinePerpendicularVisitor visitor(line, this->perpendicular, this->isValid);
	this->secondPerpendicularBase->accept(&visitor);
}


/////////////////////////////////////////////////////////////////////


ShFirstLinePerpendicularVisitor::ShFirstLinePerpendicularVisitor(ShLine *firstLine, ShPoint3d &perpendicular, bool &isValid)
	:firstLine(firstLine), perpendicular(perpendicular), isValid(isValid) {

}

ShFirstLinePerpendicularVisitor::~ShFirstLinePerpendicularVisitor() {

}

void ShFirstLinePerpendicularVisitor::visit(ShLine *line) {

	double angle = math::getAbsAngle(line->getStart().x, line->getStart().y,
		line->getEnd().x, line->getEnd().y);
	double angle2 = math::getAbsAngle(this->firstLine->getStart().x, this->firstLine->getStart().y,
		this->firstLine->getEnd().x, this->firstLine->getEnd().y);

	if (math::compare(math::getAngleDifference(angle, angle2), 180) == 0 ||
		math::compare(math::getAngleDifference(angle, angle2, false), 180) == 0 ||
		math::compare(math::getAngleDifference(angle, angle2), 0) == 0) {

		this->isValid = true;
		return;
	}

	this->isValid = false;
}
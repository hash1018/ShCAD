
#include "ShLineBothPerpendicularVisitor.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Private\ShFootOfPerpendicularVisitor.h"

ShLineBothPerpendicularVisitor::ShLineBothPerpendicularVisitor(ShEntity *secondPerpendicularBase, ShPoint3d &perpendicular, bool &isValid)
	:secondPerpendicularBase(secondPerpendicularBase), perpendicular(perpendicular), isValid(isValid) {

}

ShLineBothPerpendicularVisitor::~ShLineBothPerpendicularVisitor() {

}

void ShLineBothPerpendicularVisitor::visit(ShLine *line) {

	ShFirstLinePerpendicularVisitor visitor(line, this->perpendicular, this->isValid);
	this->secondPerpendicularBase->accept(&visitor);
}

void ShLineBothPerpendicularVisitor::visit(ShCircle *circle) {

	ShFirstCirclePerpendicularVisitor visitor(circle, this->perpendicular, this->isValid);
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

void ShFirstLinePerpendicularVisitor::visit(ShCircle *circle) {

	ShPoint3d center = circle->getCenter();
	double radius = circle->getRadius();

	ShPoint3d point;
	ShFootOfPerpendicularVisitor visitor(point.x, point.y, center);
	this->firstLine->accept(&visitor);


	double angle = math::getAbsAngle(center.x, center.y, point.x, point.y);
	math::rotate(angle, center.x, center.y, center.x + radius, center.y, this->perpendicular.x, this->perpendicular.y);


	this->isValid = true;
}


//////////////////////////////////////////////////////////////////////////

ShFirstCirclePerpendicularVisitor::ShFirstCirclePerpendicularVisitor(ShCircle *firstCircle, ShPoint3d &perpendicular, bool &isValid)
	:firstCircle(firstCircle), perpendicular(perpendicular), isValid(isValid) {

}

ShFirstCirclePerpendicularVisitor::~ShFirstCirclePerpendicularVisitor() {

}

void ShFirstCirclePerpendicularVisitor::visit(ShLine *line) {

	ShPoint3d center = this->firstCircle->getCenter();

	ShFootOfPerpendicularVisitor visitor(this->perpendicular.x, this->perpendicular.y, center);
	line->accept(&visitor);

	this->isValid = true;
}

void ShFirstCirclePerpendicularVisitor::visit(ShCircle *circle) {

	ShPoint3d center = this->firstCircle->getCenter();

	ShFootOfPerpendicularVisitor visitor(this->perpendicular.x, this->perpendicular.y, center);
	circle->accept(&visitor);

	this->isValid = true;

}


#include "ShBothPerpendicularVisitor.h"
#include "Entity\Leaf\ShLine.h"
#include "ShMath.h"
ShBothPerpendicularVisitor::ShBothPerpendicularVisitor(ShEntity *perpendicularEntity, ShPoint3d &perpendicular,
	bool &isValid)
	:perpendicularEntity(perpendicularEntity), perpendicular(perpendicular), isValid(isValid) {

}

ShBothPerpendicularVisitor::~ShBothPerpendicularVisitor() {

}

void ShBothPerpendicularVisitor::Visit(ShLine *line) {

	ShLinePerpendicularVisitor visitor(line, this->perpendicular, this->isValid);
	this->perpendicularEntity->Accept(&visitor);
}

void ShBothPerpendicularVisitor::Visit(ShCircle *circle) {

}

void ShBothPerpendicularVisitor::Visit(ShArc *arc) {


}

/////////////////////////////////////////////////////////////////////////////////////////////

ShLinePerpendicularVisitor::ShLinePerpendicularVisitor(ShLine *baseLine, ShPoint3d &perpendicular,
	bool &isValid)
	:baseLine(baseLine), perpendicular(perpendicular), isValid(isValid) {

}

ShLinePerpendicularVisitor::~ShLinePerpendicularVisitor() {

}


void ShLinePerpendicularVisitor::Visit(ShLine *line) {
	
	double angle = Math::GetAbsAngle(line->GetStart().x, line->GetStart().y, line->GetEnd().x, line->GetEnd().y);
	double angle2 = Math::GetAbsAngle(this->baseLine->GetStart().x, this->baseLine->GetStart().y,
		this->baseLine->GetEnd().x, this->baseLine->GetEnd().y);



	if (Math::Compare(Math::GetAngleDifference(angle, angle2), 180) == 0 ||
		Math::Compare(Math::GetAngleDifference(angle, angle2, false), 180) == 0 ||
		Math::Compare(Math::GetAngleDifference(angle, angle2), 0) == 0) {

		this->isValid = true;
		return;
	}
	
	this->isValid = false;
}

void ShLinePerpendicularVisitor::Visit(ShCircle *circle) {

}

void ShLinePerpendicularVisitor::Visit(ShArc *arc) {


}
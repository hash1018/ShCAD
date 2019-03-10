

#include "ShBothPerpendicularVisitor.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "ShMath.h"
ShBothPerpendicularVisitor::ShBothPerpendicularVisitor(ShEntity *perpendicularEntity, ShPoint3d &perpendicular,
	bool &isValid)
	:perpendicularEntity(perpendicularEntity), perpendicular(perpendicular), isValid(isValid) {

}

ShBothPerpendicularVisitor::~ShBothPerpendicularVisitor() {

}

void ShBothPerpendicularVisitor::Visit(ShLine *firstPerpendicularLine) {

	ShFirstLinePerpendicularVisitor visitor(firstPerpendicularLine, this->perpendicular, this->isValid);
	this->perpendicularEntity->Accept(&visitor);
}

void ShBothPerpendicularVisitor::Visit(ShCircle *firstPerpendicularCircle) {

}

void ShBothPerpendicularVisitor::Visit(ShArc *firstPerpendicularArc) {


}

/////////////////////////////////////////////////////////////////////////////////////////////

ShFirstLinePerpendicularVisitor::ShFirstLinePerpendicularVisitor(ShLine *firstLine, ShPoint3d &perpendicular,
	bool &isValid)
	:firstLine(firstLine), perpendicular(perpendicular), isValid(isValid) {

}

ShFirstLinePerpendicularVisitor::~ShFirstLinePerpendicularVisitor() {

}


void ShFirstLinePerpendicularVisitor::Visit(ShLine *secondPerpendicularLine) {
	
	double angle = Math::GetAbsAngle(secondPerpendicularLine->GetStart().x, secondPerpendicularLine->GetStart().y,
		secondPerpendicularLine->GetEnd().x, secondPerpendicularLine->GetEnd().y);
	double angle2 = Math::GetAbsAngle(this->firstLine->GetStart().x, this->firstLine->GetStart().y,
		this->firstLine->GetEnd().x, this->firstLine->GetEnd().y);



	if (Math::Compare(Math::GetAngleDifference(angle, angle2), 180) == 0 ||
		Math::Compare(Math::GetAngleDifference(angle, angle2, false), 180) == 0 ||
		Math::Compare(Math::GetAngleDifference(angle, angle2), 0) == 0) {

		this->isValid = true;
		return;
	}
	
	this->isValid = false;
}

#include "Visitor Pattern\ShFootOfPerpendicularVisitor.h"
void ShFirstLinePerpendicularVisitor::Visit(ShCircle *secondPerpendicularCircle) {

	ShPoint3d center = secondPerpendicularCircle->GetCenter();
	double radius = secondPerpendicularCircle->GetRadius();

	ShPoint3d point;
	ShFootOfPerpendicularVisitor visitor(point.x, point.y, center);
	this->firstLine->Accept(&visitor);


	double angle = Math::GetAbsAngle(center.x, center.y, point.x, point.y);
	Math::Rotate(angle, center.x, center.y, center.x + radius, center.y, this->perpendicular.x, this->perpendicular.y);


	this->isValid = true;

}

void ShFirstLinePerpendicularVisitor::Visit(ShArc *secondPerpendicularArc) {


}

///////////////////////////////////////////////////////////////////////
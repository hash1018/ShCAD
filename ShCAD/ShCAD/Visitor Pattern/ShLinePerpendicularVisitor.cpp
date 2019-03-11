

#include "ShLineBothPerpendicularVisitor.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "ShMath.h"
ShLineBothPerpendicularVisitor::ShLineBothPerpendicularVisitor(ShEntity *secondPerpendicularEntity, ShPoint3d &perpendicular,
	bool &isValid)
	:secondPerpendicularEntity(secondPerpendicularEntity), perpendicular(perpendicular), isValid(isValid) {

}

ShLineBothPerpendicularVisitor::~ShLineBothPerpendicularVisitor() {

}

void ShLineBothPerpendicularVisitor::Visit(ShLine *firstPerpendicularLine) {

	ShFirstLinePerpendicularVisitor visitor(firstPerpendicularLine, this->perpendicular, this->isValid);
	this->secondPerpendicularEntity->Accept(&visitor);
}

void ShLineBothPerpendicularVisitor::Visit(ShCircle *firstPerpendicularCircle) {

	ShFirstCirclePerpendicularVisitor visitor(firstPerpendicularCircle, this->perpendicular, this->isValid);
	this->secondPerpendicularEntity->Accept(&visitor);
}

void ShLineBothPerpendicularVisitor::Visit(ShArc *firstPerpendicularArc) {

	ShFirstArcPerpendicularVisitor visitor(firstPerpendicularArc, this->perpendicular, this->isValid);
	this->secondPerpendicularEntity->Accept(&visitor);

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

	ShPoint3d center = secondPerpendicularArc->GetCenter();
	
	ShPoint3d point;
	ShFootOfPerpendicularVisitor visitor(point.x, point.y, center);
	this->firstLine->Accept(&visitor);


	double angle = Math::GetAbsAngle(center.x, center.y, point.x, point.y);

	if (Math::CheckAngleLiesOnAngleBetween(secondPerpendicularArc->GetStartAngle(),
		secondPerpendicularArc->GetEndAngle(), angle) == true) {

		double radius = secondPerpendicularArc->GetRadius();
		Math::Rotate(angle, center.x, center.y, center.x + radius, center.y, this->perpendicular.x, this->perpendicular.y);
		this->isValid = true;
	}
	else {
		if (Math::CheckAngleLiesOnAngleBetween(Math::AddAngle(secondPerpendicularArc->GetStartAngle(), 180),
			Math::AddAngle(secondPerpendicularArc->GetEndAngle(), 180), angle) == true) {
		
			ShFootOfPerpendicularVisitor visitor(this->perpendicular.x, this->perpendicular.y, point);
			secondPerpendicularArc->Accept(&visitor);
			this->isValid = true;
		}
		else
			this->isValid = false;
	}
}

///////////////////////////////////////////////////////////////////////

ShFirstCirclePerpendicularVisitor::ShFirstCirclePerpendicularVisitor(ShCircle *firstCircle, ShPoint3d &perpendicular, bool &isValid)
	:firstCircle(firstCircle), perpendicular(perpendicular), isValid(isValid) {

}

ShFirstCirclePerpendicularVisitor::~ShFirstCirclePerpendicularVisitor() {

}


void ShFirstCirclePerpendicularVisitor::Visit(ShLine *secondPerpendicularLine) {

	ShPoint3d center = this->firstCircle->GetCenter();
	
	ShFootOfPerpendicularVisitor visitor(this->perpendicular.x, this->perpendicular.y, center);
	secondPerpendicularLine->Accept(&visitor);

	this->isValid = true;
}

void ShFirstCirclePerpendicularVisitor::Visit(ShCircle *secondPerpendicularCircle) {

	ShPoint3d center = this->firstCircle->GetCenter();

	ShFootOfPerpendicularVisitor visitor(this->perpendicular.x, this->perpendicular.y, center);
	secondPerpendicularCircle->Accept(&visitor);

	this->isValid = true;
}

void ShFirstCirclePerpendicularVisitor::Visit(ShArc *secondPerpendicularArc) {

	ShPoint3d center = this->firstCircle->GetCenter();

	double angle = Math::GetAbsAngle(secondPerpendicularArc->GetCenter().x,
		secondPerpendicularArc->GetCenter().y, center.x, center.y);

	if (Math::CheckAngleLiesOnAngleBetween(secondPerpendicularArc->GetStartAngle(),
		secondPerpendicularArc->GetEndAngle(), angle) == true) {

		ShFootOfPerpendicularVisitor visitor(this->perpendicular.x, this->perpendicular.y, center);
		secondPerpendicularArc->Accept(&visitor);
		this->isValid = true;
	}
	else {
		if (Math::CheckAngleLiesOnAngleBetween(Math::AddAngle(secondPerpendicularArc->GetStartAngle(), 180),
			Math::AddAngle(secondPerpendicularArc->GetEndAngle(), 180), angle) == true) {

			ShFootOfPerpendicularVisitor visitor(this->perpendicular.x, this->perpendicular.y, center);
			secondPerpendicularArc->Accept(&visitor);
			this->isValid = true;
		}
		else {
			this->isValid = false;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

ShFirstArcPerpendicularVisitor::ShFirstArcPerpendicularVisitor(ShArc *firstArc, ShPoint3d &perpendicular, bool &isValid)
	:firstArc(firstArc), perpendicular(perpendicular), isValid(isValid) {

}

ShFirstArcPerpendicularVisitor::~ShFirstArcPerpendicularVisitor() {

}

void ShFirstArcPerpendicularVisitor::Visit(ShLine *secondPerpendicularLine) {

	ShPoint3d center = this->firstArc->GetCenter();

	ShPoint3d point;
	ShFootOfPerpendicularVisitor visitor(point.x, point.y, center);
	secondPerpendicularLine->Accept(&visitor);

	double angle = Math::GetAbsAngle(center.x, center.y, point.x, point.y);

	if (Math::CheckAngleLiesOnAngleBetween(this->firstArc->GetStartAngle(),
		this->firstArc->GetEndAngle(), angle) == true) {

		this->perpendicular = point;
		this->isValid = true;
	}
	else {

		if (Math::CheckAngleLiesOnAngleBetween(Math::AddAngle(this->firstArc->GetStartAngle(), 180),
			Math::AddAngle(this->firstArc->GetEndAngle(), 180), angle) == true) {

			this->perpendicular = point;
			this->isValid = true;

		}
		else
			this->isValid = false;
	}
}

void ShFirstArcPerpendicularVisitor::Visit(ShCircle *secondPerpendicularCircle) {

	ShPoint3d center = this->firstArc->GetCenter();

	ShPoint3d point;
	ShFootOfPerpendicularVisitor visitor(point.x, point.y, center);
	secondPerpendicularCircle->Accept(&visitor);

	double angle = Math::GetAbsAngle(center.x, center.y, point.x, point.y);

	if (Math::CheckAngleLiesOnAngleBetween(this->firstArc->GetStartAngle(),
		this->firstArc->GetEndAngle(), angle) == true) {

		this->perpendicular = point;
		this->isValid = true;
	}
	else {

		if (Math::CheckAngleLiesOnAngleBetween(Math::AddAngle(this->firstArc->GetStartAngle(), 180),
			Math::AddAngle(this->firstArc->GetEndAngle(), 180), angle) == true) {

			this->perpendicular = point;
			this->isValid = true;

		}
		else
			this->isValid = false;
	}
}

void ShFirstArcPerpendicularVisitor::Visit(ShArc *secondPerpendicularArc) {

	ShPoint3d firstCenter = this->firstArc->GetCenter();
	ShPoint3d secondCenter = secondPerpendicularArc->GetCenter();

	double firstAngle = Math::GetAbsAngle(firstCenter.x, firstCenter.y, secondCenter.x, secondCenter.y);
	double secondAngle = Math::GetAbsAngle(secondCenter.x, secondCenter.y, firstCenter.x, firstCenter.y);

	ShPoint3d point;

	if (Math::CheckAngleLiesOnAngleBetween(secondPerpendicularArc->GetStartAngle(),
		secondPerpendicularArc->GetEndAngle(), secondAngle) == true) {
	
		ShFootOfPerpendicularVisitor visitor(point.x, point.y, firstCenter);
		secondPerpendicularArc->Accept(&visitor);
	}
	else if (Math::CheckAngleLiesOnAngleBetween(Math::AddAngle(secondPerpendicularArc->GetStartAngle(), 180),
		Math::AddAngle(secondPerpendicularArc->GetEndAngle(), 180), secondAngle) == true) {
		
		ShFootOfPerpendicularVisitor visitor(point.x, point.y, firstCenter);
		secondPerpendicularArc->Accept(&visitor);
	}
	else {
		this->isValid = false;
		return;
	}


	if (Math::CheckAngleLiesOnAngleBetween(this->firstArc->GetStartAngle(),
		this->firstArc->GetEndAngle(), firstAngle) == true) {

		this->perpendicular = point;
		this->isValid = true;
	}
	else if (Math::CheckAngleLiesOnAngleBetween(Math::AddAngle(this->firstArc->GetStartAngle(), 180),
		Math::AddAngle(this->firstArc->GetEndAngle(), 180), firstAngle) == true) {
		this->perpendicular = point;
		this->isValid = true;
	}
	else
		this->isValid = false;
}

#include "ShLineBothPerpendicularVisitor.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Private\Algorithm\ShFootOfPerpendicularVisitor.h"
#include "Entity\Leaf\ShArc.h"

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

void ShLineBothPerpendicularVisitor::visit(ShArc *arc) {

	ShFirstArcPerpendicularVisitor visitor(arc, this->perpendicular, this->isValid);
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
	ShFootOfPerpendicularForLinePerpendicularVisitor visitor(point.x, point.y, center);
	this->firstLine->accept(&visitor);


	double angle = math::getAbsAngle(center.x, center.y, point.x, point.y);
	math::rotate(angle, center.x, center.y, center.x + radius, center.y, this->perpendicular.x, this->perpendicular.y);


	this->isValid = true;
}

void ShFirstLinePerpendicularVisitor::visit(ShArc *arc) {

	ShPoint3d center = arc->getCenter();

	ShPoint3d point;
	ShFootOfPerpendicularForLinePerpendicularVisitor visitor(point.x, point.y, center);
	this->firstLine->accept(&visitor);


	double angle = math::getAbsAngle(center.x, center.y, point.x, point.y);

	if (math::checkAngleLiesOnAngleBetween(arc->getStartAngle(),
		arc->getEndAngle(), angle) == true) {

		double radius = arc->getRadius();
		math::rotate(angle, center.x, center.y, center.x + radius, center.y, this->perpendicular.x, this->perpendicular.y);
		this->isValid = true;
	}
	else {
		if (math::checkAngleLiesOnAngleBetween(math::addAngle(arc->getStartAngle(), 180),
			math::addAngle(arc->getEndAngle(), 180), angle) == true) {

			ShFootOfPerpendicularForLinePerpendicularVisitor visitor(this->perpendicular.x, this->perpendicular.y, point);
			arc->accept(&visitor);
			this->isValid = true;
		}
		else
			this->isValid = false;
	}
}

//////////////////////////////////////////////////////////////////////////

ShFirstCirclePerpendicularVisitor::ShFirstCirclePerpendicularVisitor(ShCircle *firstCircle, ShPoint3d &perpendicular, bool &isValid)
	:firstCircle(firstCircle), perpendicular(perpendicular), isValid(isValid) {

}

ShFirstCirclePerpendicularVisitor::~ShFirstCirclePerpendicularVisitor() {

}

void ShFirstCirclePerpendicularVisitor::visit(ShLine *line) {

	ShPoint3d center = this->firstCircle->getCenter();

	ShFootOfPerpendicularForLinePerpendicularVisitor visitor(this->perpendicular.x, this->perpendicular.y, center);
	line->accept(&visitor);

	this->isValid = true;
}

void ShFirstCirclePerpendicularVisitor::visit(ShCircle *circle) {

	ShPoint3d center = this->firstCircle->getCenter();

	ShFootOfPerpendicularForLinePerpendicularVisitor visitor(this->perpendicular.x, this->perpendicular.y, center);
	circle->accept(&visitor);

	this->isValid = true;

}

void ShFirstCirclePerpendicularVisitor::visit(ShArc *arc) {

	ShPoint3d center = this->firstCircle->getCenter();

	double angle = math::getAbsAngle(arc->getCenter().x,
		arc->getCenter().y, center.x, center.y);

	if (math::checkAngleLiesOnAngleBetween(arc->getStartAngle(),
		arc->getEndAngle(), angle) == true) {

		ShFootOfPerpendicularForLinePerpendicularVisitor visitor(this->perpendicular.x, this->perpendicular.y, center);
		arc->accept(&visitor);
		this->isValid = true;
	}
	else {
		if (math::checkAngleLiesOnAngleBetween(math::addAngle(arc->getStartAngle(), 180),
			math::addAngle(arc->getEndAngle(), 180), angle) == true) {

			ShFootOfPerpendicularForLinePerpendicularVisitor visitor(this->perpendicular.x, this->perpendicular.y, center);
			arc->accept(&visitor);
			this->isValid = true;
		}
		else {
			this->isValid = false;
		}
	}
}


/////////////////////////////////////////////////////////////////////

ShFirstArcPerpendicularVisitor::ShFirstArcPerpendicularVisitor(ShArc *firstArc, ShPoint3d &perpendicular, bool &isValid)
	:firstArc(firstArc), perpendicular(perpendicular), isValid(isValid) {

}

ShFirstArcPerpendicularVisitor::~ShFirstArcPerpendicularVisitor() {

}

void ShFirstArcPerpendicularVisitor::visit(ShLine *line) {

	ShPoint3d center = this->firstArc->getCenter();

	ShPoint3d point;
	ShFootOfPerpendicularForLinePerpendicularVisitor visitor(point.x, point.y, center);
	line->accept(&visitor);

	double angle = math::getAbsAngle(center.x, center.y, point.x, point.y);

	if (math::checkAngleLiesOnAngleBetween(this->firstArc->getStartAngle(),
		this->firstArc->getEndAngle(), angle) == true) {

		this->perpendicular = point;
		this->isValid = true;
	}
	else {

		if (math::checkAngleLiesOnAngleBetween(math::addAngle(this->firstArc->getStartAngle(), 180),
			math::addAngle(this->firstArc->getEndAngle(), 180), angle) == true) {

			this->perpendicular = point;
			this->isValid = true;

		}
		else
			this->isValid = false;
	}
}

void ShFirstArcPerpendicularVisitor::visit(ShCircle *circle) {

	ShPoint3d center = this->firstArc->getCenter();

	ShPoint3d point;
	ShFootOfPerpendicularForLinePerpendicularVisitor visitor(point.x, point.y, center);
	circle->accept(&visitor);

	double angle = math::getAbsAngle(center.x, center.y, point.x, point.y);

	if (math::checkAngleLiesOnAngleBetween(this->firstArc->getStartAngle(),
		this->firstArc->getEndAngle(), angle) == true) {

		this->perpendicular = point;
		this->isValid = true;
	}
	else {

		if (math::checkAngleLiesOnAngleBetween(math::addAngle(this->firstArc->getStartAngle(), 180),
			math::addAngle(this->firstArc->getEndAngle(), 180), angle) == true) {

			this->perpendicular = point;
			this->isValid = true;

		}
		else
			this->isValid = false;
	}
}

void ShFirstArcPerpendicularVisitor::visit(ShArc *arc) {

	ShPoint3d firstCenter = this->firstArc->getCenter();
	ShPoint3d secondCenter = arc->getCenter();

	double firstAngle = math::getAbsAngle(firstCenter.x, firstCenter.y, secondCenter.x, secondCenter.y);
	double secondAngle = math::getAbsAngle(secondCenter.x, secondCenter.y, firstCenter.x, firstCenter.y);

	ShPoint3d point;

	if (math::checkAngleLiesOnAngleBetween(arc->getStartAngle(),
		arc->getEndAngle(), secondAngle) == true) {

		ShFootOfPerpendicularForLinePerpendicularVisitor visitor(point.x, point.y, firstCenter);
		arc->accept(&visitor);
	}
	else if (math::checkAngleLiesOnAngleBetween(math::addAngle(arc->getStartAngle(), 180),
		math::addAngle(arc->getEndAngle(), 180), secondAngle) == true) {

		ShFootOfPerpendicularForLinePerpendicularVisitor visitor(point.x, point.y, firstCenter);
		arc->accept(&visitor);
	}
	else {
		this->isValid = false;
		return;
	}


	if (math::checkAngleLiesOnAngleBetween(this->firstArc->getStartAngle(),
		this->firstArc->getEndAngle(), firstAngle) == true) {

		this->perpendicular = point;
		this->isValid = true;
	}
	else if (math::checkAngleLiesOnAngleBetween(math::addAngle(this->firstArc->getStartAngle(), 180),
		math::addAngle(this->firstArc->getEndAngle(), 180), firstAngle) == true) {
		this->perpendicular = point;
		this->isValid = true;
	}
	else
		this->isValid = false;
}
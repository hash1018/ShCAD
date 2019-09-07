
#include "ShClosestIntersectionPointFinder.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"


ShClosestIntersectionPointFinder::ShClosestIntersectionPointFinder(const ShPoint3d &base, ShEntity *another, ShPoint3d &intersect, bool &valid)
	:base(base), another(another), intersect(intersect), valid(valid) {

}

ShClosestIntersectionPointFinder::~ShClosestIntersectionPointFinder() {

}

void ShClosestIntersectionPointFinder::visit(ShLine *line) {

	ShLineClosestIntersectionPointFinder visitor(this->base, line, this->intersect, this->valid);
	this->another->accept(&visitor);
}

void ShClosestIntersectionPointFinder::visit(ShCircle *circle) {

	ShCircleClosestIntersectionPointFinder visitor(this->base, circle, this->intersect, this->valid);
	this->another->accept(&visitor);
}

void ShClosestIntersectionPointFinder::visit(ShArc *arc) {

	ShArcClosestIntersectionPointFinder visitor(this->base, arc, this->intersect, this->valid);
	this->another->accept(&visitor);
}


/////////////////////////////////////////////////////////////////////////


ShLineClosestIntersectionPointFinder::ShLineClosestIntersectionPointFinder(const ShPoint3d &base, ShLine *another, ShPoint3d &intersect, bool &valid)
	:base(base), another(another), intersect(intersect), valid(valid) {

}

ShLineClosestIntersectionPointFinder::~ShLineClosestIntersectionPointFinder() {

}

void ShLineClosestIntersectionPointFinder::visit(ShLine *line) {

	this->valid = math::checkLineLineIntersect(line->getStart(), line->getEnd(),
		this->another->getStart(), this->another->getEnd(), this->intersect);
		
}

void ShLineClosestIntersectionPointFinder::visit(ShCircle *circle) {

	ShPoint3d intersect, intersect2;

	this->valid = math::checkCircleLineIntersect(circle->getCenter(), circle->getRadius(), 
		this->another->getStart(), this->another->getEnd(), intersect, intersect2);

	if (this->valid == false)
		return;

	double disIntersect = math::getDistance(this->base.x, this->base.y, intersect.x, intersect.y);
	double disIntersect2 = math::getDistance(this->base.x, this->base.y, intersect2.x, intersect2.y);

	if (math::compare(disIntersect, disIntersect2) == 1)
		this->intersect = intersect2;
	else
		this->intersect = intersect;
}

void ShLineClosestIntersectionPointFinder::visit(ShArc *arc) {

	ShPoint3d intersect, intersect2;

	this->valid = math::checkCircleLineIntersect(arc->getCenter(), arc->getRadius(),
		this->another->getStart(), this->another->getEnd(), intersect, intersect2);

	if (this->valid == false)
		return;

	double disIntersect = math::getDistance(this->base.x, this->base.y, intersect.x, intersect.y);
	double disIntersect2 = math::getDistance(this->base.x, this->base.y, intersect2.x, intersect2.y);

	if (math::compare(disIntersect, disIntersect2) == 1)
		this->intersect = intersect2;
	else
		this->intersect = intersect;

}

/////////////////////////////////////////////////////////////////////////

ShCircleClosestIntersectionPointFinder::ShCircleClosestIntersectionPointFinder(const ShPoint3d &base, ShCircle *another, ShPoint3d &intersect, bool &valid)
	:base(base), another(another), intersect(intersect), valid(valid) {

}

ShCircleClosestIntersectionPointFinder::~ShCircleClosestIntersectionPointFinder() {

}

void ShCircleClosestIntersectionPointFinder::visit(ShLine *line) {

	ShPoint3d intersect, intersect2;

	this->valid = math::checkCircleLineIntersect(this->another->getCenter(), this->another->getRadius(),
		line->getStart(), line->getEnd(), intersect, intersect2);

	if (this->valid == false)
		return;

	double disIntersect = math::getDistance(this->base.x, this->base.y, intersect.x, intersect.y);
	double disIntersect2 = math::getDistance(this->base.x, this->base.y, intersect2.x, intersect2.y);

	if (math::compare(disIntersect, disIntersect2) == 1)
		this->intersect = intersect2;
	else
		this->intersect = intersect;
}

void ShCircleClosestIntersectionPointFinder::visit(ShCircle *circle) {

	ShPoint3d intersect, intersect2;

	this->valid = math::checkTwoCirclesIntersect(this->another->getCenter(), this->another->getRadius(),
		circle->getCenter(), circle->getRadius(), intersect, intersect2);

	if (this->valid == false)
		return;

	double disIntersect = math::getDistance(this->base.x, this->base.y, intersect.x, intersect.y);
	double disIntersect2 = math::getDistance(this->base.x, this->base.y, intersect2.x, intersect2.y);

	if (math::compare(disIntersect, disIntersect2) == 1)
		this->intersect = intersect2;
	else
		this->intersect = intersect;
}

void ShCircleClosestIntersectionPointFinder::visit(ShArc *arc) {

	ShPoint3d intersect, intersect2;

	this->valid = math::checkTwoCirclesIntersect(this->another->getCenter(), this->another->getRadius(),
		arc->getCenter(), arc->getRadius(), intersect, intersect2);

	if (this->valid == false)
		return;

	double disIntersect = math::getDistance(this->base.x, this->base.y, intersect.x, intersect.y);
	double disIntersect2 = math::getDistance(this->base.x, this->base.y, intersect2.x, intersect2.y);

	if (math::compare(disIntersect, disIntersect2) == 1)
		this->intersect = intersect2;
	else
		this->intersect = intersect;
}


/////////////////////////////////////////////////////////////////////////

ShArcClosestIntersectionPointFinder::ShArcClosestIntersectionPointFinder(const ShPoint3d &base, ShArc *another, ShPoint3d &intersect, bool &valid)
	:base(base), another(another), intersect(intersect), valid(valid) {

}

ShArcClosestIntersectionPointFinder::~ShArcClosestIntersectionPointFinder() {

}

void ShArcClosestIntersectionPointFinder::visit(ShLine *line) {

	ShPoint3d intersect, intersect2;

	this->valid = math::checkCircleLineIntersect(this->another->getCenter(), this->another->getRadius(),
		line->getStart(), line->getEnd(), intersect, intersect2);

	if (this->valid == false)
		return;

	double disIntersect = math::getDistance(this->base.x, this->base.y, intersect.x, intersect.y);
	double disIntersect2 = math::getDistance(this->base.x, this->base.y, intersect2.x, intersect2.y);

	if (math::compare(disIntersect, disIntersect2) == 1)
		this->intersect = intersect2;
	else
		this->intersect = intersect;
}

void ShArcClosestIntersectionPointFinder::visit(ShCircle *circle) {

	ShPoint3d intersect, intersect2;

	this->valid = math::checkTwoCirclesIntersect(this->another->getCenter(), this->another->getRadius(),
		circle->getCenter(), circle->getRadius(), intersect, intersect2);

	if (this->valid == false)
		return;

	double disIntersect = math::getDistance(this->base.x, this->base.y, intersect.x, intersect.y);
	double disIntersect2 = math::getDistance(this->base.x, this->base.y, intersect2.x, intersect2.y);

	if (math::compare(disIntersect, disIntersect2) == 1)
		this->intersect = intersect2;
	else
		this->intersect = intersect;
}

void ShArcClosestIntersectionPointFinder::visit(ShArc *arc) {

	ShPoint3d intersect, intersect2;

	this->valid = math::checkTwoCirclesIntersect(this->another->getCenter(), this->another->getRadius(),
		arc->getCenter(), arc->getRadius(), intersect, intersect2);

	if (this->valid == false)
		return;

	double disIntersect = math::getDistance(this->base.x, this->base.y, intersect.x, intersect.y);
	double disIntersect2 = math::getDistance(this->base.x, this->base.y, intersect2.x, intersect2.y);

	if (math::compare(disIntersect, disIntersect2) == 1)
		this->intersect = intersect2;
	else
		this->intersect = intersect;
}
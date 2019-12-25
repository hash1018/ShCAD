
#include "ShOffsetVisitor.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Base\ShMath.h"
#include "Entity\Private\Algorithm\ShFootOfPerpendicularVisitor.h"
#include "Entity\Leaf\ShConstructionLine.h"

ShOffsetVisitor::ShOffsetVisitor(double offsetDistance, const ShPoint3d &mouse, ShEntity *original)
	:offsetDistance(offsetDistance), mouse(mouse), original(original) {

}

ShOffsetVisitor::~ShOffsetVisitor() {

}

void ShOffsetVisitor::visit(ShLine *line) {

	if (!dynamic_cast<ShLine*>(this->original))
		return;

	ShPoint3d perpendicular;
	ShFootOfPerpendicularVisitor visitor(perpendicular.x, perpendicular.y, this->mouse);
	this->original->accept(&visitor);

	double angle = math::getAbsAngle(perpendicular.x, perpendicular.y, this->mouse.x, this->mouse.y);

	ShLineData data = dynamic_cast<ShLine*>(original)->getData();

	math::rotate(angle, data.start.x, data.start.y, data.start.x + this->offsetDistance, data.start.y, data.start.x, data.start.y);
	math::rotate(angle, data.end.x, data.end.y, data.end.x + this->offsetDistance, data.end.y, data.end.x, data.end.y);

	line->setData(data);
}

void ShOffsetVisitor::visit(ShCircle *circle) {

	if (!dynamic_cast<ShCircle*>(this->original))
		return;

	ShCircle *original = dynamic_cast<ShCircle*>(this->original);
	double distance = math::getDistance(original->getCenter().x, original->getCenter().y, this->mouse.x, this->mouse.y);
	double radius;

	if (distance > original->getRadius()) {
	
		radius = original->getRadius() + this->offsetDistance;
	}
	else {
	
		radius = original->getRadius() - this->offsetDistance;

		if (radius <= 0) {
			radius = original->getRadius() + this->offsetDistance;
		}
	}

	circle->setRadius(radius);
}

void ShOffsetVisitor::visit(ShArc *arc) {

	if (!dynamic_cast<ShArc*>(this->original))
		return;

	ShArc *original = dynamic_cast<ShArc*>(this->original);
	double distance = math::getDistance(original->getCenter().x, original->getCenter().y, this->mouse.x, this->mouse.y);
	double radius;

	if (distance > original->getRadius()) {

		radius = original->getRadius() + this->offsetDistance;
	}
	else {

		radius = original->getRadius() - this->offsetDistance;

		if (radius <= 0) {
			radius = original->getRadius() + this->offsetDistance;
		}
	}

	arc->setRadius(radius);
}

void ShOffsetVisitor::visit(ShConstructionLine *constructionLine) {

	if (!dynamic_cast<ShConstructionLine*>(this->original))
		return;

	ShPoint3d perpendicular;
	ShFootOfPerpendicularVisitor visitor(perpendicular.x, perpendicular.y, this->mouse);
	this->original->accept(&visitor);

	double angle = math::getAbsAngle(perpendicular.x, perpendicular.y, this->mouse.x, this->mouse.y);

	ShLineData data = dynamic_cast<ShConstructionLine*>(original)->getData();

	math::rotate(angle, data.start.x, data.start.y, data.start.x + this->offsetDistance, data.start.y, data.start.x, data.start.y);
	math::rotate(angle, data.end.x, data.end.y, data.end.x + this->offsetDistance, data.end.y, data.end.x, data.end.y);

	constructionLine->setData(data);
}
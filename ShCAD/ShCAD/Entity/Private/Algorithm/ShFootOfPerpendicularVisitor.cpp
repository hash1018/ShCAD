
#include "ShFootOfPerpendicularVisitor.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Leaf\ShConstructionLine.h"

ShFootOfPerpendicularForLinePerpendicularVisitor::ShFootOfPerpendicularForLinePerpendicularVisitor(double &perpendicularX, double &perpendicularY,
	const ShPoint3d& point)
	:perpendicularX(perpendicularX), perpendicularY(perpendicularY), point(point) {


}


ShFootOfPerpendicularForLinePerpendicularVisitor::~ShFootOfPerpendicularForLinePerpendicularVisitor() {

}

void ShFootOfPerpendicularForLinePerpendicularVisitor::visit(ShLine *line) {

	ShLineData data = line->getData();

	double angle = math::getAbsAngle(data.start.x, data.start.y, data.end.x, data.end.y);
	double angleX, angleY;

	double x = point.x;
	double y = point.y;

	math::rotate(angle + 90, x, y, x + 10, y, angleX, angleY);
	ShPoint3d intersect;

	if (math::checkLineLineIntersect(data.start, data.end, ShPoint3d(x, y),
		ShPoint3d(angleX, angleY), intersect) == true) {

		this->perpendicularX = intersect.x;
		this->perpendicularY = intersect.y;

		return;
	}
}

void ShFootOfPerpendicularForLinePerpendicularVisitor::visit(ShCircle *circle) {

	ShCircleData data = circle->getData();

	double angle = math::getAbsAngle(data.center.x, data.center.y, this->point.x, this->point.y);
	math::rotate(angle, data.center.x, data.center.y, data.center.x + data.radius, data.center.y,
		this->perpendicularX, this->perpendicularY);
}

void ShFootOfPerpendicularForLinePerpendicularVisitor::visit(ShArc *arc) {

	ShArcData data = arc->getData();

	double angle = math::getAbsAngle(data.center.x, data.center.y, this->point.x, this->point.y);

	if (math::checkAngleLiesOnAngleBetween(arc->getStartAngle(),
		arc->getEndAngle(), angle) == true) {

		math::rotate(angle, data.center.x, data.center.y, data.center.x + data.radius, data.center.y,
			this->perpendicularX, this->perpendicularY);
	}
	else {

		if (math::checkAngleLiesOnAngleBetween(math::addAngle(arc->getStartAngle(), 180),
			math::addAngle(arc->getEndAngle(), 180), angle) == true) {

			math::rotate(angle + 180, data.center.x, data.center.y, data.center.x + data.radius, data.center.y,
				this->perpendicularX, this->perpendicularY);
		}
		else {
			this->perpendicularX = arc->getEnd().x;
			this->perpendicularY = arc->getEnd().y;
		}

	}
}

void ShFootOfPerpendicularForLinePerpendicularVisitor::visit(ShConstructionLine *constructionLine) {

	ShLineData data = constructionLine->getData();

	double angle = math::getAbsAngle(data.start.x, data.start.y, data.end.x, data.end.y);
	double angleX, angleY;

	double x = point.x;
	double y = point.y;

	math::rotate(angle + 90, x, y, x + 10, y, angleX, angleY);
	ShPoint3d intersect;

	if (math::checkLineLineIntersect(data.start, data.end, ShPoint3d(x, y),
		ShPoint3d(angleX, angleY), intersect) == true) {

		this->perpendicularX = intersect.x;
		this->perpendicularY = intersect.y;

		return;
	}
}

///////////////////////////////////////////////////////////////////////////////

ShFootOfPerpendicularVisitor::ShFootOfPerpendicularVisitor(double &perpendicularX, double &perpendicularY,
	const ShPoint3d& point)
	:perpendicularX(perpendicularX), perpendicularY(perpendicularY), point(point) {


}


ShFootOfPerpendicularVisitor::~ShFootOfPerpendicularVisitor() {

}

void ShFootOfPerpendicularVisitor::visit(ShLine *line) {

	ShLineData data = line->getData();

	double angle = math::getAbsAngle(data.start.x, data.start.y, data.end.x, data.end.y);
	double angleX, angleY;

	double x = point.x;
	double y = point.y;

	math::rotate(angle + 90, x, y, x + 10, y, angleX, angleY);
	ShPoint3d intersect;

	if (math::checkLineLineIntersect(data.start, data.end, ShPoint3d(x, y),
		ShPoint3d(angleX, angleY), intersect) == true) {

		this->perpendicularX = intersect.x;
		this->perpendicularY = intersect.y;

		return;
	}
}

void ShFootOfPerpendicularVisitor::visit(ShCircle *circle) {

	ShCircleData data = circle->getData();

	double angle = math::getAbsAngle(data.center.x, data.center.y, this->point.x, this->point.y);
	math::rotate(angle, data.center.x, data.center.y, data.center.x + data.radius, data.center.y,
		this->perpendicularX, this->perpendicularY);
}

void ShFootOfPerpendicularVisitor::visit(ShArc *arc) {

	ShArcData data = arc->getData();

	double angle = math::getAbsAngle(data.center.x, data.center.y, this->point.x, this->point.y);
	math::rotate(angle, data.center.x, data.center.y, data.center.x + data.radius, data.center.y,
		this->perpendicularX, this->perpendicularY);
}

void ShFootOfPerpendicularVisitor::visit(ShConstructionLine *constructionLine) {

	ShLineData data = constructionLine->getData();

	double angle = math::getAbsAngle(data.start.x, data.start.y, data.end.x, data.end.y);
	double angleX, angleY;

	double x = point.x;
	double y = point.y;

	math::rotate(angle + 90, x, y, x + 10, y, angleX, angleY);
	ShPoint3d intersect;

	if (math::checkLineLineIntersect(data.start, data.end, ShPoint3d(x, y),
		ShPoint3d(angleX, angleY), intersect) == true) {

		this->perpendicularX = intersect.x;
		this->perpendicularY = intersect.y;

		return;
	}
}
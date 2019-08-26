
#include "ShSnapPointFinder.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShMath.h"
#include "ShFootOfPerpendicularVisitor.h"
#include "Entity\Leaf\ShCircle.h"

ShSnapPointFinder::ShSnapPointFinder(ObjectSnap objectSnap, double x, double y, double &snapX, double &snapY, bool &isValid)
	:objectSnap(objectSnap), x(x), y(y), snapX(snapX), snapY(snapY), isValid(isValid), mode(Mode::Normal) {

}

ShSnapPointFinder::ShSnapPointFinder(ObjectSnap objectSnap, double x, double y, double &snapX, double &snapY, bool &isValid,
	double perpendicularX, double perpendicularY)
	: objectSnap(objectSnap), x(x), y(y), snapX(snapX), snapY(snapY), isValid(isValid), mode(Mode::FootOfPerpendicular),
	perpendicularX(perpendicularX), perpendicularY(perpendicularY) {


}


ShSnapPointFinder::~ShSnapPointFinder() {

}

void ShSnapPointFinder::visit(ShLine *line) {

	if (this->objectSnap == ObjectSnap::ObjectSnapEndPoint) {
	
		ShLineData data = line->getData();
		ShPoint3d start = data.start;
		ShPoint3d end = data.end;

		double disStart = math::getDistance(this->x, this->y, start.x, start.y);
		double disEnd = math::getDistance(this->x, this->y, end.x, end.y);

		if (math::compare(disStart, disEnd) == 1) {
			this->snapX = end.x;
			this->snapY = end.y;
		}
		else {
			this->snapX = start.x;
			this->snapY = start.y;
		}

		this->isValid = true;
		return;
	
	}
	else if (this->objectSnap == ObjectSnap::ObjectSnapMidPoint) {

		ShPoint3d mid = line->getMid();

		this->snapX = mid.x;
		this->snapY = mid.y;
		this->isValid = true;
		return;
	}
	else if (this->objectSnap == ObjectSnap::ObjectSnapPerpendicular) {

		double x, y;

		if (mode == Mode::Normal) {
			x = this->x;
			y = this->y;
		}
		else {
			x = this->perpendicularX;
			y = this->perpendicularY;
		}

		ShFootOfPerpendicularVisitor visitor(this->snapX, this->snapY, ShPoint3d(x, y));
		line->accept(&visitor);

		this->isValid = true;
		return;

	}

	this->isValid = false;
}

void ShSnapPointFinder::visit(ShCircle *circle) {

	if (this->objectSnap == ObjectSnap::ObjectSnapQuadrant) {

		ShPoint3d center = circle->getCenter();
		double radius = circle->getRadius();

		double angle = math::getAbsAngle(center.x, center.y, this->x, this->y);

		//315 degree ~ 45 degree.
		if ((angle >= 315 && angle < 360) || (angle >= 0 && angle < 45)) {
			this->snapX = center.x + radius;
			this->snapY = center.y;
		}
		//45 degree ~ 135 degree.
		else if (angle >= 45 && angle < 135) {
			this->snapX = center.x;
			this->snapY = center.y + radius;
		}
		//135 degree ~ 225 degree
		else if (angle >= 135 && angle < 225) {
			this->snapX = center.x - radius;
			this->snapY = center.y;
		}
		//225 degree ~ 315 degree
		else {
			this->snapX = center.x;
			this->snapY = center.y - radius;
		}

		this->isValid = true;
		return;
	}
	else if (this->objectSnap == ObjectSnap::ObjectSnapCenter) {

		this->snapX = circle->getCenter().x;
		this->snapY = circle->getCenter().y;
		this->isValid = true;
		return;
	}
	else if (this->objectSnap == ObjectSnap::ObjectSnapPerpendicular) {

		double x, y;

		if (mode == Mode::Normal) {
			x = this->x;
			y = this->y;
		}
		else {
			x = this->perpendicularX;
			y = this->perpendicularY;
		}

		ShFootOfPerpendicularVisitor visitor(this->snapX, this->snapY, ShPoint3d(x, y));
		circle->accept(&visitor);

		this->isValid = true;
		return;
	}

	this->isValid = false;
}
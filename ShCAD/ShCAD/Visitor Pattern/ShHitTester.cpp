

#include "ShHitTester.h"
#include "ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
ShHitTester::ShHitTester(double x, double y, double zoomRate, HitPoint &hitPoint, double tolerance)
	:x(x), y(y), zoomRate(zoomRate), hitPoint(hitPoint), tolerance(tolerance) {

}

ShHitTester::~ShHitTester() {

}

void ShHitTester::Visit(ShLine *line) {

	ShLineData data = line->GetData();
	ShPoint3d start = data.start;
	ShPoint3d end = data.end;
	ShPoint3d mid = line->GetMid();

	if (this->x >= start.x - (this->tolerance / this->zoomRate) && 
		this->x <= start.x + (this->tolerance / this->zoomRate) &&
		this->y >= start.y - (this->tolerance / this->zoomRate) && 
		this->y <= start.y + (this->tolerance / this->zoomRate)) {

		this->hitPoint = HitPoint::HitStart;
		return;
	}

	if (this->x >= end.x - (this->tolerance / this->zoomRate) && 
		this->x <= end.x + (this->tolerance / this->zoomRate) &&
		this->y >= end.y- (this->tolerance / this->zoomRate) && 
		this->y <= end.y + (this->tolerance / this->zoomRate)) {

		this->hitPoint = HitPoint::HitEnd;
		return;
	}

	if (this->x >= mid.x - (this->tolerance / this->zoomRate) &&
		this->x <= mid.x + (this->tolerance / this->zoomRate) &&
		this->y >= mid.y - (this->tolerance / this->zoomRate) &&
		this->y <= mid.y + (this->tolerance / this->zoomRate)) {

		this->hitPoint = HitPoint::HitMid;
		return;
	}

	if (Math::CheckPointLiesOnLine(ShPoint3d(this->x, this->y), start, end, this->tolerance) == true)
		this->hitPoint = HitPoint::HitOther;
	else
		this->hitPoint = HitPoint::HitNothing;

}

void ShHitTester::Visit(ShCircle *circle) {

	ShPoint3d center = circle->GetCenter();
	double radius = circle->GetRadius();

	if (this->x >= center.x - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + (this->tolerance / this->zoomRate)) {

		this->hitPoint = HitPoint::HitCenter;
		return;
	}

	if (this->x >= center.x + radius - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + radius + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + (this->tolerance / this->zoomRate)) {

		this->hitPoint = HitPoint::HitRight;
		return;
	}

	if (this->x >= center.x - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - radius - (this->tolerance / this->zoomRate) &&
		this->y <= center.y - radius + (this->tolerance / this->zoomRate)) {

		this->hitPoint = HitPoint::HitBottom;
		return;
	}

	if (this->x >= center.x - radius - (this->tolerance / this->zoomRate) &&
		this->x <= center.x - radius + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + (this->tolerance / this->zoomRate)) {

		this->hitPoint = HitPoint::HitLeft;
		return;
	}

	if (this->x >= center.x - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + (this->tolerance / this->zoomRate) &&
		this->y >= center.y + radius - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + radius + (this->tolerance / this->zoomRate)) {

		this->hitPoint = HitPoint::HitTop;
		return;
	}

	if (Math::CheckPointLiesOnCircleBoundary(ShPoint3d(this->x, this->y), center, radius, this->tolerance)==true)
		this->hitPoint = HitPoint::HitOther;
	else
		this->hitPoint = HitPoint::HitNothing;
	
}

void ShHitTester::Visit(ShArc *arc) {


}
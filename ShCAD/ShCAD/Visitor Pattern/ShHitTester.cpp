

#include "ShHitTester.h"
#include "ShMath.h"
#include "Entity\Leaf\ShLine.h"
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


}

void ShHitTester::Visit(ShArc *arc) {


}
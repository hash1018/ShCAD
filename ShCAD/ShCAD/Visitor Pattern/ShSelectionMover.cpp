

#include "ShSelectionMover.h"
#include "Entity\Leaf\ShLine.h"
ShSelectionMover::ShSelectionMover(double x, double y)
	:x(x), y(y) {


}

ShSelectionMover::~ShSelectionMover() {

}

void ShSelectionMover::SetHitPoint(HitPoint hitPoint) {

	this->hitPoint = hitPoint;
}

void ShSelectionMover::Visit(ShLine *line) {

	ShLineData data = line->GetData();
	ShPoint3d start = data.start;
	ShPoint3d end = data.end;


	if (this->hitPoint == HitPoint::HitStart) {
		start.x = this->x;
		start.y = this->y;
	}
	else if (this->hitPoint == HitPoint::HitEnd) {
		end.x = this->x;
		end.y = this->y;
	}
	else if (this->hitPoint == HitPoint::HitMid) {
		ShPoint3d mid = line->GetMid();
		double disX = mid.x - this->x;
		double disY = mid.y - this->y;
		start.x -= disX;
		start.y -= disY;
		end.x -= disX;
		end.y -= disY;
	}

	line->SetData(ShLineData(start, end));

}

void ShSelectionMover::Visit(ShCircle *circle) {

}

void ShSelectionMover::Visit(ShArc *arc) {


}
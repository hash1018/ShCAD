

#include "ShHitTester.h"
#include "ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
ShHitTester::ShHitTester(double x, double y, double zoomRate, VertexPoint &vertexPoint, double tolerance)
	:x(x), y(y), zoomRate(zoomRate), vertexPoint(vertexPoint), tolerance(tolerance) {

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

		this->vertexPoint = VertexPoint::VertexStart;
		return;
	}

	if (this->x >= end.x - (this->tolerance / this->zoomRate) && 
		this->x <= end.x + (this->tolerance / this->zoomRate) &&
		this->y >= end.y- (this->tolerance / this->zoomRate) && 
		this->y <= end.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexEnd;
		return;
	}

	if (this->x >= mid.x - (this->tolerance / this->zoomRate) &&
		this->x <= mid.x + (this->tolerance / this->zoomRate) &&
		this->y >= mid.y - (this->tolerance / this->zoomRate) &&
		this->y <= mid.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexMid;
		return;
	}

	if (Math::CheckPointLiesOnLine(ShPoint3d(this->x, this->y), start, end, this->tolerance) == true)
		this->vertexPoint = VertexPoint::VertexOther;
	else
		this->vertexPoint = VertexPoint::VertexNothing;

}

void ShHitTester::Visit(ShCircle *circle) {

	ShPoint3d center = circle->GetCenter();
	double radius = circle->GetRadius();

	if (this->x >= center.x - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexCenter;
		return;
	}

	if (this->x >= center.x + radius - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + radius + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexRight;
		return;
	}

	if (this->x >= center.x - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - radius - (this->tolerance / this->zoomRate) &&
		this->y <= center.y - radius + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexBottom;
		return;
	}

	if (this->x >= center.x - radius - (this->tolerance / this->zoomRate) &&
		this->x <= center.x - radius + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexLeft;
		return;
	}

	if (this->x >= center.x - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + (this->tolerance / this->zoomRate) &&
		this->y >= center.y + radius - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + radius + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexTop;
		return;
	}

	if (Math::CheckPointLiesOnCircleBoundary(ShPoint3d(this->x, this->y), center, radius, this->tolerance)==true)
		this->vertexPoint = VertexPoint::VertexOther;
	else
		this->vertexPoint = VertexPoint::VertexNothing;
	
}

void ShHitTester::Visit(ShArc *arc) {

	ShPoint3d center = arc->GetCenter();

	if (this->x >= center.x - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexCenter;
		return;
	}

	ShPoint3d start = arc->GetStart();

	if (this->x >= start.x - (this->tolerance / this->zoomRate) &&
		this->x <= start.x + (this->tolerance / this->zoomRate) &&
		this->y >= start.y - (this->tolerance / this->zoomRate) &&
		this->y <= start.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexStart;
		return;
	}

	ShPoint3d end = arc->GetEnd();

	if (this->x >= end.x - (this->tolerance / this->zoomRate) &&
		this->x <= end.x + (this->tolerance / this->zoomRate) &&
		this->y >= end.y - (this->tolerance / this->zoomRate) &&
		this->y <= end.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexEnd;
		return;
	}

	ShPoint3d mid = arc->GetMid();

	if (this->x >= mid.x - (this->tolerance / this->zoomRate) &&
		this->x <= mid.x + (this->tolerance / this->zoomRate) &&
		this->y >= mid.y - (this->tolerance / this->zoomRate) &&
		this->y <= mid.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexMid;
		return;
	}

	if (Math::CheckPointLiesOnArcBoundary(ShPoint3d(this->x, this->y), center, arc->GetRadius(), arc->GetStartAngle(),
		arc->GetEndAngle(), tolerance) == true) 
		this->vertexPoint = VertexPoint::VertexOther;
	else
		this->vertexPoint = VertexPoint::VertexNothing;


}
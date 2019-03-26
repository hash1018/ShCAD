

#include "ShHitTester.h"
#include "ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Composite\ShPolyLine.h"
ShHitTester::ShHitTester(double x, double y, double zoomRate, VertexPoint &vertexPoint, ShPoint3d &vertex, double tolerance)
	:x(x), y(y), zoomRate(zoomRate), vertexPoint(vertexPoint), vertex(vertex), tolerance(tolerance) {

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
		this->vertex = start;
		return;
	}

	if (this->x >= end.x - (this->tolerance / this->zoomRate) && 
		this->x <= end.x + (this->tolerance / this->zoomRate) &&
		this->y >= end.y- (this->tolerance / this->zoomRate) && 
		this->y <= end.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexEnd;
		this->vertex = end;
		return;
	}

	if (this->x >= mid.x - (this->tolerance / this->zoomRate) &&
		this->x <= mid.x + (this->tolerance / this->zoomRate) &&
		this->y >= mid.y - (this->tolerance / this->zoomRate) &&
		this->y <= mid.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexMid;
		this->vertex = mid;
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
		this->vertex = center;
		return;
	}

	if (this->x >= center.x + radius - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + radius + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexRight;
		this->vertex.x = center.x + radius;
		this->vertex.y = center.y;
		return;
	}

	if (this->x >= center.x - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - radius - (this->tolerance / this->zoomRate) &&
		this->y <= center.y - radius + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexBottom;
		this->vertex.x = center.x;
		this->vertex.y = center.y - radius;
		return;
	}

	if (this->x >= center.x - radius - (this->tolerance / this->zoomRate) &&
		this->x <= center.x - radius + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexLeft;
		this->vertex.x = center.x - radius;
		this->vertex.y = center.y;
		return;
	}

	if (this->x >= center.x - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + (this->tolerance / this->zoomRate) &&
		this->y >= center.y + radius - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + radius + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexTop;
		this->vertex.x = center.x;
		this->vertex.y = center.y + radius;
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
		this->vertex = center;
		return;
	}

	ShPoint3d start = arc->GetStart();

	if (this->x >= start.x - (this->tolerance / this->zoomRate) &&
		this->x <= start.x + (this->tolerance / this->zoomRate) &&
		this->y >= start.y - (this->tolerance / this->zoomRate) &&
		this->y <= start.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexStart;
		this->vertex = start;
		return;
	}

	ShPoint3d end = arc->GetEnd();

	if (this->x >= end.x - (this->tolerance / this->zoomRate) &&
		this->x <= end.x + (this->tolerance / this->zoomRate) &&
		this->y >= end.y - (this->tolerance / this->zoomRate) &&
		this->y <= end.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexEnd;
		this->vertex = end;
		return;
	}

	ShPoint3d mid = arc->GetMid();

	if (this->x >= mid.x - (this->tolerance / this->zoomRate) &&
		this->x <= mid.x + (this->tolerance / this->zoomRate) &&
		this->y >= mid.y - (this->tolerance / this->zoomRate) &&
		this->y <= mid.y + (this->tolerance / this->zoomRate)) {

		this->vertexPoint = VertexPoint::VertexMid;
		this->vertex = mid;
		return;
	}

	if (Math::CheckPointLiesOnArcBoundary(ShPoint3d(this->x, this->y), center, arc->GetRadius(), arc->GetStartAngle(),
		arc->GetEndAngle(), tolerance) == true) 
		this->vertexPoint = VertexPoint::VertexOther;
	else
		this->vertexPoint = VertexPoint::VertexNothing;


}

void ShHitTester::Visit(ShPolyLine *polyLine) {

	VertexPoint vertexPoint = VertexPoint::VertexNothing;
	ShPoint3d vertex;
	ShHitTester visitor(this->x, this->y, this->zoomRate, vertexPoint, vertex, this->tolerance);

	QLinkedList<ShEntity*>::iterator itr = polyLine->Begin();
	while (itr != polyLine->End() && 
		(vertexPoint == VertexPoint::VertexNothing || 
			vertexPoint == VertexPoint::VertexOther)) {
	
		(*itr)->Accept(&visitor);
		++itr;
	}

	if (vertexPoint != VertexPoint::VertexNothing && vertexPoint != VertexPoint::VertexOther) {
		this->vertexPoint = vertexPoint;
		this->vertex = vertex;
	}
	else 
		this->vertexPoint = VertexPoint::VertexNothing;
	

}
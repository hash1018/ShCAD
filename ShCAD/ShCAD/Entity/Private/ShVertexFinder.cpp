
#include "ShVertexFinder.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"


ShNearestVertexFinder::ShNearestVertexFinder(double x, double y, double zoomRate, VertexType &vertexType, ShPoint3d &vertexPoint, double tolerance)
	:x(x), y(y), zoomRate(zoomRate), vertexType(vertexType), vertexPoint(vertexPoint), tolerance(tolerance) {

}

ShNearestVertexFinder::~ShNearestVertexFinder() {

}

void ShNearestVertexFinder::visit(ShLine *line) {

	ShLineData data = line->getData();
	ShPoint3d start = data.start;
	ShPoint3d end = data.end;
	ShPoint3d mid = line->getMid();

	if (this->x >= start.x - (this->tolerance / this->zoomRate) &&
		this->x <= start.x + (this->tolerance / this->zoomRate) &&
		this->y >= start.y - (this->tolerance / this->zoomRate) &&
		this->y <= start.y + (this->tolerance / this->zoomRate)) {

		this->vertexType = VertexType::VertexStart;
		this->vertexPoint = start;
		return;
	}

	if (this->x >= end.x - (this->tolerance / this->zoomRate) &&
		this->x <= end.x + (this->tolerance / this->zoomRate) &&
		this->y >= end.y - (this->tolerance / this->zoomRate) &&
		this->y <= end.y + (this->tolerance / this->zoomRate)) {

		this->vertexType = VertexType::VertexEnd;
		this->vertexPoint = end;
		return;
	}

	if (this->x >= mid.x - (this->tolerance / this->zoomRate) &&
		this->x <= mid.x + (this->tolerance / this->zoomRate) &&
		this->y >= mid.y - (this->tolerance / this->zoomRate) &&
		this->y <= mid.y + (this->tolerance / this->zoomRate)) {

		this->vertexType = VertexType::VertexMid;
		this->vertexPoint = mid;
		return;
	}

	if (math::checkPointLiesOnLine(ShPoint3d(this->x, this->y), start, end, this->tolerance) == true)
		this->vertexType = VertexType::VertexOther;
	else
		this->vertexType = VertexType::VertexNothing;
}

void ShNearestVertexFinder::visit(ShCircle *circle) {

	ShPoint3d center = circle->getCenter();
	double radius = circle->getRadius();

	if (this->x >= center.x - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + (this->tolerance / this->zoomRate)) {

		this->vertexType = VertexType::VertexCenter;
		this->vertexPoint = center;
		return;
	}

	if (this->x >= center.x + radius - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + radius + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + (this->tolerance / this->zoomRate)) {

		this->vertexType = VertexType::VertexRight;
		this->vertexPoint.x = center.x + radius;
		this->vertexPoint.y = center.y;
		return;
	}

	if (this->x >= center.x - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - radius - (this->tolerance / this->zoomRate) &&
		this->y <= center.y - radius + (this->tolerance / this->zoomRate)) {

		this->vertexType = VertexType::VertexBottom;
		this->vertexPoint.x = center.x;
		this->vertexPoint.y = center.y - radius;
		return;
	}

	if (this->x >= center.x - radius - (this->tolerance / this->zoomRate) &&
		this->x <= center.x - radius + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + (this->tolerance / this->zoomRate)) {

		this->vertexType = VertexType::VertexLeft;
		this->vertexPoint.x = center.x - radius;
		this->vertexPoint.y = center.y;
		return;
	}

	if (this->x >= center.x - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + (this->tolerance / this->zoomRate) &&
		this->y >= center.y + radius - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + radius + (this->tolerance / this->zoomRate)) {

		this->vertexType = VertexType::VertexTop;
		this->vertexPoint.x = center.x;
		this->vertexPoint.y = center.y + radius;
		return;
	}

	if (math::checkPointLiesOnCircleBoundary(ShPoint3d(this->x, this->y), center, radius, this->tolerance) == true)
		this->vertexType = VertexType::VertexOther;
	else
		this->vertexType = VertexType::VertexNothing;
}

void ShNearestVertexFinder::visit(ShArc *arc) {

	ShPoint3d center = arc->getCenter();

	if (this->x >= center.x - (this->tolerance / this->zoomRate) &&
		this->x <= center.x + (this->tolerance / this->zoomRate) &&
		this->y >= center.y - (this->tolerance / this->zoomRate) &&
		this->y <= center.y + (this->tolerance / this->zoomRate)) {

		this->vertexType = VertexType::VertexCenter;
		this->vertexPoint = center;
		return;
	}

	ShPoint3d start = arc->getStart();

	if (this->x >= start.x - (this->tolerance / this->zoomRate) &&
		this->x <= start.x + (this->tolerance / this->zoomRate) &&
		this->y >= start.y - (this->tolerance / this->zoomRate) &&
		this->y <= start.y + (this->tolerance / this->zoomRate)) {

		this->vertexType = VertexType::VertexStart;
		this->vertexPoint = start;
		return;
	}

	ShPoint3d end = arc->getEnd();

	if (this->x >= end.x - (this->tolerance / this->zoomRate) &&
		this->x <= end.x + (this->tolerance / this->zoomRate) &&
		this->y >= end.y - (this->tolerance / this->zoomRate) &&
		this->y <= end.y + (this->tolerance / this->zoomRate)) {

		this->vertexType = VertexType::VertexEnd;
		this->vertexPoint = end;
		return;
	}

	ShPoint3d mid = arc->getMid();

	if (this->x >= mid.x - (this->tolerance / this->zoomRate) &&
		this->x <= mid.x + (this->tolerance / this->zoomRate) &&
		this->y >= mid.y - (this->tolerance / this->zoomRate) &&
		this->y <= mid.y + (this->tolerance / this->zoomRate)) {

		this->vertexType = VertexType::VertexMid;
		this->vertexPoint = mid;
		return;
	}

	if (math::checkPointLiesOnArcBoundary(ShPoint3d(this->x, this->y), center, arc->getRadius(), arc->getStartAngle(),
		arc->getEndAngle(), tolerance) == true)
		this->vertexType = VertexType::VertexOther;
	else
		this->vertexType = VertexType::VertexNothing;
}


/////////////////////////////////////////////////////////////////////////////

PointAndVertexTypeMathchedEntityFinder::PointAndVertexTypeMathchedEntityFinder(const ShPoint3d &mustMatchPoint, VertexType vertexType, bool &matched)
	:mustMatchPoint(mustMatchPoint), vertexType(vertexType), matched(matched) {
	
}

PointAndVertexTypeMathchedEntityFinder::~PointAndVertexTypeMathchedEntityFinder() {

}

void PointAndVertexTypeMathchedEntityFinder::visit(ShLine *line) {

	if ((this->vertexType & VertexType::VertexStart) == VertexType::VertexStart) {

		if (this->mustMatchPoint == line->getStart()) {

			this->matched = true;
			return;
		}
	}

	if ((this->vertexType & VertexType::VertexEnd) == VertexType::VertexEnd) {
		
		if (this->mustMatchPoint == line->getEnd()) {
		
			this->matched = true;
			return;
		}
	}
	if ((this->vertexType & VertexType::VertexMid) == VertexType::VertexMid) {

		if (this->mustMatchPoint == line->getMid()) {

			this->matched = true;
			return;
		}
	}

	this->matched = false;
}

void PointAndVertexTypeMathchedEntityFinder::visit(ShCircle *circle) {

	if ((this->vertexType & VertexType::VertexCenter) == VertexType::VertexCenter) {

		if (this->mustMatchPoint == circle->getCenter()) {

			this->matched = true;
			return;
		}
	}

	this->matched = false;
}

void PointAndVertexTypeMathchedEntityFinder::visit(ShArc *arc) {

	if ((this->vertexType & VertexType::VertexStart) == VertexType::VertexStart) {

		if (this->mustMatchPoint == arc->getStart()) {

			this->matched = true;
			return;
		}
	}
	if ((this->vertexType & VertexType::VertexEnd) == VertexType::VertexEnd) {

		if (this->mustMatchPoint == arc->getEnd()) {

			this->matched = true;
			return;
		}
	}
	if ((this->vertexType & VertexType::VertexMid) == VertexType::VertexMid) {

		if (this->mustMatchPoint == arc->getMid()) {

			this->matched = true;
			return;
		}
	}
	if ((this->vertexType & VertexType::VertexCenter) == VertexType::VertexCenter) {

		if (this->mustMatchPoint == arc->getCenter()) {

			this->matched = true;
			return;
		}
	}

	this->matched = false;
}
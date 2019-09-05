
#include "ShFinder.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"

ShFinder::ShFinder(double x, double y, double zoomRate, ShEntity* *foundEntity)
	:x(x), y(y), zoomRate(zoomRate), foundEntity(foundEntity) {

}

ShFinder::~ShFinder() {

}

void ShFinder::visit(ShLine *line) {

	double tolerance = 5.0 / this->zoomRate;

	ShLineData data = line->getData();

	if (math::checkPointLiesOnLine(ShPoint3d(this->x, this->y), data.start, data.end, tolerance) == true)
		*this->foundEntity = line;
}

void ShFinder::visit(ShCircle *circle) {

	double tolerance = 5.0 / this->zoomRate;

	ShCircleData data = circle->getData();

	if (math::checkPointLiesOnCircleBoundary(ShPoint3d(this->x, this->y), data.center, data.radius, tolerance) == true)
		*this->foundEntity = circle;
}

void ShFinder::visit(ShArc *arc) {

	double tolerance = 5.0 / this->zoomRate;

	ShArcData data = arc->getData();

	if (math::checkPointLiesOnArcBoundary(ShPoint3d(this->x, this->y), data.center, data.radius, data.startAngle, data.endAngle, tolerance) == true)
		*this->foundEntity = arc;
}

//////////////////////////////////////////

ShRectFinder::ShRectFinder(const ShPoint3d &topLeft, const ShPoint3d &bottomRight, ShEntity* *foundEntity, FindMethod findMethod)
	:topLeft(topLeft), bottomRight(bottomRight), foundEntity(foundEntity), findMethod(findMethod) {

}

ShRectFinder::~ShRectFinder() {

}

void ShRectFinder::visit(ShLine *line) {

	ShLineData data = line->getData();

	if (math::checkPointLiesInsideRect(data.start, this->topLeft, this->bottomRight, 0) == true &&
		math::checkPointLiesInsideRect(data.end, this->topLeft, this->bottomRight, 0) == true) {
		*this->foundEntity = line;
		return;
	}

	if (findMethod == FindMethod::OnePartLiesInsideRect) {

		//Rectangle has four line-segment.
		ShPoint3d intersect;
		if (math::checkTwoLineSegmentsIntersect(data.start, data.end, this->topLeft, ShPoint3d(this->topLeft.x, this->bottomRight.y),
			intersect) == true) {
			*this->foundEntity = line;
			return;
		}
		if (math::checkTwoLineSegmentsIntersect(data.start, data.end, this->topLeft, ShPoint3d(this->bottomRight.x, this->topLeft.y),
			intersect) == true) {
			*this->foundEntity = line;
			return;
		}
		if (math::checkTwoLineSegmentsIntersect(data.start, data.end, ShPoint3d(this->topLeft.x, this->bottomRight.y), this->bottomRight,
			intersect) == true) {
			*this->foundEntity = line;
			return;
		}
		if (math::checkTwoLineSegmentsIntersect(data.start, data.end, ShPoint3d(this->bottomRight.x, this->topLeft.y), this->bottomRight,
			intersect) == true) {
			*this->foundEntity = line;
			return;
		}
	}
}

void ShRectFinder::visit(ShCircle *circle) {

	ShCircleData data = circle->getData();

	if (data.center.x - data.radius >= this->topLeft.x &&
		data.center.x + data.radius <= this->bottomRight.x &&
		data.center.y - data.radius >= this->bottomRight.y &&
		data.center.y + data.radius <= this->topLeft.y) {
		*this->foundEntity = circle;
		return;
	}

	if (this->findMethod == FindMethod::OnePartLiesInsideRect) {

		if (math::checkCircleLineSegmentIntersect(data.center, data.radius, this->topLeft,
			ShPoint3d(this->topLeft.x, this->bottomRight.y)) == true) {
			*this->foundEntity = circle;
			return;
		}
		if (math::checkCircleLineSegmentIntersect(data.center, data.radius, this->topLeft,
			ShPoint3d(this->bottomRight.x, this->topLeft.y)) == true) {
			*this->foundEntity = circle;
			return;
		}
		if (math::checkCircleLineSegmentIntersect(data.center, data.radius,
			ShPoint3d(this->topLeft.x, this->bottomRight.y), this->bottomRight) == true) {
			*this->foundEntity = circle;
			return;
		}
		if (math::checkCircleLineSegmentIntersect(data.center, data.radius,
			ShPoint3d(this->bottomRight.x, this->topLeft.y), this->bottomRight) == true) {
			*this->foundEntity = circle;
			return;
		}
	}
}

void ShRectFinder::visit(ShArc *arc) {

	ShArcData data = arc->getData();

	if (math::checkPointLiesInsideRect(arc->getStart(), this->topLeft, this->bottomRight, 0) == true &&
		math::checkPointLiesInsideRect(arc->getEnd(), this->topLeft, this->bottomRight, 0) == true &&
		math::checkPointLiesInsideRect(arc->getMid(), this->topLeft, this->bottomRight, 0) == true) {

		ShPoint3d top(data.center.x, data.center.y + data.radius);
		ShPoint3d left(data.center.x + data.radius, data.center.y);
		ShPoint3d bottom(data.center.x, data.center.y - data.radius);
		ShPoint3d right(data.center.x - data.radius, data.center.y);


		bool flag = true;
		if (math::checkAngleLiesOnAngleBetween(data.startAngle, data.endAngle, 90.0) == true) {
			if (math::checkPointLiesInsideRect(top, this->topLeft, this->bottomRight, 0) == false)
				flag = false;
		}
		if (math::checkAngleLiesOnAngleBetween(data.startAngle, data.endAngle, 0) == true) {
			if (flag == true && math::checkPointLiesInsideRect(left, this->topLeft, this->bottomRight, 0) == false)
				flag = false;
		}
		if (math::checkAngleLiesOnAngleBetween(data.startAngle, data.endAngle, 270) == true) {
			if (flag == true && math::checkPointLiesInsideRect(bottom, this->topLeft, this->bottomRight, 0) == false)
				flag = false;
		}
		if (math::checkAngleLiesOnAngleBetween(data.startAngle, data.endAngle, 180) == true) {
			if (flag == true && math::checkPointLiesInsideRect(right, this->topLeft, this->bottomRight, 0) == false)
				flag = false;
		}

		if (flag == true) {
			*this->foundEntity = arc;
			return;
		}
	}

	if (this->findMethod == FindMethod::OnePartLiesInsideRect) {

		if (math::checkArcLineSegmentIntersect(data.center, data.radius, data.startAngle, data.endAngle,
			this->topLeft, ShPoint3d(this->topLeft.x, this->bottomRight.y)) == true) {
			*this->foundEntity = arc;
			return;
		}
		if (math::checkArcLineSegmentIntersect(data.center, data.radius, data.startAngle, data.endAngle,
			this->topLeft, ShPoint3d(this->bottomRight.x, this->topLeft.y)) == true) {
			*this->foundEntity = arc;
			return;
		}
		if (math::checkArcLineSegmentIntersect(data.center, data.radius, data.startAngle, data.endAngle,
			ShPoint3d(this->topLeft.x, this->bottomRight.y), this->bottomRight) == true) {
			*this->foundEntity = arc;
			return;
		}
		if (math::checkArcLineSegmentIntersect(data.center, data.radius, data.startAngle, data.endAngle,
			ShPoint3d(this->bottomRight.x, this->topLeft.y), this->bottomRight) == true) {
			*this->foundEntity = arc;
			return;
		}
	}
}


/////////////////////////////////////////////////////////////////

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

#include "ShFinder.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"

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
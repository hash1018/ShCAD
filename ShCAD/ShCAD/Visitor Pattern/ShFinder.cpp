

#include "ShFinder.h"
#include "ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
ShFinder::ShFinder(double x, double y, double zoomRate,ShEntity* *foundEntity)
	:x(x), y(y), zoomRate(zoomRate),foundEntity(foundEntity) {

}

ShFinder::~ShFinder() {

}

void ShFinder::Visit(ShLine *line) {

	double tolerance = 5.0 / this->zoomRate;

	ShLineData data = line->GetData();


	if (Math::CheckPointLiesOnLine(ShPoint3d(this->x, this->y), data.start, data.end, tolerance) == true)
		*this->foundEntity = line;
	

}

void ShFinder::Visit(ShCircle *circle) {

	double tolerance = 5.0 / this->zoomRate;

	ShCircleData data = circle->GetData();

	if (Math::CheckPointLiesOnCircleBoundary(ShPoint3d(this->x, this->y), data.center, data.radius, tolerance) == true)
		*this->foundEntity = circle;

}

void ShFinder::Visit(ShArc *arc) {

	double tolerance = 5.0 / this->zoomRate;

	ShArcData data = arc->GetData();

	if (Math::CheckPointLiesOnArcBoundary(ShPoint3d(this->x, this->y), data.center, data.radius, data.startAngle, data.endAngle, tolerance) == true)
		*this->foundEntity = arc;

}


#include "ShFinder.h"
#include "ShMath.h"
#include "Entity\Leaf\ShLine.h"
ShFinder::ShFinder(double x, double y, double zoomRate,ShEntity* *foundEntity)
	:x(x), y(y), zoomRate(zoomRate),foundEntity(foundEntity) {

}

ShFinder::~ShFinder() {

}

void ShFinder::Visit(ShLine *shLine) {

	double tolerance = 5.0f / this->zoomRate;

	ShLineData data = shLine->GetData();


	if (Math::CheckPointLiesOnLine(ShVector(this->x, this->y), data.start, data.end, tolerance) == true)
		*this->foundEntity = shLine;
	

}

void ShFinder::Visit(ShCircle *shCircle) {

}

void ShFinder::Visit(ShArc *shArc) {

}
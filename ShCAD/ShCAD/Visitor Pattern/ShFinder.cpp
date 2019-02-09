

#include "ShFinder.h"
#include "ShMath.h"
#include "Entity\Leaf\ShLine.h"
ShFinder::ShFinder(double x, double y, double zoomRate,ShEntity* *foundEntity)
	:x(x), y(y), zoomRate(zoomRate),foundEntity(foundEntity) {

}

ShFinder::~ShFinder() {

}

void ShFinder::Visit(ShLine *line) {

	double tolerance = 5.0f / this->zoomRate;

	ShLineData data = line->GetData();


	if (Math::CheckPointLiesOnLine(ShPoint3d(this->x, this->y), data.start, data.end, tolerance) == true)
		*this->foundEntity = line;
	

}

void ShFinder::Visit(ShCircle *circle) {

}

void ShFinder::Visit(ShArc *arc) {

}
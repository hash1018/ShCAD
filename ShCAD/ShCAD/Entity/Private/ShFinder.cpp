
#include "ShFinder.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShLine.h"

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
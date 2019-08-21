
#include "ShRotater.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShMath.h"

ShRotater::ShRotater(const ShPoint3d &center, double angle)
	:center(center), angle(angle) {

}

ShRotater::~ShRotater() {

}

void ShRotater::visit(ShLine *line) {

	ShLineData data = line->getData();

	math::rotate(this->angle, this->center.x, this->center.y, data.start.x, data.start.y, data.start.x, data.start.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.end.x, data.end.y, data.end.x, data.end.y);

	line->setData(data);
}
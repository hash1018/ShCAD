
#include "ShRotater.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"

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

void ShRotater::visit(ShCircle *circle) {

	ShCircleData data = circle->getData();

	math::rotate(this->angle, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);

	circle->setData(data);
}

void ShRotater::visit(ShArc *arc) {

	ShArcData data = arc->getData();

	math::rotate(this->angle, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);

	data.startAngle = math::addAngle(data.startAngle, this->angle);
	data.endAngle = math::addAngle(data.endAngle, this->angle);

	arc->setData(data);
}
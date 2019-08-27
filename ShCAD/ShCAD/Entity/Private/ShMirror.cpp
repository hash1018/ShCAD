
#include "ShMirror.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"

ShMirror::ShMirror(const ShPoint3d &center, double angle)
	:center(center), angle(angle), original(nullptr) {

}

ShMirror::~ShMirror() {

}

void ShMirror::visit(ShLine *line) {

	if (this->original == nullptr || !dynamic_cast<ShLine*>(this->original))
		return;

	ShLine *original = dynamic_cast<ShLine*>(this->original);
	ShLineData data = original->getData();

	double angleStart = math::getAbsAngle(this->center.x, this->center.y, data.start.x, data.start.y);
	double angleEnd = math::getAbsAngle(this->center.x, this->center.y, data.end.x, data.end.y);

	math::rotate((this->angle - angleStart) * 2, this->center.x, this->center.y,
		data.start.x, data.start.y, data.start.x, data.start.y);
	math::rotate((this->angle - angleEnd) * 2, this->center.x, this->center.y,
		data.end.x, data.end.y, data.end.x, data.end.y);

	line->setData(data);
}

void ShMirror::visit(ShCircle *circle) {

	if (this->original == 0 || !dynamic_cast<ShCircle*>(this->original))
		return;

	ShCircle *original = dynamic_cast<ShCircle*>(this->original);
	ShCircleData data = original->getData();

	double angleCenter = math::getAbsAngle(this->center.x, this->center.y, data.center.x, data.center.y);

	math::rotate((this->angle - angleCenter) * 2, this->center.x, this->center.y,
		data.center.x, data.center.y, data.center.x, data.center.y);

	circle->setData(data);
}

void ShMirror::visit(ShArc *arc) {

	if (this->original == 0 || !dynamic_cast<ShArc*>(this->original))
		return;

	ShArc *original = dynamic_cast<ShArc*>(this->original);
	ShArcData data = original->getData();

	ShPoint3d start = original->getStart();
	ShPoint3d end = original->getEnd();

	double angleCenter = math::getAbsAngle(this->center.x, this->center.y, data.center.x, data.center.y);
	double angleStart = math::getAbsAngle(this->center.x, this->center.y, start.x, start.y);
	double angleEnd = math::getAbsAngle(this->center.x, this->center.y, end.x, end.y);


	math::rotate((this->angle - angleCenter) * 2, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);
	math::rotate((this->angle - angleStart) * 2, this->center.x, this->center.y, start.x, start.y, start.x, start.y);
	math::rotate((this->angle - angleEnd) * 2, this->center.x, this->center.y, end.x, end.y, end.x, end.y);

	data.startAngle = math::getAbsAngle(data.center.x, data.center.y, end.x, end.y);
	data.endAngle = math::getAbsAngle(data.center.x, data.center.y, start.x, start.y);

	arc->setData(data);
}
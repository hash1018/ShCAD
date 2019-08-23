
#include "ShMirror.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShMath.h"

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
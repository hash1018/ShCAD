
#include "ShFootOfPerpendicularVisitor.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShLine.h"

ShFootOfPerpendicularVisitor::ShFootOfPerpendicularVisitor(double &perpendicularX, double &perpendicularY,
	const ShPoint3d& point)
	:perpendicularX(perpendicularX), perpendicularY(perpendicularY), point(point) {


}


ShFootOfPerpendicularVisitor::~ShFootOfPerpendicularVisitor() {

}

void ShFootOfPerpendicularVisitor::visit(ShLine *line) {

	ShLineData data = line->getData();

	double angle = math::getAbsAngle(data.start.x, data.start.y, data.end.x, data.end.y);
	double angleX, angleY;

	double x = point.x;
	double y = point.y;

	math::rotate(angle + 90, x, y, x + 10, y, angleX, angleY);
	ShPoint3d intersect;

	if (math::checkLineLineIntersect(data.start, data.end, ShPoint3d(x, y),
		ShPoint3d(angleX, angleY), intersect) == true) {

		this->perpendicularX = intersect.x;
		this->perpendicularY = intersect.y;

		return;
	}
}
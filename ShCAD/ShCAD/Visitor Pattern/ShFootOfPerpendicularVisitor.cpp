

#include "ShFootOfPerpendicularVisitor.h"
#include "ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"

ShFootOfPerpendicularVisitor::ShFootOfPerpendicularVisitor(double &perpendicularX, double &perpendicularY,
	const ShPoint3d& point)
	:perpendicularX(perpendicularX), perpendicularY(perpendicularY), point(point) {


}


ShFootOfPerpendicularVisitor::~ShFootOfPerpendicularVisitor() {

}

void ShFootOfPerpendicularVisitor::Visit(ShLine *perpendicularBaseLine) {

	ShLineData data = perpendicularBaseLine->GetData();

	double angle = Math::GetAbsAngle(data.start.x, data.start.y, data.end.x, data.end.y);
	double angleX, angleY;

	double x = point.x;
	double y = point.y;

	Math::Rotate(angle + 90, x, y, x + 10, y, angleX, angleY);
	ShPoint3d intersect;

	if (Math::CheckLineLineIntersect(data.start, data.end, ShPoint3d(x, y),
		ShPoint3d(angleX, angleY), intersect) == true) {

		this->perpendicularX = intersect.x;
		this->perpendicularY = intersect.y;
		
		return;
	}



}

void ShFootOfPerpendicularVisitor::Visit(ShCircle *perpendicularBaseCircle) {

	ShCircleData data = perpendicularBaseCircle->GetData();

	double angle = Math::GetAbsAngle(data.center.x, data.center.y, this->point.x, this->point.y);
	Math::Rotate(angle, data.center.x, data.center.y, data.center.x + data.radius, data.center.y,
		this->perpendicularX, this->perpendicularY);

}

void ShFootOfPerpendicularVisitor::Visit(ShArc *perpendicularBaseArc) {


}
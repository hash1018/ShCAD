

#include "ShStretchVisitor.h"
#include "ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
ShStretchVisitor::ShStretchVisitor(double x, double y)
	:x(x), y(y), origianlEntity(0), hitPoint(HitPoint::HitNothing) {


}

ShStretchVisitor::~ShStretchVisitor() {

}


void ShStretchVisitor::Visit(ShLine *line) {

	ShLineData data = line->GetData();
	ShPoint3d start = data.start;
	ShPoint3d end = data.end;


	if (this->hitPoint == HitPoint::HitStart) {
		start.x = this->x;
		start.y = this->y;
	}
	else if (this->hitPoint == HitPoint::HitEnd) {
		end.x = this->x;
		end.y = this->y;
	}
	else if (this->hitPoint == HitPoint::HitMid) {
		ShPoint3d mid = line->GetMid();
		double disX = mid.x - this->x;
		double disY = mid.y - this->y;
		start.x -= disX;
		start.y -= disY;
		end.x -= disX;
		end.y -= disY;
	}

	line->SetData(ShLineData(start, end));

}

void ShStretchVisitor::Visit(ShCircle *circle) {

	ShCircleData data = circle->GetData();
	ShPoint3d center = data.center;
	
	if (this->hitPoint == HitPoint::HitCenter) {
		double disX = center.x - this->x;
		double disY = center.y - this->y;
		center.x -= disX;
		center.y -= disY;
		data.center = center;
	}
	else if (this->hitPoint == HitPoint::HitRight ||
		this->hitPoint == HitPoint::HitBottom ||
		this->hitPoint == HitPoint::HitLeft ||
		this->hitPoint == HitPoint::HitTop) {
	
		double radius = Math::GetDistance(center.x, center.y, this->x, this->y);
		data.radius = radius;
	}

	circle->SetData(data);
}

void ShStretchVisitor::Visit(ShArc *arc) {

	ShArcData data = arc->GetData();

	if (this->hitPoint == HitPoint::HitCenter) {

		ShPoint3d center = data.center;

		double disX = center.x - this->x;
		double disY = center.y - this->y;
		center.x -= disX;
		center.y -= disY;
		data.center = center;
	}
	else if (this->hitPoint == HitPoint::HitStart || 
		this->hitPoint==HitPoint::HitEnd ||
		this->hitPoint==HitPoint::HitMid) {

		ShArc *arc = dynamic_cast<ShArc*>(this->origianlEntity);
		ShPoint3d start = arc->GetStart();
		ShPoint3d end = arc->GetEnd();
		ShPoint3d mid = arc->GetMid();
		ShPoint3d center;

		if (this->hitPoint == HitPoint::HitStart)
			start = ShPoint3d(this->x, this->y);
		else if (this->hitPoint == HitPoint::HitEnd)
			end = ShPoint3d(this->x, this->y);
		else if (this->hitPoint == HitPoint::HitMid)
			mid = ShPoint3d(this->x, this->y);

		if (Math::GetCenterWithThreePoint(start, mid, end, center) == false)
			return;

		double startAngle = Math::GetAbsAngle(center.x, center.y, start.x, start.y);
		double endAngle = Math::GetAbsAngle(center.x, center.y, end.x, end.y);
		double midAngle = Math::GetAbsAngle(center.x, center.y, mid.x, mid.y);
		double radius = Math::GetDistance(center.x, center.y, this->x, this->y);

		data.center = center;
		data.radius = radius;

		if (Math::CheckAngleLiesOnAngleBetween(startAngle, endAngle, midAngle) == true) {
			data.startAngle = startAngle;
			data.endAngle = endAngle;
		}
		else {
			data.startAngle = endAngle;
			data.endAngle = startAngle;
		}
	}
	
	arc->SetData(data);

}

#include "ShMirror.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"


#include "ShMath.h"
ShMirror::ShMirror(const ShPoint3d& center, double angle)
	:center(center), angle(angle),original(0) {

}

ShMirror::~ShMirror() {

}

void ShMirror::Visit(ShLine *line) {

	if (this->original == 0 || !dynamic_cast<ShLine*>(this->original))
		return;

	ShLine *original = dynamic_cast<ShLine*>(this->original);
	ShLineData data = original->GetData();

	double angleStart = Math::GetAbsAngle(this->center.x, this->center.y, data.start.x, data.start.y);
	double angleEnd = Math::GetAbsAngle(this->center.x, this->center.y, data.end.x, data.end.y);

	Math::Rotate((this->angle - angleStart) * 2, this->center.x, this->center.y, 
		data.start.x, data.start.y, data.start.x, data.start.y);
	Math::Rotate((this->angle - angleEnd) * 2, this->center.x, this->center.y, 
		data.end.x, data.end.y, data.end.x, data.end.y);

	line->SetData(data);

}

void ShMirror::Visit(ShCircle *circle) {

	if (this->original == 0 || !dynamic_cast<ShCircle*>(this->original))
		return;

	ShCircle *original = dynamic_cast<ShCircle*>(this->original);
	ShCircleData data = original->GetData();

	double angleCenter = Math::GetAbsAngle(this->center.x, this->center.y, data.center.x, data.center.y);

	Math::Rotate((this->angle - angleCenter) * 2, this->center.x, this->center.y, 
		data.center.x, data.center.y, data.center.x, data.center.y);

	circle->SetData(data);

}

void ShMirror::Visit(ShArc *arc) {

	if (this->original == 0 || !dynamic_cast<ShArc*>(this->original))
		return;

	ShArc *original = dynamic_cast<ShArc*>(this->original);
	ShArcData data = original->GetData();

	ShPoint3d start = original->GetStart();
	ShPoint3d end = original->GetEnd();

	double angleCenter = Math::GetAbsAngle(this->center.x, this->center.y, data.center.x, data.center.y);
	double angleStart = Math::GetAbsAngle(this->center.x, this->center.y, start.x, start.y);
	double angleEnd = Math::GetAbsAngle(this->center.x, this->center.y, end.x, end.y);

	
	Math::Rotate((this->angle - angleCenter) * 2, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);
	Math::Rotate((this->angle - angleStart) * 2, this->center.x, this->center.y, start.x, start.y, start.x, start.y);
	Math::Rotate((this->angle - angleEnd) * 2, this->center.x, this->center.y, end.x, end.y, end.x, end.y);

	data.startAngle = Math::GetAbsAngle(data.center.x, data.center.y, end.x, end.y);
	data.endAngle = Math::GetAbsAngle(data.center.x, data.center.y, start.x, start.y);

	arc->SetData(data);
	
}
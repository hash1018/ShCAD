

#include "ShRotater.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "ShMath.h"
ShRotater::ShRotater(const ShPoint3d& center, double angle)
	:center(center), angle(angle) {

}

ShRotater::~ShRotater() {

}

void ShRotater::Visit(ShLine *line) {

	ShLineData data = line->GetData();

	Math::Rotate(this->angle, this->center.x, this->center.y, data.start.x, data.start.y, data.start.x, data.start.y);
	Math::Rotate(this->angle, this->center.x, this->center.y, data.end.x, data.end.y, data.end.x, data.end.y);

	line->SetData(data);
	
}

void ShRotater::Visit(ShCircle *circle) {

	ShCircleData data = circle->GetData();

	Math::Rotate(this->angle, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);

	circle->SetData(data);
}

void ShRotater::Visit(ShArc *arc) {

	ShArcData data = arc->GetData();

	Math::Rotate(this->angle, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);

	data.startAngle = Math::AddAngle(data.startAngle, this->angle);
	data.endAngle = Math::AddAngle(data.endAngle, this->angle);

}
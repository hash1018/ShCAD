
#include "ShRotater.h"
#include "Entity\Leaf\ShLine.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Leaf\ShPoint.h"
#include "Entity\Leaf\ShDot.h"
#include "Entity\Composite\Dim\ShDimLinear.h"
#include "Entity\Composite\Dim\ShDimAligned.h"
#include "Entity\Composite\Dim\ShDimRadius.h"
#include "Entity\Composite\Dim\ShDimDiameter.h"
#include "Entity\Composite\Dim\ShDimArcLength.h"
#include "Entity\Composite\Dim\ShDimAngular.h"

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

void ShRotater::visit(ShPoint *point) {

	ShPoint3d position = point->getPosition();

	math::rotate(this->angle, this->center.x, this->center.y, position.x, position.y, position.x, position.y);

	point->setPosition(position);
}

void ShRotater::visit(ShDot *dot) {

	ShPoint3d position = dot->getPosition();

	math::rotate(this->angle, this->center.x, this->center.y, position.x, position.y, position.x, position.y);

	dot->setPosition(position);
}

void ShRotater::visit(ShDimLinear *dimLinear) {

	ShDimLinearData data = dimLinear->getData();

	math::rotate(this->angle, this->center.x, this->center.y, data.firstOrigin.x, data.firstOrigin.y, data.firstOrigin.x, data.firstOrigin.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.firstDim.x, data.firstDim.y, data.firstDim.x, data.firstDim.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.secondOrigin.x, data.secondOrigin.y, data.secondOrigin.x, data.secondOrigin.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.secondDim.x, data.secondDim.y, data.secondDim.x, data.secondDim.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.text.x, data.text.y, data.text.x, data.text.y);

	dimLinear->setData(data);
}

void ShRotater::visit(ShDimAligned *dimAligned) {

	ShDimAlignedData data = dimAligned->getData();

	math::rotate(this->angle, this->center.x, this->center.y, data.firstOrigin.x, data.firstOrigin.y, data.firstOrigin.x, data.firstOrigin.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.firstDim.x, data.firstDim.y, data.firstDim.x, data.firstDim.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.secondOrigin.x, data.secondOrigin.y, data.secondOrigin.x, data.secondOrigin.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.secondDim.x, data.secondDim.y, data.secondDim.x, data.secondDim.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.text.x, data.text.y, data.text.x, data.text.y);

	dimAligned->setData(data);
}

void ShRotater::visit(ShDimRadius *dimRadius) {

	ShDimRadiusData data = dimRadius->getData();

	math::rotate(this->angle, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.dim.x, data.dim.y, data.dim.x, data.dim.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.text.x, data.text.y, data.text.x, data.text.y);

	dimRadius->setData(data);
}

void ShRotater::visit(ShDimDiameter *dimDiameter) {

	ShDimDiameterData data = dimDiameter->getData();

	math::rotate(this->angle, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.firstDim.x, data.firstDim.y, data.firstDim.x, data.firstDim.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.secondDim.x, data.secondDim.y, data.secondDim.x, data.secondDim.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.text.x, data.text.y, data.text.x, data.text.y);

	dimDiameter->setData(data);
}

void ShRotater::visit(ShDimArcLength *dimArcLength) {

	ShDimArcLengthData data = dimArcLength->getData();

	math::rotate(this->angle, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.start.x, data.start.y, data.start.x, data.start.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.end.x, data.end.y, data.end.x, data.end.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.text.x, data.text.y, data.text.x, data.text.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.boundary.x, data.boundary.y, data.boundary.x, data.boundary.y);

	dimArcLength->setData(data);
}

void ShRotater::visit(ShDimAngular *dimAngular) {

	ShDimAngularData data = dimAngular->getData();

	math::rotate(this->angle, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.start.x, data.start.y, data.start.x, data.start.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.end.x, data.end.y, data.end.x, data.end.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.text.x, data.text.y, data.text.x, data.text.y);
	math::rotate(this->angle, this->center.x, this->center.y, data.boundary.x, data.boundary.y, data.boundary.x, data.boundary.y);

	dimAngular->setData(data);
}
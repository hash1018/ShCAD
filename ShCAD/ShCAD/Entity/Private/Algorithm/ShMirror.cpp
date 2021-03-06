
#include "ShMirror.h"
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
#include "Entity\Leaf\ShConstructionLine.h"

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

	if (this->original == nullptr || !dynamic_cast<ShCircle*>(this->original))
		return;

	ShCircle *original = dynamic_cast<ShCircle*>(this->original);
	ShCircleData data = original->getData();

	double angleCenter = math::getAbsAngle(this->center.x, this->center.y, data.center.x, data.center.y);

	math::rotate((this->angle - angleCenter) * 2, this->center.x, this->center.y,
		data.center.x, data.center.y, data.center.x, data.center.y);

	circle->setData(data);
}

void ShMirror::visit(ShArc *arc) {

	if (this->original == nullptr || !dynamic_cast<ShArc*>(this->original))
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

void ShMirror::visit(ShPoint *point) {

	if (this->original == nullptr || !dynamic_cast<ShPoint*>(this->original))
		return;

	ShPoint *original = dynamic_cast<ShPoint*>(this->original);
	ShPoint3d position = original->getPosition();

	double angle = math::getAbsAngle(this->center.x, this->center.y, position.x, position.y);

	math::rotate((this->angle - angle) * 2, this->center.x, this->center.y, position.x, position.y, position.x, position.y);

	point->setPosition(position);
}

void ShMirror::visit(ShDot *dot) {

	if (this->original == nullptr || !dynamic_cast<ShDot*>(this->original))
		return;

	ShDot *original = dynamic_cast<ShDot*>(this->original);
	ShPoint3d position = original->getPosition();

	double angle = math::getAbsAngle(this->center.x, this->center.y, position.x, position.y);

	math::rotate((this->angle - angle) * 2, this->center.x, this->center.y, position.x, position.y, position.x, position.y);

	dot->setPosition(position);
}

void ShMirror::visit(ShDimLinear *dimLinear) {

	if (this->original == nullptr || !dynamic_cast<ShDimLinear*>(this->original))
		return;

	ShDimLinear *original = dynamic_cast<ShDimLinear*>(this->original);
	ShDimLinearData data = original->getData();

	double angleFirstOrigin = math::getAbsAngle(this->center.x, this->center.y, data.firstOrigin.x, data.firstOrigin.y);
	double angleFirstDim = math::getAbsAngle(this->center.x, this->center.y, data.firstDim.x, data.firstDim.y);
	double angleSecondOrigin = math::getAbsAngle(this->center.x, this->center.y, data.secondOrigin.x, data.secondOrigin.y);
	double angleSecondDim = math::getAbsAngle(this->center.x, this->center.y, data.secondDim.x, data.secondDim.y);
	double angleText = math::getAbsAngle(this->center.x, this->center.y, data.text.x, data.text.y);

	math::rotate((this->angle - angleFirstOrigin) * 2, this->center.x, this->center.y, data.firstOrigin.x, data.firstOrigin.y, data.firstOrigin.x, data.firstOrigin.y);
	math::rotate((this->angle - angleFirstDim) * 2, this->center.x, this->center.y, data.firstDim.x, data.firstDim.y, data.firstDim.x, data.firstDim.y);
	math::rotate((this->angle - angleSecondOrigin) * 2, this->center.x, this->center.y, data.secondOrigin.x, data.secondOrigin.y, data.secondOrigin.x, data.secondOrigin.y);
	math::rotate((this->angle - angleSecondDim) * 2, this->center.x, this->center.y, data.secondDim.x, data.secondDim.y, data.secondDim.x, data.secondDim.y);
	math::rotate((this->angle - angleText) * 2, this->center.x, this->center.y, data.text.x, data.text.y, data.text.x, data.text.y);

	dimLinear->setData(data);
}

void ShMirror::visit(ShDimAligned *dimAligned) {

	if (this->original == nullptr || !dynamic_cast<ShDimAligned*>(this->original))
		return;

	ShDimAligned *original = dynamic_cast<ShDimAligned*>(this->original);
	ShDimAlignedData data = original->getData();

	double angleFirstOrigin = math::getAbsAngle(this->center.x, this->center.y, data.firstOrigin.x, data.firstOrigin.y);
	double angleFirstDim = math::getAbsAngle(this->center.x, this->center.y, data.firstDim.x, data.firstDim.y);
	double angleSecondOrigin = math::getAbsAngle(this->center.x, this->center.y, data.secondOrigin.x, data.secondOrigin.y);
	double angleSecondDim = math::getAbsAngle(this->center.x, this->center.y, data.secondDim.x, data.secondDim.y);
	double angleText = math::getAbsAngle(this->center.x, this->center.y, data.text.x, data.text.y);

	math::rotate((this->angle - angleFirstOrigin) * 2, this->center.x, this->center.y, data.firstOrigin.x, data.firstOrigin.y, data.firstOrigin.x, data.firstOrigin.y);
	math::rotate((this->angle - angleFirstDim) * 2, this->center.x, this->center.y, data.firstDim.x, data.firstDim.y, data.firstDim.x, data.firstDim.y);
	math::rotate((this->angle - angleSecondOrigin) * 2, this->center.x, this->center.y, data.secondOrigin.x, data.secondOrigin.y, data.secondOrigin.x, data.secondOrigin.y);
	math::rotate((this->angle - angleSecondDim) * 2, this->center.x, this->center.y, data.secondDim.x, data.secondDim.y, data.secondDim.x, data.secondDim.y);
	math::rotate((this->angle - angleText) * 2, this->center.x, this->center.y, data.text.x, data.text.y, data.text.x, data.text.y);

	dimAligned->setData(data);
}

void ShMirror::visit(ShDimRadius *dimRadius) {

	if (this->original == nullptr || !dynamic_cast<ShDimRadius*>(this->original))
		return;

	ShDimRadius *original = dynamic_cast<ShDimRadius*>(this->original);
	ShDimRadiusData data = original->getData();

	double angleCenter = math::getAbsAngle(this->center.x, this->center.y, data.center.x, data.center.y);
	double angleDim = math::getAbsAngle(this->center.x, this->center.y, data.dim.x, data.dim.y);
	double angleText = math::getAbsAngle(this->center.x, this->center.y, data.text.x, data.text.y);

	math::rotate((this->angle - angleCenter) * 2, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);
	math::rotate((this->angle - angleDim) * 2, this->center.x, this->center.y, data.dim.x, data.dim.y, data.dim.x, data.dim.y);
	math::rotate((this->angle - angleText) * 2, this->center.x, this->center.y, data.text.x, data.text.y, data.text.x, data.text.y);

	dimRadius->setData(data);
}

void ShMirror::visit(ShDimDiameter *dimDiameter) {

	if (this->original == nullptr || !dynamic_cast<ShDimDiameter*>(this->original))
		return;

	ShDimDiameter *original = dynamic_cast<ShDimDiameter*>(this->original);
	ShDimDiameterData data = original->getData();

	double angleCenter = math::getAbsAngle(this->center.x, this->center.y, data.center.x, data.center.y);
	double angleFirstDim = math::getAbsAngle(this->center.x, this->center.y, data.firstDim.x, data.firstDim.y);
	double angleSecondDim = math::getAbsAngle(this->center.x, this->center.y, data.secondDim.x, data.secondDim.y);
	double angleText = math::getAbsAngle(this->center.x, this->center.y, data.text.x, data.text.y);

	math::rotate((this->angle - angleCenter) * 2, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);
	math::rotate((this->angle - angleFirstDim) * 2, this->center.x, this->center.y, data.firstDim.x, data.firstDim.y, data.firstDim.x, data.firstDim.y);
	math::rotate((this->angle - angleSecondDim) * 2, this->center.x, this->center.y, data.secondDim.x, data.secondDim.y, data.secondDim.x, data.secondDim.y);
	math::rotate((this->angle - angleText) * 2, this->center.x, this->center.y, data.text.x, data.text.y, data.text.x, data.text.y);

	dimDiameter->setData(data);
}

void ShMirror::visit(ShDimArcLength *dimArcLength) {

	if (this->original == 0 || !dynamic_cast<ShDimArcLength*>(this->original))
		return;

	ShDimArcLength *original = dynamic_cast<ShDimArcLength*>(this->original);
	ShDimArcLengthData data = original->getData();

	double angleCenter = math::getAbsAngle(this->center.x, this->center.y, data.center.x, data.center.y);
	double angleBoundary = math::getAbsAngle(this->center.x, this->center.y, data.boundary.x, data.boundary.y);
	double angleText = math::getAbsAngle(this->center.x, this->center.y, data.text.x, data.text.y);
	double angleStart = math::getAbsAngle(this->center.x, this->center.y, data.start.x, data.start.y);
	double angleEnd = math::getAbsAngle(this->center.x, this->center.y, data.end.x, data.end.y);

	math::rotate((this->angle - angleCenter) * 2, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);
	math::rotate((this->angle - angleBoundary) * 2, this->center.x, this->center.y, data.boundary.x, data.boundary.y, data.boundary.x, data.boundary.y);
	math::rotate((this->angle - angleText) * 2, this->center.x, this->center.y, data.text.x, data.text.y, data.text.x, data.text.y);
	math::rotate((this->angle - angleStart) * 2, this->center.x, this->center.y, data.start.x, data.start.y, data.start.x, data.start.y);
	math::rotate((this->angle - angleEnd) * 2, this->center.x, this->center.y, data.end.x, data.end.y, data.end.x, data.end.y);

	ShPoint3d temp = data.start;
	data.start = data.end;
	data.end = temp;

	dimArcLength->setData(data);
}

void ShMirror::visit(ShDimAngular *dimAngular) {

	if (this->original == 0 || !dynamic_cast<ShDimAngular*>(this->original))
		return;

	ShDimAngular *original = dynamic_cast<ShDimAngular*>(this->original);
	ShDimAngularData data = original->getData();

	double angleCenter = math::getAbsAngle(this->center.x, this->center.y, data.center.x, data.center.y);
	double angleBoundary = math::getAbsAngle(this->center.x, this->center.y, data.boundary.x, data.boundary.y);
	double angleText = math::getAbsAngle(this->center.x, this->center.y, data.text.x, data.text.y);
	double angleStart = math::getAbsAngle(this->center.x, this->center.y, data.start.x, data.start.y);
	double angleEnd = math::getAbsAngle(this->center.x, this->center.y, data.end.x, data.end.y);

	math::rotate((this->angle - angleCenter) * 2, this->center.x, this->center.y, data.center.x, data.center.y, data.center.x, data.center.y);
	math::rotate((this->angle - angleBoundary) * 2, this->center.x, this->center.y, data.boundary.x, data.boundary.y, data.boundary.x, data.boundary.y);
	math::rotate((this->angle - angleText) * 2, this->center.x, this->center.y, data.text.x, data.text.y, data.text.x, data.text.y);
	math::rotate((this->angle - angleStart) * 2, this->center.x, this->center.y, data.start.x, data.start.y, data.start.x, data.start.y);
	math::rotate((this->angle - angleEnd) * 2, this->center.x, this->center.y, data.end.x, data.end.y, data.end.x, data.end.y);

	ShPoint3d temp = data.start;
	data.start = data.end;
	data.end = temp;

	dimAngular->setData(data);
}

void ShMirror::visit(ShConstructionLine *constructionLine) {

	if (this->original == nullptr || !dynamic_cast<ShConstructionLine*>(this->original))
		return;

	ShConstructionLine *original = dynamic_cast<ShConstructionLine*>(this->original);
	ShLineData data = original->getData();

	double angleStart = math::getAbsAngle(this->center.x, this->center.y, data.start.x, data.start.y);
	double angleEnd = math::getAbsAngle(this->center.x, this->center.y, data.end.x, data.end.y);

	math::rotate((this->angle - angleStart) * 2, this->center.x, this->center.y,
		data.start.x, data.start.y, data.start.x, data.start.y);
	math::rotate((this->angle - angleEnd) * 2, this->center.x, this->center.y,
		data.end.x, data.end.y, data.end.x, data.end.y);

	constructionLine->setData(data);
}
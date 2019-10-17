
#include "ShMover.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Leaf\ShPoint.h"
#include "Entity\Leaf\ShDot.h"
#include "Entity\Composite\Dim\ShDimLinear.h"
#include "Entity\Composite\Dim\ShDimAligned.h"
#include "Entity\Composite\Dim\ShDimRadius.h"

ShMover::ShMover(double disX, double disY)
	:disX(disX), disY(disY) {

}

ShMover::~ShMover() {

}

void ShMover::visit(ShLine *line) {

	ShPoint3d start = line->getStart();
	ShPoint3d end = line->getEnd();

	start.move(this->disX, this->disY);
	end.move(this->disX, this->disY);

	line->setStart(start);
	line->setEnd(end);
}

void ShMover::visit(ShCircle *circle) {

	ShPoint3d center = circle->getCenter();

	center.move(this->disX, this->disY);

	circle->setCenter(center);
}

void ShMover::visit(ShArc *arc) {

	ShPoint3d center = arc->getCenter();

	center.move(this->disX, this->disY);

	arc->setCenter(center);
}

void ShMover::visit(ShPoint *point) {

	ShPoint3d position = point->getPosition();

	position.move(this->disX, this->disY);

	point->setPosition(position);
}

void ShMover::visit(ShDot *dot) {

	ShPoint3d position = dot->getPosition();

	position.move(this->disX, this->disY);

	dot->setPosition(position);
}

void ShMover::visit(ShDimLinear *dimLinear) {

	ShDimLinearData data = dimLinear->getData();

	data.firstOrigin.move(this->disX, this->disY);
	data.firstDim.move(this->disX, this->disY);
	data.secondOrigin.move(this->disX, this->disY);
	data.secondDim.move(this->disX, this->disY);
	data.text.move(this->disX, this->disY);

	dimLinear->setData(data);
}

void ShMover::visit(ShDimAligned *dimAligned) {

	ShDimAlignedData data = dimAligned->getData();

	data.firstOrigin.move(this->disX, this->disY);
	data.firstDim.move(this->disX, this->disY);
	data.secondOrigin.move(this->disX, this->disY);
	data.secondDim.move(this->disX, this->disY);
	data.text.move(this->disX, this->disY);

	dimAligned->setData(data);
}

void ShMover::visit(ShDimRadius *dimRadius) {

	ShDimRadiusData data = dimRadius->getData();

	data.center.move(this->disX, this->disY);
	data.dim.move(this->disX, this->disY);
	data.text.move(this->disX, this->disY);

	dimRadius->setData(data);
}

////////////////////////////////////////////////////////////////

ShMoverByAxis::ShMoverByAxis(const ShScrollPosition &scroll, const ShPoint3d &prevCenter, const ShPoint3d &currentCenter, double zoomRate)
	:scroll(scroll), prevCenter(prevCenter), currentCenter(currentCenter), zoomRate(zoomRate) {

}

ShMoverByAxis::~ShMoverByAxis() {

}

void ShMoverByAxis::visit(ShLine *line) {

	ShLineData data = line->getData();

	this->convert(data.start, data.start);
	this->convert(data.end, data.end);

	line->setData(data);
}

void ShMoverByAxis::visit(ShCircle *circle) {

	ShCircleData data = circle->getData();

	this->convert(data.center, data.center);

	circle->setData(data);
}

void ShMoverByAxis::visit(ShArc *arc) {

	ShArcData data = arc->getData();

	this->convert(data.center, data.center);

	arc->setData(data);
}

void ShMoverByAxis::visit(ShPoint *point) {

	ShPoint3d position = point->getPosition();

	this->convert(position, position);

	point->setPosition(position);
}

void ShMoverByAxis::visit(ShDot *dot) {

	ShPoint3d position = dot->getPosition();

	this->convert(position, position);

	dot->setPosition(position);
}

void ShMoverByAxis::visit(ShDimLinear *dimLinear) {

	ShDimLinearData data = dimLinear->getData();

	this->convert(data.firstOrigin, data.firstOrigin);
	this->convert(data.firstDim, data.firstDim);
	this->convert(data.secondOrigin, data.secondOrigin);
	this->convert(data.secondDim, data.secondDim);
	this->convert(data.text, data.text);

	dimLinear->setData(data);
}

void ShMoverByAxis::visit(ShDimAligned *dimAligned) {

	ShDimAlignedData data = dimAligned->getData();

	this->convert(data.firstOrigin, data.firstOrigin);
	this->convert(data.firstDim, data.firstDim);
	this->convert(data.secondOrigin, data.secondOrigin);
	this->convert(data.secondDim, data.secondDim);
	this->convert(data.text, data.text);

	dimAligned->setData(data);
}

void ShMoverByAxis::visit(ShDimRadius *dimRadius) {

	ShDimRadiusData data = dimRadius->getData();

	this->convert(data.center, data.center);
	this->convert(data.dim, data.dim);
	this->convert(data.text, data.text);

	dimRadius->setData(data);
}

void ShMoverByAxis::convert(const ShPoint3d &point, ShPoint3d &converted) {

	ShPoint3d temp;

	temp.x = (point.x*this->zoomRate) - this->scroll.horizontal + (this->prevCenter.x*this->zoomRate);
	temp.y = -1 * ((point.y*this->zoomRate) + this->scroll.vertical - (this->prevCenter.y*this->zoomRate));

	converted.x = (temp.x + this->scroll.horizontal - (this->currentCenter.x*this->zoomRate)) / this->zoomRate;
	converted.y = (-1 * (temp.y + this->scroll.vertical - (this->currentCenter.y*this->zoomRate))) / this->zoomRate;
}
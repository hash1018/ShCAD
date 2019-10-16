
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
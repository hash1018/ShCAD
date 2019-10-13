
#include "ShMover.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Leaf\ShPoint.h"
#include "Entity\Leaf\ShDot.h"
#include "Entity\Composite\Dim\ShDimLinear.h"

ShMover::ShMover(double disX, double disY)
	:disX(disX), disY(disY) {

}

ShMover::~ShMover() {

}

void ShMover::visit(ShLine *line) {

	ShPoint3d start = line->getStart();
	ShPoint3d end = line->getEnd();

	start.x += this->disX;
	start.y += this->disY;
	end.x += this->disX;
	end.y += this->disY;

	line->setStart(start);
	line->setEnd(end);
}

void ShMover::visit(ShCircle *circle) {

	ShPoint3d center = circle->getCenter();

	center.x += this->disX;
	center.y += this->disY;

	circle->setCenter(center);
}

void ShMover::visit(ShArc *arc) {

	ShPoint3d center = arc->getCenter();

	center.x += this->disX;
	center.y += this->disY;

	arc->setCenter(center);
}

void ShMover::visit(ShPoint *point) {

	ShPoint3d position = point->getPosition();

	position.x += this->disX;
	position.y += this->disY;

	point->setPosition(position);
}

void ShMover::visit(ShDot *dot) {

	ShPoint3d position = dot->getPosition();

	position.x += this->disX;
	position.y += this->disY;

	dot->setPosition(position);
}

void ShMover::visit(ShDimLinear *dimLinear) {

	ShDimLinearData data = dimLinear->getData();

	data.firstOrigin.x += this->disX;
	data.firstOrigin.y += this->disY;
	data.firstDim.x += this->disX;
	data.firstDim.y += this->disY;
	data.secondOrigin.x += this->disX;
	data.secondOrigin.y += this->disY;
	data.secondDim.x += this->disX;
	data.secondDim.y += this->disY;
	data.text.x += this->disX;
	data.text.y += this->disY;

	dimLinear->setData(data);
}
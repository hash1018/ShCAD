
#include "ShMover.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"

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

#include "ShMover.h"
#include "Entity\Leaf\ShLine.h"

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
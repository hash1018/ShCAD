

#include "ShRubberBand.h"

ShRubberBand::ShRubberBand(const ShVector& start, const ShVector& end)
	:start(start), end(end) {

}

ShRubberBand::~ShRubberBand() {

}

void ShRubberBand::SetStartX(double startX) {

	this->start.x = startX;
}

void ShRubberBand::SetStartY(double startY) {

	this->start.y = startY;
}

void ShRubberBand::SetEndX(double endX) {

	this->end.x = endX;
}

void ShRubberBand::SetEndY(double endY) {

	this->end.y = endY;
}


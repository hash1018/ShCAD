
#include "ShRubberBand.h"
#include "Entity\Private\ShVisitor.h"

ShRubberBand::ShRubberBand()
	:line(nullptr) {

}

ShRubberBand::ShRubberBand(const ShRubberBand &other)
	: ShLine(other) {

	this->line = other.line->clone();
}

ShRubberBand::~ShRubberBand() {

	if (this->line != nullptr)
		delete this->line;
}

ShRubberBand* ShRubberBand::clone() {

	return new ShRubberBand(*this);
}

void ShRubberBand::accept(ShVisitor *visitor) {

	visitor->visit(this);
}

void ShRubberBand::setData(const ShLineData &data) {

	if (this->line == nullptr)
		this->line = new ShLine(data);

	this->line->setData(data);
}

void ShRubberBand::setStart(const ShPoint3d &start) {

	if (this->line == nullptr)
		this->line = new ShLine;

	this->line->setStart(start);
}

void ShRubberBand::setEnd(const ShPoint3d &end) {

	if (this->line == nullptr)
		this->line = new ShLine;

	this->line->setEnd(end);
}

ShLineData ShRubberBand::getData() {
	
	if (this->line == nullptr)
		this->line = new ShLine;

	return this->line->getData();
}

ShPoint3d ShRubberBand::getStart() {

	if (this->line == nullptr)
		this->line = new ShLine;

	return this->line->getStart();
}

ShPoint3d ShRubberBand::getEnd() {

	if (this->line == nullptr)
		this->line = new ShLine;

	return this->line->getEnd();
}

void ShRubberBand::clear() {

	if (this->line != nullptr)
		delete this->line;

	this->line = nullptr;
}

void ShRubberBand::create(const ShLineData &data) {

	if (this->line == nullptr)
		this->line = new ShLine;

	this->line->setData(data);
}

bool ShRubberBand::isExist() {

	if (this->line == nullptr)
		return false;

	return true;
}

#include "ShDimLinear.h"
#include "Entity\Private\ShVisitor.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShLine.h"

ShDimLinear::ShDimLinear(const ShDimLinearData &data, const ShPropertyData &propertyData, ShLayer *layer)
	:ShDim(propertyData, layer), angle(data.angle), distance(data.distance), distancePosition(data.distancePosition) {

	this->add(new ShLine(propertyData, ShLineData(data.first, data.first2), layer));
	this->add(new ShLine(propertyData, ShLineData(data.second, data.second2), layer));
	this->add(new ShLine(propertyData, ShLineData(data.first2, data.second2), layer));
}

ShDimLinear::ShDimLinear(const ShDimLinear &other)
	:ShDim(other), angle(other.angle), distance(other.distance), distancePosition(other.distancePosition) {

}

ShDimLinear::~ShDimLinear() {

}

ShDimLinear& ShDimLinear::operator=(const ShDimLinear &other) {

	ShDim::operator=(other);

	this->angle = other.angle;
	this->distance = other.distance;
	this->distancePosition = other.distancePosition;

	return *this;
}

ShDimLinear* ShDimLinear::clone() {

	return new ShDimLinear(*this);
}

void ShDimLinear::accept(ShVisitor *visitor) {

	visitor->visit(this);
}

void ShDimLinear::updateDistance() {

	this->distance = math::getDistance(this->getFirstLine()->getEnd().x, this->getFirstLine()->getEnd().y,
		this->getSecondLine()->getEnd().x, this->getSecondLine()->getEnd().y);
}

void ShDimLinear::updateAngle() {

	const ShLine *line = this->getFirstLine();

	this->angle = math::getAbsAngle(line->getStart().x, line->getStart().y,
		line->getEnd().x, line->getEnd().y);
}

void ShDimLinear::setData(const ShDimLinearData &data) {

	this->angle = data.angle;
	this->distance = data.distance;
	this->distancePosition = data.distancePosition;

	const_cast<ShLine*>(this->getFirstLine())->setData(ShLineData(data.first, data.first2));
	const_cast<ShLine*>(this->getSecondLine())->setData(ShLineData(data.second, data.second2));
	const_cast<ShLine*>(this->getThirdLine())->setData(ShLineData(data.first2, data.second2));
}

ShDimLinearData ShDimLinear::getData() {

	ShDimLinearData data;

	data.angle = this->angle;
	data.distance = this->distance;
	data.distancePosition = this->distancePosition;
	data.first = this->getFirstLine()->getStart();
	data.first2 = this->getFirstLine()->getEnd();
	data.second = this->getSecondLine()->getStart();
	data.second2 = this->getSecondLine()->getEnd();

	return data;
}

const ShLine* ShDimLinear::getFirstLine() {

	auto itr = this->list.begin();

	ShLine *line = dynamic_cast<ShLine*>(*itr);

	return line;
}

const ShLine* ShDimLinear::getSecondLine() {

	auto itr = this->list.begin();
	++itr;
	ShLine *line = dynamic_cast<ShLine*>(*itr);

	return line;
}

const ShLine* ShDimLinear::getThirdLine() {

	auto itr = this->list.begin();
	++itr;
	++itr;
	ShLine *line = dynamic_cast<ShLine*>(*itr);

	return line;
}
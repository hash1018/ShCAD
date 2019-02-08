

#include "ShLine.h"
#include "Visitor Pattern\ShVisitor.h"

ShLineData::ShLineData() {

}

ShLineData::ShLineData(const ShPoint3d &start, const ShPoint3d &end)
	:start(start), end(end) {


}

ShLineData::ShLineData(const ShLineData &data)
	: start(data.start), end(data.end) {


}

bool ShLineData::operator==(const ShLineData& data) {

	if (this->start == data.start && this->end == data.end)
		return true;

	return false;

}

ShLineData& ShLineData::operator=(const ShLineData& data) {


	this->start = data.start;
	this->end = data.end;

	return *this;
}


ShLine::ShLine() {


}

ShLine::ShLine(const ShLineData& data)
	:data(data) {

}

ShLine::ShLine(const ShPropertyData& propertyData, const ShLineData &data, ShLayer *layer)
	: ShLeaf(propertyData, layer), data(data) {


}

ShLine::ShLine(const ShLine& other)
	: ShLeaf(other), data(other.data) {


}

ShLine& ShLine::operator=(const ShLine& other) {

	ShLeaf::operator=(other);

	this->data = other.data;

	return *this;
}

ShLine::~ShLine() {


}

ShLine* ShLine::Clone() {

	return new ShLine(*this);
}

void ShLine::Accept(ShVisitor *shVisitor) {

	shVisitor->Visit(this);

}

void ShLine::SetData(const ShLineData &data) {

	this->data = data;

}

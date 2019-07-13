
#include "ShEntityData.h"

ShEntityData::ShEntityData() {

}

ShEntityData::ShEntityData(const ShEntityData &other) {

}

ShEntityData::~ShEntityData() {

}

ShEntityData& ShEntityData::operator=(const ShEntityData &other) {

	return *this;
}

////////////////////////////////////////////////////////////

ShLineData::ShLineData() {

}

ShLineData::ShLineData(const ShPoint3d &start, const ShPoint3d &end)
	:start(start), end(end) {

}

ShLineData::ShLineData(const ShLineData &other)
	: start(other.start), end(other.end) {

}

ShLineData::~ShLineData() {

}

ShLineData& ShLineData::operator=(const ShLineData &other) {

	this->start = other.start;
	this->end = other.end;

	return *this;
}
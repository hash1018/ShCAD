
#include "ShAvailableDraft.h"

ShAvailableDraft::ShAvailableDraft()
	:availableOrthogonal(false), availableSnap(false) {

}

ShAvailableDraft::~ShAvailableDraft() {

}

ShAvailableDraft& ShAvailableDraft::operator=(const ShAvailableDraft &other) {

	this->availableOrthogonal = other.availableOrthogonal;
	this->orthogonalBasePoint = other.orthogonalBasePoint;
	this->availableSnap = other.availableSnap;
	this->snapBasePoint = other.snapBasePoint;

	return *this;
}
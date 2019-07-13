
#include "ShScrollPosition.h"

ShScrollPosition::ShScrollPosition()
	:vertical(0), horizontal(0) {

}

ShScrollPosition::ShScrollPosition(const double &vertical, const double &horizontal)
	: vertical(vertical), horizontal(horizontal) {

}

ShScrollPosition::ShScrollPosition(const ShScrollPosition &other)
	: vertical(other.vertical), horizontal(other.horizontal) {

}

ShScrollPosition::~ShScrollPosition() {

}

ShScrollPosition& ShScrollPosition::operator=(const ShScrollPosition &other) {

	this->vertical = other.vertical;
	this->horizontal = other.horizontal;

	return *this;
}
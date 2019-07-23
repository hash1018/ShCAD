
#include "ShPreview.h"

ShPreview::ShPreview() {

}

ShPreview::ShPreview(const ShPreview &other)
	:ShComposite(other) {

}

ShPreview::~ShPreview() {

}

ShPreview& ShPreview::operator=(const ShPreview &other) {

	ShComposite::operator=(other);
	return *this;
}

ShPreview* ShPreview::clone() {

	return new ShPreview(*this);
}

void ShPreview::accept(ShVisitor *visitor) {

	
}

void ShPreview::empty() {

	while (!this->list.isEmpty())
		this->list.takeFirst();
}

void ShPreview::clear() {

	while (!this->list.isEmpty())
		delete this->list.takeFirst();
}
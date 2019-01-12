

#include "ShPreview.h"

ShPreview::ShPreview() {

}

ShPreview::~ShPreview() {

}

ShPreview::ShPreview(const ShPreview& other)
	:ShComposite(other) {

}

ShPreview& ShPreview::operator=(const ShPreview& other) {

	ShComposite::operator=(other);

	return *this;
}

ShPreview* ShPreview::Clone() {

	return new ShPreview(*this);
}

void ShPreview::Accept(ShVisitor *shVisitor) {


}

void ShPreview::Empty() {

	while (!this->list.isEmpty())
		this->list.takeFirst();
}

void ShPreview::DeleteAll() {

	while (!this->list.isEmpty())
		delete this->list.takeFirst();
}


#include "ShPolyLine.h"
#include "Visitor Pattern\ShVisitor.h"

ShPolyLine::ShPolyLine(const ShPropertyData &propertyData, ShLayer *layer)
	:ShComposite(propertyData, layer) {

}

ShPolyLine::ShPolyLine(const ShPolyLine& other)
	:ShComposite(other) {

}

ShPolyLine::~ShPolyLine() {

}

ShPolyLine& ShPolyLine::operator=(const ShPolyLine& other) {

	ShComposite::operator=(other);

	return *this;
}

ShPolyLine* ShPolyLine::Clone() {

	return new ShPolyLine(*this);
}

void ShPolyLine::Accept(ShVisitor *visitor) {

	visitor->Visit(this);
}

void ShPolyLine::Move(double cx, double cy) {
	
	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->Begin(); itr != this->End(); ++itr)
		(*itr)->Move(cx, cy);

}

void ShPolyLine::Select() {

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->Begin(); itr != this->End(); ++itr)
		(*itr)->Select();
}

void ShPolyLine::UnSelect() {

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->Begin(); itr != this->End(); ++itr)
		(*itr)->UnSelect();
}
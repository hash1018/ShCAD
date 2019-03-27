
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

	this->isSelected = true;
}

void ShPolyLine::UnSelect() {

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->Begin(); itr != this->End(); ++itr)
		(*itr)->UnSelect();

	this->isSelected = false;
}

void ShPolyLine::SetLayer(ShLayer *layer) {

	this->layer = layer;

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->Begin(); itr != this->End(); ++itr)
		(*itr)->SetLayer(layer);
}

void ShPolyLine::SetPropertyData(const ShPropertyData& data) {

	this->propertyData = data;

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->Begin(); itr != this->End(); ++itr)
		(*itr)->SetPropertyData(data);

}

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
	
	this->data.start.x += cx;
	this->data.start.y += cy;
	this->data.end.x += cx;
	this->data.end.y += cy;

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

#include "Entity\Leaf\ShLine.h"
void ShPolyLine::UpdateStartEnd() {

	//only line works at the moment.

	ShLine *first = dynamic_cast<ShLine*>(*this->Begin());
	this->data.start = first->GetStart();

	ShLine *last = dynamic_cast<ShLine*>(*(--(this->End())));
	this->data.end = last->GetEnd();

}

ShEntity* ShPolyLine::ReplaceEntity(ShEntity *newEntity, int index) {

	int i = 0;
	QLinkedList<ShEntity*>::iterator itr = this->Begin();

	while (i < index) {
		++itr;
		i++;
	}
	ShEntity *oldEntity = (*itr);

	itr=this->list.erase(itr);
	this->list.insert(itr, newEntity);
	
	
	return oldEntity;
}


#include "ShLayer.h"
#include "Entity\ShEntity.h"
ShLayer::ShLayer() {

}

ShLayer::ShLayer(const ShLayerData& data)
	:data(data) {

}

ShLayer::ShLayer(const ShLayer& other)
	: data(other.data), list(other.list) {

	//shallow copy for list;

}

ShLayer::~ShLayer() {

}

void ShLayer::Add(ShEntity *entity) {
	
	this->list.append(entity);
}

void ShLayer::Remove(ShEntity *entity) {

	this->list.removeOne(entity);
}

#include "Memento Pattern\ShMemento.h"
ShLayerMemento* ShLayer::CreateMemento() {
	
	ShLayerMemento *memento = new ShLayerMemento;

	memento->layer = this;
	memento->data = new ShLayerData(this->data);
	
	return memento;
}

void ShLayer::SetMemento(ShLayerMemento *memento) {

	this->data = *memento->data;

	this->SetPropertyData(memento->data->GetPropertyData());

}

void ShLayer::SetPropertyData(const ShPropertyData& data) {

	this->data.propertyData = data;

	QLinkedList<ShEntity*>::iterator itr;

	ShPropertyData propertyData;
	bool referenceToLayer = false;

	for (itr = this->list.begin(); itr != this->list.end(); ++itr) {
		
		propertyData = (*itr)->GetPropertyData();
		referenceToLayer = false;

		if (propertyData.GetColor().GetType() == ShColor::Type::ByLayer) {
			propertyData.SetColor(data.GetColor());
			referenceToLayer = true;
		}
		if (propertyData.GetLineStyle().GetType() == ShLineStyle::Type::ByLayer) {
			propertyData.SetLineStyle(data.GetLineStyle());
			referenceToLayer = true;
		}

		if (referenceToLayer == true)
			(*itr)->SetPropertyData(propertyData);
			
	}


}

void ShLayer::SetLayerData(const ShLayerData &data) {

	this->data = data;

	this->SetPropertyData(data.propertyData);

}
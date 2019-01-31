

#include "ShLayerTable.h"

ShLayerTable::ShLayerTable() {

	ShPropertyData propertyData;
	propertyData.SetColor(ShColor(255, 255, 255, ShColor::Type::ByLayer));
	propertyData.SetLineStyle(ShLineStyle(0xFFFF, ShLineStyle::Type::ByLayer));

	
	ShLayer *layer = new ShLayer(ShLayerData("0", propertyData));
	this->list.append(layer);

	this->currentLayer = layer;

	propertyData.SetColor(ShColor(134,234,222,ShColor::Type::ByLayer));
	ShLayer *layer2 = new ShLayer(ShLayerData("1234", propertyData));
	this->list.append(layer2);

	propertyData.SetColor(ShColor(222, 12, 123, ShColor::Type::ByLayer));
	ShLayer *layer3 = new ShLayer(ShLayerData("kkkkkk", propertyData));
	this->list.append(layer3);
}

ShLayerTable::~ShLayerTable() {

	for (int i = 0; i < this->list.size(); i++)
		delete this->list.at(i);
}

void ShLayerTable::Add(ShLayer *layer) {

	this->list.append(layer);
}

//void ShLayerTable::Delete(ShLayer *layer) {

	//this->list.removeOne(layer);

	//delete layer;
//}

void ShLayerTable::Remove(ShLayer *layer) {

	this->list.removeOne(layer);
}

void ShLayerTable::SetCurrentLayerIndex(int index) {

	this->currentLayer = this->list.at(index);
}

void ShLayerTable::SetCurrentLayer(ShLayer* layer) {

	this->currentLayer = layer;

}

int ShLayerTable::GetCurrentLayerIndex() {

	return this->list.indexOf(this->currentLayer, 0);
}

void ShLayerTable::UpdateTurnOnLayerList() {

	while (!this->turnOnList.isEmpty())
		this->turnOnList.removeFirst();

	for (int i = 0; i < this->list.size(); i++) {

		ShLayer *layer = this->list.at(i);

		if (layer->IsTurnOn() == true) {

			QLinkedList<ShEntity*>::iterator itr;

			for (itr = layer->Begin(); itr != layer->End(); ++itr)
				this->turnOnList.append((*itr));

		}
	}
}
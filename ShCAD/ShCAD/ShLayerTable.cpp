

#include "ShLayerTable.h"
#include "ShLayer.h"
ShLayerTable::ShLayerTable() {

	ShPropertyData propertyData;
	propertyData.color.type = ShColor::Type::ByLayer;
	propertyData.lineStyle.type = ShLineStyle::Type::ByLayer;

	
	ShLayer *layer = new ShLayer(ShLayerData("0", propertyData));
	this->list.append(layer);

	this->currentLayer = layer;

	ShLayer *layer2 = new ShLayer(ShLayerData("1234", propertyData));
	this->list.append(layer2);

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

void ShLayerTable::Delete(ShLayer *layer) {

	this->list.removeOne(layer);

	delete layer;
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
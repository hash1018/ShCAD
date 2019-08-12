
#include "ShLayerTable.h"
#include "ShLayer.h"

ShLayerTable::ShLayerTable() {

	ShPropertyData propertyData;
	propertyData.setColor(ShColor(255, 255, 255, ShColor::Type::ByLayer));
	propertyData.setLineStyle(ShLineStyle(0xFFFF, ShLineStyle::Type::ByLayer));

	ShLayer *layer = new ShLayer("0", propertyData);
	this->layerList.append(layer);
	this->currentLayer = layer;

	propertyData.setColor(ShColor(134, 234, 222, ShColor::Type::ByLayer));
	ShLayer *layer2 = new ShLayer("temp1", propertyData);
	this->layerList.append(layer2);

	propertyData.setColor(ShColor(222, 12, 123, ShColor::Type::ByLayer));
	ShLayer *layer3 = new ShLayer("temp2", propertyData);
	this->layerList.append(layer3);
}

ShLayerTable::~ShLayerTable() {

	for (int i = 0; i < this->layerList.size(); i++)
		delete this->layerList.at(i);
}

void ShLayerTable::add(ShLayer *layer) {

	this->layerList.append(layer);
}

void ShLayerTable::remove(ShLayer *layer) {

	this->layerList.removeOne(layer);
}

void ShLayerTable::updateTurnOnLayerList() {


}
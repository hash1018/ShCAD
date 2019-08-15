
#include "ShLayer.h"
#include "Entity\ShEntity.h"

ShLayer::ShLayer(const QString &name, const ShPropertyData &propertyData, bool turnOn)
	:name(name), propertyData(propertyData), turnOn(turnOn) {

}

ShLayer::ShLayer(const ShLayer &other)
	: name(other.name), propertyData(other.propertyData), turnOn(other.turnOn) {

}

ShLayer::~ShLayer() {

}

void ShLayer::add(ShEntity *entity) {

	this->list.append(entity);
}

void ShLayer::remove(ShEntity *entity) {

	this->list.removeOne(entity);
}

void ShLayer::setPropertyData(const ShPropertyData &propertyData) {

	this->propertyData = propertyData;

	QLinkedList<ShEntity*>::iterator itr;

	ShPropertyData temp;
	bool referenceToLayer = false;

	for (itr = this->list.begin(); itr != this->list.end(); ++itr) {

		temp = (*itr)->getPropertyData();
		referenceToLayer = false;

		if (temp.getColor().getType() == ShColor::Type::ByLayer) {
			temp.setColor(propertyData.getColor());
			referenceToLayer = true;
		}
		if (temp.getLineStyle().getType() == ShLineStyle::Type::ByLayer) {
			temp.setLineStyle(propertyData.getLineStyle());
			referenceToLayer = true;
		}

		if (referenceToLayer == true)
			(*itr)->setPropertyData(temp);
	}
}
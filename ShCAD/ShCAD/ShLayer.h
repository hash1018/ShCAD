

#ifndef _SHLAYER_H
#define _SHLAYER_H

#include <qlinkedlist.h>
#include "ShPropertyData.h"
#include <qstring.h>
#include <qmetatype.h>
class ShLayerData {

public:
	QString name;
	ShPropertyData propertyData;
	bool isTurnOn;

	ShLayerData() :name(""), isTurnOn(true) {}
	ShLayerData(const QString& name, const ShPropertyData& propertyData, bool isTurnOn = true)
		:name(name), propertyData(propertyData), isTurnOn(isTurnOn) {
	}
	ShLayerData(const ShLayerData& other) :name(other.name), propertyData(other.propertyData), isTurnOn(other.isTurnOn) {}
	ShLayerData& operator=(const ShLayerData& other) {
		this->name = other.name;
		this->propertyData = other.propertyData; this->isTurnOn = other.isTurnOn;
		return *this;
	}
	~ShLayerData() {}

};


class ShEntity;
class ShLayerMemento;
class ShLayer {

private:
	ShLayerData data;
	QLinkedList<ShEntity*> list;

public:
	ShLayer();
	ShLayer(const ShLayerData& data);
	ShLayer(const ShLayer& other);
	//no operator=
	~ShLayer();

	void Add(ShEntity *entity);
	void Remove(ShEntity* entity);

	ShLayerMemento* CreateMemento();
	void SetMemento(ShLayerMemento *memento);

	inline  ShLayerData& GetData()  { return this->data; }
};

Q_DECLARE_METATYPE(ShLayerData);

#endif //_SHLAYER_H
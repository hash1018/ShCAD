

#ifndef _SHLAYER_H
#define _SHLAYER_H

#include <qlinkedlist.h>
#include "ShPropertyData.h"
#include <qstring.h>
#include <qmetatype.h>
class ShLayerData {
	friend class ShLayer;
private:
	QString name;
	ShPropertyData propertyData;
	bool isTurnOn;

public:
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

	void SetName(const QString& name) { this->name = name; }
	void SetPropertyData(const ShPropertyData& data) { this->propertyData = data; }
	void SetTurn(bool isTurnOn) { this->isTurnOn = isTurnOn; }
	inline QString GetName() const { return this->name; }
	inline ShPropertyData GetPropertyData() const { return this->propertyData; }
	inline bool IsTurnOn() const { return this->isTurnOn; }

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

	void SetName(const QString& name) { this->data.name = name; }
	void TurnOn() { this->data.isTurnOn = true; }
	void TurnOff() { this->data.isTurnOn = false; }
	void SetPropertyData(const ShPropertyData& data);
	void SetLayerData(const ShLayerData& data);
	

	inline QString GetName() const { return this->data.name; }
	inline ShPropertyData GetPropertyData() { return this->data.propertyData; }
	inline bool IsTurnOn() { return this->data.isTurnOn;}
	inline ShLayerData GetData() { return this->data; }

	//inline  ShLayerData& GetData()  { return this->data; }
	inline int GetSize() const { return this->list.size(); }

	inline QLinkedList<ShEntity*>::iterator Begin() { return this->list.begin(); }
	inline QLinkedList<ShEntity*>::iterator End() { return this->list.end(); }

};

Q_DECLARE_METATYPE(ShLayerData);

#endif //_SHLAYER_H
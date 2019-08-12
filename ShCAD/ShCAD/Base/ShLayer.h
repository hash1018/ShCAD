
#ifndef _SHLAYER_H
#define _SHLAYER_H

#include <qmetatype.h>
#include <qstring.h>
#include <qlinkedlist.h>
#include "Data\ShPropertyData.h"

class ShEntity;

class ShLayer {

private:
	QString name;
	ShPropertyData propertyData;
	bool turnOn;
	QLinkedList<ShEntity*> list;

public:
	ShLayer(const QString &name, const ShPropertyData &propertyData, bool turnOn = true);
	ShLayer(const ShLayer &other);
	~ShLayer();

	void add(ShEntity *entity);
	void remove(ShEntity *entity);

public:
	void setName(const QString &name) { this->name = name; }
	void turnOnOff(bool turnOn) { this->turnOn = turnOn; }
	void setPropertyData(const ShPropertyData &propertyData);

public:
	inline int getSize() const { return this->list.size(); }
	inline const QString& getName() const { return this->name; }
	inline const ShPropertyData& getPropertyData() const{ return this->propertyData; }
	inline bool isTurnOn() const { return this->turnOn; }
	inline QLinkedList<ShEntity*>::iterator begin() { return this->list.begin(); }
	inline QLinkedList<ShEntity*>::iterator end() { return this->list.end(); }

};

Q_DECLARE_METATYPE(ShLayer*);

#endif //_SHLAYER_H
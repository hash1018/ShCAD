


#ifndef _SHENTITY_H
#define _SHENTITY_H

/*Base class for all objects having a graphical representation.*/

#include "Memento Pattern\ShMemento.h"
#include "ShPropertyData.h"


class ShEntityMemento;
class ShVisitor;
class ShLayer;
class ShEntity {

protected:
	ShPropertyData propertyData;
	bool isSelected;
	ShLayer *layer;

public:
	ShEntity();
	ShEntity(const ShPropertyData &propertyData, ShLayer *layer);
	ShEntity(const ShPropertyData &propertyData);
	ShEntity(ShLayer *layer);
	virtual ~ShEntity() = 0;
	ShEntity(const ShEntity& other);
	ShEntity& operator=(const ShEntity& other);

	virtual ShEntity* Clone() = 0;
	virtual void Accept(ShVisitor *shVisitor) = 0;

	virtual ShEntityMemento* CreateMemento() { return 0; }
	virtual void SetMemento(const ShEntityMemento* memento) {}

	
	void SetLayer(ShLayer *layer) { this->layer = layer; }
	void SetPropertyData(const ShPropertyData& data) { this->propertyData = data; }
	
	
	inline ShPropertyData GetPropertyData() const { return this->propertyData; }
	inline ShLayer* GetLayer() const { return this->layer; }
	inline bool IsSelected() const { return this->isSelected; }

	friend class ShSelectedEntityManager;
protected:
	void Select();
	void UnSelect();
};





#endif //_SHENTITY_H

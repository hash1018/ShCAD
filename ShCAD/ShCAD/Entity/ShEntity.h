


#ifndef _SHENTITY_H
#define _SHENTITY_H

/*Base class for all objects having a graphical representation.*/

#include "ShPropertyData.h"
#include "ShPoint.h"
#include "ShVariable.h"
#include "ShEntityData.h"

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
	virtual void Move(double cx, double cy) {}
	
	virtual void SetLayer(ShLayer *layer) { this->layer = layer; }
	virtual void SetPropertyData(const ShPropertyData& data) { this->propertyData = data; }
	
	
	inline ShPropertyData GetPropertyData() const { return this->propertyData; }
	inline ShLayer* GetLayer() const { return this->layer; }
	inline bool IsSelected() const { return this->isSelected; }

	friend class ShSelectedEntityManager;
	friend class ShPolyLine;
protected:
	virtual void Select();
	virtual void UnSelect();
};





#endif //_SHENTITY_H



#ifndef _SHENTITY_H
#define _SHENTITY_H

#include "Private\ShEntityData.h"
#include "Data\ShPropertyData.h"

//Composite Pattern, Visitor Pattern, Prototype Pattern

class ShVisitor;
class ShEntity {

protected:
	ShPropertyData propertyData;
	bool selected;

public:
	ShEntity();
	ShEntity(const ShPropertyData &propertyData);
	ShEntity(const ShEntity &other);
	virtual ~ShEntity() = 0;
	ShEntity& operator=(const ShEntity &other);


	virtual ShEntity* clone() = 0;
	virtual void accept(ShVisitor *visitor) = 0;

	virtual void select();
	virtual void unSelect();

	void setPropertyData(const ShPropertyData &propertyData) { this->propertyData = propertyData; }

	inline const ShPropertyData& getPropertyData() const { return this->propertyData; }
	inline bool isSelected() const { return this->selected; }

};

#endif //_SHENTITY_H
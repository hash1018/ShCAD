

#ifndef _SHENTITY_H
#define _SHENTITY_H

#include "Private\ShEntityData.h"

//Composite Pattern, Visitor Pattern, Prototype Pattern

class ShVisitor;
class ShEntity {

protected:
	bool selected;

public:
	ShEntity();
	ShEntity(const ShEntity &other);
	virtual ~ShEntity() = 0;
	ShEntity& operator=(const ShEntity &other);


	virtual ShEntity* clone() = 0;
	virtual void accept(ShVisitor *visitor) = 0;

	virtual void select();
	virtual void unSelect();

	inline bool isSelected() const { return this->selected; }
};

#endif //_SHENTITY_H
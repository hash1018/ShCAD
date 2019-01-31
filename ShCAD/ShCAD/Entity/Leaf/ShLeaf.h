

#ifndef _SHLEAF_H
#define _SHLEAF_H

#include "Entity\ShEntity.h"

/* This class is the Base class that has no children */

class ShLeaf : public ShEntity {

public:
	ShLeaf();
	ShLeaf(const ShPropertyData& propertyData, ShLayer *layer);
	virtual ~ShLeaf() = 0;
	ShLeaf(const ShLeaf& other);
	ShLeaf& operator=(const ShLeaf& other);

	virtual ShLeaf* Clone() = 0;
	virtual void Accept(ShVisitor *shVisitor) = 0;

};

#endif //_SHLEAF_H
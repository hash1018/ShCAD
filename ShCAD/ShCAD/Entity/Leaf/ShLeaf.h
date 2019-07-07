

#ifndef _SHLEAF_H
#define _SHLEAF_H

#include "Entity\ShEntity.h"

class ShLeaf : public ShEntity {

public:
	ShLeaf();
	ShLeaf(const ShLeaf &other);
	virtual ~ShLeaf() = 0;

	ShLeaf& operator=(const ShLeaf &other);

};

#endif //_SHLEAF_H
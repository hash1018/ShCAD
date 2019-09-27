
#ifndef _SHDIM_H
#define _SHDIM_H

#include "Entity\Composite\ShComposite.h"

class ShDim : public ShComposite {

public: 
	ShDim();
	ShDim(const ShPropertyData &propertyData, ShLayer *layer);
	ShDim(const ShDim &other);
	virtual ~ShDim() = 0;
	ShDim& operator=(const ShDim &other);

};

#endif //_SHDIM_H
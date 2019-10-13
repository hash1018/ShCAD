
#ifndef _SHDIM_H
#define _SHDIM_H

#include "Entity\Composite\ShComposite.h"

class ShDimensionStyle;

class ShDim : public ShComposite {

protected:
	ShDimensionStyle *dimensionStyle;

public: 
	ShDim();
	ShDim(const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle);
	ShDim(const ShDim &other);
	virtual ~ShDim() = 0;
	ShDim& operator=(const ShDim &other);

public:
	void setDimensionStyle(ShDimensionStyle *dimensionStyle) { this->dimensionStyle = dimensionStyle; }

public:
	inline const ShDimensionStyle* getDimensionStyle() const { return this->dimensionStyle; }
};

#endif //_SHDIM_H
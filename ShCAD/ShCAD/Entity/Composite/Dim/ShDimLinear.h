
#ifndef _SHDIMLINEAR_H
#define _SHDIMLINEAR_H

#include "ShDim.h"

class ShLine;

class ShDimLinear : public ShDim {

protected:
	ShDimLinearData data;

public:
	ShDimLinear(const ShDimLinearData &data, const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle);
	ShDimLinear(const ShDimLinear &other);
	~ShDimLinear();
	ShDimLinear& operator=(const ShDimLinear &other);

	virtual ShDimLinear* clone();
	virtual void accept(ShVisitor *visitor);

	void updateChild();

public:
	void setData(const ShDimLinearData &data);
	const ShDimLinearData& getData() { return this->data; }

	double getDistance();
};

#endif //_SHDIMLINEAR_H

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

	virtual void updateChild();

public:
	void setData(const ShDimLinearData &data);
	const ShDimLinearData& getData() { return this->data; }

	double getDistance();
	void getFirstArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3);
	void getSecondArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3);
};

#endif //_SHDIMLINEAR_H
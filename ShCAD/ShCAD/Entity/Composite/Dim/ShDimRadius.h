
#ifndef _SHDIMRADIUS_H
#define _SHDIMRADIUS_H

#include "ShDim.h"

class ShDimRadius : public ShDim {

protected:
	ShDimRadiusData data;

public:
	ShDimRadius(const ShDimRadiusData &data, const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle);
	ShDimRadius(const ShDimRadius &other);
	~ShDimRadius();
	ShDimRadius& operator=(const ShDimRadius &other);

	virtual ShDimRadius* clone();
	virtual void accept(ShVisitor *visitor);

	virtual void updateChild();

public:
	void setData(const ShDimRadiusData &data);
	const ShDimRadiusData& getData() const { return this->data; }

	double getRadius();
	void getArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3);
};

#endif //_SHDIMRADIUS_H
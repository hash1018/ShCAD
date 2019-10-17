

#ifndef _SHDIMDIAMETER_H
#define _SHDIMDIAMETER_H

#include "ShDim.h"

class ShDimDiameter : public ShDim {

protected:
	ShDimDiameterData data;

public:
	ShDimDiameter(const ShDimDiameterData &data, const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle);
	ShDimDiameter(const ShDimDiameter &other);
	~ShDimDiameter();
	ShDimDiameter& operator=(const ShDimDiameter &other);

	virtual ShDimDiameter* clone();
	virtual void accept(ShVisitor *visitor);

	virtual void updateChild();

public:
	void setData(const ShDimDiameterData &data);
	const ShDimDiameterData& getData() const { return this->data; }

	double getRadius();
	double getDiameter();
	void getFirstArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3);
	void getSecondArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3);
	bool isCenterToTextDistanceShorterThanRadius();
};

#endif //_SHDIMDIAMETER_H
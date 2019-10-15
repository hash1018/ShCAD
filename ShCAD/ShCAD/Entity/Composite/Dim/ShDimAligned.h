
#ifndef _SHDIMALIGNED_H
#define _SHDIMALIGNED_H

#include "ShDim.h"

class ShLine;

class ShDimAligned : public ShDim {

protected:
	ShDimAlignedData data;

public:
	ShDimAligned(const ShDimAlignedData &data, const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle);
	ShDimAligned(const ShDimAligned &other);
	~ShDimAligned();
	ShDimAligned& operator=(const ShDimAligned &other);

	virtual ShDimAligned* clone();
	virtual void accept(ShVisitor *visitor);

	void updateChild();

public:
	void setData(const ShDimAlignedData &data);
	const ShDimAlignedData& getData() { return this->data; }

	double getDistance();
	void getFirstArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3);
	void getSecondArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3);
};

#endif //_SHDIMALIGNED_H
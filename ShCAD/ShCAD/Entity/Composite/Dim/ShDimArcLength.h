
#ifndef _SHDIMARCLENGTH_H
#define _SHDIMARCLENGTH_H

#include "ShDim.h"

class ShDimArcLength : public ShDim {

protected:
	ShDimArcLengthData data;

public:
	ShDimArcLength(const ShDimArcLengthData &data, const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle);
	ShDimArcLength(const ShDimArcLength &other);
	~ShDimArcLength();
	ShDimArcLength& operator=(const ShDimArcLength &other);

	virtual ShDimArcLength* clone();
	virtual void accept(ShVisitor *visitor);

	virtual void updateChild();

public:
	void setData(const ShDimArcLengthData &data);
	const ShDimArcLengthData& getData() const { return this->data; }

	double getArcRadius();
	ShPoint3d getArcStart();
	ShPoint3d getArcEnd();
	double getStartAngle();
	double getEndAngle();
	double getArcLength();
	void getFirstArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3);
	void getSecondArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3);

};

#endif //_SHDIMARCLENGTH_H
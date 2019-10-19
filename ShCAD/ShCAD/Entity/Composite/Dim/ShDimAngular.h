
#ifndef _SHDIMANGULAR_H
#define _SHDIMANGULAR_H

#include "ShDim.h"

class ShDimAngular : public ShDim {

protected:
	ShDimAngularData data;

public:
	ShDimAngular(const ShDimAngularData &data, const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle);
	ShDimAngular(const ShDimAngular &other);
	~ShDimAngular();
	ShDimAngular& operator=(const ShDimAngular &other);

	virtual ShDimAngular* clone();
	virtual void accept(ShVisitor *visitor);

	virtual void updateChild();

public:
	void setData(const ShDimAngularData &data);
	const ShDimAngularData& getData() const { return this->data; }

	double getArcRadius();
	ShPoint3d getArcStart();
	ShPoint3d getArcEnd();
	double getStartAngle();
	double getEndAngle();
	double getAngle();
	void getFirstArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3);
	void getSecondArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3);

};

#endif //_SHDIMANGULAR_H
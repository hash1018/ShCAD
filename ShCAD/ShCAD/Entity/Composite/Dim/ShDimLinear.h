
#ifndef _SHDIMLINEAR_H
#define _SHDIMLINEAR_H

#include "ShDim.h"

class ShLine;

class ShDimLinear : public ShDim {

protected:
	double angle;
	double distance;
	ShPoint3d distancePosition;

public:
	ShDimLinear(const ShDimLinearData &data, const ShPropertyData &propertyData, ShLayer *layer);
	ShDimLinear(const ShDimLinear &other);
	~ShDimLinear();
	ShDimLinear& operator=(const ShDimLinear &other);

	virtual ShDimLinear* clone();
	virtual void accept(ShVisitor *visitor);

	void updateDistance();
	void updateAngle();

public:
	void setData(const ShDimLinearData &data);
	ShDimLinearData getData();

private:
	const ShLine* getFirstLine();
	const ShLine* getSecondLine();
	const ShLine* getThirdLine();
};

#endif //_SHDIMLINEAR_H


#ifndef _SHMATH_
#define _SHMATH_

#include "ShVector.h"

namespace Math {

	int ToInt(double value);
	int Compare(double first, double second, double epsilon = 0.0001);

	bool CheckPointLiesOnLine(const ShVector& point, const ShVector& start, const ShVector& end, double tolerance);
	bool CheckPointLiesInsideRect(const ShVector& point, const ShVector& topLeft, const ShVector& bottomRight,double tolerance);



	double GetAbsAngle(double centerX, double centerY, double anotherX, double anotherY);
	void Rotate(double angle, double centerX, double centerY, double anotherX, double anotherY, double &appliedX, double &appliedY);
}


#endif //_SHMATH_
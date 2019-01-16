

#ifndef _SHMATH_
#define _SHMATH_

#include "ShPoint.h"

namespace Math {

	int ToInt(double value);
	int Compare(double first, double second, double epsilon = 0.0001);

	bool CheckPointLiesOnLine(const ShPoint3d& point, const ShPoint3d& start, const ShPoint3d& end, double tolerance);
	bool CheckPointLiesInsideRect(const ShPoint3d& point, const ShPoint3d& topLeft, const ShPoint3d& bottomRight,double tolerance);



	double GetAbsAngle(double centerX, double centerY, double anotherX, double anotherY);
	void Rotate(double angle, double centerX, double centerY, double anotherX, double anotherY, double &appliedX, double &appliedY);
}


#endif //_SHMATH_
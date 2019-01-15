

#include "ShMath.h"
#include <math.h>

int Math::ToInt(double value) {

	if (value >0) {

		return (int)(value + 0.5);
	}
	else if (value < 0) {

		return (int)(value - 0.5);
	}

	return 0;
}
int Math::Compare(double first, double second, double epsilon) {

	double takeAway = first - second;

	if (fabs(takeAway) < epsilon)
		return 0;
	
	if (takeAway >0 && takeAway >= epsilon)
		return 1;
	

	if (takeAway < 0 && takeAway <= epsilon)
		return -1;
	


	return 2;

}

bool Math::CheckPointLiesOnLine(const ShVector& point, const ShVector& start, const ShVector& end, double tolerance) {

	ShVector topLeft, bottomRight;

	if (start.x < end.x) {
		topLeft.x = start.x;
		bottomRight.x = end.x;
	}
	else {
		topLeft.x = end.x;
		bottomRight.x = start.x;
	}

	if (start.y > end.y) {
		topLeft.y = start.y;
		bottomRight.y = end.y;	
	}
	else {
		topLeft.y = end.y;
		bottomRight.y = start.y;
	}

	if (CheckPointLiesInsideRect(point, topLeft, bottomRight, tolerance) == false)
		return false;

	double angle = GetAbsAngle(start.x, start.y, end.x, end.y);
	double pointAngle = GetAbsAngle(start.x, start.y, point.x, point.y);


	double angle0X, angle0Y;
	Rotate(360 - pointAngle, start.x, start.y, point.x, point.y, angle0X, angle0Y);

	double finalX, finalY;
	Rotate(angle, start.x, start.y, angle0X, angle0Y, finalX, finalY);

	if (finalX - tolerance <= point.x && finalX + tolerance >= point.x &&
		finalY - tolerance <= point.y && finalY + tolerance >= point.y) 
		return true;
	


	return false;
}

bool Math::CheckPointLiesInsideRect(const ShVector& point, const ShVector& topLeft, const ShVector& bottomRight,double tolerance) {

	if (point.x >= topLeft.x - tolerance && point.x <= bottomRight.x + tolerance &&
		point.y <= topLeft.y + tolerance && point.y >= bottomRight.y - tolerance)
		return true;

	return false;
}

double Math::GetAbsAngle(double centerX, double centerY, double anotherX, double anotherY) {

	double distanceX = fabs(anotherX - centerX);
	double distanceY = fabs(anotherY - centerY);

	double angle = atan2(distanceY, distanceX) * 180 / 3.1415926535897;

	if ((Compare(anotherX, centerX) == 1 || Compare(anotherX, centerX) == 0) &&
		(Compare(anotherY, centerY) == 1 || Compare(anotherY, centerY) == 0)) {
		angle = angle + 0;
		return angle;
	}

	if (Compare(centerX, anotherX) == 1 && (Compare(anotherY, centerY) == 1 || Compare(anotherY, centerY) == 0)) {
		angle = 180 - angle;
		return angle;
	}

	if ((Compare(centerX, anotherX) == 1 || Compare(centerX, anotherX) == 0) && Compare(centerY, anotherY) == 1) {
		angle = 180 + angle;
		return angle;
	}

	if (Compare(anotherX, centerX) == 1 && Compare(centerY, anotherY) == 1) {
		angle = 360 - angle;
		return angle;
	}

	return -1.0;
}

void Math::Rotate(double angle, double centerX, double centerY, double anotherX, double anotherY, double &appliedX, double &appliedY) {

	double cos_value = cos((angle*3.1415926535897) / 180);
	double sin_value = sin((angle*3.1415926535897) / 180);

	double tempX = anotherX - centerX;
	double tempY = anotherY - centerY;

	double tempX2 = cos_value*tempX - sin_value*tempY;
	double tempY2 = sin_value*tempX + cos_value*tempY;

	appliedX = tempX2 + centerX;
	appliedY = tempY2 + centerY;
}
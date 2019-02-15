
/*--
**
**   This file is part of the ShCAD project, a 2D CAD Program
**
**    Copyright (C) 2019, Seungho Ha  (sh.ha1018@gmail.com)
**
**
**   This program is free software; you can redistribute it and/or modify it
**   under the terms of the GNU Lesser General Public License as published by
**   the Free Software Foundation; either version 2.1 of the License, or (at
**   your option) any later version.
**
**   This program is distributed in the hope that it will be useful, but
**   WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
**   General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
**
**
--*/

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

bool Math::CheckPointLiesOnLine(const ShPoint3d& point, const ShPoint3d& start, const ShPoint3d& end, double tolerance) {

	ShPoint3d topLeft, bottomRight;

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

bool Math::CheckPointLiesInsideRect(const ShPoint3d& point, const ShPoint3d& topLeft, const ShPoint3d& bottomRight,double tolerance) {

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


double Math::GetDistance(double x, double y, double x2, double y2) {

	double disX = fabs(x2 - x);
	double disY = fabs(y2 - y);

	double distance = sqrt(disX*disX + disY*disY);

	return distance;

}

double Math::Det(double a, double b, double c, double d) {

	return a*d - b*c;
}

bool Math::CheckLineLineIntersect(const ShPoint3d& start1, const ShPoint3d& end1, const ShPoint3d& start2, const ShPoint3d& end2,
	ShPoint3d& intersect) {

	double detL1 = Det(start1.x, start1.y, end1.x, end1.y);
	double detL2 = Det(start2.x, start2.y, end2.x, end2.y);
	double x1mx2 = start1.x - end1.x;
	double x3mx4 = start2.x - end2.x;
	double y1my2 = start1.y - end1.y;
	double y3my4 = start2.y - end2.y;

	double xnom = Det(detL1, x1mx2, detL2, x3mx4);
	double ynom = Det(detL1, y1my2, detL2, y3my4);
	double denom = Det(x1mx2, y1my2, x3mx4, y3my4);
	
	if (denom == 0.0)//Lines don't seem to cross
	{
		intersect.x = NAN;
		intersect.y = NAN;
		return false;
	}

	intersect.x = xnom / denom;
	intersect.y = ynom / denom;
	if (!isfinite(intersect.x) || !isfinite(intersect.y)) //Probably a numerical issue
		return false;

	return true; //All OK

}

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

bool Math::IsBetween(double v, double bound1, double bound2, double tolerance) {
	
	if (bound2 >= bound1) {
		if (v >= bound1 - tolerance && v <= bound2 + tolerance)
			return true;
	}
	
	else {
		if (v >= bound2 - tolerance && v <= bound1 + tolerance)
			return true;
	}
	return false;
}

bool Math::CheckPointLiesOnLine(const ShPoint3d& point, const ShPoint3d& start, const ShPoint3d& end, double tolerance) {
	/*
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
	*/

	if (IsBetween(point.x, start.x, end.x, tolerance) == false || IsBetween(point.y, start.y, end.y, tolerance) == false)
		return false;
	

	if (Compare(end.x - start.x, 0) == 0) // Vertical line.
		return true;

	double m = (end.y - start.y) / (end.x - start.x);
	double c = -(m*start.x) + start.y;

	return fabs(point.y - (m*point.x + c)) <= tolerance;
}

bool Math::CheckPointLiesInsideRect(const ShPoint3d& point, const ShPoint3d& topLeft, const ShPoint3d& bottomRight, double tolerance) {

	if (point.x >= topLeft.x - tolerance && point.x <= bottomRight.x + tolerance &&
		point.y <= topLeft.y + tolerance && point.y >= bottomRight.y - tolerance)
		return true;

	return false;
}

bool Math::CheckPointLiesInsideCircle(const ShPoint3d& point, const ShPoint3d& center, double radius) {
	
	double dis = GetDistance(point.x, point.y, center.x, center.y);

	if (Compare(dis, radius) == 1)
		return false;
	
	return true;
}

bool Math::CheckPointLiesOnCircleBoundary(const ShPoint3d& point, const ShPoint3d& center, double radius, double tolerance) {

	double angle = GetAbsAngle(center.x, center.y, point.x, point.y);

	double x, y;
	Rotate(360 - angle, center.x, center.y, point.x, point.y, x, y);

	if (x - tolerance <= center.x + radius &&
		x + tolerance >= center.x + radius &&
		y - tolerance <= center.y &&
		y + tolerance >= center.y) {
		return true;
	}

	return false;
}

bool Math::CheckPointLiesOnArcBoundary(const ShPoint3d& point, const ShPoint3d& center, double radius, double startAngle, double endAngle, double tolerance) {

	double angle = GetAbsAngle(center.x, center.y, point.x, point.y);

	bool isAngleInside = CheckAngleLiesOnAngleBetween(startAngle, endAngle, angle);

	if (isAngleInside == true) {
		double x, y;
		Rotate(360 - angle, center.x, center.y, point.x, point.y, x, y);
		
		if (x - tolerance <= center.x + radius &&
			x + tolerance >= center.x + radius &&
			y - tolerance <= center.y &&
			y + tolerance >= center.y) {
			return true;
		}
	}

	return false;
}


bool Math::CheckAngleLiesOnAngleBetween(double startAngle, double endAngle, double angle) {

	if (Compare(endAngle, startAngle) == 1) {
		if ((Compare(angle, startAngle) == 1 || Compare(startAngle, angle) == 0) &&
			(Compare(endAngle, angle) == 1 || Compare(angle, endAngle) == 0))
			return true;
	}
	else if (Compare(startAngle, endAngle) == 1 || Compare(startAngle, endAngle) == 0) {
		if ((Compare(angle, startAngle) == 1 || Compare(angle, startAngle) == 0) && angle <360) 
			return true;
		else if (angle >= 0 && (Compare(endAngle, angle) == 1 || Compare(angle, endAngle) == 0)) 
			return true;
	}

	return false;
}

bool Math::GetCenterWithThreePoint(const ShPoint3d& first, const ShPoint3d& second, const ShPoint3d& third, ShPoint3d &center) {

	double dy1, dy2, d, d2, yi;
	double p1X = ((first.x + second.x) / 2);
	double p1Y = ((first.y + second.y) / 2);
	double p2X = ((first.x + third.x) / 2);
	double p2Y = ((first.y + third.y) / 2);
	dy1 = first.y - second.y;
	dy2 = first.y - third.y;
	//r = 0;
	if (dy1 != 0) {
		d = (second.x - first.x) / dy1;
		yi = p1Y - d * p1X;
		if (dy2 != 0) {
			d2 = (third.x - first.x) / dy2;
			if (d != d2) center.x = (yi - (p2Y - d2 * p2X)) / (d2 - d);
			else return false;
		}
		else if (third.x - first.x == 0) return false;
		else center.x = p2X;
	}
	else if (dy2 != 0 && second.x - first.x != 0) {
		d = (third.x - first.x) / dy2;
		yi = p2Y - d * p2X;
		center.x = p1X;
	}
	else return false;
	center.y = d * (center.x) + yi;
	//r = sqrt((first.x - (*startX)) * (first.x - (*startX)) + (first.y - (*startY)) * (first.y - (*startY)));
	return true;
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

bool Math::CheckTwoSegmentsIntersect(const ShPoint3d& start1, const ShPoint3d& end1, const ShPoint3d& start2, const ShPoint3d& end2,
	ShPoint3d &intersect) {

	float s1_x, s1_y, s2_x, s2_y;
	s1_x = end1.x - start1.x;     s1_y = end1.y - start1.y;
	s2_x = end2.x - start2.x;     s2_y = end2.y - start2.y;

	float s, t;
	s = (-s1_y * (start1.x - start2.x) + s1_x * (start1.y - start2.y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (start1.y - start2.y) - s2_y * (start1.x - start2.x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
		// Collision detected
		intersect.x = start1.x + (t * s1_x);
		intersect.y = start1.y + (t * s1_y);
		return true;
	}

	return false; // No collision
}

bool Math::CheckCircleLineSegmentIntersect(const ShPoint3d& center, double radius, const ShPoint3d& start, const ShPoint3d& end) {
	
	double a, b, c, d, u1, u2, ret, retP1, retP2;
	ShPoint3d v1, v2;
	
	v1.x = end.x - start.x;
	v1.y = end.y - start.y;
	v2.x = start.x - center.x;
	v2.y = start.y - center.y;
	b = (v1.x * v2.x + v1.y * v2.y);
	c = 2 * (v1.x * v1.x + v1.y * v1.y);
	b *= -2;
	d = sqrt(b * b - 2 * c * (v2.x * v2.x + v2.y * v2.y - radius * radius));

	//if (isNaN(d)) { // no intercept
	//	return[];
	//}

	u1 = (b - d) / c;  // these represent the unit distance of point one and two on the line
	u2 = (b + d) / c;
	
	if (u1 <= 1 && u1 >= 0) {  // add point if on the line segment
		//retP1.x = start.x + v1.x * u1;
		//retP1.y = start.y + v1.y * u1;
		//ret[0] = retP1;
		return true;
	}
	if (u2 <= 1 && u2 >= 0) {  // second add point if on the line segment
		//retP2.x = start.x + v1.x * u2;
		//retP2.y = start.y + v1.y * u2;
		//ret[ret.length] = retP2;
		return true;
	}

	return false;

}

bool Math::CheckCircleLineIntersect(const ShPoint3d& center, double radius, const ShPoint3d& start, const ShPoint3d& end,
	ShPoint3d &intersect, ShPoint3d &intersect2) {

	// compute the euclidean distance between A and B
	double dis = sqrt(pow((end.x - start.x), 2) + pow((end.y - start.y), 2));

	// compute the direction vector D from A to B
	double dx = (end.x - start.x) / dis;
	double dy = (end.y - start.y) / dis;

	// the equation of the line AB is x = Dx*t + start.x, y = Dy*t + start.y with 0 <= t <= LAB.

	// compute the distance between the points A and E, where
	// E is the point of AB closest the circle center (center.x, center.y)
	double t = dx*(center.x - start.x) + dy*(center.y - start.y);

	// compute the coordinates of the point E
	double ex = t*dx + start.x;
	double ey = t*dy + start.y;

	// compute the euclidean distance between E and C
	double LEC = sqrt(pow((ex - center.x), 2) + pow((ey - center.y), 2));

	// test if the line intersects the circle
	if (LEC < radius) {
		
		// compute distance from t to circle intersection point
		double dt = sqrt(pow(radius, 2) - pow(LEC, 2));

		// compute first intersection point
		intersect.x = (t - dt)*dx + start.x;
		intersect.y = (t - dt)*dy + start.y;

		// compute second intersection point
		intersect2.x = (t + dt)*dx + start.x;
		intersect2.y = (t + dt)*dy + start.y;
		return true;
	}

	// else test if the line is tangent to circle
	else if (LEC == radius)
		// tangent point to circle is E
		return false;

	// line doesn't touch circle
	return false;
}

bool Math::CheckArcLineSegmentIntersect(const ShPoint3d& center, double radius, double startAngle, double endAngle,
	const ShPoint3d& start, const ShPoint3d& end) {

	if (CheckCircleLineSegmentIntersect(center, radius, start, end) == false)
		return false;

	ShPoint3d intersect, intersect2;
	if (CheckCircleLineIntersect(center, radius, start, end, intersect, intersect2) == false)
		return false;

	double angle = GetAbsAngle(center.x, center.y, intersect.x, intersect.y);
	
	if (CheckAngleLiesOnAngleBetween(startAngle, endAngle, angle) == true) {
		if (CheckPointLiesOnLine(intersect, start, end, 1) == true)
			return true;
	}
	
	angle = GetAbsAngle(center.x, center.y, intersect2.x, intersect2.y);
	if (CheckAngleLiesOnAngleBetween(startAngle, endAngle, angle) == true)
		if (CheckPointLiesOnLine(intersect2, start, end, 1) == true)
			return true;
	
	return false;
}

double Math::GetAngleDifference(double startAngle, double endAngle, bool antiClockWise) {

	double diff = 0;

	if (antiClockWise == true) {
		if (Compare(endAngle, startAngle) == 1)
			diff = endAngle - startAngle;
		else if (Compare(endAngle, startAngle) == 0)
			return 0;
		else
			diff = (360 - startAngle) + endAngle;
	}
	else {
		if (Compare(startAngle, endAngle) == 1)
			diff = startAngle - endAngle;
		else if (Compare(startAngle, endAngle) == 0) 
			return 0;
		else 
			diff = (360 + startAngle) - endAngle;
	}
	return diff;
}

double Math::AddAngle(double angle, double angle2) {

	double addedAngle = angle + angle2;

	if (addedAngle >= 360.0)
		addedAngle -= 360;

	return addedAngle;
}
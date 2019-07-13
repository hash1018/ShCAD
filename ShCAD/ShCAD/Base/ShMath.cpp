

#include "ShMath.h"
#include <math.h>

int math::toInt(double value) {

	if (value >0) {

		return (int)(value + 0.5);
	}
	else if (value < 0) {

		return (int)(value - 0.5);
	}

	return 0;
}
int math::compare(double first, double second, double epsilon) {

	double takeAway = first - second;

	if (fabs(takeAway) < epsilon)
		return 0;

	if (takeAway >0 && takeAway >= epsilon)
		return 1;


	if (takeAway < 0 && takeAway <= epsilon)
		return -1;



	return 2;

}

bool math::isBetween(double v, double bound1, double bound2, double tolerance) {

	if (math::compare(bound2, bound1) == 1) {
		if (v >= bound1 - tolerance && v <= bound2 + tolerance)
			return true;
	}
	else {
		if (v >= bound2 - tolerance && v <= bound1 + tolerance)
			return true;
	}
	return false;
}


bool math::checkPointLiesOnLine(const ShPoint3d& point, const ShPoint3d& start, const ShPoint3d& end, double tolerance) {

	if (isBetween(point.x, start.x, end.x, tolerance) == false || isBetween(point.y, start.y, end.y, tolerance) == false)
		return false;

	if (compare(fabs(end.x - start.x), 0) == 0) // Vertical line.
		return true;

	double angle = getAbsAngle(start.x, start.y, end.x, end.y);
	double pointAngle = getAbsAngle(start.x, start.y, point.x, point.y);


	double angle0X, angle0Y;
	rotate(360 - pointAngle, start.x, start.y, point.x, point.y, angle0X, angle0Y);

	double finalX, finalY;
	rotate(angle, start.x, start.y, angle0X, angle0Y, finalX, finalY);

	if (finalX - tolerance <= point.x && finalX + tolerance >= point.x &&
		finalY - tolerance <= point.y && finalY + tolerance >= point.y)
		return true;



	return false;

}

bool math::checkPointLiesInsideRect(const ShPoint3d& point, const ShPoint3d& topLeft, const ShPoint3d& bottomRight, double tolerance) {

	if (point.x >= topLeft.x - tolerance && point.x <= bottomRight.x + tolerance &&
		point.y <= topLeft.y + tolerance && point.y >= bottomRight.y - tolerance)
		return true;

	return false;
}

bool math::checkPointLiesInsideCircle(const ShPoint3d& point, const ShPoint3d& center, double radius) {

	double dis = getDistance(point.x, point.y, center.x, center.y);

	if (compare(dis, radius) == 1)
		return false;

	return true;
}

bool math::checkPointLiesOnCircleBoundary(const ShPoint3d& point, const ShPoint3d& center, double radius, double tolerance) {

	double angle = getAbsAngle(center.x, center.y, point.x, point.y);

	double x, y;
	rotate(360 - angle, center.x, center.y, point.x, point.y, x, y);

	if (x - tolerance <= center.x + radius &&
		x + tolerance >= center.x + radius &&
		y - tolerance <= center.y &&
		y + tolerance >= center.y) {
		return true;
	}

	return false;
}

bool math::checkPointLiesOnArcBoundary(const ShPoint3d& point, const ShPoint3d& center, double radius, double startAngle, double endAngle, double tolerance) {

	double angle = getAbsAngle(center.x, center.y, point.x, point.y);

	bool isAngleInside = checkAngleLiesOnAngleBetween(startAngle, endAngle, angle);

	if (isAngleInside == true) {
		double x, y;
		rotate(360 - angle, center.x, center.y, point.x, point.y, x, y);

		if (x - tolerance <= center.x + radius &&
			x + tolerance >= center.x + radius &&
			y - tolerance <= center.y &&
			y + tolerance >= center.y) {
			return true;
		}
	}

	return false;
}


bool math::checkAngleLiesOnAngleBetween(double startAngle, double endAngle, double angle) {

	if (compare(endAngle, startAngle) == 1) {
		if ((compare(angle, startAngle) == 1 || compare(startAngle, angle) == 0) &&
			(compare(endAngle, angle) == 1 || compare(angle, endAngle) == 0))
			return true;
	}
	else if (compare(startAngle, endAngle) == 1 || compare(startAngle, endAngle) == 0) {
		if ((compare(angle, startAngle) == 1 || compare(angle, startAngle) == 0) && angle <360)
			return true;
		else if (angle >= 0 && (compare(endAngle, angle) == 1 || compare(angle, endAngle) == 0))
			return true;
	}

	return false;
}


ShPoint3d math::getCenterWithTwoPointRadius(const ShPoint3d& first, const ShPoint3d& second, const double& radius) {

	double radsq = radius * radius;
	double q = sqrt(((second.x - first.x) * (second.x - first.x)) + ((second.y - first.y) * (second.y - first.y)));
	double x3 = (first.x + second.x) / 2;
	double y3 = (first.y + second.y) / 2;

	ShPoint3d center;
	center.x = x3 + sqrt(radsq - ((q / 2) * (q / 2))) * ((first.y - second.y) / q);
	center.y = y3 + sqrt(radsq - ((q / 2) * (q / 2))) * ((second.x - first.x) / q);

	return center;
}

bool math::getCenterWithThreePoint(const ShPoint3d& first, const ShPoint3d& second, const ShPoint3d& third, ShPoint3d &center) {

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

double math::getAbsAngle(double centerX, double centerY, double anotherX, double anotherY) {

	double distanceX = fabs(anotherX - centerX);
	double distanceY = fabs(anotherY - centerY);

	double angle = atan2(distanceY, distanceX) * 180 / 3.1415926535897;

	if ((compare(anotherX, centerX) == 1 || compare(anotherX, centerX) == 0) &&
		(compare(anotherY, centerY) == 1 || compare(anotherY, centerY) == 0)) {
		angle = angle + 0;
		return angle;
	}

	if (compare(centerX, anotherX) == 1 && (compare(anotherY, centerY) == 1 || compare(anotherY, centerY) == 0)) {
		angle = 180 - angle;
		return angle;
	}

	if ((compare(centerX, anotherX) == 1 || compare(centerX, anotherX) == 0) && compare(centerY, anotherY) == 1) {
		angle = 180 + angle;
		return angle;
	}

	if (compare(anotherX, centerX) == 1 && compare(centerY, anotherY) == 1) {
		angle = 360 - angle;
		return angle;
	}

	return -1.0;
}

void math::rotate(double angle, double centerX, double centerY, double anotherX, double anotherY, double &appliedX, double &appliedY) {

	double cos_value = cos((angle*3.1415926535897) / 180);
	double sin_value = sin((angle*3.1415926535897) / 180);

	double tempX = anotherX - centerX;
	double tempY = anotherY - centerY;

	double tempX2 = cos_value*tempX - sin_value*tempY;
	double tempY2 = sin_value*tempX + cos_value*tempY;

	appliedX = tempX2 + centerX;
	appliedY = tempY2 + centerY;
}


double math::getDistance(double x, double y, double x2, double y2) {

	double disX = fabs(x2 - x);
	double disY = fabs(y2 - y);

	double distance = sqrt(disX*disX + disY*disY);

	return distance;

}

double math::det(double a, double b, double c, double d) {

	return a*d - b*c;
}

bool math::checkLineLineIntersect(const ShPoint3d& start1, const ShPoint3d& end1, const ShPoint3d& start2, const ShPoint3d& end2,
	ShPoint3d& intersect) {

	double detL1 = det(start1.x, start1.y, end1.x, end1.y);
	double detL2 = det(start2.x, start2.y, end2.x, end2.y);
	double x1mx2 = start1.x - end1.x;
	double x3mx4 = start2.x - end2.x;
	double y1my2 = start1.y - end1.y;
	double y3my4 = start2.y - end2.y;

	double xnom = det(detL1, x1mx2, detL2, x3mx4);
	double ynom = det(detL1, y1my2, detL2, y3my4);
	double denom = det(x1mx2, y1my2, x3mx4, y3my4);

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

bool math::checkTwoLineSegmentsIntersect(const ShPoint3d& start1, const ShPoint3d& end1, const ShPoint3d& start2, const ShPoint3d& end2,
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

bool math::checkCircleLineSegmentIntersect(const ShPoint3d& center, double radius, const ShPoint3d& start, const ShPoint3d& end) {

	double a, b, c, d, u1, u2;
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


bool math::checkCircleLineIntersect(const ShPoint3d& center, double radius, const ShPoint3d& start, const ShPoint3d& end,
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

bool math::checkArcLineSegmentIntersect(const ShPoint3d& center, double radius, double startAngle, double endAngle,
	const ShPoint3d& start, const ShPoint3d& end) {

	if (checkCircleLineSegmentIntersect(center, radius, start, end) == false)
		return false;

	ShPoint3d intersect, intersect2;
	if (checkCircleLineIntersect(center, radius, start, end, intersect, intersect2) == false)
		return false;

	double angle = getAbsAngle(center.x, center.y, intersect.x, intersect.y);

	if (checkAngleLiesOnAngleBetween(startAngle, endAngle, angle) == true) {
		if (checkPointLiesOnLine(intersect, start, end, 1) == true)
			return true;
	}

	angle = getAbsAngle(center.x, center.y, intersect2.x, intersect2.y);
	if (checkAngleLiesOnAngleBetween(startAngle, endAngle, angle) == true)
		if (checkPointLiesOnLine(intersect2, start, end, 1) == true)
			return true;

	return false;
}

bool math::checkTwoCirclesIntersect(const ShPoint3d& center, double radius, const ShPoint3d& center2, double radius2,
	ShPoint3d &intersect, ShPoint3d& intersect2) {

	//(x-a)^2 + (y-b)^2=r1^2
	//(x-c)^2 + (y-d)^2=r2^2
	//-2(a-c)x -2(b-d)y +a^2 + b^2 -c^2 -d^2 -r1^2 + r2^2
	//Ax +By +C=0

	double A = -2 * (center.x - center2.x);
	double B = -2 * (center.y - center2.y);
	double C = center.x*center.x + center.y*center.y - center2.x*center2.x - center2.y*center2.y -
		radius*radius + radius2*radius2;

	//y=-(Ax+C)/B
	//(1+A^2/B^2)x^2 + (-2a + 2AC/B^2 + 2Ab/B)x + a^2+ C^2/B^2 + 2bC/B + b^2 - r^2=0
	//x=(-E +-(root(E*E-DF))/D

	double D = 1 + ((A*A) / (B*B));
	double E = (-center.x + ((A*C) / (B*B)) + ((A*center.y) / B));
	double F = center.x*center.x + (C*C) / (B*B) + (2 * center.y*C) / B + center.y*center.y - radius*radius;
	double discriminant = E*E - D*F;

	if (discriminant<0) {
		return false;
	}
	if (discriminant == 0) {
		//intersect point 1 found.
		//*intersect.x= -E / D;
		//*intersect.y = (-A*intersect.x - C) / B;
		//return true 
	}
	if (discriminant>0) {

		intersect.x = -(E + sqrt(discriminant)) / D;
		intersect.y = (-A*intersect.x - C) / B;

		intersect2.x = -(E - sqrt(discriminant)) / D;
		intersect2.y = (-A*intersect2.x - C) / B;
		return true;
	}
	return false;
}

double math::getAngleDifference(double startAngle, double endAngle, bool antiClockWise) {

	double diff = 0;

	if (antiClockWise == true) {
		if (compare(endAngle, startAngle) == 1)
			diff = endAngle - startAngle;
		else if (compare(endAngle, startAngle) == 0)
			return 0;
		else
			diff = (360 - startAngle) + endAngle;
	}
	else {
		if (compare(startAngle, endAngle) == 1)
			diff = startAngle - endAngle;
		else if (compare(startAngle, endAngle) == 0)
			return 0;
		else
			diff = (360 + startAngle) - endAngle;
	}
	return diff;
}

double math::addAngle(double angle, double angle2) {

	double addedAngle = angle + angle2;

	if (addedAngle >= 360.0)
		addedAngle -= 360;

	return addedAngle;
}

void math::getEquationLine(const ShPoint3d& start, const ShPoint3d& end, double &slope, double &interceptY) {

	slope = 0.0;

	if (compare(start.x, end.x) != 0)
		slope = (end.y - start.y) / (end.x - start.x);

	interceptY = start.y - slope*start.x;
}
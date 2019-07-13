

#ifndef _MATH_H
#define _MATH_H

#include "Data\ShPoint.h"

namespace math {

	int toInt(double value);
	int compare(double first, double second, double epsilon = 0.0001);
	bool isBetween(double v, double bound1, double bound2, double tolerance);
	bool checkPointLiesOnLine(const ShPoint3d& point, const ShPoint3d& start, const ShPoint3d& end, double tolerance);
	bool checkPointLiesInsideRect(const ShPoint3d& point, const ShPoint3d& topLeft, const ShPoint3d& bottomRight, double tolerance);
	bool checkPointLiesInsideCircle(const ShPoint3d& point, const ShPoint3d& center, double radius);
	bool checkPointLiesOnCircleBoundary(const ShPoint3d& point, const ShPoint3d& center, double radius, double tolerance);
	bool checkPointLiesOnArcBoundary(const ShPoint3d& point, const ShPoint3d& center, double radius, double startAngle, double endAngle, double tolerance);
	bool checkAngleLiesOnAngleBetween(double startAngle, double endAngle, double angle);
	bool checkLineLineIntersect(const ShPoint3d& start1, const ShPoint3d& end1, const ShPoint3d& start2, const ShPoint3d& end2,
		ShPoint3d& intersect);
	bool checkTwoLineSegmentsIntersect(const ShPoint3d& start1, const ShPoint3d& end1, const ShPoint3d& start2, const ShPoint3d& end2,
		ShPoint3d& intersect);
	bool checkCircleLineSegmentIntersect(const ShPoint3d& center, double radius, const ShPoint3d& start, const ShPoint3d& end);
	bool checkCircleLineIntersect(const ShPoint3d& center, double radius, const ShPoint3d& start, const ShPoint3d& end,
		ShPoint3d &intersect, ShPoint3d &intersect2);
	bool checkArcLineSegmentIntersect(const ShPoint3d& center, double radius, double startAngle, double endAngle,
		const ShPoint3d& start, const ShPoint3d& end);
	bool checkTwoCirclesIntersect(const ShPoint3d& center, double radius, const ShPoint3d& center2, double radius2,
		ShPoint3d &intersect, ShPoint3d& intersect2);

	ShPoint3d getCenterWithTwoPointRadius(const ShPoint3d& first, const ShPoint3d& second, const double& radius);

	bool getCenterWithThreePoint(const ShPoint3d& first, const ShPoint3d& second, const ShPoint3d& third, ShPoint3d &center);
	double getAbsAngle(double centerX, double centerY, double anotherX, double anotherY);
	void rotate(double angle, double centerX, double centerY, double anotherX, double anotherY, double &appliedX, double &appliedY);

	double getDistance(double x, double y, double x2, double y2);


	double det(double a, double b, double c, double d);

	double getAngleDifference(double startAngle, double endAngle, bool antiClockWise = true);

	// **angle as a full 360 degree rotation
	double addAngle(double angle, double angle2);

	void getEquationLine(const ShPoint3d& start, const ShPoint3d& end, double &slope, double &interceptY);
}

#endif //_MATH_H
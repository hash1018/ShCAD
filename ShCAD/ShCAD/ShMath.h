
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

#ifndef _SHMATH_
#define _SHMATH_

#include "ShPoint.h"

namespace Math {

	int ToInt(double value);
	int Compare(double first, double second, double epsilon = 0.0001);
	bool IsBetween(double v, double bound1, double bound2, double tolerance);
	bool CheckPointLiesOnLine(const ShPoint3d& point, const ShPoint3d& start, const ShPoint3d& end, double tolerance);
	bool CheckPointLiesInsideRect(const ShPoint3d& point, const ShPoint3d& topLeft, const ShPoint3d& bottomRight,double tolerance);
	bool CheckPointLiesInsideCircle(const ShPoint3d& point, const ShPoint3d& center, double radius);
	bool CheckPointLiesOnCircleBoundary(const ShPoint3d& point, const ShPoint3d& center, double radius, double tolerance);
	bool CheckPointLiesOnArcBoundary(const ShPoint3d& point, const ShPoint3d& center, double radius, double startAngle, double endAngle, double tolerance);
	bool CheckAngleLiesOnAngleBetween(double startAngle, double endAngle, double angle);
	bool CheckLineLineIntersect(const ShPoint3d& start1, const ShPoint3d& end1, const ShPoint3d& start2, const ShPoint3d& end2,
		ShPoint3d& intersect);
	bool CheckTwoLineSegmentsIntersect(const ShPoint3d& start1, const ShPoint3d& end1, const ShPoint3d& start2, const ShPoint3d& end2,
		ShPoint3d& intersect);
	bool CheckCircleLineSegmentIntersect(const ShPoint3d& center, double radius, const ShPoint3d& start, const ShPoint3d& end);
	bool CheckCircleLineIntersect(const ShPoint3d& center, double radius, const ShPoint3d& start, const ShPoint3d& end,
		ShPoint3d &intersect, ShPoint3d &intersect2);
	bool CheckArcLineSegmentIntersect(const ShPoint3d& center, double radius, double startAngle, double endAngle,
		const ShPoint3d& start, const ShPoint3d& end);

	bool GetCenterWithThreePoint(const ShPoint3d& first, const ShPoint3d& second, const ShPoint3d& third, ShPoint3d &center);
	double GetAbsAngle(double centerX, double centerY, double anotherX, double anotherY);
	void Rotate(double angle, double centerX, double centerY, double anotherX, double anotherY, double &appliedX, double &appliedY);

	double GetDistance(double x, double y, double x2, double y2);


	double Det(double a, double b, double c, double d);

	double GetAngleDifference(double startAngle, double endAngle, bool antiClockWise = true);

	// **angle as a full 360 degree rotation
	double AddAngle(double angle, double angle2);
}


#endif //_SHMATH_
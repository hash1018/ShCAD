

#include "ShFinder.h"
#include "ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Composite\ShPolyLine.h"
ShFinder::ShFinder(double x, double y, double zoomRate,ShEntity* *foundEntity)
	:x(x), y(y), zoomRate(zoomRate),foundEntity(foundEntity) {

}

ShFinder::~ShFinder() {

}

void ShFinder::Visit(ShLine *line) {

	double tolerance = 5.0 / this->zoomRate;

	ShLineData data = line->GetData();


	if (Math::CheckPointLiesOnLine(ShPoint3d(this->x, this->y), data.start, data.end, tolerance) == true)
		*this->foundEntity = line;
	

}

void ShFinder::Visit(ShCircle *circle) {

	double tolerance = 5.0 / this->zoomRate;

	ShCircleData data = circle->GetData();

	if (Math::CheckPointLiesOnCircleBoundary(ShPoint3d(this->x, this->y), data.center, data.radius, tolerance) == true)
		*this->foundEntity = circle;

}

void ShFinder::Visit(ShArc *arc) {

	double tolerance = 5.0 / this->zoomRate;

	ShArcData data = arc->GetData();

	if (Math::CheckPointLiesOnArcBoundary(ShPoint3d(this->x, this->y), data.center, data.radius, data.startAngle, data.endAngle, tolerance) == true)
		*this->foundEntity = arc;

}

void ShFinder::Visit(ShPolyLine *polyLine) {

	ShEntity *foundEntity = 0;
	QLinkedList<ShEntity*>::iterator itr = polyLine->Begin();
	ShFinder visitor(this->x, this->y, this->zoomRate, &foundEntity);

	while (itr != polyLine->End() && foundEntity == 0) {
		(*itr)->Accept(&visitor);
		++itr;
	}

	if (foundEntity != 0) {
	
		*this->foundEntity = polyLine;
	}

}

//////////////////////////////////////////////////////////////////////////////////


ShRectFinder::ShRectFinder(const ShPoint3d& topLeft, const ShPoint3d& bottomRight, ShEntity* *foundEntity, FindMethod findMethod)
	:topLeft(topLeft), bottomRight(bottomRight), foundEntity(foundEntity), findMethod(findMethod) {

}

ShRectFinder::~ShRectFinder() {

}

void ShRectFinder::Visit(ShLine *line) {

	ShLineData data = line->GetData();

	if (Math::CheckPointLiesInsideRect(data.start, this->topLeft, this->bottomRight, 0) == true &&
		Math::CheckPointLiesInsideRect(data.end, this->topLeft, this->bottomRight, 0) == true) {
		*this->foundEntity = line;
		return;
	}


	if (findMethod == FindMethod::OnePartLiesInsideRect) {

		//Rectangle has four line-segment.
		ShPoint3d intersect;
		if (Math::CheckTwoLineSegmentsIntersect(data.start, data.end, this->topLeft, ShPoint3d(this->topLeft.x, this->bottomRight.y),
			intersect) == true) {
			*this->foundEntity = line;
			return;
		}
		if (Math::CheckTwoLineSegmentsIntersect(data.start, data.end, this->topLeft, ShPoint3d(this->bottomRight.x, this->topLeft.y),
			intersect) == true) {
			*this->foundEntity = line;
			return;
		}
		if (Math::CheckTwoLineSegmentsIntersect(data.start, data.end, ShPoint3d(this->topLeft.x, this->bottomRight.y), this->bottomRight,
			intersect) == true) {
			*this->foundEntity = line;
			return;
		}
		if (Math::CheckTwoLineSegmentsIntersect(data.start, data.end, ShPoint3d(this->bottomRight.x, this->topLeft.y), this->bottomRight,
			intersect) == true) {
			*this->foundEntity = line;
			return;
		}
	}

}

void ShRectFinder::Visit(ShCircle *circle) {

	ShCircleData data = circle->GetData();

	if (data.center.x - data.radius >= this->topLeft.x &&
		data.center.x + data.radius <= this->bottomRight.x &&
		data.center.y - data.radius >= this->bottomRight.y &&
		data.center.y + data.radius <= this->topLeft.y) {
		*this->foundEntity = circle;
		return;
	}

	if (this->findMethod == FindMethod::OnePartLiesInsideRect) {
	
		if (Math::CheckCircleLineSegmentIntersect(data.center, data.radius, this->topLeft, 
			ShPoint3d(this->topLeft.x, this->bottomRight.y)) == true) {
			*this->foundEntity = circle;
			return;
		}
		if (Math::CheckCircleLineSegmentIntersect(data.center, data.radius, this->topLeft,
			ShPoint3d(this->bottomRight.x, this->topLeft.y)) == true) {
			*this->foundEntity = circle;
			return;
		}
		if (Math::CheckCircleLineSegmentIntersect(data.center, data.radius, 
			ShPoint3d(this->topLeft.x, this->bottomRight.y), this->bottomRight) == true) {
			*this->foundEntity = circle;
			return;
		}
		if (Math::CheckCircleLineSegmentIntersect(data.center, data.radius, 
			ShPoint3d(this->bottomRight.x, this->topLeft.y), this->bottomRight) == true) {
			*this->foundEntity = circle;
			return;
		}
	}


}


void ShRectFinder::Visit(ShArc *arc) {

	ShArcData data = arc->GetData();

	if (Math::CheckPointLiesInsideRect(arc->GetStart(), this->topLeft, this->bottomRight, 0) == true &&
		Math::CheckPointLiesInsideRect(arc->GetEnd(), this->topLeft, this->bottomRight, 0) == true &&
		Math::CheckPointLiesInsideRect(arc->GetMid(), this->topLeft, this->bottomRight, 0) == true) {

		ShPoint3d top(data.center.x, data.center.y + data.radius);
		ShPoint3d left(data.center.x + data.radius, data.center.y);
		ShPoint3d bottom(data.center.x, data.center.y - data.radius);
		ShPoint3d right(data.center.x - data.radius, data.center.y);
		

		bool flag = true;
		if (Math::CheckAngleLiesOnAngleBetween(data.startAngle, data.endAngle, 90.0) == true) {
			if (Math::CheckPointLiesInsideRect(top, this->topLeft, this->bottomRight, 0) == false)
				flag = false;
		}
		if (Math::CheckAngleLiesOnAngleBetween(data.startAngle, data.endAngle, 0) == true) {
			if (flag == true && Math::CheckPointLiesInsideRect(left, this->topLeft, this->bottomRight, 0) == false)
				flag = false;
		}
		if (Math::CheckAngleLiesOnAngleBetween(data.startAngle, data.endAngle, 270) == true) {
			if (flag == true && Math::CheckPointLiesInsideRect(bottom, this->topLeft, this->bottomRight, 0) == false)
				flag = false;
		}
		if (Math::CheckAngleLiesOnAngleBetween(data.startAngle, data.endAngle, 180) == true) {
			if (flag == true && Math::CheckPointLiesInsideRect(right, this->topLeft, this->bottomRight, 0) == false)
				flag = false;
		}

		if (flag == true) {
			*this->foundEntity = arc;
			return;
		}
	}

	if (this->findMethod == FindMethod::OnePartLiesInsideRect) {

		if (Math::CheckArcLineSegmentIntersect(data.center, data.radius, data.startAngle, data.endAngle,
			this->topLeft, ShPoint3d(this->topLeft.x, this->bottomRight.y)) == true) {
			*this->foundEntity = arc;
			return;
		}
		if (Math::CheckArcLineSegmentIntersect(data.center, data.radius, data.startAngle, data.endAngle,
			this->topLeft, ShPoint3d(this->bottomRight.x, this->topLeft.y)) == true) {
			*this->foundEntity = arc;
			return;
		}
		if (Math::CheckArcLineSegmentIntersect(data.center, data.radius, data.startAngle, data.endAngle,
			ShPoint3d(this->topLeft.x, this->bottomRight.y), this->bottomRight) == true) {
			*this->foundEntity = arc;
			return;
		}
		if (Math::CheckArcLineSegmentIntersect(data.center, data.radius, data.startAngle, data.endAngle,
			ShPoint3d(this->bottomRight.x, this->topLeft.y), this->bottomRight) == true) {
			*this->foundEntity = arc;
			return;
		}
	}

}

void ShRectFinder::Visit(ShPolyLine *polyLine) {

	if (this->findMethod == FindMethod::AllPartLiesInsideRect) {
	
		ShEntity *foundEntity = 0;
		ShRectFinder visitor(this->topLeft, this->bottomRight, &foundEntity, this->findMethod);
		QLinkedList<ShEntity*>::iterator itr = polyLine->Begin();
		(*itr)->Accept(&visitor);

		if (foundEntity == 0)
			return;

		++itr;

		while (itr != polyLine->End() && foundEntity != 0) {
		
			foundEntity = 0;
			(*itr)->Accept(&visitor);
			++itr;
		}

		if (foundEntity != 0)
			*this->foundEntity = polyLine;

	}
	else if (this->findMethod == FindMethod::OnePartLiesInsideRect) {
	
		ShEntity *foundEntity = 0;
		ShRectFinder visitor(this->topLeft, this->bottomRight, &foundEntity, this->findMethod);
		
		QLinkedList<ShEntity*>::iterator itr = polyLine->Begin();
		(*itr)->Accept(&visitor);

		if (foundEntity != 0) {
			*this->foundEntity = polyLine;
			return;
		}

		++itr;

		while (itr != polyLine->End() && foundEntity == 0) {

			foundEntity = 0;
			(*itr)->Accept(&visitor);
			++itr;
		}

		if (foundEntity != 0)
			*this->foundEntity = polyLine;

	}
}
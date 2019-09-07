
#include "ShStretchVisitor.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"


ShStretchData::ShStretchData() {

}

ShStretchData::~ShStretchData() {

}

///////////////////////////////////////////////

ShStretchLeafData::ShStretchLeafData(StretchPoint stretchPoint)
	:stretchPoint(stretchPoint) {

}

ShStretchLeafData::~ShStretchLeafData() {

}

////////////////////////////////////////////////


ShStretchVisitor::ShStretchVisitor(const ShPoint3d &base, const ShPoint3d &current)
	:base(base), current(current), original(nullptr), stretchData(nullptr) {

}

ShStretchVisitor::~ShStretchVisitor() {

}

void ShStretchVisitor::visit(ShLine *line) {

	if (this->original == nullptr || !dynamic_cast<ShLine*>(this->original))
		return;

	if (!dynamic_cast<ShStretchLeafData*>(this->stretchData))
		return;

	ShStretchLeafData *stretchData = dynamic_cast<ShStretchLeafData*>(this->stretchData);

	ShLine *original = dynamic_cast<ShLine*>(this->original);
	ShLineData data = original->getData();

	double disX = this->current.x - this->base.x;
	double disY = this->current.y - this->base.y;

	if (stretchData->stretchPoint == StretchPoint::StretchStart) {
		data.start.x += disX;
		data.start.y += disY;
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchEnd) {
		data.end.x += disX;
		data.end.y += disY;
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchMove) {
		data.start.x += disX;
		data.start.y += disY;
		data.end.x += disX;
		data.end.y += disY;
	}


	line->setData(data);
}

void ShStretchVisitor::visit(ShCircle *circle) {

	if (this->original == nullptr || !dynamic_cast<ShCircle*>(this->original))
		return;

	if (!dynamic_cast<ShStretchLeafData*>(this->stretchData))
		return;

	ShStretchLeafData *stretchData = dynamic_cast<ShStretchLeafData*>(this->stretchData);


	ShCircle *original = dynamic_cast<ShCircle*>(this->original);

	ShCircleData data = original->getData();
	ShPoint3d center = data.center;

	double disX = this->current.x - this->base.x;
	double disY = this->current.y - this->base.y;

	if (stretchData->stretchPoint == StretchPoint::StretchMove) {
		center.x += disX;
		center.y += disY;
		data.center = center;
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchRight ||
		stretchData->stretchPoint == StretchPoint::StretchBottom ||
		stretchData->stretchPoint == StretchPoint::StretchLeft ||
		stretchData->stretchPoint == StretchPoint::StretchTop) {

		double radius = math::getDistance(center.x, center.y, this->current.x, this->current.y);
		data.radius = radius;
	}

	circle->setData(data);
}

void ShStretchVisitor::visit(ShArc *arc) {


	if (this->original == nullptr || !dynamic_cast<ShArc*>(this->original))
		return;

	if (!dynamic_cast<ShStretchLeafData*>(this->stretchData))
		return;

	ShStretchLeafData *stretchData = dynamic_cast<ShStretchLeafData*>(this->stretchData);

	ShArc *original = dynamic_cast<ShArc*>(this->original);
	ShArcData data = original->getData();

	double disX = this->current.x - this->base.x;
	double disY = this->current.y - this->base.y;

	if (stretchData->stretchPoint == StretchPoint::StretchMove) {

		data.center.x += disX;
		data.center.y += disY;
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchStart ||
		stretchData->stretchPoint == StretchPoint::StretchEnd ||
		stretchData->stretchPoint == StretchPoint::StretchMid) {

		ShPoint3d start = original->getStart();
		ShPoint3d end = original->getEnd();
		ShPoint3d mid = original->getMid();
		ShPoint3d center;

		if (stretchData->stretchPoint == StretchPoint::StretchStart) {

			start.x += disX;
			start.y += disY;
		}
		else if (stretchData->stretchPoint == StretchPoint::StretchEnd) {

			end.x += disX;
			end.y += disY;
		}
		else if (stretchData->stretchPoint == StretchPoint::StretchMid) {

			mid.x += disX;
			mid.y += disY;
		}

		if (math::getCenterWithThreePoint(start, mid, end, center) == false)
			return;

		double startAngle = math::getAbsAngle(center.x, center.y, start.x, start.y);
		double endAngle = math::getAbsAngle(center.x, center.y, end.x, end.y);
		double midAngle = math::getAbsAngle(center.x, center.y, mid.x, mid.y);
		double radius = math::getDistance(center.x, center.y, start.x, start.y);

		data.center = center;
		data.radius = radius;

		if (math::checkAngleLiesOnAngleBetween(startAngle, endAngle, midAngle) == true) {
			data.startAngle = startAngle;
			data.endAngle = endAngle;
		}
		else {
			data.startAngle = endAngle;
			data.endAngle = startAngle;
		}

	}

	arc->setData(data);
}


///////////////////////////////////////////////////

ShPossibleEntityToStretchFinder::ShPossibleEntityToStretchFinder(const ShPoint3d &point, bool &possible, ShStretchData* *stretchData)
	:point(point), possible(possible), stretchData(stretchData) {

}

ShPossibleEntityToStretchFinder::~ShPossibleEntityToStretchFinder() {

}

void ShPossibleEntityToStretchFinder::visit(ShLine *line) {

	if (this->point.isEqual(line->getStart()) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchStart);
		this->possible = true;
	}

	else if (this->point.isEqual(line->getEnd()) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchEnd);
		this->possible = true;
	}
	else if (this->point.isEqual(line->getMid()) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchMove);
		this->possible = true;
	}
}

void ShPossibleEntityToStretchFinder::visit(ShCircle *circle) {

	ShPoint3d center = circle->getCenter();
	double radius = circle->getRadius();

	if (this->point.isEqual(center) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchMove);
		this->possible = true;
		return;
	}

	ShPoint3d temp;
	temp.x = center.x + radius;
	temp.y = center.y;

	if (this->point.isEqual(temp) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchRight);
		this->possible = true;
		return;
	}

	temp.x = center.x;
	temp.y = center.y - radius;

	if (this->point.isEqual(temp) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchBottom);
		this->possible = true;
		return;
	}

	temp.x = center.x - radius;
	temp.y = center.y;

	if (this->point.isEqual(temp) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchLeft);
		this->possible = true;
		return;
	}

	temp.x = center.x;
	temp.y = center.y + radius;

	if (this->point.isEqual(temp) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchTop);
		this->possible = true;
		return;
	}
}

void ShPossibleEntityToStretchFinder::visit(ShArc *arc) {

	if (this->point.isEqual(arc->getCenter()) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchMove);
		this->possible = true;
	}
	else if (this->point.isEqual(arc->getStart()) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchStart);
		this->possible = true;
	}
	else if (this->point.isEqual(arc->getEnd()) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchEnd);
		this->possible = true;
	}
	else if (this->point.isEqual(arc->getMid()) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchMid);
		this->possible = true;
	}
}


////////////////////////////////////////////////////////////////


ShStretchDataForMoveCreator::ShStretchDataForMoveCreator(ShStretchData* *stretchData)
	:stretchData(stretchData) {

}

ShStretchDataForMoveCreator::~ShStretchDataForMoveCreator() {

}

void ShStretchDataForMoveCreator::visit(ShLine *line) {

	*this->stretchData = new ShStretchLeafData(StretchPoint::StretchMove);
}

void ShStretchDataForMoveCreator::visit(ShCircle *circle) {

	*this->stretchData = new ShStretchLeafData(StretchPoint::StretchMove);
}

void ShStretchDataForMoveCreator::visit(ShArc *arc) {

	*this->stretchData = new ShStretchLeafData(StretchPoint::StretchMove);
}


///////////////////////////////////////////////////////////////////


ShStretchPointRectFinder::ShStretchPointRectFinder(const ShPoint3d &topLeft, const ShPoint3d &bottomRight, ShStretchData* *stretchData)
	:topLeft(topLeft), bottomRight(bottomRight), stretchData(stretchData) {

}

ShStretchPointRectFinder::~ShStretchPointRectFinder() {

}

void ShStretchPointRectFinder::visit(ShLine *line) {

	int insideCount = 0;
	StretchPoint stretchPoint = StretchPoint::StretchNothing;

	if (math::checkPointLiesInsideRect(line->getStart(), this->topLeft, this->bottomRight, 0) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchStart;
	}

	if (math::checkPointLiesInsideRect(line->getEnd(), this->topLeft, this->bottomRight, 0) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchEnd;
	}

	if (insideCount == 2)
		stretchPoint = StretchPoint::StretchMove;

	*this->stretchData = new ShStretchLeafData(stretchPoint);
}

void ShStretchPointRectFinder::visit(ShCircle *circle) {

	StretchPoint stretchPoint = StretchPoint::StretchNothing;

	if (math::checkPointLiesInsideRect(circle->getCenter(), this->topLeft, this->bottomRight, 0) == true)
		stretchPoint = StretchPoint::StretchMove;

	*this->stretchData = new ShStretchLeafData(stretchPoint);
}

void ShStretchPointRectFinder::visit(ShArc *arc) {

	int insideCount = 0;
	StretchPoint stretchPoint = StretchPoint::StretchNothing;

	if (math::checkPointLiesInsideRect(arc->getStart(), this->topLeft, this->bottomRight, 0) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchStart;
	}

	if (math::checkPointLiesInsideRect(arc->getEnd(), this->topLeft, this->bottomRight, 0) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchEnd;
	}

	if (insideCount == 2)
		stretchPoint = StretchPoint::StretchMove;

	*this->stretchData = new ShStretchLeafData(stretchPoint);
}

#include "ShStretchVisitor.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Leaf\ShPoint.h"
#include "Entity\Leaf\ShDot.h"
#include "Entity\Composite\Dim\ShDimLinear.h"
#include "Entity\Composite\Dim\ShDimAligned.h"

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

void ShStretchVisitor::visit(ShPoint *point) {

	if (this->original == nullptr || !dynamic_cast<ShPoint*>(this->original))
		return;

	if (!dynamic_cast<ShStretchLeafData*>(this->stretchData))
		return;

	ShStretchLeafData *stretchData = dynamic_cast<ShStretchLeafData*>(this->stretchData);

	ShPoint *original = dynamic_cast<ShPoint*>(this->original);
	ShPoint3d position = original->getPosition();

	double disX = this->current.x - this->base.x;
	double disY = this->current.y - this->base.y;

	if (stretchData->stretchPoint == StretchPoint::StretchMove) {

		position.x += disX;
		position.y += disY;
	}

	point->setPosition(position);
}

void ShStretchVisitor::visit(ShDot *dot) {

	if (this->original == nullptr || !dynamic_cast<ShDot*>(this->original))
		return;

	if (!dynamic_cast<ShStretchLeafData*>(this->stretchData))
		return;

	ShStretchLeafData *stretchData = dynamic_cast<ShStretchLeafData*>(this->stretchData);

	ShDot *original = dynamic_cast<ShDot*>(this->original);
	ShPoint3d position = original->getPosition();

	double disX = this->current.x - this->base.x;
	double disY = this->current.y - this->base.y;

	if (stretchData->stretchPoint == StretchPoint::StretchMove) {

		position.x += disX;
		position.y += disY;
	}

	dot->setPosition(position);
}

void ShStretchVisitor::visit(ShDimLinear *dimLinear) {

	if (this->original == nullptr || !dynamic_cast<ShDimLinear*>(this->original))
		return;

	if (!dynamic_cast<ShStretchLeafData*>(this->stretchData))
		return;

	ShStretchLeafData *stretchData = dynamic_cast<ShStretchLeafData*>(this->stretchData);

	ShDimLinear *original = dynamic_cast<ShDimLinear*>(this->original);
	ShDimLinearData data = original->getData();

	if (stretchData->stretchPoint == StretchPoint::StretchFirstOrigin) {
	
		double angle = math::getAbsAngle(data.firstOrigin.x, data.firstOrigin.y, data.firstDim.x, data.firstDim.y);
		data.firstOrigin = this->current;

		ShPoint3d rotate;
		math::rotate(angle, data.firstOrigin.x, data.firstOrigin.y, data.firstOrigin.x + 10, data.firstOrigin.y, rotate.x, rotate.y);
		math::checkLineLineIntersect(data.firstOrigin, rotate, data.firstDim, data.secondDim, data.firstDim);

		dimLinear->setData(data);
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchFirstDim) {
	
		double dimDistance = math::getDistance(data.firstDim.x, data.firstDim.y, data.text.x, data.text.y);
		double dimAngle = math::getAbsAngle(data.firstDim.x, data.firstDim.y, data.text.x, data.text.y);

		double angle = math::getAbsAngle(data.firstDim.x, data.firstDim.y, data.secondDim.x, data.secondDim.y);
		ShPoint3d rotate;

		math::rotate(angle, this->current.x, this->current.y, this->current.x + 10, this->current.y, rotate.x, rotate.y);
		math::checkLineLineIntersect(data.firstOrigin, data.firstDim, this->current, rotate, data.firstDim);

		math::rotate(angle, data.firstDim.x, data.firstDim.y, data.firstDim.x + 10, data.firstDim.y, rotate.x, rotate.y);
		math::checkLineLineIntersect(data.firstDim, rotate, data.secondOrigin, data.secondDim, data.secondDim);

		math::rotate(dimAngle, data.firstDim.x, data.firstDim.y, data.firstDim.x + dimDistance, data.firstDim.y, data.text.x, data.text.y);

		dimLinear->setData(data);
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchSecondOrigin) {
	
		double angle = math::getAbsAngle(data.secondOrigin.x, data.secondOrigin.y, data.secondDim.x, data.secondDim.y);
		data.secondOrigin = this->current;

		ShPoint3d rotate;
		math::rotate(angle, data.secondOrigin.x, data.secondOrigin.y, data.secondOrigin.x + 10, data.secondOrigin.y, rotate.x, rotate.y);
		math::checkLineLineIntersect(data.secondOrigin, rotate, data.secondDim, data.firstDim, data.secondDim);

		dimLinear->setData(data);
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchSecondDim) {
	
		double dimDistance = math::getDistance(data.firstDim.x, data.firstDim.y, data.text.x, data.text.y);
		double dimAngle = math::getAbsAngle(data.firstDim.x, data.firstDim.y, data.text.x, data.text.y);

		double angle = math::getAbsAngle(data.secondDim.x, data.secondDim.y, data.firstDim.x, data.firstDim.y);
		ShPoint3d rotate;

		math::rotate(angle, this->current.x, this->current.y, this->current.x + 10, this->current.y, rotate.x, rotate.y);
		math::checkLineLineIntersect(data.secondOrigin, data.secondDim, this->current, rotate, data.secondDim);

		math::rotate(angle, data.secondDim.x, data.secondDim.y, data.secondDim.x + 10, data.secondDim.y, rotate.x, rotate.y);
		math::checkLineLineIntersect(data.secondDim, rotate, data.firstOrigin, data.firstDim, data.firstDim);

		math::rotate(dimAngle, data.firstDim.x, data.firstDim.y, data.firstDim.x + dimDistance, data.firstDim.y, data.text.x, data.text.y);

		dimLinear->setData(data);
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchText) {
	
		data.text = this->current;
		double angle = math::getAbsAngle(data.firstDim.x, data.firstDim.y, data.secondDim.x, data.secondDim.y);
		ShPoint3d rotate;
		math::rotate(angle, this->current.x, this->current.y, this->current.x + 10, this->current.y, rotate.x, rotate.y);
		math::checkLineLineIntersect(this->current, rotate, data.firstOrigin, data.firstDim, data.firstDim);
		math::checkLineLineIntersect(this->current, rotate, data.secondOrigin, data.secondDim, data.secondDim);

		dimLinear->setData(data);
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchMove) {

		double disX = this->current.x - this->base.x;
		double disY = this->current.y - this->base.y;

		data.firstOrigin.x += disX;
		data.firstOrigin.y += disY;
		data.firstDim.x += disX;
		data.firstDim.y += disY;
		data.secondOrigin.x += disX;
		data.secondOrigin.y += disY;
		data.secondDim.x += disX;
		data.secondDim.y += disY;
		data.text.x += disX;
		data.text.y += disY;

		dimLinear->setData(data);
	}
}

void ShStretchVisitor::visit(ShDimAligned *dimAligned) {

	if (this->original == nullptr || !dynamic_cast<ShDimAligned*>(this->original))
		return;

	if (!dynamic_cast<ShStretchLeafData*>(this->stretchData))
		return;

	ShStretchLeafData *stretchData = dynamic_cast<ShStretchLeafData*>(this->stretchData);

	ShDimAligned *original = dynamic_cast<ShDimAligned*>(this->original);
	ShDimAlignedData data = original->getData();

	if (stretchData->stretchPoint == StretchPoint::StretchFirstOrigin) {

		double angle = math::getAbsAngle(this->current.x, this->current.y, data.secondOrigin.x, data.secondOrigin.y);
		double distance = math::getDistance(this->current.x, this->current.y, data.secondOrigin.x, data.secondOrigin.y);

		ShPoint3d temp, temp2;
		math::rotate(angle + 90, this->current.x, this->current.y, this->current.x + 10, this->current.y, temp.x, temp.y);
		math::rotate(angle, data.text.x, data.text.y, data.text.x + 10, data.text.y, temp2.x, temp2.y);
		math::checkLineLineIntersect(this->current, temp, data.text, temp2, data.firstDim);

		math::rotate(angle + 90, data.secondOrigin.x, data.secondOrigin.y, data.secondOrigin.x + 10, data.secondOrigin.y, temp.x, temp.y);
		math::checkLineLineIntersect(data.secondOrigin, temp, data.text, temp2, data.secondDim);

		data.firstOrigin = this->current;
		dimAligned->setData(data);
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchSecondOrigin) {

		double angle = math::getAbsAngle(this->current.x, this->current.y, data.firstOrigin.x, data.firstOrigin.y);
		double distance = math::getDistance(this->current.x, this->current.y, data.firstOrigin.x, data.firstOrigin.y);

		ShPoint3d temp, temp2;
		math::rotate(angle + 90, this->current.x, this->current.y, this->current.x + 10, this->current.y, temp.x, temp.y);
		math::rotate(angle, data.text.x, data.text.y, data.text.x + 10, data.text.y, temp2.x, temp2.y);
		math::checkLineLineIntersect(this->current, temp, data.text, temp2, data.secondDim);

		math::rotate(angle + 90, data.firstOrigin.x, data.firstOrigin.y, data.firstOrigin.x + 10, data.firstOrigin.y, temp.x, temp.y);
		math::checkLineLineIntersect(data.firstOrigin, temp, data.text, temp2, data.firstDim);

		data.secondOrigin = this->current;
		dimAligned->setData(data);
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchFirstDim) {

		double dimDistance = math::getDistance(data.firstDim.x, data.firstDim.y, data.text.x, data.text.y);
		double dimAngle = math::getAbsAngle(data.firstDim.x, data.firstDim.y, data.text.x, data.text.y);

		double angle = math::getAbsAngle(data.firstDim.x, data.firstDim.y, data.secondDim.x, data.secondDim.y);
		ShPoint3d temp;

		math::rotate(angle, this->current.x, this->current.y, this->current.x + 10, this->current.y, temp.x, temp.y);
		math::checkLineLineIntersect(data.firstOrigin, data.firstDim, this->current, temp, data.firstDim);

		math::rotate(angle, data.firstDim.x, data.firstDim.y, data.firstDim.x + 10, data.firstDim.y, temp.x, temp.y);
		math::checkLineLineIntersect(data.firstDim, temp, data.secondOrigin, data.secondDim, data.secondDim);

		math::rotate(dimAngle, data.firstDim.x, data.firstDim.y, data.firstDim.x + dimDistance, data.firstDim.y, data.text.x, data.text.y);

		dimAligned->setData(data);
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchSecondDim) {

		double dimDistance = math::getDistance(data.firstDim.x, data.firstDim.y, data.text.x, data.text.y);
		double dimAngle = math::getAbsAngle(data.firstDim.x, data.firstDim.y, data.text.x, data.text.y);

		double angle = math::getAbsAngle(data.secondDim.x, data.secondDim.y, data.firstDim.x, data.firstDim.y);
		ShPoint3d temp;

		math::rotate(angle, this->current.x, this->current.y, this->current.x + 10, this->current.y, temp.x, temp.y);
		math::checkLineLineIntersect(data.secondOrigin, data.secondDim, this->current, temp, data.secondDim);

		math::rotate(angle, data.secondDim.x, data.secondDim.y, data.secondDim.x + 10, data.secondDim.y, temp.x, temp.y);
		math::checkLineLineIntersect(data.secondDim, temp, data.firstOrigin, data.firstDim, data.firstDim);

		math::rotate(dimAngle, data.firstDim.x, data.firstDim.y, data.firstDim.x + dimDistance, data.firstDim.y, data.text.x, data.text.y);

		dimAligned->setData(data);
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchText) {

		data.text = this->current;
		double angle = math::getAbsAngle(data.firstDim.x, data.firstDim.y, data.secondDim.x, data.secondDim.y);
		ShPoint3d temp;
		math::rotate(angle, this->current.x, this->current.y, this->current.x + 10, this->current.y, temp.x, temp.y);
		math::checkLineLineIntersect(this->current, temp, data.firstOrigin, data.firstDim, data.firstDim);
		math::checkLineLineIntersect(this->current, temp, data.secondOrigin, data.secondDim, data.secondDim);

		dimAligned->setData(data);
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchMove) {

		double disX = this->current.x - this->base.x;
		double disY = this->current.y - this->base.y;

		data.firstOrigin.x += disX;
		data.firstOrigin.y += disY;
		data.firstDim.x += disX;
		data.firstDim.y += disY;
		data.secondOrigin.x += disX;
		data.secondOrigin.y += disY;
		data.secondDim.x += disX;
		data.secondDim.y += disY;
		data.text.x += disX;
		data.text.y += disY;

		dimAligned->setData(data);
	}
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

void ShPossibleEntityToStretchFinder::visit(ShPoint *point) {

	if (this->point.isEqual(point->getPosition()) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchMove);
		this->possible = true;
	}
}

void ShPossibleEntityToStretchFinder::visit(ShDot *dot) {

	if (this->point.isEqual(dot->getPosition()) == true) {

		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchMove);
		this->possible = true;
	}
}

void ShPossibleEntityToStretchFinder::visit(ShDimLinear *dimLinear) {

	ShDimLinearData data = dimLinear->getData();

	if (this->point.isEqual(data.firstOrigin) == true) {
		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchFirstOrigin);
		this->possible = true;
	}
	else if (this->point.isEqual(data.secondOrigin) == true) {
		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchSecondOrigin);
		this->possible = true;
	}
	else if (this->point.isEqual(data.firstDim) == true) {
		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchFirstDim);
		this->possible = true;
	}
	else if (this->point.isEqual(data.secondDim) == true) {
		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchSecondDim);
		this->possible = true;
	}
	else if (this->point.isEqual(data.text) == true) {
		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchText);
		this->possible = true;
	}
}

void ShPossibleEntityToStretchFinder::visit(ShDimAligned *dimAligned) {

	ShDimAlignedData data = dimAligned->getData();

	if (this->point.isEqual(data.firstOrigin) == true) {
		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchFirstOrigin);
		this->possible = true;
	}
	else if (this->point.isEqual(data.secondOrigin) == true) {
		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchSecondOrigin);
		this->possible = true;
	}
	else if (this->point.isEqual(data.firstDim) == true) {
		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchFirstDim);
		this->possible = true;
	}
	else if (this->point.isEqual(data.secondDim) == true) {
		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchSecondDim);
		this->possible = true;
	}
	else if (this->point.isEqual(data.text) == true) {
		*this->stretchData = new ShStretchLeafData(StretchPoint::StretchText);
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

void ShStretchDataForMoveCreator::visit(ShPoint *point) {

	*this->stretchData = new ShStretchLeafData(StretchPoint::StretchMove);
}

void ShStretchDataForMoveCreator::visit(ShDot *dot) {

	*this->stretchData = new ShStretchLeafData(StretchPoint::StretchMove);
}

void ShStretchDataForMoveCreator::visit(ShDimLinear *dimLinear) {

	*this->stretchData = new ShStretchLeafData(StretchPoint::StretchMove);
}

void ShStretchDataForMoveCreator::visit(ShDimAligned *dimAligned) {

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

	if (this->checkPointLiesInsideRect(line->getStart()) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchStart;
	}

	if (this->checkPointLiesInsideRect(line->getEnd()) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchEnd;
	}

	if (insideCount == 2)
		stretchPoint = StretchPoint::StretchMove;

	*this->stretchData = new ShStretchLeafData(stretchPoint);
}

void ShStretchPointRectFinder::visit(ShCircle *circle) {

	StretchPoint stretchPoint = StretchPoint::StretchNothing;

	if (this->checkPointLiesInsideRect(circle->getCenter()) == true)
		stretchPoint = StretchPoint::StretchMove;

	*this->stretchData = new ShStretchLeafData(stretchPoint);
}

void ShStretchPointRectFinder::visit(ShArc *arc) {

	int insideCount = 0;
	StretchPoint stretchPoint = StretchPoint::StretchNothing;

	if (this->checkPointLiesInsideRect(arc->getStart()) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchStart;
	}

	if (this->checkPointLiesInsideRect(arc->getEnd()) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchEnd;
	}

	if (insideCount == 2)
		stretchPoint = StretchPoint::StretchMove;

	*this->stretchData = new ShStretchLeafData(stretchPoint);
}

void ShStretchPointRectFinder::visit(ShPoint *point) {

	StretchPoint stretchPoint = StretchPoint::StretchNothing;

	if (this->checkPointLiesInsideRect(point->getPosition()) == true) {

		stretchPoint = StretchPoint::StretchMove;
	}

	*this->stretchData = new ShStretchLeafData(stretchPoint);
}

void ShStretchPointRectFinder::visit(ShDot *dot) {

	StretchPoint stretchPoint = StretchPoint::StretchNothing;

	if (this->checkPointLiesInsideRect(dot->getPosition()) == true) {

		stretchPoint = StretchPoint::StretchMove;
	}

	*this->stretchData = new ShStretchLeafData(stretchPoint);
}

void ShStretchPointRectFinder::visit(ShDimLinear *dimLinear) {

	int insideCount = 0;
	StretchPoint stretchPoint = StretchPoint::StretchNothing;
	ShDimLinearData data = dimLinear->getData();

	if (this->checkPointLiesInsideRect(data.firstOrigin) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchFirstOrigin;
	}
	if (this->checkPointLiesInsideRect(data.secondOrigin) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchSecondOrigin;
	}
	if (this->checkPointLiesInsideRect(data.firstDim) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchFirstDim;
	}
	if (this->checkPointLiesInsideRect(data.secondDim) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchSecondDim;
	}
	if (this->checkPointLiesInsideRect(data.text) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchText;
	}

	if (insideCount > 1)
		stretchPoint = StretchPoint::StretchMove;

	*this->stretchData = new ShStretchLeafData(stretchPoint);
}

void ShStretchPointRectFinder::visit(ShDimAligned *dimAligned) {

	int insideCount = 0;
	StretchPoint stretchPoint = StretchPoint::StretchNothing;
	ShDimAlignedData data = dimAligned->getData();

	if (this->checkPointLiesInsideRect(data.firstOrigin) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchFirstOrigin;
	}
	if (this->checkPointLiesInsideRect(data.secondOrigin) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchSecondOrigin;
	}
	if (this->checkPointLiesInsideRect(data.firstDim) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchFirstDim;
	}
	if (this->checkPointLiesInsideRect(data.secondDim) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchSecondDim;
	}
	if (this->checkPointLiesInsideRect(data.text) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchText;
	}

	if (insideCount > 1)
		stretchPoint = StretchPoint::StretchMove;

	*this->stretchData = new ShStretchLeafData(stretchPoint);
}

bool ShStretchPointRectFinder::checkPointLiesInsideRect(const ShPoint3d &point) {

	return math::checkPointLiesInsideRect(point, this->topLeft, this->bottomRight, 0);
}
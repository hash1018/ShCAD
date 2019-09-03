
#include "ShTrimer.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Base\ShMath.h"
#include "ShFootOfPerpendicularVisitor.h"

ShTrimer::ShTrimer(const QLinkedList<ShEntity*> &baseEntities, const ShPoint3d &clickPoint, QLinkedList<ShEntity*> &trimedEntities, bool &valid)
	:baseEntities(baseEntities), clickPoint(clickPoint), trimedEntities(trimedEntities), valid(valid) {

}

ShTrimer::~ShTrimer() {

}


void ShTrimer::visit(ShLine *line) {

	QLinkedList<ShPoint3d> betweenStartAndClickTrimPointList;
	QLinkedList<ShPoint3d> betweenEndAndClickTrimPointList;

	ShLineTrimPointFinder visitor(line, this->clickPoint, betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);

	auto itr = this->baseEntities.begin();
	for (itr; itr != this->baseEntities.end(); ++itr) {
	
		(*itr)->accept(&visitor);
	}

	if (betweenStartAndClickTrimPointList.count() == 0 &&
		betweenEndAndClickTrimPointList.count() == 0)
		return;

	ShPoint3d trimPoint, trimPoint2;
	ShLine *trimedLine;
	if (betweenStartAndClickTrimPointList.count() != 0 &&
		betweenEndAndClickTrimPointList.count() == 0) {
	
		trimPoint = this->getClosestByDistance(this->clickPoint, betweenStartAndClickTrimPointList);
		trimedLine = line->clone();
		trimedLine->setEnd(trimPoint);
		this->trimedEntities.append(trimedLine);
		this->valid = true;
	}
	else if (betweenStartAndClickTrimPointList.count() == 0 &&
		betweenEndAndClickTrimPointList.count() != 0) {
	
		trimPoint = this->getClosestByDistance(this->clickPoint, betweenEndAndClickTrimPointList);
		trimedLine = line->clone();
		trimedLine->setStart(trimPoint);
		this->trimedEntities.append(trimedLine);
		this->valid = true;
	}
	else if (betweenStartAndClickTrimPointList.count() != 0 &&
		betweenEndAndClickTrimPointList.count() != 0) {
	
		trimPoint = this->getClosestByDistance(this->clickPoint, betweenStartAndClickTrimPointList);
		trimPoint2 = this->getClosestByDistance(this->clickPoint, betweenEndAndClickTrimPointList);
	
		trimedLine = line->clone();
		ShLine *trimedLine2 = line->clone();
		trimedLine->setEnd(trimPoint);
		trimedLine2->setStart(trimPoint2);

		this->trimedEntities.append(trimedLine);
		this->trimedEntities.append(trimedLine2);

		this->valid = true;
	}

}

void ShTrimer::visit(ShCircle *circle) {

	QLinkedList<ShPoint3d> clockWiseTrimPointList;
	QLinkedList<ShPoint3d> antiClockWiseTrimPointList;

	ShCircleTrimPointFinder visitor(circle, this->clickPoint, clockWiseTrimPointList, antiClockWiseTrimPointList);

	auto itr = this->baseEntities.begin();
	for (itr; itr != this->baseEntities.end(); ++itr) {

		(*itr)->accept(&visitor);
	}

	if (clockWiseTrimPointList.count() == 0 && antiClockWiseTrimPointList.count() == 0)
		return;

	ShPoint3d trimPoint, trimPoint2;

	if (clockWiseTrimPointList.count() >= 2 && antiClockWiseTrimPointList.count() == 0) {

		trimPoint = this->getClosestByAngle(this->clickPoint, circle->getCenter(), clockWiseTrimPointList, false);
		trimPoint2 = this->getClosestByAngle(this->clickPoint, circle->getCenter(), clockWiseTrimPointList);
	}
	else if (clockWiseTrimPointList.count() == 0 && antiClockWiseTrimPointList.count() >= 2) {

		trimPoint = this->getClosestByAngle(this->clickPoint, circle->getCenter(), antiClockWiseTrimPointList, false);
		trimPoint2 = this->getClosestByAngle(this->clickPoint, circle->getCenter(), antiClockWiseTrimPointList);
	}
	else if (clockWiseTrimPointList.count() >= 1 && antiClockWiseTrimPointList.count() >= 1) {

		trimPoint = this->getClosestByAngle(this->clickPoint, circle->getCenter(), clockWiseTrimPointList, false);
		trimPoint2 = this->getClosestByAngle(this->clickPoint, circle->getCenter(), antiClockWiseTrimPointList);
	}
	else {
	
		return;
	}

	double startAngle = math::getAbsAngle(circle->getCenter().x, circle->getCenter().y, trimPoint2.x, trimPoint2.y);
	double endAngle = math::getAbsAngle(circle->getCenter().x, circle->getCenter().y, trimPoint.x, trimPoint.y);

	ShArcData data = ShArcData(circle->getCenter(), circle->getRadius(), startAngle, endAngle);
	ShArc *trimedArc = new ShArc(circle->getPropertyData(), data, circle->getLayer());

	this->trimedEntities.append(trimedArc);
	this->valid = true;

}

void ShTrimer::visit(ShArc *arc) {

	QLinkedList<ShPoint3d> clockWiseTrimPointList;
	QLinkedList<ShPoint3d> antiClockWiseTrimPointList;

	ShArcTrimPointFinder visitor(arc, this->clickPoint, clockWiseTrimPointList, antiClockWiseTrimPointList);

	auto itr = this->baseEntities.begin();
	for (itr; itr != this->baseEntities.end(); ++itr) {

		(*itr)->accept(&visitor);
	}

	if (clockWiseTrimPointList.count() == 0 && antiClockWiseTrimPointList.count() == 0)
		return;

	if (clockWiseTrimPointList.count() != 0 && antiClockWiseTrimPointList.count() == 0) {
	
		ShPoint3d trimPoint = this->getClosestByAngle(this->clickPoint, arc->getCenter(), clockWiseTrimPointList, false);
		double angle = math::getAbsAngle(arc->getCenter().x, arc->getCenter().y, trimPoint.x, trimPoint.y);

		ShArc *trimedArc = arc->clone();
		trimedArc->setEndAngle(angle);
		this->trimedEntities.append(trimedArc);
		this->valid = true;
	}
	else if (clockWiseTrimPointList.count() == 0 && antiClockWiseTrimPointList.count() != 0) {
	
		ShPoint3d trimPoint = this->getClosestByAngle(this->clickPoint, arc->getCenter(), antiClockWiseTrimPointList);
		double angle = math::getAbsAngle(arc->getCenter().x, arc->getCenter().y, trimPoint.x, trimPoint.y);

		ShArc *trimedArc = arc->clone();
		trimedArc->setStartAngle(angle);
		this->trimedEntities.append(trimedArc);
		this->valid = true;
	}
	else if (clockWiseTrimPointList.count() != 0 && antiClockWiseTrimPointList.count() != 0) {
	
		ShPoint3d trimPoint = this->getClosestByAngle(this->clickPoint, arc->getCenter(), clockWiseTrimPointList, false);
		ShPoint3d trimPoint2 = this->getClosestByAngle(this->clickPoint, arc->getCenter(), antiClockWiseTrimPointList);

		double angle = math::getAbsAngle(arc->getCenter().x, arc->getCenter().y, trimPoint.x, trimPoint.y);
		double angle2 = math::getAbsAngle(arc->getCenter().x, arc->getCenter().y, trimPoint2.x, trimPoint2.y);

		ShArc *trimedArc = arc->clone();
		ShArc *trimedArc2 = arc->clone();

		trimedArc->setEndAngle(angle);
		trimedArc2->setStartAngle(angle2);

		this->trimedEntities.append(trimedArc);
		this->trimedEntities.append(trimedArc2);
		this->valid = true;
	}
}

ShPoint3d ShTrimer::getClosestByDistance(const ShPoint3d &clickPoint, const QLinkedList<ShPoint3d> &trimPointList) {

	auto trimItr = const_cast<QLinkedList<ShPoint3d>&>(trimPointList).begin();
	ShPoint3d closest = (*trimItr);
	++trimItr;
	double disToTrim;
	double disToClosest = math::getDistance(clickPoint.x, clickPoint.y,
		closest.x, closest.y);


	while (trimItr != const_cast<QLinkedList<ShPoint3d>&>(trimPointList).end()) {

		disToTrim = math::getDistance(clickPoint.x, clickPoint.y,
			(*trimItr).x, (*trimItr).y);

		if (math::compare(disToClosest, disToTrim) == 1) {
			closest = (*trimItr);
			disToClosest = disToTrim;
		}

		++trimItr;
	}

	return closest;
}

ShPoint3d ShTrimer::getClosestByAngle(const ShPoint3d &clickPoint, const ShPoint3d &center, const QLinkedList<ShPoint3d> &trimPointList, bool antiClockWise) {

	double angleToClick = math::getAbsAngle(center.x, center.y, clickPoint.x, clickPoint.y);

	auto trimItr = const_cast<QLinkedList<ShPoint3d>&>(trimPointList).begin();
	ShPoint3d closest = (*trimItr);
	++trimItr;

	double angleToClosest = math::getAbsAngle(center.x, center.y, closest.x, closest.y);
	double differenceAngleClickToClosest, differenceAngleClickToTrim;

	if (antiClockWise == true)
		differenceAngleClickToClosest = math::getAngleDifference(angleToClick, angleToClosest);
	else
		differenceAngleClickToClosest = math::getAngleDifference(angleToClick, angleToClosest, false);


	while (trimItr != const_cast<QLinkedList<ShPoint3d>&>(trimPointList).end()) {

		double angleToTrim = math::getAbsAngle(center.x, center.y, (*trimItr).x, (*trimItr).y);

		if (antiClockWise == true)
			differenceAngleClickToTrim = math::getAngleDifference(angleToClick, angleToTrim);
		else
			differenceAngleClickToTrim = math::getAngleDifference(angleToClick, angleToTrim, false);

		if (math::compare(differenceAngleClickToClosest, differenceAngleClickToTrim) == 1) {
			closest = (*trimItr);
			differenceAngleClickToClosest = differenceAngleClickToTrim;
		}
		++trimItr;
	}

	return closest;
}


///////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////

ShLineTrimPointFinder::ShLineTrimPointFinder(ShLine *lineToTrim, const ShPoint3d &clickPoint, QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
	QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList)
	:lineToTrim(lineToTrim), clickPoint(clickPoint), betweenStartAndClickTrimPointList(betweenStartAndClickTrimPointList),
	betweenEndAndClickTrimPointList(betweenEndAndClickTrimPointList) {

}

ShLineTrimPointFinder::~ShLineTrimPointFinder() {

}

void ShLineTrimPointFinder::visit(ShLine *line) {

	ShPoint3d intersect;

	if (math::checkTwoLineSegmentsIntersect(this->lineToTrim->getStart(), this->lineToTrim->getEnd(),
		line->getStart(), line->getEnd(), intersect) == false)
		return;

	if (math::checkPointLiesOnLine(intersect, this->lineToTrim->getStart(), this->lineToTrim->getEnd(), 0.001) == false)
		return;

	if (this->checkIntersectLiesOnStartEnd(intersect, this->lineToTrim->getStart(), this->lineToTrim->getEnd()) == true)
		return;

	this->appendTrimPointToList(intersect);
}

void ShLineTrimPointFinder::visit(ShCircle *circle) {

	ShPoint3d intersect, intersect2;

	if (math::checkCircleLineIntersect(circle->getCenter(), circle->getRadius(),
		this->lineToTrim->getStart(), this->lineToTrim->getEnd(), intersect, intersect2) == false)
		return;

	bool insideIntersect, insideIntersect2;

	insideIntersect = math::checkPointLiesOnLine(intersect, this->lineToTrim->getStart(), this->lineToTrim->getEnd(), 0.001);
	insideIntersect2 = math::checkPointLiesOnLine(intersect2, this->lineToTrim->getStart(), this->lineToTrim->getEnd(), 0.001);

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false) {
	
		if (this->checkIntersectLiesOnStartEnd(intersect, this->lineToTrim->getStart(), this->lineToTrim->getEnd()) == false)
			this->appendTrimPointToList(intersect);
	}
	else if (insideIntersect == false && insideIntersect2 == true) {
	
		if (this->checkIntersectLiesOnStartEnd(intersect2, this->lineToTrim->getStart(), this->lineToTrim->getEnd()) == false)
			this->appendTrimPointToList(intersect2);
	}
	else if (insideIntersect == true && insideIntersect2 == true) {

		bool sameIntersect = this->checkIntersectLiesOnStartEnd(intersect, this->lineToTrim->getStart(), this->lineToTrim->getEnd());
		bool sameIntersec2 = this->checkIntersectLiesOnStartEnd(intersect2, this->lineToTrim->getStart(), this->lineToTrim->getEnd());

		if (sameIntersect == true && sameIntersec2 == true)
			return;

		if (sameIntersect == true && sameIntersec2 == false)
			this->appendTrimPointToList(intersect2);
		else if (sameIntersect == false && sameIntersec2 == true)
			this->appendTrimPointToList(intersect);
		else if (sameIntersect == false && sameIntersec2 == false)
			this->appendTrimPointToList(intersect, intersect2);
	}

}

void ShLineTrimPointFinder::visit(ShArc *arc) {

	ShPoint3d intersect, intersect2;

	if (math::checkCircleLineIntersect(arc->getCenter(), arc->getRadius(),
		this->lineToTrim->getStart(), this->lineToTrim->getEnd(), intersect, intersect2) == false)
		return;

	bool insideIntersect, insideIntersect2;

	insideIntersect = math::checkPointLiesOnArcBoundary(intersect, arc->getCenter(), arc->getRadius(), arc->getStartAngle(), arc->getEndAngle(), 0.001);
	insideIntersect2 = math::checkPointLiesOnArcBoundary(intersect2, arc->getCenter(), arc->getRadius(), arc->getStartAngle(), arc->getEndAngle(), 0.001);

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false) {
	
		if (this->checkIntersectLiesOnStartEnd(intersect, this->lineToTrim->getStart(), this->lineToTrim->getEnd()) == false)
			this->appendTrimPointToList(intersect);
	}
	else if (insideIntersect == false && insideIntersect2 == true) {
	
		if (this->checkIntersectLiesOnStartEnd(intersect2, this->lineToTrim->getStart(), this->lineToTrim->getEnd()) == false)
			this->appendTrimPointToList(intersect2);
	}
	else if (insideIntersect == true && insideIntersect2 == true) {

		insideIntersect = math::checkPointLiesOnLine(intersect, this->lineToTrim->getStart(), this->lineToTrim->getEnd(), 0.001);
		insideIntersect2 = math::checkPointLiesOnLine(intersect2, this->lineToTrim->getStart(), this->lineToTrim->getEnd(), 0.001);

		if (insideIntersect == false && insideIntersect2 == false)
			return;

		if (insideIntersect == true && insideIntersect2 == false) {
			if (this->checkIntersectLiesOnStartEnd(intersect, this->lineToTrim->getStart(), this->lineToTrim->getEnd()) == false)
				this->appendTrimPointToList(intersect);
		}
		else if (insideIntersect == false && insideIntersect2 == true) {
			if (this->checkIntersectLiesOnStartEnd(intersect2, this->lineToTrim->getStart(), this->lineToTrim->getEnd()) == false)
				this->appendTrimPointToList(intersect2);
		}
		else if (insideIntersect == true && insideIntersect2 == true) {

			bool sameIntersect = this->checkIntersectLiesOnStartEnd(intersect, this->lineToTrim->getStart(), this->lineToTrim->getEnd());
			bool sameIntersec2 = this->checkIntersectLiesOnStartEnd(intersect2, this->lineToTrim->getStart(), this->lineToTrim->getEnd());

			if (sameIntersect == true && sameIntersec2 == true)
				return;

			if (sameIntersect == true && sameIntersec2 == false)
				this->appendTrimPointToList(intersect2);
			else if (sameIntersect == false && sameIntersec2 == true)
				this->appendTrimPointToList(intersect);
			else if (sameIntersect == false && sameIntersec2 == false)
				this->appendTrimPointToList(intersect, intersect2);
		}
	}
}

bool ShLineTrimPointFinder::checkIntersectLiesOnStartEnd(const ShPoint3d &intersect, const ShPoint3d &start, const ShPoint3d &end) {

	if (math::compare(start.x, intersect.x) == 0 &&
		math::compare(start.y, intersect.y) == 0)
		return true;

	if (math::compare(end.x, intersect.x) == 0 &&
		math::compare(end.y, intersect.y) == 0)
		return true;

	return false;
}

void ShLineTrimPointFinder::appendTrimPointToList(const ShPoint3d &trimPoint) {

	ShPoint3d clickPoint;
	ShFootOfPerpendicularVisitor visitor(clickPoint.x, clickPoint.y, this->clickPoint);
	this->lineToTrim->accept(&visitor);

	double angleClickToStart = math::getAbsAngle(clickPoint.x, clickPoint.y, this->lineToTrim->getStart().x, this->lineToTrim->getStart().y);
	double angleClickToEnd = math::getAbsAngle(clickPoint.x, clickPoint.y, this->lineToTrim->getEnd().x, this->lineToTrim->getEnd().y);
	double angleClickToTrimPoint = math::getAbsAngle(clickPoint.x, clickPoint.y, trimPoint.x, trimPoint.y);

	if (math::compare(angleClickToStart, angleClickToTrimPoint) == 0)
		this->betweenStartAndClickTrimPointList.append(trimPoint);
	else
		this->betweenEndAndClickTrimPointList.append(trimPoint);

}

void ShLineTrimPointFinder::appendTrimPointToList(const ShPoint3d &trimPoint, const ShPoint3d &trimPoint2) {

	ShPoint3d clickPoint;
	ShFootOfPerpendicularVisitor visitor(clickPoint.x, clickPoint.y, this->clickPoint);
	this->lineToTrim->accept(&visitor);

	double angleClickToStart = math::getAbsAngle(clickPoint.x, clickPoint.y, this->lineToTrim->getStart().x, this->lineToTrim->getStart().y);
	double angleClickToEnd = math::getAbsAngle(clickPoint.x, clickPoint.y, this->lineToTrim->getEnd().x, this->lineToTrim->getEnd().y);
	double angleClickToTrimPoint = math::getAbsAngle(clickPoint.x, clickPoint.y, trimPoint.x, trimPoint.y);
	double angleClickToTrimPoint2 = math::getAbsAngle(clickPoint.x, clickPoint.y, trimPoint2.x, trimPoint2.y);

	if (math::compare(angleClickToTrimPoint, angleClickToTrimPoint2) == 0) {
	
		double disClickToTrimPoint = math::getDistance(clickPoint.x, clickPoint.y, trimPoint.x, trimPoint.y);
		double disClickToTrimPoint2 = math::getDistance(clickPoint.x, clickPoint.y, trimPoint2.x, trimPoint2.y);

		ShPoint3d closest;
		if (math::compare(disClickToTrimPoint, disClickToTrimPoint2) == 1)
			closest = trimPoint2;
		else
			closest = trimPoint;

		if (math::compare(angleClickToStart, angleClickToTrimPoint) == 0)
			this->betweenStartAndClickTrimPointList.append(closest);
		else
			this->betweenEndAndClickTrimPointList.append(closest);
	}
	else {
	
		if (math::compare(angleClickToStart, angleClickToTrimPoint) == 0) {
			this->betweenStartAndClickTrimPointList.append(trimPoint);
			this->betweenEndAndClickTrimPointList.append(trimPoint2);
		}
		else {
			this->betweenStartAndClickTrimPointList.append(trimPoint2);
			this->betweenEndAndClickTrimPointList.append(trimPoint);
		}
	}
}



///////////////////////////////////////////////////////////////////////////////


ShCircleTrimPointFinder::ShCircleTrimPointFinder(ShCircle *circleToTrim, const ShPoint3d &clickPoint, QLinkedList<ShPoint3d> &clockWiseTrimPointList,
	QLinkedList<ShPoint3d> &antiClockWiseTrimPointList)
	:circleToTrim(circleToTrim), clickPoint(clickPoint), clockWiseTrimPointList(clockWiseTrimPointList), antiClockWiseTrimPointList(antiClockWiseTrimPointList) {

}

	
ShCircleTrimPointFinder::~ShCircleTrimPointFinder() {

}

void ShCircleTrimPointFinder::visit(ShLine *line) {

	ShPoint3d intersect, intersect2;

	if (math::checkCircleLineIntersect(this->circleToTrim->getCenter(), this->circleToTrim->getRadius(),
		line->getStart(), line->getEnd(), intersect, intersect2) == false)
		return;

	bool insideIntersect = math::checkPointLiesOnLine(intersect, line->getStart(), line->getEnd(), 0.001);
	bool insideIntersect2 = math::checkPointLiesOnLine(intersect2, line->getStart(), line->getEnd(), 0.001);

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false)
		this->appendTrimPointToList(intersect);
	else if (insideIntersect == false && insideIntersect2 == true)
		this->appendTrimPointToList(intersect2);
	else if (insideIntersect == true && insideIntersect2 == true)
		this->appendTrimPointToList(intersect, intersect2);
	
}

void ShCircleTrimPointFinder::visit(ShCircle *circle) {

	ShPoint3d intersect, intersect2;

	if (math::checkTwoCirclesIntersect(this->circleToTrim->getCenter(), this->circleToTrim->getRadius(),
		circle->getCenter(), circle->getRadius(), intersect, intersect2) == false)
		return;

	this->appendTrimPointToList(intersect, intersect2);
}

void ShCircleTrimPointFinder::visit(ShArc *arc) {

	ShPoint3d intersect, intersect2;

	if (math::checkTwoCirclesIntersect(this->circleToTrim->getCenter(), this->circleToTrim->getRadius(),
		arc->getCenter(), arc->getRadius(), intersect, intersect2) == false)
		return;

	bool insideIntersect = math::checkPointLiesOnArcBoundary(intersect, arc->getCenter(), arc->getRadius(),
		arc->getStartAngle(), arc->getEndAngle(), 0.001);
	bool insideIntersect2 = math::checkPointLiesOnArcBoundary(intersect2, arc->getCenter(), arc->getRadius(),
		arc->getStartAngle(), arc->getEndAngle(), 0.001);

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false)
		this->appendTrimPointToList(intersect);
	else if (insideIntersect == false && insideIntersect2 == true)
		this->appendTrimPointToList(intersect2);
	else if (insideIntersect == true && insideIntersect2 == true)
		this->appendTrimPointToList(intersect, intersect2);
}

void ShCircleTrimPointFinder::appendTrimPointToList(const ShPoint3d &trimPoint) {

	double angleCenterToClick = math::getAbsAngle(this->circleToTrim->getCenter().x, this->circleToTrim->getCenter().y, 
		this->clickPoint.x, this->clickPoint.y);
	double angleCenterToIntersect = math::getAbsAngle(this->circleToTrim->getCenter().x, this->circleToTrim->getCenter().y,
		trimPoint.x, trimPoint.y);

	double difference = math::getAngleDifference(angleCenterToClick, angleCenterToIntersect);

	if (math::compare(difference, 180) == 1)
		this->clockWiseTrimPointList.append(trimPoint);
	else
		this->antiClockWiseTrimPointList.append(trimPoint);
}

void ShCircleTrimPointFinder::appendTrimPointToList(const ShPoint3d &trimPoint, const ShPoint3d &trimPoint2) {

	double angleCenterToClick = math::getAbsAngle(this->circleToTrim->getCenter().x, this->circleToTrim->getCenter().y,
		this->clickPoint.x, this->clickPoint.y);
	double angleCenterToIntersect = math::getAbsAngle(this->circleToTrim->getCenter().x, this->circleToTrim->getCenter().y,
		trimPoint.x, trimPoint.y);
	double angleCenterToIntersect2 = math::getAbsAngle(this->circleToTrim->getCenter().x, this->circleToTrim->getCenter().y,
		trimPoint2.x, trimPoint2.y);

	double difference = math::getAngleDifference(angleCenterToClick, angleCenterToIntersect);
	double difference2 = math::getAngleDifference(angleCenterToClick, angleCenterToIntersect2);

	if (math::compare(difference, difference2) == 1) {
		this->antiClockWiseTrimPointList.append(trimPoint2);
		this->clockWiseTrimPointList.append(trimPoint);
	}
	else {
		this->antiClockWiseTrimPointList.append(trimPoint);
		this->clockWiseTrimPointList.append(trimPoint2);
	}
}


/////////////////////////////////////////////////////////////////////////


ShArcTrimPointFinder::ShArcTrimPointFinder(ShArc *arcToTrim, const ShPoint3d &clickPoint, QLinkedList<ShPoint3d> &clockWiseTrimPointList,
	QLinkedList<ShPoint3d> &antiClockWiseTrimPointList)
	:arcToTrim(arcToTrim), clickPoint(clickPoint), clockWiseTrimPointList(clockWiseTrimPointList),
	antiClockWiseTrimPointList(antiClockWiseTrimPointList) {

}

ShArcTrimPointFinder::~ShArcTrimPointFinder() {

}

void ShArcTrimPointFinder::visit(ShLine *line) {

	ShPoint3d intersect, intersect2;

	if (math::checkCircleLineIntersect(this->arcToTrim->getCenter(), this->arcToTrim->getRadius(),
		line->getStart(), line->getEnd(), intersect, intersect2) == false)
		return;

	bool insideIntersect = math::checkPointLiesOnLine(intersect, line->getStart(), line->getEnd(), 0.001);
	bool insideIntersect2 = math::checkPointLiesOnLine(intersect2, line->getStart(), line->getEnd(), 0.001);

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false) {
	
		if (math::checkPointLiesOnArcBoundary(intersect, this->arcToTrim->getCenter(), this->arcToTrim->getRadius(),
			this->arcToTrim->getStartAngle(), this->arcToTrim->getEndAngle(), 0.001) == true) {
		
			if (this->checkIntersectLiesOnStartEnd(intersect, this->arcToTrim->getStart(), this->arcToTrim->getEnd()) == false)
				this->appendTrimPointToList(intersect);
		}
	}
	else if (insideIntersect == false && insideIntersect2 == true) {

		if (math::checkPointLiesOnArcBoundary(intersect2, this->arcToTrim->getCenter(), this->arcToTrim->getRadius(),
			this->arcToTrim->getStartAngle(), this->arcToTrim->getEndAngle(), 0.001) == true) {

			if (this->checkIntersectLiesOnStartEnd(intersect2, this->arcToTrim->getStart(), this->arcToTrim->getEnd()) == false)
				this->appendTrimPointToList(intersect2);
		}
	}
	else if (insideIntersect == true && insideIntersect2 == true) {
	
		insideIntersect = math::checkPointLiesOnArcBoundary(intersect, this->arcToTrim->getCenter(), this->arcToTrim->getRadius(),
			this->arcToTrim->getStartAngle(), this->arcToTrim->getEndAngle(), 0.001);
		insideIntersect2 = math::checkPointLiesOnArcBoundary(intersect2, this->arcToTrim->getCenter(), this->arcToTrim->getRadius(),
			this->arcToTrim->getStartAngle(), this->arcToTrim->getEndAngle(), 0.001);

		if (insideIntersect == false && insideIntersect2 == false)
			return;

		if (insideIntersect == true && insideIntersect2 == false) {
		
			if (this->checkIntersectLiesOnStartEnd(intersect, this->arcToTrim->getStart(), this->arcToTrim->getEnd()) == false)
				this->appendTrimPointToList(intersect);
		}
		else if (insideIntersect == false && insideIntersect2 == true) {
		
			if (this->checkIntersectLiesOnStartEnd(intersect2, this->arcToTrim->getStart(), this->arcToTrim->getEnd()) == false)
				this->appendTrimPointToList(intersect2);
		}
		else if (insideIntersect == true && insideIntersect2 == true) {
		
			bool sameIntersect, sameIntersect2;
			sameIntersect = this->checkIntersectLiesOnStartEnd(intersect, this->arcToTrim->getStart(), this->arcToTrim->getEnd());
			sameIntersect2 = this->checkIntersectLiesOnStartEnd(intersect2, this->arcToTrim->getStart(), this->arcToTrim->getEnd());

			if (sameIntersect == true && sameIntersect2 == true)
				return;

			if (sameIntersect == false && sameIntersect2 == true) {
				this->appendTrimPointToList(intersect);
			}
			else if (sameIntersect == true && sameIntersect2 == false) {
				this->appendTrimPointToList(intersect2);
			}
			else if (sameIntersect == false && sameIntersect2 == false) {
				this->appendTrimPointToList(intersect, intersect2);
			}
		}
	}
}

void ShArcTrimPointFinder::visit(ShCircle *circle) {

	ShPoint3d intersect, intersect2;

	if (math::checkTwoCirclesIntersect(this->arcToTrim->getCenter(), this->arcToTrim->getRadius(),
		circle->getCenter(), circle->getRadius(), intersect, intersect2) == false)
		return;

	bool insideIntersect = math::checkPointLiesOnArcBoundary(intersect, this->arcToTrim->getCenter(), this->arcToTrim->getRadius(),
		this->arcToTrim->getStartAngle(), this->arcToTrim->getEndAngle(), 0.001);
	bool insideIntersect2 = math::checkPointLiesOnArcBoundary(intersect2, this->arcToTrim->getCenter(), this->arcToTrim->getRadius(),
		this->arcToTrim->getStartAngle(), this->arcToTrim->getEndAngle(), 0.001);

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false) {

		if (this->checkIntersectLiesOnStartEnd(intersect, this->arcToTrim->getStart(), this->arcToTrim->getEnd()) == false)
			this->appendTrimPointToList(intersect);
	}
	else if (insideIntersect == false && insideIntersect2 == true) {

		if (this->checkIntersectLiesOnStartEnd(intersect2, this->arcToTrim->getStart(), this->arcToTrim->getEnd()) == false)
			this->appendTrimPointToList(intersect2);
	}
	else if (insideIntersect == true && insideIntersect2 == true) {

		bool sameIntersect, sameIntersect2;
		sameIntersect = this->checkIntersectLiesOnStartEnd(intersect, this->arcToTrim->getStart(), this->arcToTrim->getEnd());
		sameIntersect2 = this->checkIntersectLiesOnStartEnd(intersect2, this->arcToTrim->getStart(), this->arcToTrim->getEnd());

		if (sameIntersect == true && sameIntersect2 == true)
			return;

		if (sameIntersect == false && sameIntersect2 == true) {
			this->appendTrimPointToList(intersect);
		}
		else if (sameIntersect == true && sameIntersect2 == false) {
			this->appendTrimPointToList(intersect2);
		}
		else if (sameIntersect == false && sameIntersect2 == false) {
			this->appendTrimPointToList(intersect, intersect2);
		}
	}
}

void ShArcTrimPointFinder::visit(ShArc *arc) {

	ShPoint3d intersect, intersect2;

	if (math::checkTwoCirclesIntersect(this->arcToTrim->getCenter(), this->arcToTrim->getRadius(),
		arc->getCenter(), arc->getRadius(), intersect, intersect2) == false)
		return;

	bool insideIntersect = math::checkPointLiesOnArcBoundary(intersect, arc->getCenter(), arc->getRadius(),
		arc->getStartAngle(), arc->getEndAngle(), 0.001);
	bool insideIntersect2 = math::checkPointLiesOnArcBoundary(intersect2, arc->getCenter(), arc->getRadius(),
		arc->getStartAngle(), arc->getEndAngle(), 0.001);

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false) {
	
		if (math::checkPointLiesOnArcBoundary(intersect, this->arcToTrim->getCenter(), this->arcToTrim->getRadius(),
			this->arcToTrim->getStartAngle(), this->arcToTrim->getEndAngle(), 0.001) == true) {

			if (this->checkIntersectLiesOnStartEnd(intersect, this->arcToTrim->getStart(), this->arcToTrim->getEnd()) == false)
				this->appendTrimPointToList(intersect);
		}
	}
	else if (insideIntersect == false && insideIntersect == true) {
	
		if (math::checkPointLiesOnArcBoundary(intersect2, this->arcToTrim->getCenter(), this->arcToTrim->getRadius(),
			this->arcToTrim->getStartAngle(), this->arcToTrim->getEndAngle(), 0.001) == true) {

			if (this->checkIntersectLiesOnStartEnd(intersect2, this->arcToTrim->getStart(), this->arcToTrim->getEnd()) == false)
				this->appendTrimPointToList(intersect2);
		}
	}
	else if (insideIntersect == true && insideIntersect2 == true) {
	
		insideIntersect = math::checkPointLiesOnArcBoundary(intersect, this->arcToTrim->getCenter(), this->arcToTrim->getRadius(),
			this->arcToTrim->getStartAngle(), this->arcToTrim->getEndAngle(), 0.001);
		insideIntersect2 = math::checkPointLiesOnArcBoundary(intersect2, this->arcToTrim->getCenter(), this->arcToTrim->getRadius(),
			this->arcToTrim->getStartAngle(), this->arcToTrim->getEndAngle(), 0.001);

		if (insideIntersect == false && insideIntersect2 == false)
			return;

		if (insideIntersect == true && insideIntersect2 == false) {

			if (this->checkIntersectLiesOnStartEnd(intersect, this->arcToTrim->getStart(), this->arcToTrim->getEnd()) == false)
				this->appendTrimPointToList(intersect);
		}
		else if (insideIntersect == false && insideIntersect2 == true) {

			if (this->checkIntersectLiesOnStartEnd(intersect2, this->arcToTrim->getStart(), this->arcToTrim->getEnd()) == false)
				this->appendTrimPointToList(intersect2);
		}
		else if (insideIntersect == true && insideIntersect2 == true) {

			bool sameIntersect, sameIntersect2;
			sameIntersect = this->checkIntersectLiesOnStartEnd(intersect, this->arcToTrim->getStart(), this->arcToTrim->getEnd());
			sameIntersect2 = this->checkIntersectLiesOnStartEnd(intersect2, this->arcToTrim->getStart(), this->arcToTrim->getEnd());

			if (sameIntersect == true && sameIntersect2 == true)
				return;

			if (sameIntersect == false && sameIntersect2 == true) {
				this->appendTrimPointToList(intersect);
			}
			else if (sameIntersect == true && sameIntersect2 == false) {
				this->appendTrimPointToList(intersect2);
			}
			else if (sameIntersect == false && sameIntersect2 == false) {
				this->appendTrimPointToList(intersect, intersect2);
			}
		}
	}
}

bool ShArcTrimPointFinder::checkIntersectLiesOnStartEnd(const ShPoint3d &intersect, const ShPoint3d &start, const ShPoint3d &end) {

	if (math::compare(start.x, intersect.x) == 0 &&
		math::compare(start.y, intersect.y) == 0)
		return true;

	if (math::compare(end.x, intersect.x) == 0 &&
		math::compare(end.y, intersect.y) == 0)
		return true;

	return false;
}

void ShArcTrimPointFinder::appendTrimPointToList(const ShPoint3d &trimPoint) {

	double angleCenterToClick = math::getAbsAngle(this->arcToTrim->getCenter().x, this->arcToTrim->getCenter().y,
		this->clickPoint.x, this->clickPoint.y);
	double angleCenterToTrimPoint = math::getAbsAngle(this->arcToTrim->getCenter().x, this->arcToTrim->getCenter().y,
		trimPoint.x, trimPoint.y);

	double difference = math::getAngleDifference(angleCenterToClick, angleCenterToTrimPoint);

	if (math::compare(difference, 180) == 1) {
		this->clockWiseTrimPointList.append(trimPoint);
	}
	else {
		this->antiClockWiseTrimPointList.append(trimPoint);
	}
}

void ShArcTrimPointFinder::appendTrimPointToList(const ShPoint3d &trimPoint, const ShPoint3d &trimPoint2) {

	double angleCenterToClick = math::getAbsAngle(this->arcToTrim->getCenter().x, this->arcToTrim->getCenter().y,
		this->clickPoint.x, this->clickPoint.y);
	double angleCenterToTrimPoint = math::getAbsAngle(this->arcToTrim->getCenter().x, this->arcToTrim->getCenter().y,
		trimPoint.x, trimPoint.y);
	double angleCenterToTrimPoint2 = math::getAbsAngle(this->arcToTrim->getCenter().x, this->arcToTrim->getCenter().y,
		trimPoint2.x, trimPoint2.y);

	double difference = math::getAngleDifference(angleCenterToClick, angleCenterToTrimPoint);
	double difference2 = math::getAngleDifference(angleCenterToClick, angleCenterToTrimPoint2);

	//this means in the antiClockWise, the intersect2 reaches first. 
	if (math::compare(difference, difference2) == 1) {

		//click point is between intersect and intersect2.
		if (math::checkAngleLiesOnAngleBetween(angleCenterToTrimPoint, this->arcToTrim->getEndAngle(),
			angleCenterToTrimPoint2) == true) {
			this->clockWiseTrimPointList.append(trimPoint);
			this->antiClockWiseTrimPointList.append(trimPoint2);
		}
		else if (math::checkAngleLiesOnAngleBetween(this->arcToTrim->getStartAngle(), angleCenterToTrimPoint2,
			angleCenterToClick) == true) {

			this->appendTrimPointToList(trimPoint2);
		}
		else if (math::checkAngleLiesOnAngleBetween(angleCenterToTrimPoint, this->arcToTrim->getEndAngle(),
			angleCenterToClick) == true) {

			this->appendTrimPointToList(trimPoint);
		}
	}
	//this means in the antiClockWise, the intersect reaches first.
	else {

		if (math::checkAngleLiesOnAngleBetween(angleCenterToTrimPoint2, this->arcToTrim->getEndAngle(),
			angleCenterToTrimPoint) == true) {
			clockWiseTrimPointList.append(trimPoint2);
			antiClockWiseTrimPointList.append(trimPoint);
		}
		else if (math::checkAngleLiesOnAngleBetween(this->arcToTrim->getStartAngle(), angleCenterToTrimPoint,
			angleCenterToClick) == true) {

			this->appendTrimPointToList(trimPoint);
		}
		else if (math::checkAngleLiesOnAngleBetween(angleCenterToTrimPoint2, this->arcToTrim->getEndAngle(),
			angleCenterToClick) == true) {

			this->appendTrimPointToList(trimPoint2);
		}
	}
}
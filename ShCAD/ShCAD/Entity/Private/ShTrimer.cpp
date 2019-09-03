
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

}

void ShTrimer::visit(ShArc *arc) {


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

}

void ShLineTrimPointFinder::visit(ShArc *arc) {

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
		betweenStartAndClickTrimPointList.append(trimPoint);
	else
		betweenEndAndClickTrimPointList.append(trimPoint);

}
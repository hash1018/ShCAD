
#include "ShExtender.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Base\ShMath.h"


ShEntityPartToExtendFinder::ShEntityPartToExtendFinder(ShEntityPartToExtend &entityPartToExtend, ShPoint3d &pointToExtend, const ShPoint3d &clickPoint)
	:entityPartToExtend(entityPartToExtend), pointToExtend(pointToExtend), clickPoint(clickPoint) {

}

ShEntityPartToExtendFinder::~ShEntityPartToExtendFinder() {

}

void ShEntityPartToExtendFinder::visit(ShLine *line) {

	double disClickToStart = math::getDistance(this->clickPoint.x, this->clickPoint.y,
		line->getStart().x, line->getStart().y);
	double disClickToEnd = math::getDistance(this->clickPoint.x, this->clickPoint.y,
		line->getEnd().x, line->getEnd().y);

	if (math::compare(disClickToStart, disClickToEnd) == 1) {
		this->entityPartToExtend = ShEntityPartToExtend::End;
		this->pointToExtend = line->getEnd();
	}
	else {
		this->entityPartToExtend = ShEntityPartToExtend::Start;
		this->pointToExtend = line->getStart();
	}
	
}

void ShEntityPartToExtendFinder::visit(ShArc *arc) {

	ShArcData data = arc->getData();

	double angleCenterToClick = math::getAbsAngle(data.center.x, data.center.y,
		this->clickPoint.x, this->clickPoint.y);
	double differenceAngle = math::getAngleDifference(data.startAngle, data.endAngle);

	
	if (math::checkAngleLiesOnAngleBetween(data.startAngle,
		math::addAngle(data.startAngle, differenceAngle / 2),
		angleCenterToClick) == true) {

		this->pointToExtend = arc->getStart();
		this->entityPartToExtend = ShEntityPartToExtend::Start;
	}
	else {
		this->pointToExtend = arc->getEnd();
		this->entityPartToExtend = ShEntityPartToExtend::End;
	}
}


/////////////////////////////////////////////////////////

ShExtender::ShExtender(const QLinkedList<ShEntity*> &baseEntities, const ShPoint3d &clickPoint, ShEntity* *extendedEntity, bool &valid)
	:baseEntities(baseEntities), clickPoint(clickPoint), extendedEntity(extendedEntity), valid(valid) {

}

ShExtender::~ShExtender() {

}

void ShExtender::visit(ShLine *line) {

	QLinkedList<ShPoint3d> extensionPointList;
	ShEntityPartToExtend entityPartToExtend;
	ShPoint3d linePointToExtend;


	ShEntityPartToExtendFinder entityPartToExtendFinder(entityPartToExtend, linePointToExtend, this->clickPoint);
	line->accept(&entityPartToExtendFinder);


	ShLineExtensionPointFinder extensionPointFinder(extensionPointList, line, entityPartToExtend);
	
	auto itr = this->baseEntities.begin();
	for (itr; itr != this->baseEntities.end(); ++itr)
		(*itr)->accept(&extensionPointFinder);

	if (extensionPointList.count() == 0) {
		this->valid = false;
		return;
	}

	auto pointItr = extensionPointList.begin();
	ShPoint3d closest = (*pointItr);
	++pointItr;

	while (pointItr != extensionPointList.end()) {
	
		double disToClosest = math::getDistance(linePointToExtend.x, linePointToExtend.y, closest.x, closest.y);
		double disToExtension = math::getDistance(linePointToExtend.x, linePointToExtend.y, (*pointItr).x, (*pointItr).y);

		if (math::compare(disToClosest, disToExtension) == 1)
			closest = (*pointItr);

		++pointItr;
	}

	this->valid = true;
	ShLine *extendedLine = line->clone();

	if (entityPartToExtend == ShEntityPartToExtend::Start)
		extendedLine->setStart(closest);
	else
		extendedLine->setEnd(closest);

	*this->extendedEntity = extendedLine;
}

void ShExtender::visit(ShCircle *circle) {

}

void ShExtender::visit(ShArc *arc) {

	QLinkedList<ShPoint3d> extensionPointList;
	ShEntityPartToExtend entityPartToExtend;
	ShPoint3d arcPointToExtend;
	
	ShEntityPartToExtendFinder entityPartToExtendFinder(entityPartToExtend, arcPointToExtend, this->clickPoint);
	arc->accept(&entityPartToExtendFinder);

	ShArcExtensionPointFinder extensionPointFinder(extensionPointList, arc, entityPartToExtend);

	auto itr = this->baseEntities.begin();
	for (itr; itr != this->baseEntities.end(); ++itr)
		(*itr)->accept(&extensionPointFinder);

	if (extensionPointList.count() == 0) {
		this->valid = false;
		return;
	}

	auto pointItr = extensionPointList.begin();
	ShPoint3d closest = (*pointItr);
	++pointItr;
	
	ShArcData data = arc->getData();

	while (pointItr != extensionPointList.end()) {
	
		double angleCenterToClosest = math::getAbsAngle(data.center.x, data.center.y, closest.x, closest.y);
		double angleCenterToExtensionPoint = math::getAbsAngle(data.center.x, data.center.y,
			(*pointItr).x, (*pointItr).y);
		double angleCenterToPointToExtend = math::getAbsAngle(data.center.x, data.center.y,
			arcPointToExtend.x, arcPointToExtend.y);

		if (entityPartToExtend == ShEntityPartToExtend::Start) {
			double difference = math::getAngleDifference(angleCenterToPointToExtend, angleCenterToExtensionPoint, false);
			double difference2 = math::getAngleDifference(angleCenterToPointToExtend, angleCenterToClosest, false);
			if (math::compare(difference2, difference) == 1)
				closest = (*pointItr);
		}
		else if (entityPartToExtend == ShEntityPartToExtend::End) {
			double difference = math::getAngleDifference(angleCenterToPointToExtend, angleCenterToExtensionPoint);
			double difference2 = math::getAngleDifference(angleCenterToPointToExtend, angleCenterToClosest);
			if (math::compare(difference2, difference) == 1)
				closest = (*pointItr);
		}

		++pointItr;
	}


	this->valid = true;
	ShArc *extendedArc = arc->clone();

	if (entityPartToExtend == ShEntityPartToExtend::Start)
		extendedArc->setStartAngle(math::getAbsAngle(data.center.x, data.center.y, closest.x, closest.y));
	else
		extendedArc->setEndAngle(math::getAbsAngle(data.center.x, data.center.y, closest.x, closest.y));

	*this->extendedEntity = extendedArc;
}


/////////////////////////////////////////////////////////

ShExtensionPointFinder::ShExtensionPointFinder(QLinkedList<ShPoint3d> &extensionPointList)
	:extensionPointList(extensionPointList) {

}

ShExtensionPointFinder::~ShExtensionPointFinder() {

}

////////////////////////////////////////////////////////


ShLineExtensionPointFinder::ShLineExtensionPointFinder(QLinkedList<ShPoint3d> &extensionPointList, ShLine *lineToExtend, ShEntityPartToExtend entityPartToExtend)
	:ShExtensionPointFinder(extensionPointList), lineToExtend(lineToExtend), entityPartToExtend(entityPartToExtend) {

}

ShLineExtensionPointFinder::~ShLineExtensionPointFinder() {

}

void ShLineExtensionPointFinder::visit(ShLine *line) {

	ShLineData lineToExtendData = this->lineToExtend->getData();
	ShLineData baseLineData = line->getData();

	ShPoint3d intersect;
	if (math::checkTwoLineSegmentsIntersect(lineToExtendData.start, lineToExtendData.end,
		baseLineData.start, baseLineData.end, intersect) == true)
		return;

	if (math::checkLineLineIntersect(lineToExtendData.start, lineToExtendData.end,
		baseLineData.start, baseLineData.end, intersect) == false)
		return;

	if (math::checkPointLiesOnLine(intersect, baseLineData.start, baseLineData.end, 0.001) == false)
		return;

	if (this->checkPossibleToExtend(this->lineToExtend, this->entityPartToExtend, intersect) == false)
		return;

	this->extensionPointList.append(intersect);
}

void ShLineExtensionPointFinder::visit(ShCircle *circle) {

	ShLineData lineToExtendData = this->lineToExtend->getData();
	ShCircleData baseCircleData = circle->getData();

	ShPoint3d intersect, intersect2, finalIntersect;
	if (math::checkCircleLineIntersect(baseCircleData.center, baseCircleData.radius,
		lineToExtendData.start, lineToExtendData.end, intersect, intersect2) == false)
		return;

	if (this->checkPossibleToExtend(this->lineToExtend, this->entityPartToExtend, intersect, intersect2, finalIntersect) == false)
		return;

	this->extensionPointList.append(finalIntersect);
}

void ShLineExtensionPointFinder::visit(ShArc *arc) {

	ShLineData lineToExtendData = this->lineToExtend->getData();
	ShArcData baseArcData = arc->getData();

	ShPoint3d intersect, intersect2, finalIntersect;
	if (math::checkCircleLineIntersect(baseArcData.center, baseArcData.radius,
		lineToExtendData.start, lineToExtendData.end, intersect, intersect2) == false)
		return;

	bool insideArcIntersect = false;
	bool insideArcIntersect2 = false;

	if (math::checkPointLiesOnArcBoundary(intersect, baseArcData.center, baseArcData.radius,
		baseArcData.startAngle, baseArcData.endAngle, 0.001) == true)
		insideArcIntersect = true;
	if (math::checkPointLiesOnArcBoundary(intersect2, baseArcData.center, baseArcData.radius,
		baseArcData.startAngle, baseArcData.endAngle, 0.001) == true)
		insideArcIntersect2 = true;

	if (insideArcIntersect == false && insideArcIntersect2 == false)
		return;


	if (insideArcIntersect == true && insideArcIntersect2 == false) {
		if (this->checkPossibleToExtend(this->lineToExtend, this->entityPartToExtend, intersect) == true)
			this->extensionPointList.append(intersect);
	}
	else if (insideArcIntersect == false && insideArcIntersect2 == true) {
		if (this->checkPossibleToExtend(this->lineToExtend, this->entityPartToExtend, intersect2) == true)
			this->extensionPointList.append(intersect2);
	}
	else if (insideArcIntersect == true && insideArcIntersect2 == true) {
		if (this->checkPossibleToExtend(this->lineToExtend, this->entityPartToExtend, intersect, intersect2, finalIntersect) == true)
			this->extensionPointList.append(finalIntersect);
	}
}

bool ShLineExtensionPointFinder::checkPossibleToExtend(ShLine *lineToExtend, ShEntityPartToExtend entityPartToExtend, const ShPoint3d &extensionPoint) {

	ShLineData data = lineToExtend->getData();

	if (math::checkPointLiesOnLine(extensionPoint, data.start, data.end, 0.001) == true)
		return false;

	double disStartToExtension = math::getDistance(data.start.x, data.start.y,
		extensionPoint.x, extensionPoint.y);
	double disEndToExtension = math::getDistance(data.end.x, data.end.y,
		extensionPoint.x, extensionPoint.y);

	if (entityPartToExtend == ShEntityPartToExtend::Start) {
		if (math::compare(disEndToExtension, disStartToExtension) == 1)
			if (math::compare(data.start.x, extensionPoint.x) != 0 ||
				math::compare(data.start.y, extensionPoint.y) != 0)
				return true;
	}
	else if (entityPartToExtend == ShEntityPartToExtend::End) {
		if (math::compare(disStartToExtension, disEndToExtension) == 1)
			if (math::compare(data.end.x, extensionPoint.x) != 0 ||
				math::compare(data.end.y, extensionPoint.y) != 0)
				return true;
	}

	return false;
}

bool ShLineExtensionPointFinder::checkPossibleToExtend(ShLine *lineToExtend, ShEntityPartToExtend entityPartToExtend,
	const ShPoint3d &extensionPoint, const ShPoint3d &extensionPoint2, ShPoint3d &finalExtensionPoint) {

	ShLineData data = lineToExtend->getData();

	bool insideIntersect = false;
	bool insideIntersect2 = false;

	if (math::checkPointLiesOnLine(extensionPoint, data.start, data.end, 0.001) == true)
		insideIntersect = true;
	if (math::checkPointLiesOnLine(extensionPoint2, data.start, data.end, 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == true && insideIntersect2 == true)
		return false;


	double disStartToIntersect = math::getDistance(data.start.x, data.start.y, extensionPoint.x, extensionPoint.y);
	double disEndToIntersect = math::getDistance(data.end.x, data.end.y, extensionPoint.x, extensionPoint.y);
	double disStartToIntersect2 = math::getDistance(data.start.x, data.start.y, extensionPoint2.x, extensionPoint2.y);
	double disEndToIntersect2 = math::getDistance(data.end.x, data.end.y, extensionPoint2.x, extensionPoint2.y);

	bool validExtension = false;

	if (insideIntersect == false && insideIntersect2 == true) {

		if (entityPartToExtend == ShEntityPartToExtend::Start) {
			if (math::compare(disEndToIntersect, disStartToIntersect) == 1) {
				finalExtensionPoint = extensionPoint;
				validExtension = true;
			}
		}
		else if (entityPartToExtend == ShEntityPartToExtend::End) {
			if (math::compare(disStartToIntersect, disEndToIntersect) == 1) {
				finalExtensionPoint = extensionPoint;
				validExtension = true;
			}
		}
	}
	else if (insideIntersect == true && insideIntersect2 == false) {

		if (entityPartToExtend == ShEntityPartToExtend::Start) {
			if (math::compare(disEndToIntersect2, disStartToIntersect2) == 1) {
				finalExtensionPoint = extensionPoint2;
				validExtension = true;
			}
		}
		else if (entityPartToExtend == ShEntityPartToExtend::End) {
			if (math::compare(disStartToIntersect2, disEndToIntersect2) == 1) {
				finalExtensionPoint = extensionPoint2;
				validExtension = true;
			}
		}
	}
	else if (insideIntersect == false && insideIntersect2 == false) {
		ShPoint3d mid = lineToExtend->getMid();
		double angle = math::getAbsAngle(mid.x, mid.y, extensionPoint.x, extensionPoint.y);
		double angleMidToStart = math::getAbsAngle(mid.x, mid.y, data.start.x, data.start.y);
		double angleMidToEnd = math::getAbsAngle(mid.x, mid.y, data.end.x, data.end.y);

		if (math::compare(angle, angleMidToStart) == 0) {
			if (entityPartToExtend == ShEntityPartToExtend::Start) {
				if (math::compare(disStartToIntersect, disStartToIntersect2) == 1) {
					finalExtensionPoint = extensionPoint2;
					validExtension = true;
				}
				else {
					finalExtensionPoint = extensionPoint;
					validExtension = true;
				}
			}
		}
		else {
			if (entityPartToExtend == ShEntityPartToExtend::End) {
				if (math::compare(disEndToIntersect, disEndToIntersect2) == 1) {
					finalExtensionPoint = extensionPoint2;
					validExtension = true;
				}
				else {
					finalExtensionPoint = extensionPoint;
					validExtension = true;
				}
			}
		}
	}

	if (validExtension == false)
		return false;

	if (entityPartToExtend == ShEntityPartToExtend::Start) {
		if (math::compare(data.start.x, finalExtensionPoint.x) != 0 ||
			math::compare(data.start.y, finalExtensionPoint.y) != 0)
			return true;
	}
	else if (entityPartToExtend == ShEntityPartToExtend::End) {
		if (math::compare(data.end.x, finalExtensionPoint.x) != 0 ||
			math::compare(data.end.y, finalExtensionPoint.y) != 0)
			return true;
	}

	return false;
}


////////////////////////////////////////////////////////////////////////////


ShArcExtensionPointFinder::ShArcExtensionPointFinder(QLinkedList<ShPoint3d> &extensionPointList, ShArc *arcToExtend, ShEntityPartToExtend entityPartToExtend)
	:ShExtensionPointFinder(extensionPointList), arcToExtend(arcToExtend), entityPartToExtend(entityPartToExtend) {

}

ShArcExtensionPointFinder::~ShArcExtensionPointFinder() {

}

void ShArcExtensionPointFinder::visit(ShLine *line) {

	ShArcData data = this->arcToExtend->getData();

	ShPoint3d intersect, intersect2, finalExtension;
	if (math::checkCircleLineIntersect(data.center, data.radius, line->getStart(), line->getEnd(),
		intersect, intersect2) == false)
		return;

	bool insideIntersect = false;
	bool insideIntersect2 = false;
	if (math::checkPointLiesOnLine(intersect, line->getStart(), line->getEnd(), 0.001) == true)
		insideIntersect = true;
	if (math::checkPointLiesOnLine(intersect2, line->getStart(), line->getEnd(), 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false) {
		if (this->checkPossibleToExtend(this->arcToExtend, this->entityPartToExtend, intersect) == true)
			this->extensionPointList.append(intersect);
	}
	else if (insideIntersect == false && insideIntersect2 == true) {
		if (this->checkPossibleToExtend(this->arcToExtend, this->entityPartToExtend, intersect2) == true)
			this->extensionPointList.append(intersect2);
	}
	else if (insideIntersect == true && insideIntersect2 == true) {
		if (this->checkPossibleToExtend(this->arcToExtend, this->entityPartToExtend, intersect, intersect2,
			finalExtension) == true)
			this->extensionPointList.append(finalExtension);
	}
}

void ShArcExtensionPointFinder::visit(ShCircle *circle) {

	ShArcData arcData = this->arcToExtend->getData();

	ShPoint3d intersect, intersect2;
	if (math::checkTwoCirclesIntersect(arcData.center, arcData.radius, circle->getCenter(), circle->getRadius(),
		intersect, intersect2) == false)
		return;

	ShPoint3d finalIntersect;
	if (this->checkPossibleToExtend(this->arcToExtend, this->entityPartToExtend, intersect, intersect2,
		finalIntersect) == true)
		this->extensionPointList.append(finalIntersect);
}

void ShArcExtensionPointFinder::visit(ShArc *arc) {

	ShArcData arcData = this->arcToExtend->getData();

	ShPoint3d intersect, intersect2;
	if (math::checkTwoCirclesIntersect(arcData.center, arcData.radius, arc->getCenter(), arc->getRadius(),
		intersect, intersect2) == false)
		return;

	bool insideIntersect = false;
	bool insideIntersect2 = false;

	if (math::checkPointLiesOnArcBoundary(intersect, arc->getCenter(), arc->getRadius(),
		arc->getStartAngle(), arc->getEndAngle(), 0.001) == true)
		insideIntersect = true;

	if (math::checkPointLiesOnArcBoundary(intersect2, arc->getCenter(), arc->getRadius(),
		arc->getStartAngle(), arc->getEndAngle(), 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false) {
		if (this->checkPossibleToExtend(this->arcToExtend, this->entityPartToExtend, intersect) == true)
			this->extensionPointList.append(intersect);
	}
	else if (insideIntersect == false && insideIntersect2 == true) {
		if (this->checkPossibleToExtend(this->arcToExtend, this->entityPartToExtend, intersect2) == true)
			this->extensionPointList.append(intersect2);
	}
	else if (insideIntersect == true && insideIntersect2 == true) {
		ShPoint3d finalIntersect;
		if (this->checkPossibleToExtend(this->arcToExtend, this->entityPartToExtend, intersect, intersect2,
			finalIntersect) == true)
			this->extensionPointList.append(finalIntersect);
	}
}

bool ShArcExtensionPointFinder::checkPossibleToExtend(ShArc *arcToExtend, ShEntityPartToExtend entityPartToExtend, const ShPoint3d &extensionPoint) {

	ShArcData data = arcToExtend->getData();

	if (math::checkPointLiesOnArcBoundary(extensionPoint, data.center, data.radius,
		data.startAngle, data.endAngle, 0.001) == true)
		return false;

	if (entityPartToExtend == ShEntityPartToExtend::Start) {
		ShPoint3d start = arcToExtend->getStart();
		if (math::compare(start.x, extensionPoint.x) != 0 ||
			math::compare(start.y, extensionPoint.y) != 0)
			return true;
	}
	else if (entityPartToExtend == ShEntityPartToExtend::End) {
		ShPoint3d end = arcToExtend->getEnd();
		if (math::compare(end.x, extensionPoint.x) != 0 ||
			math::compare(end.y, extensionPoint.y) != 0)
			return true;
	}

	return false;
}

bool ShArcExtensionPointFinder::checkPossibleToExtend(ShArc *arcToExtend, ShEntityPartToExtend entityPartToExtend,
	const ShPoint3d &extensionPoint, const ShPoint3d &extensionPoint2, ShPoint3d &finalExtensionPoint) {

	ShArcData data = arcToExtend->getData();

	bool insideIntersect = false;
	bool insideIntersect2 = false;

	if (math::checkPointLiesOnArcBoundary(extensionPoint, data.center, data.radius,
		data.startAngle, data.endAngle, 0.001) == true)
		insideIntersect = true;
	if (math::checkPointLiesOnArcBoundary(extensionPoint2, data.center, data.radius,
		data.startAngle, data.endAngle, 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == true && insideIntersect2 == true)
		return false;

	bool validExtension = false;

	if (insideIntersect == false && insideIntersect2 == true) {
		finalExtensionPoint = extensionPoint;
		validExtension = true;
	}
	else if (insideIntersect == true && insideIntersect2 == false) {
		finalExtensionPoint = extensionPoint2;
		validExtension = true;
	}
	else if (insideIntersect == false && insideIntersect2 == false) {

		double angleCenterToStart = math::getAbsAngle(data.center.x, data.center.y,
			arcToExtend->getStart().x, arcToExtend->getStart().y);
		double angleCenterToIntersect = math::getAbsAngle(data.center.x, data.center.y,
			extensionPoint.x, extensionPoint.y);
		double angleCenterToIntersect2 = math::getAbsAngle(data.center.x, data.center.y,
			extensionPoint2.x, extensionPoint2.y);
		double angleCenterToEnd = math::getAbsAngle(data.center.x, data.center.y,
			arcToExtend->getEnd().x, arcToExtend->getEnd().y);


		if (entityPartToExtend == ShEntityPartToExtend::Start) {

			double difference = math::getAngleDifference(angleCenterToStart, angleCenterToIntersect, false);
			double difference2 = math::getAngleDifference(angleCenterToStart, angleCenterToIntersect2, false);

			if (math::compare(difference, difference2) == 1)
				finalExtensionPoint = extensionPoint2;
			else
				finalExtensionPoint = extensionPoint;

			validExtension = true;
		}
		else if (entityPartToExtend == ShEntityPartToExtend::End) {

			double difference = math::getAngleDifference(angleCenterToEnd, angleCenterToIntersect);
			double difference2 = math::getAngleDifference(angleCenterToEnd, angleCenterToIntersect2);

			if (math::compare(difference, difference2) == 1)
				finalExtensionPoint = extensionPoint2;
			else
				finalExtensionPoint = extensionPoint;

			validExtension = true;
		}

	}

	if (validExtension == false)
		return false;

	if (entityPartToExtend == ShEntityPartToExtend::Start) {
		ShPoint3d start = arcToExtend->getStart();
		if (math::compare(start.x, finalExtensionPoint.x) != 0 ||
			math::compare(start.y, finalExtensionPoint.y) != 0)
			return true;
	}
	else if (entityPartToExtend == ShEntityPartToExtend::End) {
		ShPoint3d end = arcToExtend->getEnd();
		if (math::compare(end.x, finalExtensionPoint.x) != 0 ||
			math::compare(end.y, finalExtensionPoint.y) != 0)
			return true;
	}

	return false;
}
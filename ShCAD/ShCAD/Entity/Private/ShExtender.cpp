
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


}


/////////////////////////////////////////////////////////

ShExtensionPointFinder::ShExtensionPointFinder(QLinkedList<ShPoint3d> &extensionPointList)
	:extensionPointList(extensionPointList) {

}

ShExtensionPointFinder::~ShExtensionPointFinder() {

}

////////////////////////////////////////////////////////


ShLineExtensionPointFinder::ShLineExtensionPointFinder(QLinkedList<ShPoint3d> &extensionPointList, const ShLine *const lineToExtend, ShEntityPartToExtend entityPartToExtend)
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

}

void ShLineExtensionPointFinder::visit(ShArc *arc) {

}

bool ShLineExtensionPointFinder::checkPossibleToExtend(const ShLine *const lineToExtend, ShEntityPartToExtend entityPartToExtend, const ShPoint3d &extensionPoint) {

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

bool ShLineExtensionPointFinder::checkPossibleToExtend(const ShLine *const lineToExtend, ShEntityPartToExtend entityPartToExtend,
	const ShPoint3d &extensionPoint, const ShPoint3d &extensionPoint2, ShPoint3d &finalExtensionPoint) {

	return false;
}


////////////////////////////////////////////////////////////////////////////


ShArcExtensionPointFinder::ShArcExtensionPointFinder(QLinkedList<ShPoint3d> &extensionPointList, const ShArc *const arcToExtend, ShEntityPartToExtend entityPartToExtend)
	:ShExtensionPointFinder(extensionPointList), arcToExtend(arcToExtend), entityPartToExtend(entityPartToExtend) {

}

ShArcExtensionPointFinder::~ShArcExtensionPointFinder() {

}

void ShArcExtensionPointFinder::visit(ShLine *line) {

}

void ShArcExtensionPointFinder::visit(ShCircle *circle) {

}

void ShArcExtensionPointFinder::visit(ShArc *arc) {

}

bool ShArcExtensionPointFinder::checkPossibleToExtend(const ShArc *const arcToExtend, ShEntityPartToExtend entityPartToExtend, const ShPoint3d &extensionPoint) {

	return false;
}

bool ShArcExtensionPointFinder::checkPossibleToExtend(const ShArc *const arcToExtend, ShEntityPartToExtend entityPartToExtend,
	const ShPoint3d &extensionPoint, const ShPoint3d &extensionPoint2, ShPoint3d &finalExtensionPoint) {

	return false;
}
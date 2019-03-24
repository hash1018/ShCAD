

#include "ShTrimer.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Composite\ShPolyLine.h"
#include "ShMath.h"
#include "Interface\ShGraphicView.h"
ShTrimer::ShTrimer(ShGraphicView *view, const QLinkedList<ShEntity*>& baseEntities, const ShPoint3d& clickPoint)
	:view(view), baseEntities(baseEntities), clickPoint(clickPoint) {

}

ShTrimer::~ShTrimer() {

}

#include "Command Pattern\Entity Command\ShTrimEntityCommand.h"
void ShTrimer::CreateCommand(ShEntity *original, ShEntity *trimedEntity, ShEntity *trimedEntity2) {

	ShTrimEntityCommand *command = new ShTrimEntityCommand(this->view, original, trimedEntity, trimedEntity2);

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}

ShPoint3d ShTrimer::GetClosestPointByDistance(const ShPoint3d& clickPoint, const QLinkedList<ShPoint3d>& trimPointList) {

	QLinkedList<ShPoint3d>::iterator trimItr = const_cast<QLinkedList<ShPoint3d>&>(trimPointList).begin();
	ShPoint3d closest = (*trimItr);
	++trimItr;
	double disToTrim;
	double disToClosest = Math::GetDistance(clickPoint.x, clickPoint.y,
		closest.x, closest.y);


	while (trimItr != const_cast<QLinkedList<ShPoint3d>&>(trimPointList).end()) {

		disToTrim = Math::GetDistance(clickPoint.x, clickPoint.y,
			(*trimItr).x, (*trimItr).y);

		if (Math::Compare(disToClosest, disToTrim) == 1) {
			closest = (*trimItr);
			disToClosest = disToTrim;
		}

		++trimItr;
	}

	return closest;
}

ShPoint3d ShTrimer::GetClosestPointByAngle(const ShPoint3d& clickPoint, const ShPoint3d& center,
	const QLinkedList<ShPoint3d>& trimPointList, bool antiClockWise) {

	double angleToClick = Math::GetAbsAngle(center.x, center.y, clickPoint.x, clickPoint.y);

	QLinkedList<ShPoint3d>::iterator trimItr = const_cast<QLinkedList<ShPoint3d>&>(trimPointList).begin();
	ShPoint3d closest = (*trimItr);
	++trimItr;

	double angleToClosest = Math::GetAbsAngle(center.x, center.y, closest.x, closest.y);
	double differenceAngleClickToClosest, differenceAngleClickToTrim;
	
	if (antiClockWise == true)
		differenceAngleClickToClosest = Math::GetAngleDifference(angleToClick, angleToClosest);
	else
		differenceAngleClickToClosest = Math::GetAngleDifference(angleToClick, angleToClosest, false);


	while (trimItr != const_cast<QLinkedList<ShPoint3d>&>(trimPointList).end()) {

		double angleToTrim = Math::GetAbsAngle(center.x, center.y, (*trimItr).x, (*trimItr).y);

		if (antiClockWise == true)
			differenceAngleClickToTrim = Math::GetAngleDifference(angleToClick, angleToTrim);
		else
			differenceAngleClickToTrim = Math::GetAngleDifference(angleToClick, angleToTrim, false);

		if (Math::Compare(differenceAngleClickToClosest, differenceAngleClickToTrim) == 1) {
			closest = (*trimItr);
			differenceAngleClickToClosest = differenceAngleClickToTrim;
		}
		++trimItr;
	}

	return closest;
}

void ShTrimer::Visit(ShLine *line) {

	QLinkedList<ShPoint3d> betweenStartAndClickTrimPointList;
	QLinkedList<ShPoint3d> betweenEndAndClickTrimPointList;

	ShFindTrimPointLineTrimer visitor(line, this->clickPoint, betweenStartAndClickTrimPointList,
		betweenEndAndClickTrimPointList);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->baseEntities.begin(); itr != this->baseEntities.end(); ++itr)
		(*itr)->Accept(&visitor);

	if (betweenStartAndClickTrimPointList.count() == 0 &&
		betweenEndAndClickTrimPointList.count() == 0)
		return;

	ShPoint3d trimPoint, trimPoint2;
	ShLine *trimedLine;
	if (betweenStartAndClickTrimPointList.count() != 0 &&
		betweenEndAndClickTrimPointList.count() == 0) {

		trimPoint = this->GetClosestPointByDistance(this->clickPoint, betweenStartAndClickTrimPointList);
		trimedLine = line->Clone();
		trimedLine->SetEnd(trimPoint);
		this->view->entityTable.Remove(line);
		this->view->entityTable.Add(trimedLine);
		this->CreateCommand(line, trimedLine);
		
	}
	else if (betweenStartAndClickTrimPointList.count() == 0 &&
		betweenEndAndClickTrimPointList.count() != 0) {
	
		trimPoint = this->GetClosestPointByDistance(this->clickPoint, betweenEndAndClickTrimPointList);
		trimedLine = line->Clone();
		trimedLine->SetStart(trimPoint);
		this->view->entityTable.Remove(line);
		this->view->entityTable.Add(trimedLine);
		this->CreateCommand(line, trimedLine);
	}
	else if (betweenStartAndClickTrimPointList.count() != 0 &&
		betweenEndAndClickTrimPointList.count() != 0) {
		
		trimPoint = this->GetClosestPointByDistance(this->clickPoint, betweenStartAndClickTrimPointList);
		trimPoint2 = this->GetClosestPointByDistance(this->clickPoint, betweenEndAndClickTrimPointList);
	
		trimedLine = line->Clone();
		ShLine *trimedLine2 = line->Clone();
		trimedLine->SetEnd(trimPoint);
		trimedLine2->SetStart(trimPoint2);

		this->view->entityTable.Remove(line);
		this->view->entityTable.Add(trimedLine);
		this->view->entityTable.Add(trimedLine2);
		this->CreateCommand(line, trimedLine, trimedLine2);

	}

	this->view->update((DrawType)(DrawType::DrawAll));
	this->view->CaptureImage();
}

void ShTrimer::Visit(ShCircle *circle) {

	QLinkedList<ShPoint3d> clockWiseTrimPointList;
	QLinkedList<ShPoint3d> antiClockWiseTrimPointList;

	ShFindTrimPointCircleTrimer visitor(circle, this->clickPoint, clockWiseTrimPointList, antiClockWiseTrimPointList);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->baseEntities.begin(); itr != this->baseEntities.end(); ++itr)
		(*itr)->Accept(&visitor);

	qDebug("clock count %d   anti count %d", clockWiseTrimPointList.count(), antiClockWiseTrimPointList.count());

	if (clockWiseTrimPointList.count() == 0 && antiClockWiseTrimPointList.count() == 0)
		return;

	ShPoint3d trimPoint, trimPoint2;

	if (clockWiseTrimPointList.count() >= 2 && antiClockWiseTrimPointList.count() == 0) {
		trimPoint = this->GetClosestPointByAngle(this->clickPoint, circle->GetCenter(), clockWiseTrimPointList, false);
		trimPoint2 = this->GetClosestPointByAngle(this->clickPoint, circle->GetCenter(), clockWiseTrimPointList);
	}
	else if (clockWiseTrimPointList.count() == 0 && antiClockWiseTrimPointList.count() >= 2) {
		trimPoint = this->GetClosestPointByAngle(this->clickPoint, circle->GetCenter(), antiClockWiseTrimPointList, false);
		trimPoint2 = this->GetClosestPointByAngle(this->clickPoint, circle->GetCenter(), antiClockWiseTrimPointList);
	}
	else {
		trimPoint = this->GetClosestPointByAngle(this->clickPoint, circle->GetCenter(), clockWiseTrimPointList, false);
		trimPoint2 = this->GetClosestPointByAngle(this->clickPoint, circle->GetCenter(), antiClockWiseTrimPointList);
	}

	double startAngle = Math::GetAbsAngle(circle->GetCenter().x, circle->GetCenter().y, trimPoint2.x, trimPoint2.y);
	double endAngle = Math::GetAbsAngle(circle->GetCenter().x, circle->GetCenter().y, trimPoint.x, trimPoint.y);

	ShArcData data = ShArcData(circle->GetCenter(), circle->GetRadius(), startAngle, endAngle);
	ShArc *trimedArc = new ShArc(circle->GetPropertyData(), data, circle->GetLayer());

	this->view->entityTable.Remove(circle);
	this->view->entityTable.Add(trimedArc);
	this->CreateCommand(circle, trimedArc);
	
	this->view->update((DrawType)(DrawType::DrawAll));
	this->view->CaptureImage();

}

void ShTrimer::Visit(ShArc *arc) {

	QLinkedList<ShPoint3d> clockWiseTrimPointList;
	QLinkedList<ShPoint3d> antiClockWiseTrimPointList;

	ShFindTrimPointArcTrimer visitor(arc, this->clickPoint, clockWiseTrimPointList, antiClockWiseTrimPointList);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->baseEntities.begin(); itr != this->baseEntities.end(); ++itr)
		(*itr)->Accept(&visitor);

	if (clockWiseTrimPointList.count() == 0 && antiClockWiseTrimPointList.count() == 0)
		return;

	if (clockWiseTrimPointList.count() != 0 && antiClockWiseTrimPointList.count() == 0) {
	
		ShPoint3d trimPoint = this->GetClosestPointByAngle(this->clickPoint, arc->GetCenter(), clockWiseTrimPointList, false);
		
		double angle = Math::GetAbsAngle(arc->GetCenter().x, arc->GetCenter().y, trimPoint.x, trimPoint.y);

		ShArc *trimedArc = arc->Clone();
		trimedArc->SetEndAngle(angle);

		this->view->entityTable.Remove(arc);
		this->view->entityTable.Add(trimedArc);

		this->CreateCommand(arc, trimedArc);
	}
	else if (clockWiseTrimPointList.count() == 0 && antiClockWiseTrimPointList.count() != 0) {

		ShPoint3d trimPoint = this->GetClosestPointByAngle(this->clickPoint, arc->GetCenter(), antiClockWiseTrimPointList);

		double angle = Math::GetAbsAngle(arc->GetCenter().x, arc->GetCenter().y, trimPoint.x, trimPoint.y);

		ShArc *trimedArc = arc->Clone();
		trimedArc->SetStartAngle(angle);

		this->view->entityTable.Remove(arc);
		this->view->entityTable.Add(trimedArc);

		this->CreateCommand(arc, trimedArc);
	}
	else if (clockWiseTrimPointList.count() != 0 && antiClockWiseTrimPointList.count() != 0) {
		qDebug("clock count %d    anti count %d", clockWiseTrimPointList.count(), antiClockWiseTrimPointList.count());
		ShPoint3d trimPoint = this->GetClosestPointByAngle(this->clickPoint, arc->GetCenter(), clockWiseTrimPointList, false);
		ShPoint3d trimPoint2 = this->GetClosestPointByAngle(this->clickPoint, arc->GetCenter(), antiClockWiseTrimPointList);

		double angle = Math::GetAbsAngle(arc->GetCenter().x, arc->GetCenter().y, trimPoint.x, trimPoint.y);
		double angle2 = Math::GetAbsAngle(arc->GetCenter().x, arc->GetCenter().y, trimPoint2.x, trimPoint2.y);

		ShArc *trimedArc = arc->Clone();
		ShArc *trimedArc2 = arc->Clone();

		trimedArc->SetEndAngle(angle);
		trimedArc2->SetStartAngle(angle2);

		this->view->entityTable.Remove(arc);
		this->view->entityTable.Add(trimedArc);
		this->view->entityTable.Add(trimedArc2);

		this->CreateCommand(arc, trimedArc, trimedArc2);
	}

	this->view->update((DrawType)(DrawType::DrawAll));
	this->view->CaptureImage();
}



///////////////////////////////////////////////////////////////////////////////////////////////


#include "ShFootOfPerpendicularVisitor.h"
ShFindTrimPointLineTrimer::ShFindTrimPointLineTrimer(ShLine *lineToTrim, const ShPoint3d& clickPoint,
	QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
	QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList)
	:lineToTrim(lineToTrim), clickPoint(clickPoint), 
	betweenStartAndClickTrimPointList(betweenStartAndClickTrimPointList),
	betweenEndAndClickTrimPointList(betweenEndAndClickTrimPointList) {


}

ShFindTrimPointLineTrimer::~ShFindTrimPointLineTrimer() {

}

void ShFindTrimPointLineTrimer::OneIntersectLiesOnBaseEntity(ShLine *lineToTrim, const ShPoint3d& clickPoint,
	const ShPoint3d& intersect,
	QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
	QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList) {

	ShLineData data = lineToTrim->GetData();

	if (Math::CheckPointLiesOnLine(intersect, data.start, data.end, 0.001) == false)
		return;

	this->OneIntersectLiesOnLineToTrim(lineToTrim, clickPoint, intersect,
		betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);

}

void ShFindTrimPointLineTrimer::TwoIntersectsLieOnBaseEntity(ShLine *lineToTrim, const ShPoint3d& clickPoint,
	const ShPoint3d& intersect, const ShPoint3d& intersect2,
	QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
	QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList) {

	ShLineData data = lineToTrim->GetData();

	bool insideIntersect = false, insideIntersect2 = false;
	if (Math::CheckPointLiesOnLine(intersect, data.start, data.end, 0.001) == true)
		insideIntersect = true;
	if (Math::CheckPointLiesOnLine(intersect2, data.start, data.end, 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false)
		this->OneIntersectLiesOnLineToTrim(lineToTrim, clickPoint, intersect,
			betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);

	else if (insideIntersect == false && insideIntersect2 == true)
		this->OneIntersectLiesOnLineToTrim(lineToTrim, clickPoint, intersect2,
			betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);

	else if (insideIntersect == true && insideIntersect2 == true)
		this->TwoIntersectsLieOnLineToTrim(lineToTrim, clickPoint, intersect, intersect2, 
			betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);

}

void ShFindTrimPointLineTrimer::OneIntersectLiesOnLineToTrim(ShLine *lineToTrim, const ShPoint3d& clickPoint, const ShPoint3d& intersect,
	QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
	QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList) {

	ShLineData data = lineToTrim->GetData();

	if (Math::Compare(data.start.x, intersect.x) == 0 &&
		Math::Compare(data.start.y, intersect.y) == 0)
		return;

	if (Math::Compare(data.end.x, intersect.x) == 0 &&
		Math::Compare(data.end.y, intersect.y) == 0)
		return;


	ShPoint3d clickP;
	ShFootOfPerpendicularVisitor visitor(clickP.x, clickP.y, clickPoint);
	this->lineToTrim->Accept(&visitor);

	double angleClickToStart = Math::GetAbsAngle(clickP.x, clickP.y, data.start.x, data.start.y);
	double angleClickToEnd = Math::GetAbsAngle(clickP.x, clickP.y, data.end.x, data.end.y);
	double angleClickToTrimPoint = Math::GetAbsAngle(clickP.x, clickP.y, intersect.x, intersect.y);

	if (Math::Compare(angleClickToStart, angleClickToTrimPoint) == 0)
		betweenStartAndClickTrimPointList.append(intersect);
	else
		betweenEndAndClickTrimPointList.append(intersect);
}

void ShFindTrimPointLineTrimer::TwoIntersectsLieOnLineToTrim(ShLine *lineToTrim, const ShPoint3d& clickPoint, const ShPoint3d& intersect,
	const ShPoint3d& intersect2, QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
	QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList) {

	ShLineData data = lineToTrim->GetData();

	bool sameStartIntersect = false, sameStartIntersect2 = false,
		sameEndIntersect = false, sameEndIntersect2 = false;

	if (Math::Compare(data.start.x, intersect.x) == 0 &&
		Math::Compare(data.start.y, intersect.y) == 0)
		sameStartIntersect = true;
	if (Math::Compare(data.start.x, intersect2.x) == 0 &&
		Math::Compare(data.start.y, intersect2.y) == 0)
		sameStartIntersect2 = true;
	if (Math::Compare(data.end.x, intersect.x) == 0 &&
		Math::Compare(data.end.y, intersect.y) == 0)
		sameEndIntersect = true;
	if (Math::Compare(data.end.x, intersect2.x) == 0 &&
		Math::Compare(data.end.y, intersect2.y) == 0)
		sameEndIntersect2 = true;

	if (sameStartIntersect == true && sameEndIntersect2 == true)
		return;

	else if (sameStartIntersect2 == true && sameEndIntersect == true)
		return;

	else if (sameStartIntersect == true && sameEndIntersect2 == false)
		this->OneIntersectLiesOnLineToTrim(lineToTrim, clickPoint, intersect2,
			betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);

	else if (sameStartIntersect == false && sameEndIntersect2 == true)
		this->OneIntersectLiesOnLineToTrim(lineToTrim, clickPoint, intersect,
			betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);

	else if (sameStartIntersect2 == true && sameEndIntersect == false)
		this->OneIntersectLiesOnLineToTrim(lineToTrim, clickPoint, intersect,
			betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);

	else if (sameStartIntersect2 == false && sameEndIntersect == true)
		this->OneIntersectLiesOnLineToTrim(lineToTrim, clickPoint, intersect2, 
			betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);

	else if ((sameStartIntersect == false && sameEndIntersect2 == false) ||
		sameStartIntersect2 == false && sameEndIntersect == false) {
	

		ShPoint3d clickP;
		ShFootOfPerpendicularVisitor visitor(clickP.x, clickP.y, clickPoint);
		this->lineToTrim->Accept(&visitor);

		double angleClickToStart = Math::GetAbsAngle(clickP.x, clickP.y, data.start.x, data.start.y);
		double angleClickToEnd = Math::GetAbsAngle(clickP.x, clickP.y, data.end.x, data.end.y);
		double angleClickToTrimPoint = Math::GetAbsAngle(clickP.x, clickP.y, intersect.x, intersect.y);
		double angleClickToTrimPoint2 = Math::GetAbsAngle(clickP.x, clickP.y, intersect2.x, intersect2.y);

		if (Math::Compare(angleClickToTrimPoint, angleClickToTrimPoint2) == 0) {
			double disClickToTrimPoint = Math::GetDistance(clickP.x, clickP.y, intersect.x, intersect.y);
			double disClickToTrimPoint2 = Math::GetDistance(clickP.x, clickP.y, intersect2.x, intersect2.y);

			ShPoint3d closest;
			if (Math::Compare(disClickToTrimPoint, disClickToTrimPoint2) == 1)
				closest = intersect2;
			else
				closest = intersect;

			if (Math::Compare(angleClickToStart, angleClickToTrimPoint) == 0)
				betweenStartAndClickTrimPointList.append(closest);
			else
				betweenEndAndClickTrimPointList.append(closest);

		}
		else {
			if (Math::Compare(angleClickToStart, angleClickToTrimPoint) == 0) {
				betweenStartAndClickTrimPointList.append(intersect);
				betweenEndAndClickTrimPointList.append(intersect2);
			}
			else {
				betweenStartAndClickTrimPointList.append(intersect2);
				betweenEndAndClickTrimPointList.append(intersect);
			}
		}
	}

}

void ShFindTrimPointLineTrimer::Visit(ShLine *line) {

	ShLineData data = this->lineToTrim->GetData();
	ShPoint3d intersect;
	if (Math::CheckTwoLineSegmentsIntersect(data.start, data.end,
		line->GetStart(), line->GetEnd(), intersect) == false)
		return;

	this->OneIntersectLiesOnBaseEntity(this->lineToTrim, this->clickPoint, intersect,
		this->betweenStartAndClickTrimPointList, this->betweenEndAndClickTrimPointList);
}

void ShFindTrimPointLineTrimer::Visit(ShCircle *circle) {

	ShLineData data = this->lineToTrim->GetData();
	ShPoint3d intersect, intersect2;
	if (Math::CheckCircleLineIntersect(circle->GetCenter(), circle->GetRadius(), data.start, data.end,
		intersect, intersect2) == false)
		return;

	this->TwoIntersectsLieOnBaseEntity(this->lineToTrim, this->clickPoint, intersect, intersect2,
		this->betweenStartAndClickTrimPointList, this->betweenEndAndClickTrimPointList);

	
}

void ShFindTrimPointLineTrimer::Visit(ShArc *arc) {

	ShLineData data = this->lineToTrim->GetData();
	ShPoint3d intersect, intersect2;
	if (Math::CheckCircleLineIntersect(arc->GetCenter(), arc->GetRadius(), data.start, data.end,
		intersect, intersect2) == false)
		return;

	bool insideIntersect = false, insideIntersect2 = false;
	if (Math::CheckPointLiesOnArcBoundary(intersect, arc->GetCenter(), arc->GetRadius(),
		arc->GetStartAngle(), arc->GetEndAngle(), 0.001) == true)
		insideIntersect = true;
	if (Math::CheckPointLiesOnArcBoundary(intersect2, arc->GetCenter(), arc->GetRadius(),
		arc->GetStartAngle(), arc->GetEndAngle(), 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false) {
		this->OneIntersectLiesOnBaseEntity(this->lineToTrim, this->clickPoint, intersect,
			this->betweenStartAndClickTrimPointList, this->betweenEndAndClickTrimPointList);
	}
	else if (insideIntersect == false && insideIntersect2 == true) {
		this->OneIntersectLiesOnBaseEntity(this->lineToTrim, this->clickPoint, intersect2,
			this->betweenStartAndClickTrimPointList, this->betweenEndAndClickTrimPointList);
	}
	else if (insideIntersect == true && insideIntersect2 == true) {
		this->TwoIntersectsLieOnBaseEntity(this->lineToTrim, this->clickPoint, intersect, intersect2,
			this->betweenStartAndClickTrimPointList, this->betweenEndAndClickTrimPointList);
	}

}

void ShFindTrimPointLineTrimer::Visit(ShPolyLine *polyLine) {

	ShFindTrimPointLineTrimer visitor(this->lineToTrim, this->clickPoint, 
		this->betweenStartAndClickTrimPointList, this->betweenEndAndClickTrimPointList);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = polyLine->Begin(); itr != polyLine->End(); ++itr)
		(*itr)->Accept(&visitor);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////


ShFindTrimPointCircleTrimer::ShFindTrimPointCircleTrimer(ShCircle *circleToTrim, const ShPoint3d& clickPoint,
	QLinkedList<ShPoint3d> &clockWiseTrimPointList,
	QLinkedList<ShPoint3d> &antiClockWiseTrimPointList)
	:circleToTrim(circleToTrim), clickPoint(clickPoint), clockWiseTrimPointList(clockWiseTrimPointList), 
	antiClockWiseTrimPointList(antiClockWiseTrimPointList) {

}

ShFindTrimPointCircleTrimer::~ShFindTrimPointCircleTrimer() {

}

void ShFindTrimPointCircleTrimer::OneIntersecLiesOnBaseEntity(ShCircle *circleToTrim, const ShPoint3d& clickPoint,
	const ShPoint3d& intersect,
	QLinkedList<ShPoint3d> &clockWiseTrimPointList,
	QLinkedList<ShPoint3d> &antiClockWiseTrimPointList) {

	ShCircleData data = circleToTrim->GetData();

	double angleCenterToClick = Math::GetAbsAngle(data.center.x, data.center.y, clickPoint.x, clickPoint.y);
	double angleCenterToIntersect = Math::GetAbsAngle(data.center.x, data.center.y, intersect.x, intersect.y);


	double difference = Math::GetAngleDifference(angleCenterToClick, angleCenterToIntersect);

	if (Math::Compare(difference, 180) == 1) {
		clockWiseTrimPointList.append(intersect);
	}
	else {
		antiClockWiseTrimPointList.append(intersect);
	}

}

void ShFindTrimPointCircleTrimer::TwoIntersectsLieOnBaseEntity(ShCircle *circleToTrim, const ShPoint3d& clickPoint,
	const ShPoint3d& intersect, const ShPoint3d& intersect2,
	QLinkedList<ShPoint3d> &clockWiseTrimPointList,
	QLinkedList<ShPoint3d> &antiClockWiseTrimPointList) {

	ShCircleData data = circleToTrim->GetData();

	double angleCenterToClick = Math::GetAbsAngle(data.center.x, data.center.y, clickPoint.x, clickPoint.y);
	double angleCenterToIntersect = Math::GetAbsAngle(data.center.x, data.center.y, intersect.x, intersect.y);
	double angleCenterToIntersect2 = Math::GetAbsAngle(data.center.x, data.center.y, intersect2.x, intersect2.y);

	double difference = Math::GetAngleDifference(angleCenterToClick, angleCenterToIntersect);
	double difference2 = Math::GetAngleDifference(angleCenterToClick, angleCenterToIntersect2);

	if (Math::Compare(difference, difference2) == 1) {
		antiClockWiseTrimPointList.append(intersect2);
		clockWiseTrimPointList.append(intersect);
	}
	else {
		antiClockWiseTrimPointList.append(intersect);
		clockWiseTrimPointList.append(intersect2);
	}
}

void ShFindTrimPointCircleTrimer::Visit(ShLine *line) {

	ShCircleData data = this->circleToTrim->GetData();
	ShPoint3d intersect, intersect2;
	if (Math::CheckCircleLineIntersect(data.center, data.radius,
		line->GetStart(), line->GetEnd(), intersect, intersect2) == false)
		return;

	bool insideIntersect = false, insideIntersect2 = false;
	if (Math::CheckPointLiesOnLine(intersect, line->GetStart(), line->GetEnd(), 0.001) == true)
		insideIntersect = true;
	if (Math::CheckPointLiesOnLine(intersect2, line->GetStart(), line->GetEnd(), 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false) {
		this->OneIntersecLiesOnBaseEntity(this->circleToTrim, this->clickPoint, intersect,
			this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);
	}
	else if (insideIntersect == false && insideIntersect2 == true) {
		this->OneIntersecLiesOnBaseEntity(this->circleToTrim, this->clickPoint, intersect2,
			this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);
	}
	else if (insideIntersect == true && insideIntersect2 == true) {
		this->TwoIntersectsLieOnBaseEntity(this->circleToTrim, this->clickPoint, intersect, intersect2,
			this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);
	}
}

void ShFindTrimPointCircleTrimer::Visit(ShCircle *circle) {

	ShCircleData data = this->circleToTrim->GetData();
	ShPoint3d intersect, intersect2;
	if (Math::CheckTwoCirclesIntersect(data.center, data.radius, circle->GetCenter(), circle->GetRadius(),
		intersect, intersect2) == false)
		return;

	this->TwoIntersectsLieOnBaseEntity(this->circleToTrim, this->clickPoint, intersect, intersect2,
		this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);

}

void ShFindTrimPointCircleTrimer::Visit(ShArc *arc) {

	ShPoint3d intersect, intersect2;
	if (Math::CheckTwoCirclesIntersect(this->circleToTrim->GetCenter(), this->circleToTrim->GetRadius(),
		arc->GetCenter(), arc->GetRadius(), intersect, intersect2) == false)
		return;

	bool insideIntersect = false, insideIntersect2 = false;
	if (Math::CheckPointLiesOnArcBoundary(intersect, arc->GetCenter(), arc->GetRadius(),
		arc->GetStartAngle(), arc->GetEndAngle(), 0.001) == true)
		insideIntersect = true;
	if (Math::CheckPointLiesOnArcBoundary(intersect2, arc->GetCenter(), arc->GetRadius(),
		arc->GetStartAngle(), arc->GetEndAngle(), 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false) {
		this->OneIntersecLiesOnBaseEntity(this->circleToTrim, this->clickPoint, intersect,
			this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);
	}
	else if (insideIntersect == false && insideIntersect2 == true) {
		this->OneIntersecLiesOnBaseEntity(this->circleToTrim, this->clickPoint, intersect2,
			this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);
	}
	else if (insideIntersect == true && insideIntersect2 == true) {
		this->TwoIntersectsLieOnBaseEntity(this->circleToTrim, this->clickPoint, intersect, intersect2,
			this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);
	}

}


void ShFindTrimPointCircleTrimer::Visit(ShPolyLine *polyLine) {

	ShFindTrimPointCircleTrimer visitor(this->circleToTrim, this->clickPoint,
		this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = polyLine->Begin(); itr != polyLine->End(); ++itr)
		(*itr)->Accept(&visitor);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

ShFindTrimPointArcTrimer::ShFindTrimPointArcTrimer(ShArc *arcToTrim, const ShPoint3d& clickPoint,
	QLinkedList<ShPoint3d> &clockWiseTrimPointList,
	QLinkedList<ShPoint3d> &antiClockWiseTrimPointList)
	:arcToTrim(arcToTrim), clickPoint(clickPoint), clockWiseTrimPointList(clockWiseTrimPointList), 
	antiClockWiseTrimPointList(antiClockWiseTrimPointList) {

}

ShFindTrimPointArcTrimer::~ShFindTrimPointArcTrimer() {

}

void ShFindTrimPointArcTrimer::OneIntersectLiesOnBaseEntity(ShArc *arcToTrim, const ShPoint3d& clickPoint,
	const ShPoint3d& intersect,
	QLinkedList<ShPoint3d> &clockWiseTrimPointList,
	QLinkedList<ShPoint3d> &antiClockWiseTrimPointList) {

	ShArcData data = arcToTrim->GetData();
	if (Math::CheckPointLiesOnArcBoundary(intersect, data.center, data.radius,
		data.startAngle, data.endAngle, 0.001) == false)
		return;

	this->OneIntersectLiesOnArcToTrim(arcToTrim, clickPoint, intersect,
		clockWiseTrimPointList, antiClockWiseTrimPointList);

}

void ShFindTrimPointArcTrimer::TwoIntersectsLieOnBaseEntity(ShArc *arcToTrim, const ShPoint3d& clickPoint,
	const ShPoint3d& intersect, const ShPoint3d& intersect2,
	QLinkedList<ShPoint3d> &clockWiseTrimPointList,
	QLinkedList<ShPoint3d> &antiClockWiseTrimPointList) {

	ShArcData data = arcToTrim->GetData();
	
	bool insideIntersect = false, insideIntersect2 = false;
	if (Math::CheckPointLiesOnArcBoundary(intersect, data.center, data.radius, 
		data.startAngle, data.endAngle, 0.001) == true)
		insideIntersect = true;
	if (Math::CheckPointLiesOnArcBoundary(intersect2, data.center, data.radius,
		data.startAngle, data.endAngle, 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false)
		this->OneIntersectLiesOnArcToTrim(arcToTrim, clickPoint, intersect,
			clockWiseTrimPointList, antiClockWiseTrimPointList);

	else if (insideIntersect == false && insideIntersect2 == true)
		this->OneIntersectLiesOnArcToTrim(arcToTrim, clickPoint, intersect2,
			clockWiseTrimPointList, antiClockWiseTrimPointList);

	else if (insideIntersect == true && insideIntersect2 == true)
		this->TwoIntersectsLieOnArcToTrim(arcToTrim, clickPoint, intersect, intersect2,
			clockWiseTrimPointList, antiClockWiseTrimPointList);

}

void ShFindTrimPointArcTrimer::OneIntersectLiesOnArcToTrim(ShArc *arcToTrim, const ShPoint3d& clickPoint,
	const ShPoint3d& intersect,
	QLinkedList<ShPoint3d> &clockWiseTrimPointList,
	QLinkedList<ShPoint3d> &antiClockWiseTrimPointList) {

	ShArcData data = arcToTrim->GetData();

	ShPoint3d start = arcToTrim->GetStart();
	if (Math::Compare(start.x, intersect.x) == 0 &&
		Math::Compare(start.y, intersect.y) == 0)
		return;

	ShPoint3d end = arcToTrim->GetEnd();
	if (Math::Compare(end.x, intersect.x) == 0 &&
		Math::Compare(end.y, intersect.y) == 0)
		return;

	double angleCenterToClick = Math::GetAbsAngle(data.center.x, data.center.y, clickPoint.x, clickPoint.y);
	double angleCenterToIntersect = Math::GetAbsAngle(data.center.x, data.center.y, intersect.x, intersect.y);


	double difference = Math::GetAngleDifference(angleCenterToClick, angleCenterToIntersect);

	if (Math::Compare(difference, 180) == 1) {
		clockWiseTrimPointList.append(intersect);
	}
	else {
		antiClockWiseTrimPointList.append(intersect);
	}
}

void ShFindTrimPointArcTrimer::TwoIntersectsLieOnArcToTrim(ShArc *arcToTrim, const ShPoint3d& clickPoint,
	const ShPoint3d& intersect, const ShPoint3d& intersect2,
	QLinkedList<ShPoint3d> &clockWiseTrimPointList,
	QLinkedList<ShPoint3d> &antiClockWiseTrimPointList) {

	ShArcData data = arcToTrim->GetData();
	ShPoint3d start = arcToTrim->GetStart();
	ShPoint3d end = arcToTrim->GetEnd();

	if (Math::Compare(start.x, intersect.x) == 0 &&
		Math::Compare(start.y, intersect.y) == 0) {
		this->OneIntersectLiesOnArcToTrim(arcToTrim, clickPoint, intersect2,
			clockWiseTrimPointList, antiClockWiseTrimPointList);
		return;
	}
	if (Math::Compare(end.x, intersect.x) == 0 &&
		Math::Compare(end.y, intersect.y) == 0) {
		this->OneIntersectLiesOnArcToTrim(arcToTrim, clickPoint, intersect2, 
			clockWiseTrimPointList, antiClockWiseTrimPointList);
		return;
	}
	if (Math::Compare(start.x, intersect2.x) == 0 &&
		Math::Compare(start.y, intersect2.y) == 0) {
		this->OneIntersectLiesOnArcToTrim(arcToTrim, clickPoint, intersect, 
			clockWiseTrimPointList, antiClockWiseTrimPointList);
		return;
	}
	if (Math::Compare(end.x, intersect2.x) == 0 &&
		Math::Compare(end.y, intersect2.y) == 0) {
		this->OneIntersectLiesOnArcToTrim(arcToTrim, clickPoint, intersect, 
			clockWiseTrimPointList, antiClockWiseTrimPointList);
		return;
	}

	double angleCenterToClick = Math::GetAbsAngle(data.center.x, data.center.y, clickPoint.x, clickPoint.y);
	double angleCenterIntersect = Math::GetAbsAngle(data.center.x, data.center.y, intersect.x, intersect.y);
	double angleCenterIntersect2 = Math::GetAbsAngle(data.center.x, data.center.y, intersect2.x, intersect2.y);

	double difference = Math::GetAngleDifference(angleCenterToClick, angleCenterIntersect);
	double difference2 = Math::GetAngleDifference(angleCenterToClick, angleCenterIntersect2);
	
	//this means in the antiClockWise, the intersect2 reaches first. 
	if (Math::Compare(difference, difference2) == 1) {

		//click point is between intersect and intersect2.
		if (Math::CheckAngleLiesOnAngleBetween(angleCenterIntersect, data.endAngle,
			angleCenterIntersect2) == true) {
			clockWiseTrimPointList.append(intersect);
			antiClockWiseTrimPointList.append(intersect2);
		}
		else if (Math::CheckAngleLiesOnAngleBetween(data.startAngle, angleCenterIntersect2,
			angleCenterToClick) == true) {
		
			this->OneIntersectLiesOnArcToTrim(arcToTrim, clickPoint, intersect2, clockWiseTrimPointList,
				antiClockWiseTrimPointList);
		}
		else if (Math::CheckAngleLiesOnAngleBetween(angleCenterIntersect, data.endAngle,
			angleCenterToClick) == true) {
		
			this->OneIntersectLiesOnArcToTrim(arcToTrim, clickPoint, intersect, clockWiseTrimPointList, 
				antiClockWiseTrimPointList);
		}
	}
	//this means in the antiClockWise, the intersect reaches first.
	else {
	
		if (Math::CheckAngleLiesOnAngleBetween(angleCenterIntersect2, data.endAngle,
			angleCenterIntersect) == true) {
			clockWiseTrimPointList.append(intersect2);
			antiClockWiseTrimPointList.append(intersect);
		}
		else if (Math::CheckAngleLiesOnAngleBetween(data.startAngle, angleCenterIntersect,
			angleCenterToClick) == true) {
		
			this->OneIntersectLiesOnArcToTrim(arcToTrim, clickPoint, intersect, clockWiseTrimPointList, 
				antiClockWiseTrimPointList);
		}
		else if (Math::CheckAngleLiesOnAngleBetween(angleCenterIntersect2, data.endAngle,
			angleCenterToClick) == true) {
		
			this->OneIntersectLiesOnArcToTrim(arcToTrim, clickPoint, intersect2, clockWiseTrimPointList,
				antiClockWiseTrimPointList);
		}
	}
}

void ShFindTrimPointArcTrimer::Visit(ShLine *line) {

	ShPoint3d intersect, intersect2;
	if (Math::CheckCircleLineIntersect(this->arcToTrim->GetCenter(), this->arcToTrim->GetRadius(),
		line->GetStart(), line->GetEnd(), intersect, intersect2) == false)
		return;

	bool insideIntersect = false, insideIntersect2 = false;
	if (Math::CheckPointLiesOnLine(intersect, line->GetStart(), line->GetEnd(), 0.001) == true)
		insideIntersect = true;
	if (Math::CheckPointLiesOnLine(intersect2, line->GetStart(), line->GetEnd(), 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false)
		this->OneIntersectLiesOnBaseEntity(this->arcToTrim, this->clickPoint, intersect,
			this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);

	else if (insideIntersect == false && insideIntersect2 == true)
		this->OneIntersectLiesOnBaseEntity(this->arcToTrim, this->clickPoint, intersect2,
			this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);

	else if (insideIntersect == true && insideIntersect2 == true)
		this->TwoIntersectsLieOnBaseEntity(this->arcToTrim, this->clickPoint, intersect, intersect2,
			this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);


}

void ShFindTrimPointArcTrimer::Visit(ShCircle *circle) {

	ShPoint3d intersect, intersect2;
	if (Math::CheckTwoCirclesIntersect(this->arcToTrim->GetCenter(), this->arcToTrim->GetRadius(),
		circle->GetCenter(), circle->GetRadius(), intersect, intersect2) == false)
		return;

	this->TwoIntersectsLieOnBaseEntity(this->arcToTrim, clickPoint, intersect, intersect2,
		this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);

}

void ShFindTrimPointArcTrimer::Visit(ShArc *arc) {

	ShPoint3d intersect, intersect2;
	if (Math::CheckTwoCirclesIntersect(this->arcToTrim->GetCenter(), this->arcToTrim->GetRadius(),
		arc->GetCenter(), arc->GetRadius(), intersect, intersect2) == false)
		return;

	bool insideIntersect = false, insideIntersect2 = false;
	if (Math::CheckPointLiesOnArcBoundary(intersect, arc->GetCenter(), arc->GetRadius(),
		arc->GetStartAngle(), arc->GetEndAngle(), 0.001) == true)
		insideIntersect = true;
	if (Math::CheckPointLiesOnArcBoundary(intersect2, arc->GetCenter(), arc->GetRadius(),
		arc->GetStartAngle(), arc->GetEndAngle(), 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false)
		this->OneIntersectLiesOnBaseEntity(this->arcToTrim, this->clickPoint, intersect,
			this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);

	else if (insideIntersect == false && insideIntersect2 == true)
		this->OneIntersectLiesOnBaseEntity(this->arcToTrim, this->clickPoint, intersect2,
			this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);

	else if (insideIntersect == true && insideIntersect2 == true)
		this->TwoIntersectsLieOnBaseEntity(this->arcToTrim, this->clickPoint, intersect, intersect2,
			this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);


}


void ShFindTrimPointArcTrimer::Visit(ShPolyLine *polyLine) {

	ShFindTrimPointArcTrimer visitor(this->arcToTrim, this->clickPoint,
		this->clockWiseTrimPointList, this->antiClockWiseTrimPointList);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = polyLine->Begin(); itr != polyLine->End(); ++itr)
		(*itr)->Accept(&visitor);

}
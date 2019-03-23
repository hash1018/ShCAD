

#include "ShTrimer.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
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

	while (trimItr != const_cast<QLinkedList<ShPoint3d>&>(trimPointList).end()) {

		double disToClosest = Math::GetDistance(clickPoint.x, clickPoint.y,
			closest.x, closest.y);
		double disToTrim = Math::GetDistance(clickPoint.x, clickPoint.y,
			(*trimItr).x, (*trimItr).y);

		if (Math::Compare(disToClosest, disToTrim) == 1)
			closest = (*trimItr);

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

}

void ShTrimer::Visit(ShArc *arc) {


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

	if (Math::Compare(data.start.x, intersect.x) == 0 &&
		Math::Compare(data.start.y, intersect.y) == 0)
		return;

	if (Math::Compare(data.end.x, intersect.x) == 0 &&
		Math::Compare(data.end.y, intersect.y) == 0)
		return;

	this->AppendTrimPointIntoProperList(lineToTrim, clickPoint, intersect, betweenStartAndClickTrimPointList,
		betweenEndAndClickTrimPointList);

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

	bool sameStartIntersect = false, sameEndIntersect2 = false,
		sameStartIntersect2 = false, sameEndIntersect = false;

	if (Math::Compare(data.start.x, intersect.x) == 0 &&
		Math::Compare(data.start.y, intersect.y) == 0)
		sameStartIntersect = true;

	if (Math::Compare(data.end.x, intersect2.x) == 0 &&
		Math::Compare(data.end.y, intersect2.y) == 0)
		sameEndIntersect2 = true;

	if (Math::Compare(data.end.x, intersect.x) == 0 &&
		Math::Compare(data.end.y, intersect.y) == 0)
		sameEndIntersect = true;

	if (Math::Compare(data.start.x, intersect2.x) == 0 &&
		Math::Compare(data.start.y, intersect2.y) == 0)
		sameStartIntersect2 = true;


	if (insideIntersect == true && insideIntersect2 == false) {

		if (sameStartIntersect == true || sameEndIntersect == true)
			return;

		this->AppendTrimPointIntoProperList(lineToTrim, clickPoint, intersect,
			betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);

	}
	else if (insideIntersect == false && insideIntersect2 == true) {

		if (sameStartIntersect2 == true || sameEndIntersect2 == true)
			return;

		this->AppendTrimPointIntoProperList(lineToTrim, clickPoint, intersect2,
			betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);
	}
	else if (insideIntersect == true && insideIntersect2 == true) {

		if (sameStartIntersect == true && sameEndIntersect2 == true)
			return;
		if (sameStartIntersect2 == true && sameEndIntersect == true)
			return;

		if (sameStartIntersect == true && sameEndIntersect2 == false) {
			this->AppendTrimPointIntoProperList(lineToTrim, clickPoint, intersect2,
				betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);
		}
		else if (sameStartIntersect == false && sameEndIntersect2 == true) {
			this->AppendTrimPointIntoProperList(lineToTrim, clickPoint, intersect,
				betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);
		}
		else if (sameStartIntersect2 == true && sameEndIntersect == false) {
			this->AppendTrimPointIntoProperList(lineToTrim, clickPoint, intersect,
				betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);
		}
		else if (sameStartIntersect2 == false && sameEndIntersect == true) {
			this->AppendTrimPointIntoProperList(lineToTrim, clickPoint, intersect2,
				betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);
		}
		else if (sameStartIntersect == false && sameEndIntersect2 == false) {
			this->AppendTrimPointIntoProperList(lineToTrim, clickPoint, intersect, intersect2,
				betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);
		}
		else if (sameStartIntersect2 == false && sameEndIntersect == false) {
			this->AppendTrimPointIntoProperList(lineToTrim, clickPoint, intersect, intersect2,
				betweenStartAndClickTrimPointList, betweenEndAndClickTrimPointList);
		}
	}

}

void ShFindTrimPointLineTrimer::AppendTrimPointIntoProperList(ShLine *lineToTrim, const ShPoint3d& clickPoint,
	const ShPoint3d& trimPoint, QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
	QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList) {

	ShLineData data = lineToTrim->GetData();
	ShPoint3d clickP;
	ShFootOfPerpendicularVisitor visitor(clickP.x, clickP.y, clickPoint);
	this->lineToTrim->Accept(&visitor);

	double angleClickToStart = Math::GetAbsAngle(clickP.x, clickP.y, data.start.x, data.start.y);
	double angleClickToEnd = Math::GetAbsAngle(clickP.x, clickP.y, data.end.x, data.end.y);
	double angleClickToTrimPoint = Math::GetAbsAngle(clickP.x, clickP.y, trimPoint.x, trimPoint.y);

	if (Math::Compare(angleClickToStart, angleClickToTrimPoint) == 0)
		betweenStartAndClickTrimPointList.append(trimPoint);
	else
		betweenEndAndClickTrimPointList.append(trimPoint);

}

void ShFindTrimPointLineTrimer::AppendTrimPointIntoProperList(ShLine *lineToTrim, const ShPoint3d& clickPoint,
	const ShPoint3d& trimPoint, const ShPoint3d& trimPoint2,
	QLinkedList<ShPoint3d> &betweenStartAndClickTrimPointList,
	QLinkedList<ShPoint3d> &betweenEndAndClickTrimPointList) {


	ShLineData data = lineToTrim->GetData();
	ShPoint3d clickP;
	ShFootOfPerpendicularVisitor visitor(clickP.x, clickP.y, clickPoint);
	this->lineToTrim->Accept(&visitor);

	double angleClickToStart = Math::GetAbsAngle(clickP.x, clickP.y, data.start.x, data.start.y);
	double angleClickToEnd = Math::GetAbsAngle(clickP.x, clickP.y, data.end.x, data.end.y);
	double angleClickToTrimPoint = Math::GetAbsAngle(clickP.x, clickP.y, trimPoint.x, trimPoint.y);
	double angleClickToTrimPoint2 = Math::GetAbsAngle(clickP.x, clickP.y, trimPoint2.x, trimPoint2.y);

	if (Math::Compare(angleClickToTrimPoint, angleClickToTrimPoint2) == 0) {
		double disClickToTrimPoint = Math::GetDistance(clickP.x, clickP.y, trimPoint.x, trimPoint.y);
		double disClickToTrimPoint2 = Math::GetDistance(clickP.x, clickP.y, trimPoint2.x, trimPoint2.y);

		ShPoint3d closest;
		if (Math::Compare(disClickToTrimPoint, disClickToTrimPoint2) == 1)
			closest = trimPoint2;
		else
			closest = trimPoint;

		if (Math::Compare(angleClickToStart, angleClickToTrimPoint) == 0)
			betweenStartAndClickTrimPointList.append(closest);
		else
			betweenEndAndClickTrimPointList.append(closest);

	}
	else {
		if (Math::Compare(angleClickToStart, angleClickToTrimPoint) == 0) {
			betweenStartAndClickTrimPointList.append(trimPoint);
			betweenEndAndClickTrimPointList.append(trimPoint2);
		}
		else {
			betweenStartAndClickTrimPointList.append(trimPoint2);
			betweenEndAndClickTrimPointList.append(trimPoint);
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
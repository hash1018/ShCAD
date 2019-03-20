
#include "ShExtender.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "ShMath.h"
#include "Interface\ShGraphicView.h"
ShExtender::ShExtender(ShGraphicView *view, const QLinkedList<ShEntity*>& baseEntities, const ShPoint3d& clickPoint)
	:view(view), baseEntities(baseEntities), clickPoint(clickPoint) {

}

ShExtender::~ShExtender() {

}

void ShExtender::Visit(ShLine *line) {

	QLinkedList<ShPoint3d> intersectPointList;
	ShPoint3d linePointToExtend;

	double disClickToStart = Math::GetDistance(this->clickPoint.x, this->clickPoint.y, 
		line->GetStart().x, line->GetStart().y);
	double disClickToEnd = Math::GetDistance(this->clickPoint.x, this->clickPoint.y,
		line->GetEnd().x, line->GetEnd().y);

	ShFindIntersectPointLineExtender::PointToExtend pointToExtend;
	if (Math::Compare(disClickToStart, disClickToEnd) == 1) {
		pointToExtend = ShFindIntersectPointLineExtender::PointToExtend::End;
		linePointToExtend = line->GetEnd();
	}
	else {
		pointToExtend = ShFindIntersectPointLineExtender::PointToExtend::Start;
		linePointToExtend = line->GetStart();
	}

	ShFindIntersectPointLineExtender visitor(line, intersectPointList, pointToExtend);
	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->baseEntities.begin(); itr != this->baseEntities.end(); ++itr)
		(*itr)->Accept(&visitor);


	if (intersectPointList.count() == 0)
		return;


	QLinkedList<ShPoint3d>::iterator intersectItr = intersectPointList.begin();
	ShPoint3d closest = (*intersectItr);
	++intersectItr;

	while (intersectItr != intersectPointList.end()) {
	
		double disToClosest = Math::GetDistance(linePointToExtend.x, linePointToExtend.y,
			closest.x, closest.y);
		double disToIntersect = Math::GetDistance(linePointToExtend.x, linePointToExtend.y,
			(*intersectItr).x, (*intersectItr).y);

		if (Math::Compare(disToClosest, disToIntersect) == 1)
			closest = (*intersectItr);

		++intersectItr;
	}


	if (pointToExtend == ShFindIntersectPointLineExtender::PointToExtend::Start) {
		line->SetStart(closest);
	}
	else if (pointToExtend == ShFindIntersectPointLineExtender::PointToExtend::End) {
		line->SetEnd(closest);
	}

	this->view->update((DrawType)(DrawType::DrawAll));
	this->view->CaptureImage();
}

void ShExtender::Visit(ShCircle *circle) {

}

void ShExtender::Visit(ShArc *arc) {


}


////////////////////////////////////////////////////////////////////////////////


ShFindIntersectPointLineExtender::ShFindIntersectPointLineExtender(ShLine *lineToExtend,
	QLinkedList<ShPoint3d> &intersectPointList, PointToExtend pointToExtend)
	:lineToExtend(lineToExtend), intersectPointList(intersectPointList), pointToExtend(pointToExtend) {

}

ShFindIntersectPointLineExtender::~ShFindIntersectPointLineExtender() {

}


void ShFindIntersectPointLineExtender::Visit(ShLine *line) {

	ShLineData lineToExtendData = this->lineToExtend->GetData();
	ShLineData baseLineData = line->GetData();

	ShPoint3d intersect;
	if (Math::CheckTwoLineSegmentsIntersect(lineToExtendData.start, lineToExtendData.end,
		baseLineData.start,baseLineData.end, intersect) == true)
		return;

	if (Math::CheckLineLineIntersect(lineToExtendData.start, lineToExtendData.end,
		baseLineData.start, baseLineData.end, intersect) == false)
		return;

	double disStartToIntersect = Math::GetDistance(lineToExtendData.start.x, lineToExtendData.start.y,
		intersect.x, intersect.y);
	double disEndToIntersect = Math::GetDistance(lineToExtendData.end.x, lineToExtendData.end.y,
		intersect.x, intersect.y);

	if (this->pointToExtend == PointToExtend::Start) {
		if (Math::Compare(disEndToIntersect, disStartToIntersect) == 1)
			this->intersectPointList.append(intersect);
	}
	else if (this->pointToExtend == PointToExtend::End) {
		if (Math::Compare(disStartToIntersect, disEndToIntersect) == 1)
			this->intersectPointList.append(intersect);
	}
}

void ShFindIntersectPointLineExtender::Visit(ShCircle *circle) {

}

void ShFindIntersectPointLineExtender::Visit(ShArc *arc) {


}
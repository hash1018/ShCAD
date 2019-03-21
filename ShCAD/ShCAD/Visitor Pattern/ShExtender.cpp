
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

	QLinkedList<ShPoint3d> extensionPointList;
	ShPoint3d linePointToExtend;

	double disClickToStart = Math::GetDistance(this->clickPoint.x, this->clickPoint.y, 
		line->GetStart().x, line->GetStart().y);
	double disClickToEnd = Math::GetDistance(this->clickPoint.x, this->clickPoint.y,
		line->GetEnd().x, line->GetEnd().y);

	ShFindExtensionPointLineExtender::PointToExtend pointToExtend;
	if (Math::Compare(disClickToStart, disClickToEnd) == 1) {
		pointToExtend = ShFindExtensionPointLineExtender::PointToExtend::End;
		linePointToExtend = line->GetEnd();
	}
	else {
		pointToExtend = ShFindExtensionPointLineExtender::PointToExtend::Start;
		linePointToExtend = line->GetStart();
	}

	ShFindExtensionPointLineExtender visitor(line, extensionPointList, pointToExtend);
	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->baseEntities.begin(); itr != this->baseEntities.end(); ++itr)
		(*itr)->Accept(&visitor);


	if (extensionPointList.count() == 0)
		return;
	
	QLinkedList<ShPoint3d>::iterator intersectItr = extensionPointList.begin();
	ShPoint3d closest = (*intersectItr);
	++intersectItr;

	while (intersectItr != extensionPointList.end()) {
	
		double disToClosest = Math::GetDistance(linePointToExtend.x, linePointToExtend.y,
			closest.x, closest.y);
		double disToIntersect = Math::GetDistance(linePointToExtend.x, linePointToExtend.y,
			(*intersectItr).x, (*intersectItr).y);

		if (Math::Compare(disToClosest, disToIntersect) == 1)
			closest = (*intersectItr);

		++intersectItr;
	}


	qDebug("closest %.6f  %.6f", closest.x, closest.y);
	qDebug("line pointToExtend %.6f %.6f", linePointToExtend.x, linePointToExtend.y);

	if (pointToExtend == ShFindExtensionPointLineExtender::PointToExtend::Start) {
		line->SetStart(closest);
	}
	else if (pointToExtend == ShFindExtensionPointLineExtender::PointToExtend::End) {
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


ShFindExtensionPointLineExtender::ShFindExtensionPointLineExtender(ShLine *lineToExtend,
	QLinkedList<ShPoint3d> &extensionPointList, PointToExtend pointToExtend)
	:ShFindExtensionPointer(extensionPointList), lineToExtend(lineToExtend), pointToExtend(pointToExtend) {

}

ShFindExtensionPointLineExtender::~ShFindExtensionPointLineExtender() {

}


void ShFindExtensionPointLineExtender::Visit(ShLine *line) {

	ShLineData lineToExtendData = this->lineToExtend->GetData();
	ShLineData baseLineData = line->GetData();

	ShPoint3d intersect;
	if (Math::CheckTwoLineSegmentsIntersect(lineToExtendData.start, lineToExtendData.end,
		baseLineData.start,baseLineData.end, intersect) == true)
		return;

	if (Math::CheckLineLineIntersect(lineToExtendData.start, lineToExtendData.end,
		baseLineData.start, baseLineData.end, intersect) == false)
		return;

	if (Math::CheckPointLiesOnLine(intersect, baseLineData.start, baseLineData.end, 0.001) == false)
		return;

	if (this->CheckPossibleToExtend(this->lineToExtend, this->pointToExtend, intersect) == false)
		return;

	this->extensionPointList.append(intersect);
}

void ShFindExtensionPointLineExtender::Visit(ShCircle *circle) {

	ShLineData lineToExtendData = this->lineToExtend->GetData();
	ShCircleData baseCircleData = circle->GetData();

	ShPoint3d intersect, intersect2, finalIntersect;
	if (Math::CheckCircleLineIntersect(baseCircleData.center, baseCircleData.radius,
		lineToExtendData.start, lineToExtendData.end, intersect, intersect2) == false)
		return;

	if (this->CheckPossibleToExtend(this->lineToExtend, this->pointToExtend, intersect, intersect2, finalIntersect) == false)
		return;

	this->extensionPointList.append(finalIntersect);

}

void ShFindExtensionPointLineExtender::Visit(ShArc *arc) {

	ShLineData lineToExtendData = this->lineToExtend->GetData();
	ShArcData baseArcData = arc->GetData();

	ShPoint3d intersect, intersect2, finalIntersect;
	if (Math::CheckCircleLineIntersect(baseArcData.center, baseArcData.radius,
		lineToExtendData.start, lineToExtendData.end, intersect, intersect2) == false)
		return;

	bool insideArcIntersect = false;
	bool insideArcIntersect2 = false;

	if (Math::CheckPointLiesOnArcBoundary(intersect, baseArcData.center, baseArcData.radius,
		baseArcData.startAngle, baseArcData.endAngle, 0.001) == true)
		insideArcIntersect = true;
	if (Math::CheckPointLiesOnArcBoundary(intersect2, baseArcData.center, baseArcData.radius,
		baseArcData.startAngle, baseArcData.endAngle, 0.001) == true)
		insideArcIntersect2 = true;

	if (insideArcIntersect == false && insideArcIntersect2 == false)
		return;


	if (insideArcIntersect == true && insideArcIntersect2 == false) {
		if (this->CheckPossibleToExtend(this->lineToExtend, this->pointToExtend, intersect) == true)
			this->extensionPointList.append(intersect);
	}
	else if (insideArcIntersect == false && insideArcIntersect2 == true) {
		if (this->CheckPossibleToExtend(this->lineToExtend, this->pointToExtend, intersect2) == true)
			this->extensionPointList.append(intersect2);
	}
	else if (insideArcIntersect == true && insideArcIntersect2 == true) {
		if (this->CheckPossibleToExtend(this->lineToExtend, this->pointToExtend, intersect, intersect2, finalIntersect) == true)
			this->extensionPointList.append(finalIntersect);
	}
	
}

bool ShFindExtensionPointLineExtender::CheckPossibleToExtend(ShLine *lineToExtend, PointToExtend pointToExtend, const ShPoint3d& extensionPoint) {

	ShLineData data = lineToExtend->GetData();

	if (Math::CheckPointLiesOnLine(extensionPoint, data.start, data.end, 0.001) == true)
		return false;

	double disStartToExtension = Math::GetDistance(data.start.x, data.start.y,
		extensionPoint.x, extensionPoint.y);
	double disEndToExtension = Math::GetDistance(data.end.x, data.end.y,
		extensionPoint.x, extensionPoint.y);

	if (pointToExtend == PointToExtend::Start) {
		if (Math::Compare(disEndToExtension, disStartToExtension) == 1)
			if (Math::Compare(data.start.x, extensionPoint.x) != 0 ||
				Math::Compare(data.start.y, extensionPoint.y) != 0)
				return true;
	}
	else if (pointToExtend == PointToExtend::End) {
		if (Math::Compare(disStartToExtension, disEndToExtension) == 1)
			if (Math::Compare(data.end.x, extensionPoint.x) != 0 ||
				Math::Compare(data.end.y, extensionPoint.y) != 0)
				return true;
	}

	return false;
}

bool ShFindExtensionPointLineExtender::CheckPossibleToExtend(ShLine *lineToExtend, PointToExtend pointToExtend,
	const ShPoint3d& extensionPoint, const ShPoint3d& extensionPoint2, ShPoint3d& finalExtensionPoint) {

	ShLineData data = lineToExtend->GetData();

	bool insideIntersect = false;
	bool insideIntersect2 = false;

	if (Math::CheckPointLiesOnLine(extensionPoint, data.start, data.end, 0.001) == true)
		insideIntersect = true;
	if (Math::CheckPointLiesOnLine(extensionPoint2, data.start, data.end, 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == true && insideIntersect2 == true)
		return false;


	double disStartToIntersect = Math::GetDistance(data.start.x, data.start.y, extensionPoint.x, extensionPoint.y);
	double disEndToIntersect = Math::GetDistance(data.end.x, data.end.y, extensionPoint.x, extensionPoint.y);
	double disStartToIntersect2 = Math::GetDistance(data.start.x, data.start.y, extensionPoint2.x, extensionPoint2.y);
	double disEndToIntersect2 = Math::GetDistance(data.end.x, data.end.y, extensionPoint2.x, extensionPoint2.y);

	bool validExtension = false;

	if (insideIntersect == false && insideIntersect2 == true) {

		if (pointToExtend == PointToExtend::Start) {
			if (Math::Compare(disEndToIntersect, disStartToIntersect) == 1) {
				finalExtensionPoint = extensionPoint;
				validExtension = true;
			}
		}
		else if (pointToExtend == PointToExtend::End) {
			if (Math::Compare(disStartToIntersect, disEndToIntersect) == 1) {
				finalExtensionPoint = extensionPoint;
				validExtension = true;
			}
		}
	}
	else if (insideIntersect == true && insideIntersect2 == false) {

		if (pointToExtend == PointToExtend::Start) {
			if (Math::Compare(disEndToIntersect2, disStartToIntersect2) == 1) {
				finalExtensionPoint = extensionPoint2;
				validExtension = true;
			}
		}
		else if (pointToExtend == PointToExtend::End) {
			if (Math::Compare(disStartToIntersect2, disEndToIntersect2) == 1) {
				finalExtensionPoint = extensionPoint2;
				validExtension = true;
			}
		}
	}
	else if (insideIntersect == false && insideIntersect2 == false) {
		ShPoint3d mid = this->lineToExtend->GetMid();
		double angle = Math::GetAbsAngle(mid.x, mid.y, extensionPoint.x, extensionPoint.y);
		double angleMidToStart = Math::GetAbsAngle(mid.x, mid.y, data.start.x, data.start.y);
		double angleMidToEnd = Math::GetAbsAngle(mid.x, mid.y, data.end.x, data.end.y);

		if (Math::Compare(angle, angleMidToStart) == 0) {
			if (this->pointToExtend == PointToExtend::Start) {
				if (Math::Compare(disStartToIntersect, disStartToIntersect2) == 1) {
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
			if (this->pointToExtend == PointToExtend::End) {
				if (Math::Compare(disEndToIntersect, disEndToIntersect2) == 1) {
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

	if (this->pointToExtend == PointToExtend::Start) {
		if (Math::Compare(data.start.x, finalExtensionPoint.x) != 0 ||
			Math::Compare(data.start.y, finalExtensionPoint.y) != 0)
			return true;
	}
	else if (this->pointToExtend == PointToExtend::End) {
		if (Math::Compare(data.end.x, finalExtensionPoint.x) != 0 ||
			Math::Compare(data.end.y, finalExtensionPoint.y) != 0)
			return true;
	}

	return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

ShFindExtensionPointArcExtender::ShFindExtensionPointArcExtender(ShArc *arcToExtend,
	QLinkedList<ShPoint3d> &extensionPointList, PointToExtend pointToExtend)
	:ShFindExtensionPointer(extensionPointList), arcToExtend(arcToExtend), pointToExtend(pointToExtend) {

}

ShFindExtensionPointArcExtender::~ShFindExtensionPointArcExtender() {

}

void ShFindExtensionPointArcExtender::Visit(ShLine *line) {

}

void ShFindExtensionPointArcExtender::Visit(ShCircle *circle) {

}

void ShFindExtensionPointArcExtender::Visit(ShArc *arc) {


}
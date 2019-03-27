
#include "ShExtender.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Composite\ShPolyLine.h"
#include "ShMath.h"
#include "Interface\ShGraphicView.h"

ShExtender::ShExtender(ShGraphicView *view, const QLinkedList<ShEntity*>& baseEntities, const ShPoint3d& clickPoint,
	ShEntity* *original, ShEntity* *extendedEntity, bool &validToExtend)
	:view(view), baseEntities(baseEntities), clickPoint(clickPoint),
	original(original), extendedEntity(extendedEntity), validToExtend(validToExtend) {

	this->validToExtend = false;
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
	
	QLinkedList<ShPoint3d>::iterator extensionItr = extensionPointList.begin();
	ShPoint3d closest = (*extensionItr);
	++extensionItr;

	while (extensionItr != extensionPointList.end()) {
	
		double disToClosest = Math::GetDistance(linePointToExtend.x, linePointToExtend.y,
			closest.x, closest.y);
		double disToExtension = Math::GetDistance(linePointToExtend.x, linePointToExtend.y,
			(*extensionItr).x, (*extensionItr).y);

		if (Math::Compare(disToClosest, disToExtension) == 1)
			closest = (*extensionItr);

		++extensionItr;
	}


	this->validToExtend = true;

	*this->original = line;
	ShLine *extendedLine = line->Clone();

	if (pointToExtend == ShFindExtensionPointLineExtender::PointToExtend::Start) {
		extendedLine->SetStart(closest);
	}
	else if (pointToExtend == ShFindExtensionPointLineExtender::PointToExtend::End) {
		extendedLine->SetEnd(closest);
	}

	*this->extendedEntity = extendedLine;

	this->view->entityTable.Remove(line);
	this->view->entityTable.Add(extendedLine);


	this->view->update((DrawType)(DrawType::DrawAll));
	this->view->CaptureImage();
}

void ShExtender::Visit(ShCircle *circle) {

}

void ShExtender::Visit(ShArc *arc) {

	QLinkedList<ShPoint3d> extensionPointList;
	ShArcData data = arc->GetData();
	ShPoint3d arcPointToExtend;

	double angleCenterToClick = Math::GetAbsAngle(data.center.x, data.center.y,
		this->clickPoint.x, this->clickPoint.y);
	double differenceAngle = Math::GetAngleDifference(data.startAngle, data.endAngle);
	
	ShFindExtensionPointArcExtender::PointToExtend pointToExtend;
	if (Math::CheckAngleLiesOnAngleBetween(data.startAngle,
		Math::AddAngle(data.startAngle, differenceAngle / 2), 
		angleCenterToClick) == true) {

		arcPointToExtend = arc->GetStart();
		pointToExtend = ShFindExtensionPointArcExtender::PointToExtend::Start;
	}
	else {
		arcPointToExtend = arc->GetEnd();
		pointToExtend = ShFindExtensionPointArcExtender::PointToExtend::End;
	}
	
	ShFindExtensionPointArcExtender visitor(arc, extensionPointList, pointToExtend);
	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->baseEntities.begin(); itr != this->baseEntities.end(); ++itr)
		(*itr)->Accept(&visitor);

	if (extensionPointList.count() == 0)
		return;

	QLinkedList<ShPoint3d>::iterator extensionItr = extensionPointList.begin();
	ShPoint3d closest = (*extensionItr);
	++extensionItr;

	while (extensionItr != extensionPointList.end()) {

		double angleCenterToClosest = Math::GetAbsAngle(data.center.x, data.center.y, closest.x, closest.y);
		double angleCenterToExtensionPoint = Math::GetAbsAngle(data.center.x, data.center.y,
			(*extensionItr).x, (*extensionItr).y);
		double angleCenterToPointToExtend = Math::GetAbsAngle(data.center.x, data.center.y,
			arcPointToExtend.x, arcPointToExtend.y);

		if (pointToExtend == ShFindExtensionPointArcExtender::PointToExtend::Start) {
			double difference = Math::GetAngleDifference(angleCenterToPointToExtend, angleCenterToExtensionPoint, false);
			double difference2 = Math::GetAngleDifference(angleCenterToPointToExtend, angleCenterToClosest, false);
			if (Math::Compare(difference2, difference) == 1)
				closest = (*extensionItr);
		}
		else if (pointToExtend == ShFindExtensionPointArcExtender::PointToExtend::End) {
			double difference = Math::GetAngleDifference(angleCenterToPointToExtend, angleCenterToExtensionPoint);
			double difference2 = Math::GetAngleDifference(angleCenterToPointToExtend, angleCenterToClosest);
			if (Math::Compare(difference2, difference) == 1)
				closest = (*extensionItr);
		}

		++extensionItr;
	}

	this->validToExtend = true;

	*this->original = arc;
	ShArc *extendedArc = arc->Clone();

	if (pointToExtend == ShFindExtensionPointLineExtender::PointToExtend::Start) {
		data.startAngle = Math::GetAbsAngle(data.center.x, data.center.y, closest.x, closest.y);
	}
	else if (pointToExtend == ShFindExtensionPointLineExtender::PointToExtend::End) {
		data.endAngle = Math::GetAbsAngle(data.center.x, data.center.y, closest.x, closest.y);
	}

	extendedArc->SetData(data);

	*this->extendedEntity = extendedArc;

	this->view->entityTable.Remove(arc);
	this->view->entityTable.Add(extendedArc);
	
	
	this->view->update((DrawType)(DrawType::DrawAll));
	this->view->CaptureImage();
}

void ShExtender::Visit(ShPolyLine *polyLine) {

	/*
	int count = polyLine->GetSize();
	ShEntity* entity = polyLine->FindEntity(this->clickPoint.x, this->clickPoint.y, this->view->GetZoomRate());

	if (entity == 0)
		return;

	int index = polyLine->GetIndex(entity);

	int binary = count / 2;

	if (index < binary)
		index = 0;
	else
		index = count - 1;

	ShEntityData *original;
	ShEntityData *extendedData;
	bool isValid = false;
	
	if (index == 0) {
		ShExtender visitor(this->view, this->baseEntities, this->clickPoint, &original, &extendedData, isValid);
		polyLine->GetEntity(index)->Accept(&visitor);
	}
	else {
	
	}

	if (isValid == false)
		return;
	
	*this->originalData = polyLine->CreateData();
	polyLine->GetEntity(index)->SetData(extendedData);
	*this->extendedData = polyLine->CreateData();
	this->validToExtend = true;

	delete original;
	delete extendedData;
	
	this->view->update((DrawType)(DrawType::DrawAll));
	this->view->CaptureImage();
	*/
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

void ShFindExtensionPointLineExtender::Visit(ShPolyLine *polyLine) {

	ShFindExtensionPointLineExtender visitor(this->lineToExtend, this->extensionPointList, this->pointToExtend);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = polyLine->Begin(); itr != polyLine->End(); ++itr)
		(*itr)->Accept(&visitor);

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

	ShArcData data = this->arcToExtend->GetData();
	

	ShPoint3d intersect, intersect2, finalExtension;
	if (Math::CheckCircleLineIntersect(data.center, data.radius, line->GetStart(), line->GetEnd(),
		intersect, intersect2) == false)
		return;

	bool insideIntersect = false;
	bool insideIntersect2 = false;
	if (Math::CheckPointLiesOnLine(intersect, line->GetStart(), line->GetEnd(), 0.001) == true)
		insideIntersect = true;
	if (Math::CheckPointLiesOnLine(intersect2, line->GetStart(), line->GetEnd(), 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false) {
		if (this->CheckPossibleToExtend(this->arcToExtend, this->pointToExtend, intersect) == true)
			this->extensionPointList.append(intersect);
	}
	else if (insideIntersect == false && insideIntersect2 == true) {
		if (this->CheckPossibleToExtend(this->arcToExtend, this->pointToExtend, intersect2) == true)
			this->extensionPointList.append(intersect2);
	}
	else if (insideIntersect == true && insideIntersect2 == true) {
		if (this->CheckPossibleToExtend(this->arcToExtend, this->pointToExtend, intersect, intersect2,
			finalExtension) == true)
			this->extensionPointList.append(finalExtension);
	}

}

void ShFindExtensionPointArcExtender::Visit(ShCircle *circle) {
	
	ShArcData arcData = this->arcToExtend->GetData();

	ShPoint3d intersect, intersect2;
	if (Math::CheckTwoCirclesIntersect(arcData.center, arcData.radius, circle->GetCenter(), circle->GetRadius(),
		intersect, intersect2) == false)
		return;

	ShPoint3d finalIntersect;
	if (this->CheckPossibleToExtend(this->arcToExtend, this->pointToExtend, intersect, intersect2,
		finalIntersect) == true)
		this->extensionPointList.append(finalIntersect);

}

void ShFindExtensionPointArcExtender::Visit(ShArc *arc) {

	ShArcData arcData = this->arcToExtend->GetData();

	ShPoint3d intersect, intersect2;
	if (Math::CheckTwoCirclesIntersect(arcData.center, arcData.radius, arc->GetCenter(), arc->GetRadius(),
		intersect, intersect2) == false)
		return;

	bool insideIntersect = false;
	bool insideIntersect2 = false;

	if (Math::CheckPointLiesOnArcBoundary(intersect, arc->GetCenter(), arc->GetRadius(),
		arc->GetStartAngle(), arc->GetEndAngle(), 0.001) == true)
		insideIntersect = true;

	if (Math::CheckPointLiesOnArcBoundary(intersect2, arc->GetCenter(), arc->GetRadius(),
		arc->GetStartAngle(), arc->GetEndAngle(), 0.001) == true)
		insideIntersect2 = true;

	if (insideIntersect == false && insideIntersect2 == false)
		return;

	if (insideIntersect == true && insideIntersect2 == false) {
		if (this->CheckPossibleToExtend(this->arcToExtend, this->pointToExtend, intersect) == true)
			this->extensionPointList.append(intersect);
	}
	else if (insideIntersect == false && insideIntersect2 == true) {
		if (this->CheckPossibleToExtend(this->arcToExtend, this->pointToExtend, intersect2) == true)
			this->extensionPointList.append(intersect2);
	}
	else if (insideIntersect == true && insideIntersect2 == true) {
		ShPoint3d finalIntersect;
		if (this->CheckPossibleToExtend(this->arcToExtend, this->pointToExtend, intersect, intersect2,
			finalIntersect) == true)
			this->extensionPointList.append(finalIntersect);
	}

}

void ShFindExtensionPointArcExtender::Visit(ShPolyLine *polyLine) {

	ShFindExtensionPointArcExtender visitor(this->arcToExtend, this->extensionPointList, this->pointToExtend);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = polyLine->Begin(); itr != polyLine->End(); ++itr)
		(*itr)->Accept(&visitor);

}

bool ShFindExtensionPointArcExtender::CheckPossibleToExtend(ShArc *arcToExtend, PointToExtend pointToExtend, 
	const ShPoint3d& extensionPoint) {

	ShArcData data = arcToExtend->GetData();

	if (Math::CheckPointLiesOnArcBoundary(extensionPoint, data.center, data.radius,
		data.startAngle, data.endAngle, 0.001) == true)
		return false;

	if (pointToExtend == PointToExtend::Start) {
		ShPoint3d start = arcToExtend->GetStart();
		if (Math::Compare(start.x, extensionPoint.x) != 0 ||
			Math::Compare(start.y, extensionPoint.y) != 0)
			return true;
	}
	else if (pointToExtend == PointToExtend::End) {
		ShPoint3d end = arcToExtend->GetEnd();
		if (Math::Compare(end.x, extensionPoint.x) != 0 ||
			Math::Compare(end.y, extensionPoint.y) != 0)
			return true;
	}

	return false;
}


bool ShFindExtensionPointArcExtender::CheckPossibleToExtend(ShArc *arcToExtend, PointToExtend pointToExtend,
	const ShPoint3d& extensionPoint, const ShPoint3d& extensionPoint2, ShPoint3d& finalExtensionPoint) {

	ShArcData data = arcToExtend->GetData();

	bool insideIntersect = false;
	bool insideIntersect2 = false;

	if (Math::CheckPointLiesOnArcBoundary(extensionPoint, data.center, data.radius, 
		data.startAngle, data.endAngle, 0.001) == true)
		insideIntersect = true;
	if (Math::CheckPointLiesOnArcBoundary(extensionPoint2, data.center, data.radius,
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

		double angleCenterToStart = Math::GetAbsAngle(data.center.x, data.center.y,
			arcToExtend->GetStart().x, arcToExtend->GetStart().y);
		double angleCenterToIntersect = Math::GetAbsAngle(data.center.x, data.center.y,
			extensionPoint.x, extensionPoint.y);
		double angleCenterToIntersect2 = Math::GetAbsAngle(data.center.x, data.center.y,
			extensionPoint2.x, extensionPoint2.y);
		double angleCenterToEnd = Math::GetAbsAngle(data.center.x, data.center.y,
			arcToExtend->GetEnd().x, arcToExtend->GetEnd().y);


		if (pointToExtend == PointToExtend::Start) {
		
			double difference = Math::GetAngleDifference(angleCenterToStart, angleCenterToIntersect, false);
			double difference2 = Math::GetAngleDifference(angleCenterToStart, angleCenterToIntersect2, false);

			if (Math::Compare(difference, difference2) == 1)
				finalExtensionPoint = extensionPoint2;
			else
				finalExtensionPoint = extensionPoint;

			validExtension = true;
		}
		else if (pointToExtend == PointToExtend::End) {
			
			double difference = Math::GetAngleDifference(angleCenterToEnd, angleCenterToIntersect);
			double difference2 = Math::GetAngleDifference(angleCenterToEnd, angleCenterToIntersect2);

			if (Math::Compare(difference, difference2) == 1)
				finalExtensionPoint = extensionPoint2;
			else
				finalExtensionPoint = extensionPoint;

			validExtension = true;
		}

	}

	if (validExtension == false)
		return false;

	if (pointToExtend == PointToExtend::Start) {
		ShPoint3d start = arcToExtend->GetStart();
		if (Math::Compare(start.x, finalExtensionPoint.x) != 0 ||
			Math::Compare(start.y, finalExtensionPoint.y) != 0)
			return true;
	}
	else if (pointToExtend == PointToExtend::End) {
		ShPoint3d end = arcToExtend->GetEnd();
		if (Math::Compare(end.x, finalExtensionPoint.x) != 0 ||
			Math::Compare(end.y, finalExtensionPoint.y) != 0)
			return true;
	}

	return false;
}
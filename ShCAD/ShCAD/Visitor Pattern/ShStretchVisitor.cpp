

#include "ShStretchVisitor.h"
#include "ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Composite\ShPolyLine.h"
#include <math.h>

ShStretchData::ShStretchData(){

}

ShStretchData::~ShStretchData() {

}


ShStretchLeafData::ShStretchLeafData(StretchPoint stretchPoint)
	:stretchPoint(stretchPoint) {

}

ShStretchLeafData::~ShStretchLeafData() {

}



ShStretchCompositeData::ShStretchCompositeData()
	:stretchPoint(StretchPoint::StretchChild) {

}

ShStretchCompositeData::~ShStretchCompositeData() {

	while (!this->childStretchData.isEmpty())
		delete this->childStretchData.takeFirst();
}


/////////////////////////////////////////////////////////////////////////////////////////////

ShStretchVisitor::ShStretchVisitor(const ShPoint3d& base, const ShPoint3d& current)
	:base(base), current(current), stretchData(0) {


}

ShStretchVisitor::~ShStretchVisitor() {

}

void ShStretchVisitor::Visit(ShLine *line) {

	if (this->original == 0 || !dynamic_cast<ShLine*>(this->original))
		return;

	if (!dynamic_cast<ShStretchLeafData*>(this->stretchData))
		return;

	ShStretchLeafData *stretchData = dynamic_cast<ShStretchLeafData*>(this->stretchData);

	ShLine *original = dynamic_cast<ShLine*>(this->original);
	ShLineData data = original->GetData();

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


	line->SetData(data);

}

void ShStretchVisitor::Visit(ShCircle *circle) {

	if (this->original == 0 || !dynamic_cast<ShCircle*>(this->original))
		return;

	if (!dynamic_cast<ShStretchLeafData*>(this->stretchData))
		return;

	ShStretchLeafData *stretchData = dynamic_cast<ShStretchLeafData*>(this->stretchData);


	ShCircle *original = dynamic_cast<ShCircle*>(this->original);

	ShCircleData data = original->GetData();
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
	
		double radius = Math::GetDistance(center.x, center.y, this->current.x, this->current.y);
		data.radius = radius;
	}

	circle->SetData(data);
}

void ShStretchVisitor::Visit(ShArc *arc) {

	if (this->original == 0 || !dynamic_cast<ShArc*>(this->original))
		return;

	if (!dynamic_cast<ShStretchLeafData*>(this->stretchData))
		return;

	ShStretchLeafData *stretchData = dynamic_cast<ShStretchLeafData*>(this->stretchData);

	ShArc *original = dynamic_cast<ShArc*>(this->original);
	ShArcData data = original->GetData();
	
	double disX = this->current.x - this->base.x;
	double disY = this->current.y - this->base.y;

	if (stretchData->stretchPoint == StretchPoint::StretchMove) {

		data.center.x += disX;
		data.center.y += disY;
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchStart ||
		stretchData->stretchPoint==StretchPoint::StretchEnd ||
		stretchData->stretchPoint==StretchPoint::StretchMid) {

		ShPoint3d start = original->GetStart();
		ShPoint3d end = original->GetEnd();
		ShPoint3d mid = original->GetMid();
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

		if (Math::GetCenterWithThreePoint(start, mid, end, center) == false)
			return;

		double startAngle = Math::GetAbsAngle(center.x, center.y, start.x, start.y);
		double endAngle = Math::GetAbsAngle(center.x, center.y, end.x, end.y);
		double midAngle = Math::GetAbsAngle(center.x, center.y, mid.x, mid.y);
		double radius = Math::GetDistance(center.x, center.y, start.x, start.y);

		data.center = center;
		data.radius = radius;

		if (Math::CheckAngleLiesOnAngleBetween(startAngle, endAngle, midAngle) == true) {
			data.startAngle = startAngle;
			data.endAngle = endAngle;
		}
		else {
			data.startAngle = endAngle;
			data.endAngle = startAngle;
		}
		
	}
	
	arc->SetData(data);

}

void ShStretchVisitor::Visit(ShPolyLine *polyLine) {

	if (this->original == 0 || !dynamic_cast<ShPolyLine*>(this->original))
		return;

	if (!dynamic_cast<ShStretchCompositeData*>(this->stretchData))
		return;

	ShStretchCompositeData *stretchData = dynamic_cast<ShStretchCompositeData*>(this->stretchData);
	ShPolyLine *original = dynamic_cast<ShPolyLine*>(this->original);
	
	if (stretchData->stretchPoint == StretchPoint::StretchMove) {

		ShStretchVisitor visitor(this->base, this->current);
		int index = 0;
		QLinkedList<ShEntity*>::iterator originalItr = original->Begin();
		QLinkedList<ShEntity*>::iterator itr;
		for (itr = polyLine->Begin(); itr != polyLine->End(); ++itr) {
		
			visitor.SetOriginal((*originalItr));
			visitor.SetStretchData(stretchData->childStretchData.at(index));
			(*itr)->Accept(&visitor);
			++originalItr;
			index++;
		}
	
	}
	else if (stretchData->stretchPoint == StretchPoint::StretchChild) {

		ShStretchVisitor visitor(this->base, this->current);

		int index = 0;
		for (int i = 0; i < stretchData->childStretchData.count(); i++) {

			index = stretchData->childIndex.at(i);
			visitor.SetOriginal(original->GetEntity(index));
			visitor.SetStretchData(stretchData->childStretchData.at(i));
			polyLine->GetEntity(index)->Accept(&visitor);

		}

		int prev, next;
		for (int i = 0; i < stretchData->childIndex.count(); i++) {

			index = stretchData->childIndex.at(i);
			prev = index - 1;
			next = index + 1;

			if (stretchData->childIndex.contains(prev) == false) {
				ShArrangePolyLineChildAfterStretchingVisitor visitor(polyLine->GetEntity(prev));
				polyLine->GetEntity(index)->Accept(&visitor);
			}
			if (stretchData->childIndex.contains(next) == false) {
				ShArrangePolyLineChildAfterStretchingVisitor visitor(polyLine->GetEntity(next), false);
				polyLine->GetEntity(index)->Accept(&visitor);
			}
		}
	}

}


/////////////////////////////////////////////////////////////////////////////////////////

ShFindStretchMovePointVisitor::ShFindStretchMovePointVisitor(QList<ShEntity*> &entitiesToStretch,
	QList<ShStretchData*> &stretchDataList)
	:entitiesToStretch(entitiesToStretch), stretchDataList(stretchDataList) {

}

ShFindStretchMovePointVisitor::~ShFindStretchMovePointVisitor() {

}


void ShFindStretchMovePointVisitor::Visit(ShLine *line) {

	this->entitiesToStretch.append(line);
	ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchMove);
	this->stretchDataList.append(data);
}

void ShFindStretchMovePointVisitor::Visit(ShCircle *circle) {

	this->entitiesToStretch.append(circle);
	ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchMove);
	this->stretchDataList.append(data);
}

void ShFindStretchMovePointVisitor::Visit(ShArc *arc) {
	
	this->entitiesToStretch.append(arc);
	ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchMove);
	this->stretchDataList.append(data);
}

void ShFindStretchMovePointVisitor::Visit(ShPolyLine *polyLine) {

	this->entitiesToStretch.append(polyLine);
	ShStretchCompositeData *data = new ShStretchCompositeData;
	data->stretchPoint = StretchPoint::StretchMove;
	
	QList<ShEntity*> childToStretch;
	QList<ShStretchData*> dataList;
	
	ShFindStretchMovePointVisitor visitor(childToStretch, dataList);

	int index = 0;
	QLinkedList<ShEntity*>::iterator itr;
	for (itr = polyLine->Begin(); itr != polyLine->End(); ++itr) {
		(*itr)->Accept(&visitor);
		data->childIndex.append(index);
		index++;
	}

	data->childStretchData = dataList;
	


	this->stretchDataList.append(data);

}

///////////////////////////////////////////////////////////////////////////////////////////


ShFindEntityToStretchVisitor::ShFindEntityToStretchVisitor(const ShPoint3d& point,
	QList<ShEntity*> &entitiesToStretch, QList<ShStretchData*> &stretchDataList)
	:point(point), entitiesToStretch(entitiesToStretch), stretchDataList(stretchDataList) {

}

ShFindEntityToStretchVisitor::~ShFindEntityToStretchVisitor() {

}


void ShFindEntityToStretchVisitor::Visit(ShLine *line) {

	if (this->point == line->GetStart()) {
		this->entitiesToStretch.append(line);
		ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchStart);
		this->stretchDataList.append(data);
	}
		
	else if (this->point == line->GetEnd()) {
		this->entitiesToStretch.append(line);
		ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchEnd);
		this->stretchDataList.append(data);
	}
	else if (this->point == line->GetMid()) {
		this->entitiesToStretch.append(line);
		ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchMove);
		this->stretchDataList.append(data);
	}
	
}

void ShFindEntityToStretchVisitor::Visit(ShCircle *circle) {

	ShPoint3d center = circle->GetCenter();
	double radius = circle->GetRadius();

	if (this->point == center) {
		this->entitiesToStretch.append(circle);
		ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchMove);
		this->stretchDataList.append(data);
		return;
	}

	ShPoint3d temp;
	temp.x = center.x + radius;
	temp.y = center.y;

	if (this->point == temp) {
		this->entitiesToStretch.append(circle);
		ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchRight);
		this->stretchDataList.append(data);
		return;
	}

	temp.x = center.x;
	temp.y = center.y - radius;

	if (this->point == temp) {
		this->entitiesToStretch.append(circle);
		ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchBottom);
		this->stretchDataList.append(data);
		return;
	}

	temp.x = center.x - radius;
	temp.y = center.y;

	if (this->point == temp) {
		this->entitiesToStretch.append(circle);
		ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchLeft);
		this->stretchDataList.append(data);
		return;
	}

	temp.x = center.x;
	temp.y = center.y + radius;

	if (this->point == temp) {
		this->entitiesToStretch.append(circle);
		ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchTop);
		this->stretchDataList.append(data);
		return;
	}

}

void ShFindEntityToStretchVisitor::Visit(ShArc *arc) {

	if (this->point == arc->GetCenter()) {
		this->entitiesToStretch.append(arc);
		ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchMove);
		this->stretchDataList.append(data);
	}
	else if (this->point == arc->GetStart()) {
		this->entitiesToStretch.append(arc);
		ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchStart);
		this->stretchDataList.append(data);
	}
	else if (this->point == arc->GetEnd()) {
		this->entitiesToStretch.append(arc);
		ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchEnd);
		this->stretchDataList.append(data);
	} 
	else if (this->point == arc->GetMid()) {
		this->entitiesToStretch.append(arc);
		ShStretchLeafData *data = new ShStretchLeafData(StretchPoint::StretchMid);
		this->stretchDataList.append(data);
	}

}

void ShFindEntityToStretchVisitor::Visit(ShPolyLine *polyLine) {

	QList<ShEntity*> childToStretch;
	QList<ShStretchData*> childData;
	ShFindEntityToStretchVisitor visitor(this->point, childToStretch, childData);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = polyLine->Begin(); itr != polyLine->End(); ++itr)
		(*itr)->Accept(&visitor);

	if (childToStretch.count() != 0) {
		
		ShStretchCompositeData *data = new ShStretchCompositeData;
		data->childStretchData = childData;

		int index = 0;
		for (int i = 0; i < childToStretch.count(); i++) {
		
			ShEntity *original = childToStretch.at(i);
			
			index = polyLine->GetIndex(original);
			data->childIndex.append(index);
		}
		
		
		this->entitiesToStretch.append(polyLine);
		this->stretchDataList.append(data);
	}

}

///////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////


ShFindStretchPointWithRectVisitor::ShFindStretchPointWithRectVisitor(QList<ShEntity*> &entitiesToStretch,
	QList<ShStretchData*> &stretchDataList, const ShPoint3d& topLeft, const ShPoint3d& bottomRight)
	:entitiesToStretch(entitiesToStretch), stretchDataList(stretchDataList),
	topLeft(topLeft), bottomRight(bottomRight) {

}

ShFindStretchPointWithRectVisitor::~ShFindStretchPointWithRectVisitor() {

}


void ShFindStretchPointWithRectVisitor::Visit(ShLine *line) {

	int insideCount = 0;
	StretchPoint stretchPoint = StretchPoint::StretchNothing;

	if (Math::CheckPointLiesInsideRect(line->GetStart(), this->topLeft, this->bottomRight, 0) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchStart;
	}

	if (Math::CheckPointLiesInsideRect(line->GetEnd(), this->topLeft, this->bottomRight, 0) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchEnd;
	}

	if (insideCount == 2) 
		stretchPoint = StretchPoint::StretchMove;
	
	
	this->entitiesToStretch.append(line);
	ShStretchLeafData *data = new ShStretchLeafData(stretchPoint);
	this->stretchDataList.append(data);
}

void ShFindStretchPointWithRectVisitor::Visit(ShCircle *circle) {

	StretchPoint stretchPoint = StretchPoint::StretchNothing;

	if (Math::CheckPointLiesInsideRect(circle->GetCenter(), this->topLeft, this->bottomRight, 0) == true)
		stretchPoint = StretchPoint::StretchMove;
	
	this->entitiesToStretch.append(circle);
	ShStretchLeafData *data = new ShStretchLeafData(stretchPoint);
	this->stretchDataList.append(data);

}

void ShFindStretchPointWithRectVisitor::Visit(ShArc *arc) {

	int insideCount = 0;
	StretchPoint stretchPoint = StretchPoint::StretchNothing;

	if (Math::CheckPointLiesInsideRect(arc->GetStart(), this->topLeft, this->bottomRight, 0) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchStart;
	}
	
	if (Math::CheckPointLiesInsideRect(arc->GetEnd(), this->topLeft, this->bottomRight, 0) == true) {
		insideCount++;
		stretchPoint = StretchPoint::StretchEnd;
	}

	if (insideCount == 2)
		stretchPoint = StretchPoint::StretchMove;
	
	this->entitiesToStretch.append(arc);
	ShStretchLeafData *data = new ShStretchLeafData(stretchPoint);
	this->stretchDataList.append(data);
}

void ShFindStretchPointWithRectVisitor::Visit(ShPolyLine *polyLine) {

	QList<ShEntity*> childToStretch;
	QList<ShStretchData*> childData;
	ShFindStretchPointWithRectVisitor visitor(childToStretch, childData, this->topLeft, this->bottomRight);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = polyLine->Begin(); itr != polyLine->End(); ++itr)
		(*itr)->Accept(&visitor);

	if (childToStretch.count() != 0) {

		ShStretchCompositeData *data = new ShStretchCompositeData;
		data->childStretchData = childData;
		

		
		for (int i = 0; i < childToStretch.count(); i++) {
			data->childIndex.append(i);
		}


		this->entitiesToStretch.append(polyLine);
		this->stretchDataList.append(data);
	}
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




ShArrangePolyLineChildAfterStretchingVisitor::ShArrangePolyLineChildAfterStretchingVisitor(ShEntity *entityToArrange, bool isPrevious)
	:entityToArrange(entityToArrange), isPrevious(isPrevious) {

}

ShArrangePolyLineChildAfterStretchingVisitor::~ShArrangePolyLineChildAfterStretchingVisitor() {

}

void ShArrangePolyLineChildAfterStretchingVisitor::Visit(ShLine *stretchedLine) {

	if (this->entityToArrange != 0) {
		ShArrangePolyLineChildStretchedLineVisitor visitor(stretchedLine, this->isPrevious);
		this->entityToArrange->Accept(&visitor);
	}
}

void ShArrangePolyLineChildAfterStretchingVisitor::Visit(ShCircle *circle) {

}

void ShArrangePolyLineChildAfterStretchingVisitor::Visit(ShArc *stretchedArc) {

}

//////////////////////////////////////////////////////////////////////////////////////////

ShArrangePolyLineChildStretchedLineVisitor::ShArrangePolyLineChildStretchedLineVisitor(ShLine *stretchedLine,
	bool isPrevious)
	:stretchedLine(stretchedLine), isPrevious(isPrevious) {

}

ShArrangePolyLineChildStretchedLineVisitor::~ShArrangePolyLineChildStretchedLineVisitor() {

}


void ShArrangePolyLineChildStretchedLineVisitor::Visit(ShLine *line) {

	if (this->isPrevious == true)
		line->SetEnd(this->stretchedLine->GetStart());
	else
		line->SetStart(this->stretchedLine->GetEnd());
	

}

void ShArrangePolyLineChildStretchedLineVisitor::Visit(ShCircle *circle) {

}

void ShArrangePolyLineChildStretchedLineVisitor::Visit(ShArc *arc) {


}
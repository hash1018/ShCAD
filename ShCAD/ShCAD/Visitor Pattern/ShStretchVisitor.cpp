

#include "ShStretchVisitor.h"
#include "ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include <math.h>
ShStretchVisitor::ShStretchVisitor(const ShPoint3d& base, const ShPoint3d& current)
	:base(base),current(current), original(0), vertexPoint(VertexPoint::VertexNothing) {


}

ShStretchVisitor::~ShStretchVisitor() {

}

void ShStretchVisitor::Visit(ShLine *line) {

	if (this->original == 0 || !dynamic_cast<ShLine*>(this->original))
		return;

	ShLine *original = dynamic_cast<ShLine*>(this->original);

	ShLineData data = original->GetData();
	

	double disX = this->current.x - this->base.x;
	double disY = this->current.y - this->base.y;

	if (this->vertexPoint == VertexPoint::VertexStart) {
		data.start.x += disX;
		data.start.y += disY;
	}
	else if (this->vertexPoint == VertexPoint::VertexEnd) {
		data.end.x += disX;
		data.end.y += disY;
	}
	else if (this->vertexPoint == VertexPoint::VertexMid) {
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

	ShCircle *original = dynamic_cast<ShCircle*>(this->original);

	ShCircleData data = original->GetData();
	ShPoint3d center = data.center;

	double disX = this->current.x - this->base.x;
	double disY = this->current.y - this->base.y;

	if (this->vertexPoint == VertexPoint::VertexCenter) {
		center.x += disX;
		center.y += disY;
		data.center = center;
	}
	else if (this->vertexPoint == VertexPoint::VertexRight ||
		this->vertexPoint == VertexPoint::VertexBottom ||
		this->vertexPoint == VertexPoint::VertexLeft ||
		this->vertexPoint == VertexPoint::VertexTop) {
	
		double radius = Math::GetDistance(center.x, center.y, this->current.x, this->current.y);
		data.radius = radius;
	}

	circle->SetData(data);
}

void ShStretchVisitor::Visit(ShArc *arc) {

	if (this->original == 0 || !dynamic_cast<ShArc*>(this->original))
		return;

	ShArc *original = dynamic_cast<ShArc*>(this->original);
	ShArcData data = original->GetData();

	double disX = this->current.x - this->base.x;
	double disY = this->current.y - this->base.y;

	if (this->vertexPoint == VertexPoint::VertexCenter) {

		data.center.x += disX;
		data.center.y += disY;
	}
	else if (this->vertexPoint == VertexPoint::VertexStart || 
		this->vertexPoint==VertexPoint::VertexEnd ||
		this->vertexPoint==VertexPoint::VertexMid) {

		ShPoint3d start = original->GetStart();
		ShPoint3d end = original->GetEnd();
		ShPoint3d mid = original->GetMid();
		ShPoint3d center;
		
		if (this->vertexPoint == VertexPoint::VertexStart) {
		
			start.x += disX;
			start.y += disY;
		}
		else if (this->vertexPoint == VertexPoint::VertexEnd) {
		
			end.x += disX;
			end.y += disY;
		}
		else if (this->vertexPoint == VertexPoint::VertexMid) {
			
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



/////////////////////////////////////////////////////////////////////////////////////////

ShFindStretchMovePointVisitor::ShFindStretchMovePointVisitor(VertexPoint &vertexPoint)
	:vertexPoint(vertexPoint) {

}

ShFindStretchMovePointVisitor::~ShFindStretchMovePointVisitor() {

}


void ShFindStretchMovePointVisitor::Visit(ShLine *line) {

	this->vertexPoint = VertexMid;
}

void ShFindStretchMovePointVisitor::Visit(ShCircle *circle) {

	this->vertexPoint = VertexCenter;
}

void ShFindStretchMovePointVisitor::Visit(ShArc *arc) {
	
	this->vertexPoint = VertexCenter;
}


///////////////////////////////////////////////////////////////////////////////////////////

ShFindStretchPointWithRectVisitor::ShFindStretchPointWithRectVisitor(VertexPoint &vertexPoint,
	const ShPoint3d& topLeft, const ShPoint3d& bottomRight)
	:vertexPoint(vertexPoint), topLeft(topLeft), bottomRight(bottomRight) {

}

ShFindStretchPointWithRectVisitor::~ShFindStretchPointWithRectVisitor() {

}


void ShFindStretchPointWithRectVisitor::Visit(ShLine *line) {

	int insideCount = 0;
	VertexPoint vertexPoint = VertexNothing;

	if (Math::CheckPointLiesInsideRect(line->GetStart(), this->topLeft, this->bottomRight, 0) == true) {
		insideCount++;
		vertexPoint = VertexStart;
	}

	if (Math::CheckPointLiesInsideRect(line->GetEnd(), this->topLeft, this->bottomRight, 0) == true) {
		insideCount++;
		vertexPoint = VertexEnd;
	}

	if (insideCount == 2)
		this->vertexPoint = VertexMid; // Move,
	else
		this->vertexPoint = vertexPoint;
	
}

void ShFindStretchPointWithRectVisitor::Visit(ShCircle *circle) {

	if (Math::CheckPointLiesInsideRect(circle->GetCenter(), this->topLeft, this->bottomRight, 0) == true)
		this->vertexPoint = VertexCenter;
	else
		this->vertexPoint = VertexNothing;
}

void ShFindStretchPointWithRectVisitor::Visit(ShArc *arc) {

	int insideCount = 0;
	VertexPoint vertexPoint = VertexNothing;

	if (Math::CheckPointLiesInsideRect(arc->GetStart(), this->topLeft, this->bottomRight, 0) == true) {
		insideCount++;
		vertexPoint = VertexStart;
	}
	
	if (Math::CheckPointLiesInsideRect(arc->GetEnd(), this->topLeft, this->bottomRight, 0) == true) {
		insideCount++;
		vertexPoint = VertexEnd;
	}

	if (insideCount == 2)
		this->vertexPoint = VertexCenter;
	else
		this->vertexPoint = vertexPoint;

}
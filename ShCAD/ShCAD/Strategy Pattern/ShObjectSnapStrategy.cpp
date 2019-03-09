

#include "ShObjectSnapStrategy.h"
#include <QMouseEvent>
#include <qpainter.h>

ShObjectSnapStrategy::ShObjectSnapStrategy(ShGraphicView *view)
	:view(view), isValid(false) {

}

ShObjectSnapStrategy::~ShObjectSnapStrategy() {

}


//////////////////////////////////////////////////////////////////////////


ShObjectSnapStrategy_Nothing::ShObjectSnapStrategy_Nothing(ShGraphicView *view)
	:ShObjectSnapStrategy(view) {

}

ShObjectSnapStrategy_Nothing::~ShObjectSnapStrategy_Nothing() {

}

bool ShObjectSnapStrategy_Nothing::FindSnapPoint(QMouseEvent *event) {
	
	
	return false;
}

QString ShObjectSnapStrategy_Nothing::GetCommandEditText() {

	return QString("");
}


///////////////////////////////////////////////////////////////////////////


#include "Visitor Pattern\ShSnapPointFinder.h"
#include "Interface\ShGraphicView.h"
#include "Visitor Pattern\ShFinder.h"
ShObjectSnapStrategy_EndPoint::ShObjectSnapStrategy_EndPoint(ShGraphicView *view)
	:ShObjectSnapStrategy(view) {

}

ShObjectSnapStrategy_EndPoint::~ShObjectSnapStrategy_EndPoint() {

}


bool ShObjectSnapStrategy_EndPoint::FindSnapPoint(QMouseEvent *event) {

	double x, y;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), x, y);

	ShEntity* entity = this->view->entityTable.FindEntity(x, y, this->view->GetZoomRate());

	if (entity == 0)
		return false;

	this->isValid = false;

	ShSnapPointFinder visitor(ObjectSnap::ObjectSnapEndPoint, x, y, this->snapX, this->snapY, this->isValid);
	entity->Accept(&visitor);

	//if (this->isValid == true) {
	//	drawType = (DrawType)(drawType | DrawType::DrawActionHandler | DrawType::DrawCaptureImage);
	//}

	return this->isValid;

}


void ShObjectSnapStrategy_EndPoint::Draw(QPainter *painter) {

	if (this->isValid == false)
		return;

	if (painter->isActive() == false)
		painter->begin(this->view);

	int dx, dy;
	this->view->ConvertEntityToDevice(this->snapX, this->snapY, dx, dy);
	
	QPen oldPen = painter->pen();
	QPen pen;
	pen.setWidth(2);
	pen.setColor(QColor(000, 204, 000));
	painter->setPen(pen);

	painter->drawRect(dx - 4, dy - 4, 8, 8);

	painter->setPen(oldPen);

}

QString ShObjectSnapStrategy_EndPoint::GetCommandEditText() {

	return QString("_end point ");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////


ShObjectSnapStrategy_MidPoint::ShObjectSnapStrategy_MidPoint(ShGraphicView *view)
	:ShObjectSnapStrategy(view) {

}

ShObjectSnapStrategy_MidPoint::~ShObjectSnapStrategy_MidPoint() {

}

bool ShObjectSnapStrategy_MidPoint::FindSnapPoint(QMouseEvent *event) {

	double x, y;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), x, y);

	ShEntity* entity = this->view->entityTable.FindEntity(x, y, this->view->GetZoomRate());

	if (entity == 0)
		return false;

	this->isValid = false;

	ShSnapPointFinder visitor(ObjectSnap::ObjectSnapMidPoint, x, y, this->snapX, this->snapY, this->isValid);
	entity->Accept(&visitor);

	

	return this->isValid;

}



void ShObjectSnapStrategy_MidPoint::Draw(QPainter *painter) {

	if (painter->isActive() == false)
		painter->begin(this->view);

	int dx, dy;
	this->view->ConvertEntityToDevice(this->snapX, this->snapY, dx, dy);

	QPen oldPen = painter->pen();
	QPen pen;
	pen.setWidth(2);
	pen.setColor(QColor(000, 204, 000));
	painter->setPen(pen);

	painter->drawLine(dx - 4, dy + 4, dx + 4, dy + 4);
	painter->drawLine(dx - 4, dy + 4, dx, dy - 4);
	painter->drawLine(dx + 4, dy + 4, dx, dy - 4);

	painter->setPen(oldPen);
}

QString ShObjectSnapStrategy_MidPoint::GetCommandEditText() {

	return QString("_mid point ");
}

///////////////////////////////////////////////////////////////////////////////////


ShObjectSnapStrategy_Perpendicular::ShObjectSnapStrategy_Perpendicular(ShGraphicView *view)
	:ShObjectSnapStrategy(view),perpendicularBaseEntity(0) {

}

ShObjectSnapStrategy_Perpendicular::~ShObjectSnapStrategy_Perpendicular() {

}


bool ShObjectSnapStrategy_Perpendicular::FindSnapPoint(QMouseEvent *event) {

	double x, y;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), x, y);

	ShEntity* entity = this->view->entityTable.FindEntity(x, y, this->view->GetZoomRate());

	if (entity == 0)
		return false;

	this->isValid = false;

	ShSnapPointFinder visitor(ObjectSnap::ObjectSnapPerpendicular, x, y, this->snapX, this->snapY, this->isValid);
	entity->Accept(&visitor);

	this->perpendicularBaseEntity = entity;


	return this->isValid;

}

bool ShObjectSnapStrategy_Perpendicular::FindSnapPoint(QMouseEvent *event, double perpendicularX, double perpendicularY) {

	double x, y;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), x, y);

	ShEntity* entity = this->view->entityTable.FindEntity(x, y, this->view->GetZoomRate());

	if (entity == 0)
		return false;

	this->isValid = false;

	ShSnapPointFinder visitor(ObjectSnap::ObjectSnapPerpendicular, x, y, this->snapX, this->snapY,
		this->isValid, perpendicularX, perpendicularY);

	entity->Accept(&visitor);



	return this->isValid;

}



void ShObjectSnapStrategy_Perpendicular::Draw(QPainter *painter) {
	
	if (painter->isActive() == false)
		painter->begin(this->view);

	int dx, dy;
	this->view->ConvertEntityToDevice(this->snapX, this->snapY, dx, dy);

	QPen oldPen = painter->pen();
	QPen pen;
	pen.setWidth(2);
	pen.setColor(QColor(000, 204, 000));
	painter->setPen(pen);

	painter->drawLine(dx - 4, dy + 4, dx + 4, dy + 4);
	painter->drawLine(dx - 4, dy + 4, dx - 4, dy - 4);
	painter->drawLine(dx - 4, dy, dx, dy);
	painter->drawLine(dx, dy + 4, dx, dy);

	painter->setPen(oldPen);
}

QString ShObjectSnapStrategy_Perpendicular::GetCommandEditText() {

	return QString("_perpendicular to ");
}
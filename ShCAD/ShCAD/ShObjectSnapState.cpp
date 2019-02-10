

#include "ShObjectSnapState.h"
#include <QMouseEvent>
#include <qpainter.h>
ShObjectSnapState::ShObjectSnapState(ShGraphicView *view)
	:view(view), isValid(false) {

}

ShObjectSnapState::~ShObjectSnapState() {

}


//////////////////////////////////////////////////////////////////////////


ShObjectSnapState_Nothing::ShObjectSnapState_Nothing(ShGraphicView *view)
	:ShObjectSnapState(view) {

}

ShObjectSnapState_Nothing::~ShObjectSnapState_Nothing() {

}


void ShObjectSnapState_Nothing::MousePressEvent(QMouseEvent *event) {

}

void ShObjectSnapState_Nothing::MouseMoveEvent(QMouseEvent *event, DrawType &drawType) {

	drawType = (DrawType)(drawType | DrawType::DrawCaptureImage);
}

///////////////////////////////////////////////////////////////////////////


#include "Visitor Pattern\ShSnapPointFinder.h"
#include "Interface\ShGraphicView.h"
#include "Visitor Pattern\ShFinder.h"
ShObjectSnapState_EndPoint::ShObjectSnapState_EndPoint(ShGraphicView *view)
	:ShObjectSnapState(view) {

}

ShObjectSnapState_EndPoint::~ShObjectSnapState_EndPoint() {

}

void ShObjectSnapState_EndPoint::MousePressEvent(QMouseEvent *event) {


}

void ShObjectSnapState_EndPoint::MouseMoveEvent(QMouseEvent *event, DrawType &drawType) {
	
	double x, y;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), x, y);

	ShEntity* entity = this->view->entityTable.FindEntity(x, y, this->view->GetZoomRate());

	if (entity == 0)
		return;

	this->isValid = false;

	ShSnapPointFinder visitor(ObjectSnap::ObjectSnapEndPoint, x, y, this->snapX, this->snapY, this->isValid);
	entity->Accept(&visitor);

	if (this->isValid == true) {
		drawType = (DrawType)(drawType | DrawType::DrawActionHandler | DrawType::DrawCaptureImage);
	}
	
}


void ShObjectSnapState_EndPoint::Draw(QPainter *painter) {

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

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////


ShObjectSnapState_MidPoint::ShObjectSnapState_MidPoint(ShGraphicView *view)
	:ShObjectSnapState(view) {

}

ShObjectSnapState_MidPoint::~ShObjectSnapState_MidPoint() {

}

void ShObjectSnapState_MidPoint::MousePressEvent(QMouseEvent *event) {

}

void ShObjectSnapState_MidPoint::MouseMoveEvent(QMouseEvent *event, DrawType &drawType) {

	double x, y;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), x, y);

	ShEntity* entity = this->view->entityTable.FindEntity(x, y, this->view->GetZoomRate());

	if (entity == 0)
		return;

	this->isValid = false;

	ShSnapPointFinder visitor(ObjectSnap::ObjectSnapMidPoint, x, y, this->snapX, this->snapY, this->isValid);
	entity->Accept(&visitor);

	if (this->isValid == true) {
		drawType = (DrawType)(drawType | DrawType::DrawActionHandler | DrawType::DrawCaptureImage);
	}

}


void ShObjectSnapState_MidPoint::Draw(QPainter *painter) {

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

}


#include "ShObjectSnapContext.h"
#include <QMouseEvent>
#include <qpainter.h>
#include "FactoryMethod\ShCreatorObjectSnapFactory.h"

ShObjectSnapContext::ShObjectSnapContext(ShGraphicView *view, ObjectSnap objectSnap) {

	this->objectSanpState = ShCreatorObjectSnapFactory::Create(objectSnap, view);
}

ShObjectSnapContext::~ShObjectSnapContext() {

	if (this->objectSanpState != 0)
		delete this->objectSanpState;

}

bool ShObjectSnapContext::FindSnapPoint(QMouseEvent* event) {

	return this->objectSanpState->FindSnapPoint(event);
}

ObjectSnap ShObjectSnapContext::GetType() {

	return this->objectSanpState->GetType();
}

void ShObjectSnapContext::Draw(QPainter *painter) {

	this->objectSanpState->Draw(painter);
}

double ShObjectSnapContext::GetSnapX() {

	return this->objectSanpState->GetSnapX();
}

double ShObjectSnapContext::GetSnapY() {

	return this->objectSanpState->GetSnapY();
}

/////////////////////////////////////////////////////////////////////////

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

bool ShObjectSnapState_Nothing::FindSnapPoint(QMouseEvent *event) {
	
	
	return false;
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


bool ShObjectSnapState_EndPoint::FindSnapPoint(QMouseEvent *event) {

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

bool ShObjectSnapState_MidPoint::FindSnapPoint(QMouseEvent *event) {

	double x, y;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), x, y);

	ShEntity* entity = this->view->entityTable.FindEntity(x, y, this->view->GetZoomRate());

	if (entity == 0)
		return false;

	this->isValid = false;

	ShSnapPointFinder visitor(ObjectSnap::ObjectSnapMidPoint, x, y, this->snapX, this->snapY, this->isValid);
	entity->Accept(&visitor);

	//if (this->isValid == true) {
	//	drawType = (DrawType)(drawType | DrawType::DrawActionHandler | DrawType::DrawCaptureImage);
	//}

	return this->isValid;

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
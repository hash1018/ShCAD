

#include "ShSubActionHandler.h"
#include "ActionHandler\ShActionHandler.h"
#include <qdebug.h>
ShSubActionInfo::ShSubActionInfo()
	:drawType(DrawType::DrawNone), isOrthogonalModeOn(false), isSnapModeOn(false),
	isSnapPointClicked(false), clickedObjectSnap(ObjectSnap::ObjectSnapNothing) {

}

ShSubActionInfo::ShSubActionInfo(DrawType drawType)
	: drawType(drawType), isOrthogonalModeOn(false), isSnapModeOn(false), isSnapPointClicked(false),
	clickedObjectSnap(ObjectSnap::ObjectSnapNothing) {

}

ShSubActionInfo::~ShSubActionInfo() {

}



ShSubActionHandler::ShSubActionHandler(ShActionHandler *actionHandler, ShGraphicView *view)
	:actionHandler(actionHandler), view(view), parent(0) {


}




ShSubActionHandler::ShSubActionHandler(const ShSubActionHandler& other)
	:actionHandler(other.actionHandler), view(other.view) {

}

ShSubActionHandler::~ShSubActionHandler() {


}

/////////////////////////////////////////////////////////////////////////////////////////////////////


ShSubActionDecorator::ShSubActionDecorator(ShActionHandler *actionHandler, ShGraphicView *view)
	:ShSubActionHandler(actionHandler, view), child(0) {

}

ShSubActionDecorator::ShSubActionDecorator(const ShSubActionDecorator& other)
	: ShSubActionHandler(other), child(other.child->Clone()) {

	this->child->SetParent(this);
}


ShSubActionDecorator::~ShSubActionDecorator() {

	if (this->child != 0)
		delete this->child;

}

void ShSubActionDecorator::SetChild(ShSubActionHandler *newChild) {

	if (this->child != 0)
		delete this->child;

	newChild->SetParent(this);
	this->child = newChild;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "FactoryMethod\ShCreatorObjectSnapFactory.h"
#include "State Pattern\ShObjectSnapState.h"
ShSubActionDecorator_SnapMode::ShSubActionDecorator_SnapMode(ShActionHandler *actionHandler, ShGraphicView *view,
	ObjectSnap objectSnap)
	:ShSubActionDecorator(actionHandler, view), objectSnap(objectSnap) {

	this->objectSnapState = ShCreatorObjectSnapFactory::Create(objectSnap, view);
}

ShSubActionDecorator_SnapMode::ShSubActionDecorator_SnapMode(const ShSubActionDecorator_SnapMode& other)
	: ShSubActionDecorator(other), objectSnap(other.objectSnap) {

	this->objectSnapState = ShCreatorObjectSnapFactory::Create(objectSnap, view);
}


ShSubActionDecorator_SnapMode::~ShSubActionDecorator_SnapMode() {

	if (this->objectSnapState != 0)
		delete this->objectSnapState;
}


void ShSubActionDecorator_SnapMode::MousePressEvent(QMouseEvent *event, ShSubActionInfo &info) {
	
	if (this->child == 0) {
		qDebug("child is a null pointer.");
		return;
	}

	if (this->objectSnapState->FindSnapPoint(event) == false) {
	
		return;
	}

	info.point.x = this->objectSnapState->GetSnapX();
	info.point.y = this->objectSnapState->GetSnapY();
	info.isSnapPointClicked = true;
	info.isSnapModeOn = true;
	info.clickedObjectSnap = this->objectSnapState->GetType();

	this->child->MousePressEvent(event, info);

	if (this->parent == 0)
		this->actionHandler->ChangeSubActionHandler(this->child->Clone());
	else
		this->parent->SetChild(this->child->Clone());


}

void ShSubActionDecorator_SnapMode::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info) {

	if (this->child == 0) {
		qDebug("child is a null pointer.");
		return;
	}

	if (this->objectSnapState->FindSnapPoint(event) == true) {
		info.drawType = (DrawType)(info.drawType | DrawType::DrawActionHandler | DrawType::DrawCaptureImage);
		info.isSnapModeOn = true;
	}

	this->child->MouseMoveEvent(event, info);

}


void ShSubActionDecorator_SnapMode::Draw(QPainter *painter) {

	this->objectSnapState->Draw(painter);
}

void ShSubActionDecorator_SnapMode::Decorate(ShSubActionDecorator *decorator) {
	
	if (decorator == 0) {
		qDebug("variable is a null pointer.");
		return;
	}

	if (dynamic_cast<ShSubActionDecorator_SnapMode*>(decorator)) {

		delete decorator;
		this->actionHandler->ChangeSubActionHandler(this->child->Clone());
	}
	else {

		decorator->SetChild(this->Clone());
		this->actionHandler->ChangeSubActionHandler(decorator);
	}

}


ShSubActionDecorator_SnapMode* ShSubActionDecorator_SnapMode::Clone() {

	return new ShSubActionDecorator_SnapMode(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////

/*

ShSubActionDecorator_SnapMode_Perpendicular::ShSubActionDecorator_SnapMode_Perpendicular(ShActionHandler *actionHandler,
	ShGraphicView *view, ObjectSnap objectSnap)
	:ShSubActionDecorator_SnapMode(actionHandler, view, objectSnap) {

}

ShSubActionDecorator_SnapMode_Perpendicular::ShSubActionDecorator_SnapMode_Perpendicular
(const ShSubActionDecorator_SnapMode_Perpendicular& other)
	: ShSubActionDecorator_SnapMode(other) {

}


ShSubActionDecorator_SnapMode_Perpendicular::~ShSubActionDecorator_SnapMode_Perpendicular() {

}

void ShSubActionDecorator_SnapMode_Perpendicular::MousePressEvent(QMouseEvent *event, ShSubActionInfo &info) {

	if (this->child == 0) {
		qDebug("child is a null pointer.");
		return;
	}

	//in this case, 




}

void ShSubActionDecorator_SnapMode_Perpendicular::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info) {
	
	if (this->child == 0) {
		qDebug("child is a null pointer.");
		return;
	}





}


ShSubActionDecorator_SnapMode_Perpendicular* ShSubActionDecorator_SnapMode_Perpendicular::Clone() {

	return new ShSubActionDecorator_SnapMode_Perpendicular(*this);
}

*/

///////////////////////////////////////////////////////////////////////////////////////////////////////


ShSubActionDecorator_Orthogonal::ShSubActionDecorator_Orthogonal(ShActionHandler *actionHandler, ShGraphicView *view)
	:ShSubActionDecorator(actionHandler, view) {

	this->actionHandler->ApplyOrthogonalShape(true);
}

ShSubActionDecorator_Orthogonal::ShSubActionDecorator_Orthogonal(const ShSubActionDecorator_Orthogonal& other)
	: ShSubActionDecorator(other) {
	this->actionHandler->ApplyOrthogonalShape(true);
}

ShSubActionDecorator_Orthogonal::~ShSubActionDecorator_Orthogonal() {

}


void ShSubActionDecorator_Orthogonal::MousePressEvent(QMouseEvent *event, ShSubActionInfo &info) {
	
	if (this->child == 0) {
		qDebug("child is a null pointer.");
		return;
	}

	info.isOrthogonalModeOn = true;

	this->child->MousePressEvent(event, info);




}

void ShSubActionDecorator_Orthogonal::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info) {

	if (this->child == 0) {
		qDebug("child is a null pointer.");
		return;
	}

	info.isOrthogonalModeOn = true;
	this->child->MouseMoveEvent(event, info);

}

void ShSubActionDecorator_Orthogonal::Draw(QPainter *painter) {

	this->child->Draw(painter);
}

void ShSubActionDecorator_Orthogonal::Decorate(ShSubActionDecorator *decorator) {

	if (decorator == 0) {
		qDebug("variable is a null pointer.");
		return;
	}

	if (dynamic_cast<ShSubActionDecorator_Orthogonal*>(decorator)) {

		delete decorator;
		this->actionHandler->ApplyOrthogonalShape(false);
		this->actionHandler->ChangeSubActionHandler(this->child->Clone());

	}
	else if (dynamic_cast<ShSubActionDecorator_SnapMode*>(decorator)) {

		if (dynamic_cast<ShSubActionDecorator_SnapMode*>(this->child)) {

			delete decorator;
			this->SetChild(dynamic_cast<ShSubActionDecorator_SnapMode*>(this->child)->GetChild()->Clone());
		}
		else {

			decorator->SetChild(this->child->Clone());
			this->SetChild(decorator);
		}

	}
}


ShSubActionDecorator_Orthogonal* ShSubActionDecorator_Orthogonal::Clone() {

	return new ShSubActionDecorator_Orthogonal(*this);
}
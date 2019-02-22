

#include "ShSubActionHandler.h"
#include "ActionHandler\ShActionHandler.h"
#include <qdebug.h>
#include "ShNotifyEvent.h"

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


ShSubActionHandler::~ShSubActionHandler() {


}

/////////////////////////////////////////////////////////////////////////////////////////////////////

ShSubIndividualAction::ShSubIndividualAction(ShActionHandler *actionHandler, ShGraphicView *view)
	:ShSubActionHandler(actionHandler, view) {

}


ShSubIndividualAction::~ShSubIndividualAction() {

}


void ShSubIndividualAction::Decorate(ShSubActionDecorator *decorator) {

	decorator->SetChild(this);
	this->actionHandler->ChangeSubActionHandler(decorator);
	decorator->AddCommandEditHeadTitle();
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////


ShSubActionDecorator::ShSubActionDecorator(ShActionHandler *actionHandler, ShGraphicView *view)
	:ShSubActionHandler(actionHandler, view), child(0) {

}


ShSubActionDecorator::~ShSubActionDecorator() {

	if (this->child != 0)
		delete this->child;

}

void ShSubActionDecorator::SetChild(ShSubActionHandler *newChild) {

	if (newChild != 0)
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
		this->UpdateCommandListFail();
		return;
	}

	info.point.x = this->objectSnapState->GetSnapX();
	info.point.y = this->objectSnapState->GetSnapY();
	info.isSnapPointClicked = true;
	info.isSnapModeOn = true;
	info.clickedObjectSnap = this->objectSnapState->GetType();

	this->child->MousePressEvent(event, info);

	if (this->parent == 0)
		this->actionHandler->ChangeSubActionHandler(this->child);
	else
		this->parent->SetChild(this->child);

	
	this->child = 0;
	delete this;
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
		this->actionHandler->ChangeSubActionHandler(this->child);
		
		ShUpdateListTextEvent event("");
		this->view->Notify(&event);

		ShUpdateListTextEvent event2("Invalid point.", ShUpdateListTextEvent::UpdateType::TextWithoutAnything);
		this->view->Notify(&event2);

		this->actionHandler->SetActionHeadTitle();
		

		this->child = 0;
		delete this;
	}
	else {

		decorator->SetChild(this);
		decorator->AddCommandEditHeadTitle();
		this->actionHandler->ChangeSubActionHandler(decorator);
	}

}



void ShSubActionDecorator_SnapMode::AddCommandEditHeadTitle() {

	QString headTitle = this->objectSnapState->GetCommandEditText();
	ShUpdateCommandEditHeadTitle event(headTitle, ShUpdateCommandEditHeadTitle::UpdateType::AddHeadTitleToCurrent);
	this->view->Notify(&event);

}


void ShSubActionDecorator_SnapMode::UpdateCommandListFail() {

	ShUpdateListTextEvent event2("Invalid point.",ShUpdateListTextEvent::UpdateType::TextWithoutAnything);
	this->view->Notify(&event2);


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
		this->actionHandler->ChangeSubActionHandler(this->child);

		this->child = 0;
		delete this;

	}
	else if (dynamic_cast<ShSubActionDecorator_SnapMode*>(decorator)) {

		if (dynamic_cast<ShSubActionDecorator_SnapMode*>(this->child)) {
			
			
			delete decorator;
		
			ShSubActionDecorator_SnapMode *prevChild = dynamic_cast<ShSubActionDecorator_SnapMode*>(this->child);
			
			this->SetChild(prevChild->GetChild());
			
			this->actionHandler->SetActionHeadTitle();
			prevChild->UpdateCommandListFail();

			prevChild->SetChild(0);
			delete prevChild;


			
			
		}
		else {

			decorator->SetChild(this->child);
			decorator->AddCommandEditHeadTitle();
			this->SetChild(decorator);
		}

	}
}




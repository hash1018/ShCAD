
#include "ShActionHandlerDecorator.h"
#include <qpainter.h>
#include <QMouseEvent>
#include "Visitor Pattern\ShSnapPointFinder.h"
#include "ShMath.h"
#include "ShNotifyEvent.h"
ShActionHandlerDecorator::ShActionHandlerDecorator(ShGraphicView *graphicView, ShActionHandler *actionHandler,
	ShActionHandlerDecorator *child)
	:graphicView(graphicView), actionHandler(actionHandler), child(child), parent(0) {

	if (child != 0)
		child->SetParent(this);

}

ShActionHandlerDecorator::~ShActionHandlerDecorator() {

	if (this->child != 0)
		delete this->child;
}

void ShActionHandlerDecorator::MousePressEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData) {

	if (this->child != 0)
		this->child->MousePressEvent(event, data, decoratorData);
	else
		this->actionHandler->MousePressEvent(event, data);
}

void ShActionHandlerDecorator::MouseMoveEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData) {

	if (this->child != 0)
		this->child->MouseMoveEvent(event, data, decoratorData);
	else
		this->actionHandler->MouseMoveEvent(event, data);
}

void ShActionHandlerDecorator::KeyPressEvent(QKeyEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData) {

	if (this->child != 0)
		this->child->KeyPressEvent(event, data, decoratorData);
	else
		this->actionHandler->KeyPressEvent(event, data);
}

void ShActionHandlerDecorator::MouseReleaseEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData) {

	if (this->child != 0)
		this->child->MouseReleaseEvent(event, data, decoratorData);
	else
		this->actionHandler->MouseReleaseEvent(event, data);
}

ActionType ShActionHandlerDecorator::GetType() {

	if (this->child != 0)
		return this->child->GetType();
	
	return this->actionHandler->GetType();
}

void ShActionHandlerDecorator::Draw(QPainter *painter) {

	if (this->child != 0)
		this->child->Draw(painter);
	else
		this->actionHandler->Draw(painter);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


ShActionHandlerDecorator_Default::ShActionHandlerDecorator_Default(ShGraphicView *graphicView, ShActionHandler *actionHandler,
	ShActionHandlerDecorator *child)
	:ShActionHandlerDecorator(graphicView, actionHandler, child) {

}

ShActionHandlerDecorator_Default::~ShActionHandlerDecorator_Default() {

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShActionHandlerDecorator_Draft::ShActionHandlerDecorator_Draft(ShGraphicView *graphicView, ShActionHandler *actionHandler,
	ShActionHandlerDecorator *child)
	:ShActionHandlerDecorator(graphicView, actionHandler, child) {

}

ShActionHandlerDecorator_Draft::~ShActionHandlerDecorator_Draft() {


}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Strategy Pattern\ShObjectSnapStrategy.h"
#include "FactoryMethod\ShCreatorObjectSnapFactory.h"
ShActionHandlerDecorator_DisposableSnap::ShActionHandlerDecorator_DisposableSnap(ShGraphicView *graphicView,
	ShActionHandler *actionHandler, ObjectSnap objectSnap, ShActionHandlerDecorator *child)
	:ShActionHandlerDecorator_Draft(graphicView, actionHandler, child) {

	this->objectSnapStrategy = ShCreatorObjectSnapFactory::Create(objectSnap, graphicView);
}

ShActionHandlerDecorator_DisposableSnap::~ShActionHandlerDecorator_DisposableSnap() {

	if (this->objectSnapStrategy != 0)
		delete this->objectSnapStrategy;

}

void ShActionHandlerDecorator_DisposableSnap::KeyPressEvent(QKeyEvent *event, ShActionData& data,
	ShActionDecoratorData &decoratorData) {

	ShActionHandlerDecorator_Draft::KeyPressEvent(event, data, decoratorData);
}

void ShActionHandlerDecorator_DisposableSnap::Draw(QPainter *painter) {

	this->objectSnapStrategy->Draw(painter);

	ShActionHandlerDecorator_Draft::Draw(painter);
}

void ShActionHandlerDecorator_DisposableSnap::SendFailedMessage(ObjectSnap objectSnap) {
	
	ShUpdateListTextEvent event("");
	this->graphicView->Notify(&event);

	ShUpdateListTextEvent event2("No snap point found.",
		ShUpdateListTextEvent::UpdateType::TextWithoutAnything);
	this->graphicView->Notify(&event2);

	ShUpdateCommandEditHeadTitle event4(this->actionHandler->GetActionHeadTitle());
	this->graphicView->Notify(&event4);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

ShActionHandlerDecorator_DisposableSnap_General::ShActionHandlerDecorator_DisposableSnap_General(ShGraphicView *graphicView,
	ShActionHandler *actionHandler, ObjectSnap objectSnap, ShActionHandlerDecorator *child)
	:ShActionHandlerDecorator_DisposableSnap(graphicView, actionHandler, objectSnap, child) {

}

ShActionHandlerDecorator_DisposableSnap_General::~ShActionHandlerDecorator_DisposableSnap_General() {

}

void ShActionHandlerDecorator_DisposableSnap_General::MousePressEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData) {

	ShAllowedDraftData allowedDraftData;
	this->actionHandler->IsAllowedDraftOperation(allowedDraftData);

	if (allowedDraftData.AllowSnap() == true) {
		
		if (this->objectSnapStrategy->FindSnapPoint(event) == false) {
			
			data.SetAllowActionHandler(false);
			this->SendFailedMessage(this->objectSnapStrategy->GetType());

			return;
		}
			
		data.SetPoint(ShPoint3d(this->objectSnapStrategy->GetSnapX(), this->objectSnapStrategy->GetSnapY()));
		decoratorData.SetSnapClicked(true);
	}
	
	ShActionHandlerDecorator_DisposableSnap::MousePressEvent(event, data, decoratorData);

}

void ShActionHandlerDecorator_DisposableSnap_General::MouseMoveEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData) {

	ShAllowedDraftData allowedDraftData;
	this->actionHandler->IsAllowedDraftOperation(allowedDraftData);

	if (allowedDraftData.AllowSnap() == true) {
		if (this->objectSnapStrategy->FindSnapPoint(event) == true)
			data.AppendDrawType((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			data.AppendDrawType((DrawType)DrawType::DrawCaptureImage);
	}


	ShActionHandlerDecorator_DisposableSnap::MouseMoveEvent(event, data, decoratorData);

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


ShActionHandlerDecorator_DisposableSnap_Perpendicular::ShActionHandlerDecorator_DisposableSnap_Perpendicular
(ShGraphicView *graphicView, ShActionHandler *actionHandler, ShActionHandlerDecorator *child)
	:ShActionHandlerDecorator_DisposableSnap(graphicView, actionHandler, ObjectSnap::ObjectSnapPerpendicular, child) {


}

ShActionHandlerDecorator_DisposableSnap_Perpendicular::~ShActionHandlerDecorator_DisposableSnap_Perpendicular() {

}

void ShActionHandlerDecorator_DisposableSnap_Perpendicular::MousePressEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData) {
	
	ShAllowedDraftData allowedDraftData;
	this->actionHandler->IsAllowedDraftOperation(allowedDraftData);

	if (allowedDraftData.AllowSnap() == true) {

		ShObjectSnapStrategy_Perpendicular *strategy = 
			dynamic_cast<ShObjectSnapStrategy_Perpendicular*>(this->objectSnapStrategy);
		
		if (strategy->FindSnapPoint(event,allowedDraftData.GetSnapBasePoint().x,
			allowedDraftData.GetSnapBasePoint().y) == false) {
			
			data.SetAllowActionHandler(false);
			this->SendFailedMessage(this->objectSnapStrategy->GetType());

			return;
		}

		data.SetPoint(ShPoint3d(this->objectSnapStrategy->GetSnapX(), this->objectSnapStrategy->GetSnapY()));
		decoratorData.SetSnapClicked(true);
	}

	ShActionHandlerDecorator_DisposableSnap::MousePressEvent(event, data, decoratorData);

}

void ShActionHandlerDecorator_DisposableSnap_Perpendicular::MouseMoveEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData) {

	ShAllowedDraftData allowedDraftData;
	this->actionHandler->IsAllowedDraftOperation(allowedDraftData);

	if (allowedDraftData.AllowSnap() == true) {

		ShObjectSnapStrategy_Perpendicular *strategy =
			dynamic_cast<ShObjectSnapStrategy_Perpendicular*>(this->objectSnapStrategy);

		if (strategy->FindSnapPoint(event, allowedDraftData.GetSnapBasePoint().x,
			allowedDraftData.GetSnapBasePoint().y) == true)
			data.AppendDrawType((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			data.AppendDrawType((DrawType)DrawType::DrawCaptureImage);
	}

	ShActionHandlerDecorator_DisposableSnap::MouseMoveEvent(event, data, decoratorData);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ActionHandler\DrawAction\ShDrawLineAction.h"
ShDrawLineAction_DisposableSnap_Perpendicular_PickedNothing::ShDrawLineAction_DisposableSnap_Perpendicular_PickedNothing
(ShGraphicView *graphicView, ShActionHandler *actionHandler, ShActionHandlerDecorator *child)
	:ShActionHandlerDecorator_DisposableSnap(graphicView, actionHandler, ObjectSnap::ObjectSnapPerpendicular, child) {

}

ShDrawLineAction_DisposableSnap_Perpendicular_PickedNothing::~ShDrawLineAction_DisposableSnap_Perpendicular_PickedNothing() {

}


void ShDrawLineAction_DisposableSnap_Perpendicular_PickedNothing::MousePressEvent(QMouseEvent *event,
	ShActionData& data, ShActionDecoratorData &decoratorData) {

	ShAllowedDraftData allowedDraftData;
	this->actionHandler->IsAllowedDraftOperation(allowedDraftData);

	if (allowedDraftData.AllowSnap() == true) {

		if (this->objectSnapStrategy->FindSnapPoint(event) == false) {
			
			data.SetAllowActionHandler(false);
			this->SendFailedMessage(this->objectSnapStrategy->GetType());

			return;
		}

		data.SetPoint(ShPoint3d(this->objectSnapStrategy->GetSnapX(), this->objectSnapStrategy->GetSnapY()));
		decoratorData.SetSnapClicked(true);
	}

	ShActionHandlerDecorator_DisposableSnap::MousePressEvent(event, data, decoratorData);

	ShDrawLineAction *drawLineAction = dynamic_cast<ShDrawLineAction*>(this->actionHandler);

	drawLineAction->ChangeDrawMethod(ShDrawLineAction::DrawMethod::Perpendicular);
	ShDrawLineMethod_Perpendicular* drawLineMethod =
		dynamic_cast<ShDrawLineMethod_Perpendicular*>(drawLineAction->GetDrawLineMethod());


	ShObjectSnapStrategy_Perpendicular *strategy = 
		dynamic_cast<ShObjectSnapStrategy_Perpendicular*>(this->objectSnapStrategy);

	drawLineMethod->SetPerpendicularBaseEntity(strategy->PerpendicularBaseEntity());

}


void ShDrawLineAction_DisposableSnap_Perpendicular_PickedNothing::MouseMoveEvent(QMouseEvent *event, 
	ShActionData& data, ShActionDecoratorData &decoratorData) {

	ShAllowedDraftData allowedDraftData;
	this->actionHandler->IsAllowedDraftOperation(allowedDraftData);

	if (allowedDraftData.AllowSnap() == true) {
		if (this->objectSnapStrategy->FindSnapPoint(event) == true)
			data.AppendDrawType((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			data.AppendDrawType((DrawType)DrawType::DrawCaptureImage);
	}

	ShActionHandlerDecorator_DisposableSnap::MouseMoveEvent(event, data, decoratorData);

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


ShDrawLineAction_DisposableSnap_Per_Per::ShDrawLineAction_DisposableSnap_Per_Per(ShGraphicView *graphicView,
	ShActionHandler *actionHandler, ShActionHandlerDecorator *child)
	:ShActionHandlerDecorator_DisposableSnap(graphicView, actionHandler, ObjectSnap::ObjectSnapPerpendicular, child) {

}

ShDrawLineAction_DisposableSnap_Per_Per::~ShDrawLineAction_DisposableSnap_Per_Per() {

}

#include "Visitor Pattern\ShLineBothPerpendicularVisitor.h"
void ShDrawLineAction_DisposableSnap_Per_Per::MousePressEvent(QMouseEvent *event, ShActionData& data,
	ShActionDecoratorData &decoratorData) {

	ShAllowedDraftData allowedDraftData;
	this->actionHandler->IsAllowedDraftOperation(allowedDraftData);

	if (allowedDraftData.AllowSnap() == true) {
		if (this->objectSnapStrategy->FindSnapPoint(event) == false) {
			
			data.SetAllowActionHandler(false);
			this->SendFailedMessage(this->objectSnapStrategy->GetType());

			return;
		}
		decoratorData.SetSnapClicked(true);
	}

	ShDrawLineAction *drawLineAction = dynamic_cast<ShDrawLineAction*>(this->actionHandler);
	ShObjectSnapStrategy_Perpendicular *strategy =
		dynamic_cast<ShObjectSnapStrategy_Perpendicular*>(this->objectSnapStrategy);
	ShDrawLineMethod_Perpendicular *drawLineMethod =
		dynamic_cast<ShDrawLineMethod_Perpendicular*>(drawLineAction->GetDrawLineMethod());

	//find out whether both base entities are parellel
	bool isValid = false;
	ShPoint3d point;

	//in case both entites are line and line ,
	//point should be below.
	//in the visitor class just check if two lines are parallel.
	point.x = strategy->GetSnapX();
	point.y = strategy->GetSnapY();

	ShLineBothPerpendicularVisitor visitor(strategy->PerpendicularBaseEntity(), point, isValid);
	drawLineMethod->GetPerpendicularBaseEntity()->Accept(&visitor);

	if (isValid == true) {
		data.SetPoint(point);
		ShActionHandlerDecorator_DisposableSnap::MousePressEvent(event, data, decoratorData);
	}
	else {
		//Fail message.

		ShUpdateListTextEvent event2("");
		this->graphicView->Notify(&event2);

		ShUpdateListTextEvent event3("Line specification not valid.",
			ShUpdateListTextEvent::UpdateType::TextWithoutAnything);
		this->graphicView->Notify(&event3);

		ShUpdateCommandEditHeadTitle event4(this->actionHandler->GetActionHeadTitle());
		this->graphicView->Notify(&event4);
	}

}

void ShDrawLineAction_DisposableSnap_Per_Per::MouseMoveEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData) {

	ShAllowedDraftData allowedDraftData;
	this->actionHandler->IsAllowedDraftOperation(allowedDraftData);

	if (allowedDraftData.AllowSnap() == true) {
		if (this->objectSnapStrategy->FindSnapPoint(event) == true)
			data.AppendDrawType((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			data.AppendDrawType((DrawType)DrawType::DrawCaptureImage);
	}

	ShActionHandlerDecorator_DisposableSnap::MouseMoveEvent(event, data, decoratorData);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShActionHandlerDecorator_Orthogonal::ShActionHandlerDecorator_Orthogonal(ShGraphicView *graphicView,
	ShActionHandler *actionHandler, ShActionHandlerDecorator *child)
	:ShActionHandlerDecorator_Draft(graphicView, actionHandler, child) {

}

ShActionHandlerDecorator_Orthogonal::~ShActionHandlerDecorator_Orthogonal() {

}


void ShActionHandlerDecorator_Orthogonal::MousePressEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData) {

	ShAllowedDraftData allowedDraftData;
	this->actionHandler->IsAllowedDraftOperation(allowedDraftData);

	if (allowedDraftData.AllowOrthogonal() == true) {
		ShPoint3d basePoint;
		ShPoint3d orth, mouse;
		this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), mouse.x, mouse.y);

		if (decoratorData.SnapClicked() == false) {

			basePoint = allowedDraftData.GetOrthogonalBasePoint();
			this->GetOrthogonal(basePoint.x, basePoint.y, mouse.x, mouse.y, orth.x, orth.y);
			data.SetPoint(orth);
		}
		else {

			basePoint = data.GetPoint();
			this->GetOrthogonal(basePoint.x, basePoint.y, mouse.x, mouse.y, orth.x, orth.y);
			data.SetNextPoint(orth);
		}

	}


	ShActionHandlerDecorator_Draft::MousePressEvent(event, data, decoratorData);
}

void ShActionHandlerDecorator_Orthogonal::MouseMoveEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData) {

	ShAllowedDraftData allowedDraftData;
	this->actionHandler->IsAllowedDraftOperation(allowedDraftData);

	if (allowedDraftData.AllowOrthogonal() == true) {
	
		ShPoint3d basePoint = allowedDraftData.GetOrthogonalBasePoint();
		ShPoint3d orth, mouse;
		this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), mouse.x, mouse.y);
		this->GetOrthogonal(basePoint.x, basePoint.y, mouse.x, mouse.y, orth.x, orth.y);
		data.SetPoint(orth);
	}


	ShActionHandlerDecorator_Draft::MouseMoveEvent(event, data, decoratorData);
}

void ShActionHandlerDecorator_Orthogonal::KeyPressEvent(QKeyEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData) {

	ShActionHandlerDecorator_Draft::KeyPressEvent(event, data, decoratorData);
}


void ShActionHandlerDecorator_Orthogonal::GetOrthogonal(double x, double y, double mouseX, double mouseY, double &orthX, double &orthY) {

	double disVertical, disHorizontal;

	disVertical = Math::GetDistance(x, y, x, mouseY);

	disHorizontal = Math::GetDistance(x, y, mouseX, y);

	if (Math::Compare(disVertical, disHorizontal) == 1) {

		orthX = x;
		orthY = mouseY;

	}
	else {

		orthX = mouseX;
		orthY = y;
	}
}
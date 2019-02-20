
/*--
**
**   This file is part of the ShCAD project, a 2D CAD Program
**
**    Copyright (C) 2019, Seungho Ha  (sh.ha1018@gmail.com)
**
**
**   This program is free software; you can redistribute it and/or modify it
**   under the terms of the GNU Lesser General Public License as published by
**   the Free Software Foundation; either version 2.1 of the License, or (at
**   your option) any later version.
**
**   This program is distributed in the hope that it will be useful, but
**   WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
**   General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
**
**
--*/

#include "ShDrawLineAction.h"
#include <QMouseEvent>
#include "ShNotifyEvent.h"
#include "Entity\Leaf\ShLine.h"


ShDrawLineAction::ShDrawLineAction(ShGraphicView *graphicView)
	:ShDrawAction(graphicView) {

	this->status = PickedNothing;
	ShUpdateListTextEvent event("_Line", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	ShUpdateCommandEditHeadTitle event2("Line >> Specify first point: ");
	this->graphicView->Notify(&event2);
	
	
	
	this->subActionHandler = new ShDrawLineProxy(this, this->graphicView);
}

ShDrawLineAction::~ShDrawLineAction() {

}


void ShDrawLineAction::MousePressEvent(QMouseEvent *event) {

	ShSubActionInfo info;
	this->subActionHandler->MousePressEvent(event, info);

}

void ShDrawLineAction::MouseMoveEvent(QMouseEvent *event) {

	ShSubActionInfo info(DrawType::DrawCaptureImage);
	this->subActionHandler->MouseMoveEvent(event, info);

	this->graphicView->update(info.GetDrawType());
}

void ShDrawLineAction::KeyPressEvent(QKeyEvent *event) {

	if (event->key() == Qt::Key::Key_Escape) {
	
		this->graphicView->ChangeCurrentAction(ActionType::ActionDefault);
	}

	else if (event->key() == Qt::Key::Key_F8) {
	
		this->SetOrthogonal();
	}


	else {
	
		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}

}


void ShDrawLineAction::SetObjectSnap(ObjectSnap objectSnap) {

	if (objectSnap == ObjectSnap::ObjectSnapPerpendicular)
		this->subActionHandler->Decorate(new ShSubLineDecorator_SnapMode_Perpendicular(this, this->graphicView,
			objectSnap));
	else
		this->subActionHandler->Decorate(new ShSubActionDecorator_SnapMode(this, this->graphicView, objectSnap));
	
}


ActionType ShDrawLineAction::GetType() {

	return ActionType::ActionDrawLine;
}

void ShDrawLineAction::Draw(QPainter *painter) {

	this->subActionHandler->Draw(painter);
}


void ShDrawLineAction::ApplyOrthogonalShape(bool isOrthogonalModeOn) {

	if (this->drawMethod == ShDrawLineAction::DrawMethod::Perpendicular)
		return;


	if (isOrthogonalModeOn == true) {
		if (this->status == ShDrawLineAction::Status::PickedStart) {
			ShLine *line = dynamic_cast<ShLine*>((*this->graphicView->preview.Begin()));
			this->ApplyLineEndPointToOrthogonal(line);
			this->graphicView->update((DrawType)(DrawCaptureImage | DrawPreviewEntities | DrawActionHandler));
		}
	}
	else {
		if (this->status == ShDrawLineAction::Status::PickedStart) {
			ShLine *line = dynamic_cast<ShLine*>((*this->graphicView->preview.Begin()));
			this->ApplyLineEndPointToMouse(line);
			this->graphicView->update((DrawType)(DrawCaptureImage | DrawPreviewEntities | DrawActionHandler));
		}
	}
}

void ShDrawLineAction::ApplyLineEndPointToOrthogonal(ShLine *line) {
	
	ShLineData data = line->GetData();
	ShPoint3d orth, mouse;
	QPoint pos = this->graphicView->mapFromGlobal(QCursor::pos());

	this->graphicView->ConvertDeviceToEntity(pos.x(), pos.y(), mouse.x, mouse.y);
	this->GetOrthogonal(data.start.x, data.start.y, mouse.x, mouse.y, orth.x, orth.y);

	data.end = orth;
	line->SetData(data);

}

void ShDrawLineAction::ApplyLineEndPointToMouse(ShLine *line) {

	ShLineData data = line->GetData();
	ShPoint3d mouse;

	QPoint pos = this->graphicView->mapFromGlobal(QCursor::pos());
	this->graphicView->ConvertDeviceToEntity(pos.x(), pos.y(), mouse.x, mouse.y);

	data.end = mouse;
	line->SetData(data);
}

void ShDrawLineAction::SetActionHeadTitle() {

	if (this->status == Status::PickedNothing) {
		ShUpdateCommandEditHeadTitle event("Line >> Specify first point: ");
		this->graphicView->Notify(&event);
	}
	else {
		ShUpdateCommandEditHeadTitle event("Line >> Specify next point: ");
		this->graphicView->Notify(&event);
	}


}

//////////////////////////////////////////////////////////////////////////////////////////////////////


ShDrawLineProxy::ShDrawLineProxy(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:ShSubIndividualAction(drawLineAction, view) {

	this->drawLineMethod = new ShDrawLineMethod_Default(drawLineAction, view);
}

ShDrawLineProxy::ShDrawLineProxy(const ShDrawLineProxy& other)
	: ShSubIndividualAction(other), drawLineMethod(other.drawLineMethod->Clone()) {

}

ShDrawLineProxy::~ShDrawLineProxy() {

	if (this->drawLineMethod != 0)
		delete this->drawLineMethod;
}


void ShDrawLineProxy::MousePressEvent(QMouseEvent *event, ShSubActionInfo &info) {

	ShPoint3d point;
	ShDrawLineAction* drawLineAction = dynamic_cast<ShDrawLineAction*>(this->actionHandler);

	if (info.IsSnapPointClicked() == false) {
		ShPoint3d point;
		this->view->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
		info.SetPoint(point);
	}
	
	if (info.IsSnapPointClicked() == false && info.IsOrthogonalModeOn() == true) {
	
		if (drawLineAction->GetStatus() == ShDrawLineAction::Status::PickedStart) {
			ShLine *line = dynamic_cast<ShLine*>((*this->view->preview.Begin()));
			info.SetPoint(line->GetEnd());
		}
	}
	//when snap point clicked, above is ignored.
	
	ShDrawLineAction::Status prevStatus = drawLineAction->GetStatus();

	this->drawLineMethod->MousePressEvent(event, info);



	//in this case, after mousePressEvent occurs, back to default mode.
	if (prevStatus == ShDrawLineAction::Status::PickedStart&&
		drawLineAction->GetDrawMethod() == ShDrawLineAction::DrawMethod::Perpendicular) {
		
		delete this->drawLineMethod;
		this->drawLineMethod = new ShDrawLineMethod_Default(drawLineAction, this->view);
	}


	//after inserting entitiy, apply preview orthogonal points.
	if (info.IsOrthogonalModeOn() == true) {
		if (drawLineAction->GetStatus() == ShDrawLineAction::Status::PickedStart) {
			ShLine *line = dynamic_cast<ShLine*>((*this->view->preview.Begin()));
			drawLineAction->ApplyLineEndPointToOrthogonal(line);
		}
	}
	
}

void ShDrawLineProxy::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info) {

	ShPoint3d point;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
	info.SetPoint(point);

	this->drawLineMethod->MouseMoveEvent(event, info);

	ShDrawLineAction* drawLineAction = dynamic_cast<ShDrawLineAction*>(this->actionHandler);

	if (drawLineAction->GetDrawMethod() == ShDrawLineAction::DrawMethod::Perpendicular)
		return;
	
	if (info.IsOrthogonalModeOn() == true) {
		if (drawLineAction->GetStatus() == ShDrawLineAction::Status::PickedStart) {
			ShLine *line = dynamic_cast<ShLine*>((*this->view->preview.Begin()));
			drawLineAction->ApplyLineEndPointToOrthogonal(line);
		}
	}
}

void ShDrawLineProxy::Draw(QPainter *painter) {

}

/*
void ShDrawLineProxy::Decorate(ShSubActionDecorator *decorator) {

	decorator->SetChild(this->Clone());
	this->actionHandler->ChangeSubActionHandler(decorator);

}
*/

ShDrawLineProxy* ShDrawLineProxy::Clone() {

	return new ShDrawLineProxy(*this);
}

void ShDrawLineProxy::ChangeDrawMethodToPerpendicular(ShEntity *perpendicularBaseEntity) {

	if (this->drawLineMethod != 0)
		delete this->drawLineMethod;

	this->drawLineMethod = new ShDrawLineMethod_Perpendicular(dynamic_cast<ShDrawLineAction*>(this->actionHandler),
		this->view, perpendicularBaseEntity);

}

ShEntity* ShDrawLineProxy::GetPerpendicularBaseEntity() {

	if (dynamic_cast<ShDrawLineMethod_Perpendicular*>(this->drawLineMethod))
		return dynamic_cast<ShDrawLineMethod_Perpendicular*>(this->drawLineMethod)->GetPerpendicularBaseEntity();
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

ShDrawLineMethod::ShDrawLineMethod(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:drawLineAction(drawLineAction), view(view) {

}

ShDrawLineMethod::ShDrawLineMethod(const ShDrawLineMethod& other)
	: drawLineAction(other.drawLineAction), view(other.view) {

}

ShDrawLineMethod::~ShDrawLineMethod() {


}


//////////////////////////////////////////////////////////////////////////////////////////////


ShDrawLineMethod_Default::ShDrawLineMethod_Default(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:ShDrawLineMethod(drawLineAction, view) {

	this->SetDrawMethod(ShDrawLineAction::DrawMethod::Default);
}

ShDrawLineMethod_Default::ShDrawLineMethod_Default(const ShDrawLineMethod_Default& other)
	: ShDrawLineMethod(other) {

	this->SetDrawMethod(ShDrawLineAction::DrawMethod::Default);
}

ShDrawLineMethod_Default::~ShDrawLineMethod_Default() {

}


void ShDrawLineMethod_Default::MousePressEvent(QMouseEvent *event, ShSubActionInfo& info) {

	ShDrawLineAction::Status& status = this->GetStatus();
	ShPoint3d point = info.GetPoint();
	ShPoint3d cursor;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), cursor.x, cursor.y);

	if (status == ShDrawLineAction::PickedNothing) {

		status = ShDrawLineAction::PickedStart;

		this->view->preview.Add(new ShLine(ShPropertyData(*this->view->GetData()->GetPropertyData()),
			ShLineData(point, cursor), this->view->entityTable.GetLayerTable()->GetCurrentLayer()));

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		ShUpdateListTextEvent event("");
		this->view->Notify(&event);

		ShUpdateCommandEditHeadTitle event2("Line >> Specify next point: ");
		this->view->Notify(&event2);

	}
	else if (status == ShDrawLineAction::PickedStart) {

		ShLine *prevLine = dynamic_cast<ShLine*>((*this->view->preview.Begin()));
		ShLineData data = prevLine->GetData();
		data.end = point;

		prevLine->SetData(data);

		this->AddEntity(prevLine->Clone(), "Line");

		data = ShLineData(point, cursor);
		prevLine->SetData(data);

		ShUpdateListTextEvent event("");
		this->view->Notify(&event);

		ShUpdateCommandEditHeadTitle event2("Line >> Specify next point: ");
		this->view->Notify(&event2);
	}
}

void ShDrawLineMethod_Default::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info) {

	ShDrawLineAction::Status status = this->GetStatus();

	if (status == ShDrawLineAction::PickedStart) {
		
		ShPoint3d point = info.GetPoint();

		ShLine *prevLine = dynamic_cast<ShLine*>((*this->view->preview.Begin()));

		prevLine->SetEnd(point);

		DrawType drawType = info.GetDrawType();
		drawType = (DrawType)(drawType | DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities);
		info.SetDrawType(drawType);
	}
}


ShDrawLineMethod_Default* ShDrawLineMethod_Default::Clone() {

	return new ShDrawLineMethod_Default(*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawLineMethod_Perpendicular::ShDrawLineMethod_Perpendicular(ShDrawLineAction *drawLineAction, ShGraphicView *view,
	ShEntity *perpendicularBaseEntity)
	:ShDrawLineMethod(drawLineAction, view), perpendicularBaseEntity(perpendicularBaseEntity) {

	this->SetDrawMethod(ShDrawLineAction::DrawMethod::Perpendicular);

}

ShDrawLineMethod_Perpendicular::ShDrawLineMethod_Perpendicular(const ShDrawLineMethod_Perpendicular& other)
	: ShDrawLineMethod(other), perpendicularBaseEntity(other.perpendicularBaseEntity) {

	this->SetDrawMethod(ShDrawLineAction::DrawMethod::Perpendicular);

}


ShDrawLineMethod_Perpendicular::~ShDrawLineMethod_Perpendicular() {


}

#include "Visitor Pattern\ShFootOfPerpendicularVisitor.h"
void ShDrawLineMethod_Perpendicular::MousePressEvent(QMouseEvent *event, ShSubActionInfo& info) {
	
	if (this->GetStatus() == ShDrawLineAction::PickedStart) {
		
		ShPoint3d point = info.GetPoint();
		
		ShLine *prevLine = dynamic_cast<ShLine*>((*this->view->preview.Begin()));

		ShPoint3d perpendicular;
		ShFootOfPerpendicularVisitor visitor(perpendicular.x, perpendicular.y, point);
		this->perpendicularBaseEntity->Accept(&visitor);

		prevLine->SetStart(perpendicular);
		prevLine->SetEnd(point);

		this->AddEntity(prevLine->Clone(), "Line");

		prevLine->SetStart(point);

		ShPoint3d cursor;
		this->view->ConvertDeviceToEntity(event->x(), event->y(), cursor.x, cursor.y);
		prevLine->SetEnd(cursor);

		ShUpdateListTextEvent event("");
		this->view->Notify(&event);
		
		ShUpdateCommandEditHeadTitle event2("Line >> Specify next point: ");
		this->view->Notify(&event2);
	}
	
}

void ShDrawLineMethod_Perpendicular::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info) {

	ShDrawLineAction::Status status = this->GetStatus();

	if (status == ShDrawLineAction::PickedStart) {
		ShLine *prevLine = dynamic_cast<ShLine*>((*this->view->preview.Begin()));

		ShPoint3d perpendicular;
		ShFootOfPerpendicularVisitor visitor(perpendicular.x, perpendicular.y, info.GetPoint());
		this->perpendicularBaseEntity->Accept(&visitor);

		prevLine->SetStart(perpendicular);
		prevLine->SetEnd(info.GetPoint());

		DrawType drawType = info.GetDrawType();
		drawType = (DrawType)(drawType | DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities);
		info.SetDrawType(drawType);
		
	}

}

ShDrawLineMethod_Perpendicular* ShDrawLineMethod_Perpendicular::Clone() {

	return new ShDrawLineMethod_Perpendicular(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShSubLineDecorator_SnapMode_Perpendicular::ShSubLineDecorator_SnapMode_Perpendicular(ShActionHandler *actionHandler,
	ShGraphicView *view, ObjectSnap objectSnap)
	:ShSubActionDecorator_SnapMode(actionHandler, view, objectSnap) {

}

ShSubLineDecorator_SnapMode_Perpendicular::ShSubLineDecorator_SnapMode_Perpendicular
(const ShSubLineDecorator_SnapMode_Perpendicular& other)
	: ShSubActionDecorator_SnapMode(other) {

}

ShSubLineDecorator_SnapMode_Perpendicular::~ShSubLineDecorator_SnapMode_Perpendicular() {

}

#include "State Pattern\ShObjectSnapState.h"
#include "Visitor Pattern\ShBothPerpendicularVisitor.h"
void ShSubLineDecorator_SnapMode_Perpendicular::MousePressEvent(QMouseEvent *event, ShSubActionInfo &info) {

	if (this->child == 0) {
		qDebug("child is a null pointer.");
		return;
	}

	ShDrawLineAction *drawLineAction = dynamic_cast<ShDrawLineAction*>(this->actionHandler);

	if (drawLineAction->status == ShDrawLineAction::Status::PickedNothing) {
	
		if (this->objectSnapState->FindSnapPoint(event) == false) {
			this->UpdateCommandListFail();
			return;
		}

		info.point.x = this->objectSnapState->GetSnapX();
		info.point.y = this->objectSnapState->GetSnapY();
		info.isSnapPointClicked = true;
		info.isSnapModeOn = true;
		info.clickedObjectSnap = ObjectSnap::ObjectSnapPerpendicular;

		this->child->MousePressEvent(event, info);

		ShObjectSnapState_Perpendicular *state = dynamic_cast<ShObjectSnapState_Perpendicular*>(this->objectSnapState);
		dynamic_cast<ShDrawLineProxy*>(this->child)->ChangeDrawMethodToPerpendicular(state->PerpendicularBaseEntity());
		

		if (this->parent == 0)
			this->actionHandler->ChangeSubActionHandler(this->child);
		else
			this->parent->SetChild(this->child);

		this->child = 0;
		delete this;

	}
	else if (drawLineAction->status == ShDrawLineAction::Status::PickedStart &&
		drawLineAction->drawMethod == ShDrawLineAction::DrawMethod::Default) {
	
		ShPoint3d start = dynamic_cast<ShLine*>((*this->view->preview.Begin()))->GetStart();
		ShObjectSnapState_Perpendicular *state = dynamic_cast<ShObjectSnapState_Perpendicular*>(this->objectSnapState);
	
		if (state->FindSnapPoint(event, start.x, start.y) == false) {
			this->UpdateCommandListFail();
			return;
		}

		info.point.x = this->objectSnapState->GetSnapX();
		info.point.y = this->objectSnapState->GetSnapY();
		info.isSnapPointClicked = true;
		info.isSnapModeOn = true;
		info.clickedObjectSnap = ObjectSnap::ObjectSnapPerpendicular;

		this->child->MousePressEvent(event, info);

		if (this->parent == 0)
			this->actionHandler->ChangeSubActionHandler(this->child);
		else
			this->parent->SetChild(this->child);
		
		this->child = 0;
		delete this;

	}
	else if (drawLineAction->status == ShDrawLineAction::Status::PickedStart &&
		drawLineAction->drawMethod == ShDrawLineAction::DrawMethod::Perpendicular) {
	
		if (this->objectSnapState->FindSnapPoint(event) == false) {
			this->UpdateCommandListFail();
			return;
		}

		ShObjectSnapState_Perpendicular *state = dynamic_cast<ShObjectSnapState_Perpendicular*>(this->objectSnapState);
		ShDrawLineProxy *proxy = dynamic_cast<ShDrawLineProxy*>(this->child);

		//find out whether both base entities are parellel

		bool isValid = false;
		ShPoint3d point;

		//in case both entites are line and line ,
		//point should be below.
		//in the visitor class just check if two lines are parallel.
		point.x = this->objectSnapState->GetSnapX();
		point.y = this->objectSnapState->GetSnapY();

		ShBothPerpendicularVisitor visitor(state->PerpendicularBaseEntity(), point, isValid);
		proxy->GetPerpendicularBaseEntity()->Accept(&visitor);

		if (isValid == true) {

			info.SetPoint(point);
			this->child->MousePressEvent(event, info);

			if (this->parent == 0)
				this->actionHandler->ChangeSubActionHandler(this->child);
			else
				this->parent->SetChild(this->child);
			
			this->child = 0;
			delete this;

		}
		else {
			this->UpdateCommandListFail();
			//Todo....
			return;
		}
	}
	
}

void ShSubLineDecorator_SnapMode_Perpendicular::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info) {

	if (this->child == 0) {
		qDebug("child is a null pointer.");
		return;
	}

	ShDrawLineAction *drawLineAction = dynamic_cast<ShDrawLineAction*>(this->actionHandler);

	if (drawLineAction->status == ShDrawLineAction::Status::PickedNothing) {
	
		if (this->objectSnapState->FindSnapPoint(event) == true) {
			info.drawType = (DrawType)(info.drawType | DrawType::DrawActionHandler | DrawType::DrawCaptureImage);
			info.isSnapModeOn = true;
		}
	}
	else if (drawLineAction->status == ShDrawLineAction::Status::PickedStart &&
		drawLineAction->drawMethod == ShDrawLineAction::DrawMethod::Default) {
	
		ShPoint3d start = dynamic_cast<ShLine*>((*this->view->preview.Begin()))->GetStart();
		ShObjectSnapState_Perpendicular *state = dynamic_cast<ShObjectSnapState_Perpendicular*>(this->objectSnapState);
		if (state->FindSnapPoint(event, start.x, start.y) == true) {
			info.drawType = (DrawType)(info.drawType | DrawType::DrawActionHandler | DrawType::DrawCaptureImage);
			info.isSnapModeOn = true;
		}
	}
	else if (drawLineAction->status == ShDrawLineAction::Status::PickedStart &&
		drawLineAction->drawMethod == ShDrawLineAction::DrawMethod::Perpendicular) {
	
		if (this->objectSnapState->FindSnapPoint(event) == true) {
			info.drawType = (DrawType)(info.drawType | DrawType::DrawActionHandler | DrawType::DrawCaptureImage);
			info.isSnapModeOn = true;
		}

	}

	this->child->MouseMoveEvent(event, info);

}


ShSubLineDecorator_SnapMode_Perpendicular* ShSubLineDecorator_SnapMode_Perpendicular::Clone() {

	return new ShSubLineDecorator_SnapMode_Perpendicular(*this);
}
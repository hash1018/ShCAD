
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
//#include "ActionHandler\DrawAction\SubActionHandler\ShSubDrawLineAction.h"

ShDrawLineAction::ShDrawLineAction(ShGraphicView *graphicView)
	:ShDrawAction(graphicView) {

	this->status = PickedNothing;
	//this->subDrawLineAction = new ShDrawLineMethod_Default(this, this->graphicView);
	
	this->subActionHandler = new ShDrawLineProxy(this, this->graphicView);
}

ShDrawLineAction::~ShDrawLineAction() {

	//if (this->subDrawLineAction != 0)
	//	delete this->subDrawLineAction;

	//if (this->subActionHandler != 0)
	//	delete this->subActionHandler;

}


void ShDrawLineAction::MousePressEvent(QMouseEvent *event) {
	
	//ShPoint3d point;
	//this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
	//this->subDrawLineAction->MousePressEvent(event, point);

	ShSubActionInfo info;
	this->subActionHandler->MousePressEvent(event, info);

}

void ShDrawLineAction::MouseMoveEvent(QMouseEvent *event) {

	//DrawType drawType = DrawType::DrawCaptureImage;
	
	//ShPoint3d point;
	//this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
	//this->subDrawLineAction->MouseMoveEvent(event, point, drawType);

	//this->graphicView->update(drawType);

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


	//if (objectSnap == ObjectSnap::ObjectSnapPerpendicular)
	//	this->subDrawLineAction->Decorate(new ShDrawLineDecorator_SnapMode_Perpendicular(this, this->graphicView,
	//		objectSnap));
	//else
	//	this->subDrawLineAction->Decorate(new ShDrawLineDecorator_SnapMode(this, this->graphicView, objectSnap));


	if (objectSnap == ObjectSnap::ObjectSnapPerpendicular) {
		//this->subActionHandler->Decorate(new ShSubActionDecorator_SnapMode_Perpendicular(this, this->graphicView,
		//	objectSnap));
	}
	else
		this->subActionHandler->Decorate(new ShSubActionDecorator_SnapMode(this, this->graphicView, objectSnap));
	
}

void ShDrawLineAction::SetOrthogonal() {

	//this->subDrawLineAction->Decorate(new ShDrawLineDecorator_Orthogonal(this, this->graphicView));
}

ActionType ShDrawLineAction::GetType() {

	return ActionType::ActionDrawLine;
}

void ShDrawLineAction::Draw(QPainter *painter) {

	//this->subDrawLineAction->Draw(painter);
	this->subActionHandler->Draw(painter);
}

/*
void ShDrawLineAction::ChangeSubAction(ShSubDrawLineAction *current) {

	//if (this->subDrawLineAction != 0)
	//	delete this->subDrawLineAction;

	//this->subDrawLineAction = current;
}

*/


//////////////////////////////////////////////////////////////////////////////////////////////////////


ShDrawLineProxy::ShDrawLineProxy(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:ShSubActionHandler(drawLineAction, view) {

	this->drawLineMethod = new ShDrawLineMethod_Default(drawLineAction, view);
}

ShDrawLineProxy::ShDrawLineProxy(const ShDrawLineProxy& other)
	: ShSubActionHandler(other), drawLineMethod(other.drawLineMethod->Clone()) {

}

ShDrawLineProxy::~ShDrawLineProxy() {

	if (this->drawLineMethod != 0)
		delete this->drawLineMethod;
}


void ShDrawLineProxy::MousePressEvent(QMouseEvent *event, ShSubActionInfo &info) {

	//if (info.IsOrthogonalModeOn() == false && info.IsSnapModeOn() == false) {
	
		//ShPoint3d point;
		//this->view->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
		//info.SetPoint(point);
		//this->drawLineMethod->MousePressEvent(event, info);
	//}
	ShPoint3d point;

	if (info.IsSnapPointClicked() == false) {
		ShPoint3d point;
		this->view->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
		info.SetPoint(point);
	}
	

	this->drawLineMethod->MousePressEvent(event, info);
}

void ShDrawLineProxy::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info) {

	if (info.IsOrthogonalModeOn() == false ) {
		
		ShPoint3d point;
		this->view->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
		info.SetPoint(point);
		this->drawLineMethod->MouseMoveEvent(event, info);
	}

}

void ShDrawLineProxy::Draw(QPainter *painter) {

}

void ShDrawLineProxy::Decorate(ShSubActionDecorator *decorator) {

	decorator->SetChild(this->Clone());
	this->actionHandler->ChangeSubActionHandler(decorator);

}

ShDrawLineProxy* ShDrawLineProxy::Clone() {

	return new ShDrawLineProxy(*this);
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

#include "Entity\Leaf\ShLine.h"
ShDrawLineMethod_Default::ShDrawLineMethod_Default(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:ShDrawLineMethod(drawLineAction, view) {

}

ShDrawLineMethod_Default::ShDrawLineMethod_Default(const ShDrawLineMethod_Default& other)
	: ShDrawLineMethod(other) {

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

	}
	else if (status == ShDrawLineAction::PickedStart) {

		ShLine *prevLine = dynamic_cast<ShLine*>((*this->view->preview.Begin()));
		ShLineData data = prevLine->GetData();
		data.end = point;

		prevLine->SetData(data);

		this->AddEntity(prevLine->Clone(), "Line");

		data = ShLineData(point, cursor);
		prevLine->SetData(data);
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
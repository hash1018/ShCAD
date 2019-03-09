
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
	:ShDrawAction(graphicView),status(PickedNothing),drawMethod(Default) {

	
	ShUpdateListTextEvent event("_Line", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	ShUpdateCommandEditHeadTitle event2("Line >> Specify first point: ");
	this->graphicView->Notify(&event2);
	
	this->drawLineMethod = new ShDrawLineMethod_Default(this, this->graphicView);
	
}

ShDrawLineAction::~ShDrawLineAction() {

	if (this->drawLineMethod != 0)
		delete this->drawLineMethod;
}


void ShDrawLineAction::MousePressEvent(QMouseEvent *event, ShActionData& data) {

	this->drawLineMethod->MousePressEvent(event, data);

}

void ShDrawLineAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	this->drawLineMethod->MouseMoveEvent(event, data);
}

#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
void ShDrawLineAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

	if (event->key() == Qt::Key::Key_Escape) {
	
		ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);
	
	}
	else {
	
		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}

}


ActionType ShDrawLineAction::GetType() {

	return ActionType::ActionDrawLine;
}

/*

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
	//this->GetOrthogonal(data.start.x, data.start.y, mouse.x, mouse.y, orth.x, orth.y);

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
*/

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

void ShDrawLineAction::IsAllowedDraftOperation(ShAllowedDraftData &data) {

	if (this->status == Status::PickedNothing) {
		data.SetAllowOrthogonal(false);
		data.SetAllowtSnap(true);

		QPoint point = this->graphicView->mapFromGlobal(QCursor::pos());
		ShPoint3d temp;
		this->graphicView->ConvertDeviceToEntity(point.x(), point.y(), temp.x, temp.y);
		data.SetSnapBasePoint(temp);
	}
	else {

		ShLine *prevLine = dynamic_cast<ShLine*>((*this->graphicView->preview.Begin()));

		if (this->drawMethod == DrawMethod::Default) {
			data.SetAllowOrthogonal(true);
			data.SetOrthogonalBasePoint(prevLine->GetStart());
		}

		data.SetAllowtSnap(true);
		data.SetSnapBasePoint(prevLine->GetStart());
	}
}

void ShDrawLineAction::ChangeDrawMethod(DrawMethod drawMethod) {

	if (this->drawLineMethod != 0)
		delete this->drawLineMethod;

	this->drawMethod = drawMethod;

	if (drawMethod == DrawMethod::Default)
		this->drawLineMethod = new ShDrawLineMethod_Default(this, this->graphicView);
	else
		this->drawLineMethod = new ShDrawLineMethod_Perpendicular(this, this->graphicView);
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

ShDrawLineMethod::ShDrawLineMethod(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:drawLineAction(drawLineAction), view(view) {

}

ShDrawLineMethod::~ShDrawLineMethod() {

}


ShDrawLineMethod_Default::ShDrawLineMethod_Default(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:ShDrawLineMethod(drawLineAction, view) {

}

ShDrawLineMethod_Default::~ShDrawLineMethod_Default() {

}

void ShDrawLineMethod_Default::MousePressEvent(QMouseEvent *event, ShActionData& data) {
	
	ShDrawLineAction::Status& status = this->GetStatus();
	ShPoint3d point = data.GetPoint();
	ShPoint3d nextPoint = data.GetNextPoint();
	//ShPoint3d cursor;
	//this->view->ConvertDeviceToEntity(event->x(), event->y(), cursor.x, cursor.y);

	if (status == ShDrawLineAction::PickedNothing) {

		status = ShDrawLineAction::PickedStart;

		this->view->preview.Add(new ShLine(ShPropertyData(*this->view->GetData()->GetPropertyData()),
			ShLineData(point, nextPoint), this->view->entityTable.GetLayerTable()->GetCurrentLayer()));

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

		data = ShLineData(point, nextPoint);
		prevLine->SetData(data);

		ShUpdateListTextEvent event("");
		this->view->Notify(&event);

		ShUpdateCommandEditHeadTitle event2("Line >> Specify next point: ");
		this->view->Notify(&event2);
	}
}

void ShDrawLineMethod_Default::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {
	
	ShDrawLineAction::Status status = this->GetStatus();

	if (status == ShDrawLineAction::PickedStart) {

		ShPoint3d point = data.GetPoint();

		ShLine *prevLine = dynamic_cast<ShLine*>((*this->view->preview.Begin()));

		prevLine->SetEnd(point);

		//DrawType drawType = data.GetDrawType();
		//drawType = (DrawType)(drawType | DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities);
		//data.SetDrawType(drawType);
		
		data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
		
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawLineMethod_Perpendicular::ShDrawLineMethod_Perpendicular(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:ShDrawLineMethod(drawLineAction, view) {

}

ShDrawLineMethod_Perpendicular::~ShDrawLineMethod_Perpendicular() {

}

#include "Visitor Pattern\ShFootOfPerpendicularVisitor.h"
void ShDrawLineMethod_Perpendicular::MousePressEvent(QMouseEvent *event, ShActionData& data) {

	if (this->GetStatus() == ShDrawLineAction::PickedStart) {

		ShPoint3d point = data.GetPoint();

		ShLine *prevLine = dynamic_cast<ShLine*>((*this->view->preview.Begin()));

		ShPoint3d perpendicular;
		ShFootOfPerpendicularVisitor visitor(perpendicular.x, perpendicular.y, point);
		this->perpendicularBaseEntity->Accept(&visitor);

		prevLine->SetStart(perpendicular);
		prevLine->SetEnd(point);

		this->AddEntity(prevLine->Clone(), "Line");

		prevLine->SetStart(point);

		
		prevLine->SetEnd(data.GetNextPoint());

		ShUpdateListTextEvent event("");
		this->view->Notify(&event);

		ShUpdateCommandEditHeadTitle event2("Line >> Specify next point: ");
		this->view->Notify(&event2);

		this->drawLineAction->ChangeDrawMethod(ShDrawLineAction::DrawMethod::Default);
	}

}

void ShDrawLineMethod_Perpendicular::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	ShDrawLineAction::Status status = this->GetStatus();

	if (status == ShDrawLineAction::PickedStart) {
		ShLine *prevLine = dynamic_cast<ShLine*>((*this->view->preview.Begin()));

		ShPoint3d perpendicular;
		ShFootOfPerpendicularVisitor visitor(perpendicular.x, perpendicular.y, data.GetPoint());
		this->perpendicularBaseEntity->Accept(&visitor);

		prevLine->SetStart(perpendicular);
		prevLine->SetEnd(data.GetPoint());

		DrawType drawType = data.GetDrawType();
		drawType = (DrawType)(drawType | DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities);
		data.SetDrawType(drawType);

	}

}

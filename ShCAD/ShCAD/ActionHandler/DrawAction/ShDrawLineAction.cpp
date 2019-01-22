
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
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "ShNotifyEvent.h"
ShDrawLineAction::ShDrawLineAction(ShGraphicView *graphicView)
	:ShDrawAction(graphicView) {

	this->status = PickedNothing;
}

ShDrawLineAction::~ShDrawLineAction() {

}


void ShDrawLineAction::MousePressEvent(QMouseEvent *event) {
	
	if (this->status == PickedNothing) {
	
		this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), this->start.x, this->start.y);
		this->status = PickedStart;

		this->graphicView->preview.Add(new ShLine(ShLineData(*this->graphicView->GetData()->GetPropertyData(), this->start, this->start)));
		this->graphicView->rubberBand = new ShRubberBand(ShLineData(*this->graphicView->GetData()->GetPropertyData(), this->start, this->start));
		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
		
	}
	else {
		this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), this->end.x, this->end.y);
		ShLineData data(*this->graphicView->GetData()->GetPropertyData(), start, end);
		
		dynamic_cast<ShLine*>(this->graphicView->preview.Begin().Current())->SetData(data);

		ShDrawAction::AddEntity(this->graphicView->preview.Begin().Current()->Clone(), "Line");

		this->start = this->end;

		
	}
}

void ShDrawLineAction::MouseMoveEvent(QMouseEvent *event) {

	if (this->status == PickedStart) {
		this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), this->end.x, this->end.y);

		ShLineData data(*this->graphicView->GetData()->GetPropertyData(), this->start, this->end);

		dynamic_cast<ShLine*>(this->graphicView->preview.Begin().Current())->SetData(data);
		
		this->graphicView->rubberBand->SetData(data);

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
		
	}
}

void ShDrawLineAction::KeyPressEvent(QKeyEvent *event) {

	if (event->key() == Qt::Key::Key_Escape) {
	
		this->graphicView->ChangeCurrentAction(ActionType::ActionDefault);
	}


	else {
	
		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}

}

ActionType ShDrawLineAction::GetType() {

	return ActionType::ActionDrawLine;
}
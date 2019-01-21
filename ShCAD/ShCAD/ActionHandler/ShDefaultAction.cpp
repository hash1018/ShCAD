
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

#include "ShDefaultAction.h"
#include <QKeyEvent>
#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
#include "ShNotifyEvent.h"
#include "ShCadAction.h"

ShDefaultAction::ShDefaultAction(ShGraphicView *graphicView)
	:ShActionHandler(graphicView) {

}

ShDefaultAction::~ShDefaultAction() {

}


void ShDefaultAction::MousePressEvent(QMouseEvent *event) {
	
	
	ShEntity *entity = this->graphicView->entityTable.FindEntity(this->graphicView->GetX(),
		this->graphicView->GetY(), this->graphicView->GetZoomRate());

	if (entity == NULL) {

		double firstX, firstY;
		this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), firstX, firstY);
		this->graphicView->SetTemporaryAction(new ShDragSelectAction(this->graphicView, this, firstX, firstY));
		return;
	}
	
	
	if (event->modifiers() == Qt::ShiftModifier) {
		if (this->graphicView->selectedEntityManager.Pop(entity) == true) {
			this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawJustUnSelectedEntities));
			this->graphicView->CaptureImage();
		}
		
	}
	else {
		if (this->graphicView->selectedEntityManager.Push(entity) == true){
			this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
			this->graphicView->CaptureImage();
		}
	}
	

}

void ShDefaultAction::MouseMoveEvent(QMouseEvent *event) {


}


void ShDefaultAction::KeyPressEvent(QKeyEvent *event) {

	// Ctrl + Z undo
	if (event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key::Key_Z)
		ShCadAction::Undo(this->graphicView);

	//Ctrl + Y redo
	else if (event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key::Key_Y)
		ShCadAction::Redo(this->graphicView);

	//Ctrl + A Select All
	else if (event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key::Key_A)
		ShCadAction::SelectAll(this->graphicView);

	//Delete 
	else if (event->key() == Qt::Key::Key_Delete) {
	
		if (this->graphicView->selectedEntityManager.GetSize() == 0) {
			ShKeyPressedEvent event2(event);
			this->graphicView->Notify(&event2);
		}
		else
			ShCadAction::Delete(this->graphicView);

	}

	else if (event->key() == Qt::Key::Key_Escape) {
		this->UnSelectSelectedEntities();
		ShUpdateListTextEvent event("<Cancel>");
		this->graphicView->Notify(&event);
	}
	else {
	
		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
	

}



ActionType ShDefaultAction::GetType() {

	return ActionType::ActionDefault;
}
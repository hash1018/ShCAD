
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
#include "ShNotifyEvent.h"
#include "Facade Pattern\ShCadFacade.h"
#include "ActionHandler\SubActionHandler\ShSubDefaultAction.h"

ShDefaultAction::ShDefaultAction(ShGraphicView *graphicView)
	:ShActionHandler(graphicView) {

	this->subDefaultAction = new ShSubDefaultAction_Default(this, this->graphicView);
}

ShDefaultAction::~ShDefaultAction() {

	if (this->subDefaultAction != 0)
		delete this->subDefaultAction;
}


void ShDefaultAction::MousePressEvent(QMouseEvent *event) {
	
	this->subDefaultAction->MousePressEvent(event);
	
}

void ShDefaultAction::MouseMoveEvent(QMouseEvent *event) {

	this->subDefaultAction->MouseMoveEvent(event);

}


void ShDefaultAction::KeyPressEvent(QKeyEvent *event) {

	// Ctrl + Z undo
	if (event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key::Key_Z) {
		
		this->ChangeSubAction(new ShSubDefaultAction_Default(this, this->graphicView));
		ShCadFacade::Undo(this->graphicView);
	}
	//Ctrl + Y redo
	else if (event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key::Key_Y) {

		this->ChangeSubAction(new ShSubDefaultAction_Default(this, this->graphicView));
		ShCadFacade::Redo(this->graphicView);
	}
	//Ctrl + A Select All
	else if (event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key::Key_A) {
		
		this->ChangeSubAction(new ShSubDefaultAction_Default(this, this->graphicView));
		ShCadFacade::SelectAll(this->graphicView);

	}
	//Delete 
	else if (event->key() == Qt::Key::Key_Delete) {
		
		if (this->graphicView->selectedEntityManager.GetSize() == 0) {
			ShKeyPressedEvent event2(event);
			this->graphicView->Notify(&event2);
		}
		else {

			this->ChangeSubAction(new ShSubDefaultAction_Default(this, this->graphicView));
			ShCadFacade::Delete(this->graphicView);
		}
	}

	else if (event->key() == Qt::Key::Key_Escape) {

		this->ChangeSubAction(new ShSubDefaultAction_Default(this, this->graphicView));
		this->UnSelectSelectedEntities();
		
		ShUpdateListTextEvent event("<Cancel>");
		this->graphicView->Notify(&event);

		this->SetActionHeadTitle();
	}
	else {
	
		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
	

}



ActionType ShDefaultAction::GetType() {

	return ActionType::ActionDefault;
}

void ShDefaultAction::ChangeSubAction(ShSubDefaultAction *subDefaultAction) {
	qDebug("ShDefaultAction->ChangeSubAction(); delete original subAction and replace new one.");

	if (this->subDefaultAction != 0)
		delete this->subDefaultAction;

	this->subDefaultAction = subDefaultAction;

}


void ShDefaultAction::SetActionHeadTitle() {

	ShUpdateCommandEditHeadTitle event(":: ");
	this->graphicView->Notify(&event);
	
}
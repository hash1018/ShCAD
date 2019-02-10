
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
#include "ActionHandler\DrawAction\SubActionHandler\ShSubDrawLineAction.h"
#include "ShObjectSnapState.h"

ShDrawLineAction::ShDrawLineAction(ShGraphicView *graphicView)
	:ShDrawAction(graphicView) {

	this->status = PickedNothing;
	this->subDrawLineAction = new ShSubDrawLineAction_Default(this, this->graphicView);
	this->objectSnapState = new ShObjectSnapState_Nothing;
}

ShDrawLineAction::~ShDrawLineAction() {

	if (this->objectSnapState != 0)
		delete this->objectSnapState;

	if (this->subDrawLineAction != 0)
		delete this->subDrawLineAction;
}


void ShDrawLineAction::MousePressEvent(QMouseEvent *event) {
	
	this->objectSnapState->MousePressEvent(event);

	this->subDrawLineAction->MousePressEvent(event);
}

void ShDrawLineAction::MouseMoveEvent(QMouseEvent *event) {

	this->objectSnapState->MouseMoveEvent(event);

	this->subDrawLineAction->MouseMoveEvent(event);
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
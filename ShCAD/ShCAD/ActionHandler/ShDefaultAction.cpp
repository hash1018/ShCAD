
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

ShDefaultAction::ShDefaultAction(ShGraphicView *graphicView)
	:ShActionHandler(graphicView) {

	this->SetActionHeadTitle();
	this->subDefaultAction = new ShSubDefaultAction_Default(this, this->graphicView);
}

ShDefaultAction::~ShDefaultAction() {

	if (this->subDefaultAction != 0)
		delete this->subDefaultAction;
}


void ShDefaultAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {
	
	this->subDefaultAction->LMousePressEvent(event);
	
}


void ShDefaultAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	this->subDefaultAction->MouseMoveEvent(event);

}


void ShDefaultAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
ShSubDefaultAction::ShSubDefaultAction(ShDefaultAction *defaultAction, ShGraphicView *view)
	:defaultAction(defaultAction), view(view) {

}

ShSubDefaultAction::~ShSubDefaultAction() {

}

///////////////////////////////////////////////////////////////////////////

ShSubDefaultAction_Default::ShSubDefaultAction_Default(ShDefaultAction *defaultAction, ShGraphicView *view)
	:ShSubDefaultAction(defaultAction, view) {

}

ShSubDefaultAction_Default::~ShSubDefaultAction_Default() {

}

void ShSubDefaultAction_Default::LMousePressEvent(QMouseEvent *event) {

	ShEntity *entity = this->view->entityTable.FindEntity(this->view->GetX(),
		this->view->GetY(), this->view->GetZoomRate());

	if (entity == NULL) {

		double firstX, firstY;
		this->view->ConvertDeviceToEntity(event->x(), event->y(), firstX, firstY);
		
		if (event->modifiers() == Qt::ShiftModifier)
			this->view->SetTemporaryAction(new ShDragSelectAction(this->view, firstX, firstY,
				ShDragSelectAction::Mode::UnSelectMode));
		else
			this->view->SetTemporaryAction(new ShDragSelectAction(this->view, firstX, firstY));


		return;
	}

	if (event->modifiers() == Qt::ShiftModifier) {
		if (this->view->selectedEntityManager.Pop(entity) == true) {
			this->view->update(DrawType::DrawAll);
			this->view->CaptureImage();
		}
	}
	else {
		if (this->view->selectedEntityManager.Push(entity) == true) {
			this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
			this->view->CaptureImage();
		}
	}

}


#include "Visitor Pattern\ShHitTester.h"
void ShSubDefaultAction_Default::MouseMoveEvent(QMouseEvent *event) {

	double x, y;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), x, y);

	VertexPoint vertexPoint = VertexPoint::VertexNothing;

	ShHitTester hitTester(x, y, view->GetZoomRate(), vertexPoint);

	QLinkedList<ShEntity*>::iterator itr = this->view->selectedEntityManager.Begin();

	while (itr != this->view->selectedEntityManager.End() &&
		(vertexPoint == VertexPoint::VertexNothing || vertexPoint == VertexPoint::VertexOther)) {

		(*itr)->Accept(&hitTester);
		++itr;
	}


	if (vertexPoint != VertexPoint::VertexNothing && vertexPoint != VertexPoint::VertexOther) {

		--itr;
		ShPoint3d vertex;
		(*itr)->GetVertexPoint(vertexPoint, vertex);

		//Set Cursor to vertex.
		int dx, dy;
		this->view->ConvertEntityToDevice(vertex.x, vertex.y, dx, dy);
		QCursor::setPos(this->view->mapToGlobal(QPoint(dx, dy)));


		ShSubDefaultAction_MouseIsInEntityVertex *subAction =
			new ShSubDefaultAction_MouseIsInEntityVertex(this->defaultAction, this->view, vertex);

		this->defaultAction->ChangeSubAction(subAction);

	}

}


//////////////////////////////////////////////////////////////////////////

ShSubDefaultAction_MouseIsInEntityVertex::ShSubDefaultAction_MouseIsInEntityVertex(ShDefaultAction *defaultAction,
	ShGraphicView *view, const ShPoint3d& vertex)
	:ShSubDefaultAction(defaultAction, view), vertex(vertex) {

	this->DrawVertex();
}

ShSubDefaultAction_MouseIsInEntityVertex::~ShSubDefaultAction_MouseIsInEntityVertex() {

	this->EraseVertex();
}


#include "ActionHandler\TemporaryAction\ShStretchTemporaryAction.h"
void ShSubDefaultAction_MouseIsInEntityVertex::LMousePressEvent(QMouseEvent *event) {
	//Change to SelectionMove.

	VertexPoint vertexPoint = VertexPoint::VertexNothing;
	ShHitTester hitTester(this->vertex.x, this->vertex.y, this->view->GetZoomRate(), vertexPoint);

	QLinkedList<ShEntity*> list;
	QLinkedList<VertexPoint> vertexList;

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->view->selectedEntityManager.Begin();
		itr != this->view->selectedEntityManager.End();
		++itr) {

		(*itr)->Accept(&hitTester);

		if (vertexPoint != VertexPoint::VertexNothing && vertexPoint != VertexPoint::VertexOther) {
			list.append((*itr));
			vertexList.append(vertexPoint);
		}
	}

	ShStretchTemporaryAction *action = new ShStretchTemporaryAction(this->view/*, this->defaultAction*/,
		list, vertexList, this->vertex);
	this->view->SetTemporaryAction(action);

	this->defaultAction->ChangeSubAction(new ShSubDefaultAction_Default(this->defaultAction, this->view));



}


#include "ShMath.h"
void ShSubDefaultAction_MouseIsInEntityVertex::MouseMoveEvent(QMouseEvent *event) {

	ShPoint3d point;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);

	ShPoint3d topLeft, bottomRight;
	int dx, dy;
	this->view->ConvertEntityToDevice(this->vertex.x, this->vertex.y, dx, dy);

	this->view->ConvertDeviceToEntity(dx - 3, dy - 3, topLeft.x, topLeft.y);
	this->view->ConvertDeviceToEntity(dx + 3, dy + 3, bottomRight.x, bottomRight.y);



	if (Math::CheckPointLiesInsideRect(point, topLeft, bottomRight, 1) == false) {

		this->defaultAction->ChangeSubAction(new ShSubDefaultAction_Default(this->defaultAction, this->view));
	}


}

#include <qpainter.h>
void ShSubDefaultAction_MouseIsInEntityVertex::DrawVertex() {

	int dx, dy;
	this->view->ConvertEntityToDevice(this->vertex.x, this->vertex.y, dx, dy);

	QPainter painter(this->view);
	painter.fillRect(dx - 3, dy - 3, 6, 6, QColor(255, 000, 000));

}

void ShSubDefaultAction_MouseIsInEntityVertex::EraseVertex() {

	int dx, dy;
	this->view->ConvertEntityToDevice(this->vertex.x, this->vertex.y, dx, dy);

	QPainter painter(this->view);
	painter.fillRect(dx - 3, dy - 3, 6, 6, QColor(000, 153, 255));

}
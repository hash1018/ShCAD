
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

#include "ShPanMoveAction.h"
#include "Command Pattern\UI Command\ShMoveViewCommand.h"
#include <QMouseEvent>
ShPanMoveAction::ShPanMoveAction(ShGraphicView *graphicView)
	:ShTemporaryAction(graphicView), prevX(0), prevY(0) {

}

ShPanMoveAction::~ShPanMoveAction() {

}

void ShPanMoveAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {

}

//Pan Move Start here
void ShPanMoveAction::MMousePressEvent(QMouseEvent *event, ShActionData& data) {
	qDebug("ShPanMoveAction->MousePressEvent");

	this->graphicView->setCursor(Qt::ClosedHandCursor);
	this->prevX = event->x();
	this->prevY = event->y();

	

	double ex, ey, zoomRate;
	int dx, dy;

	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), ex, ey);
	dx = event->x();
	dy = event->y();
	zoomRate = this->graphicView->GetZoomRate();

	this->graphicView->undoTaker.Push(new ShMoveViewCommand(this->graphicView, ex, ey, zoomRate, dx, dy));

	if (!this->graphicView->redoTaker.IsEmpty())
		this->graphicView->redoTaker.DeleteAll();

}

void ShPanMoveAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	double hPos = this->graphicView->GetHPos();
	hPos += this->prevX - event->x();
	double vPos = this->graphicView->GetVPos();
	vPos += this->prevY - event->y();

	this->graphicView->SetHPos(hPos);
	this->graphicView->SetVPos(vPos);


	this->prevX = event->x();
	this->prevY = event->y();

	data.AppendDrawType(DrawType::DrawAll);

}

void ShPanMoveAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

}

//Pan Move is finished
void ShPanMoveAction::MouseReleaseEvent(QMouseEvent *event, ShActionData& data) {
	qDebug("ShPanMoveAction->MouseReleaseEvent");

	this->graphicView->setCursor(this->previousAction->GetCursorShape());

	if (event->button()& Qt::MouseButton::MiddleButton) {
		this->graphicView->CaptureImage();
		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}

	this->ReturnToPrevious();

}


ActionType ShPanMoveAction::GetType() {
	
	return ActionType::ActionPanMove;
}


QCursor ShPanMoveAction::GetCursorShape() {
	
	QCursor cursor(Qt::ClosedHandCursor);
	
	return cursor;
}
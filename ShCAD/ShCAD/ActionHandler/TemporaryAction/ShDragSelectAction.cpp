
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

#include "ShDragSelectAction.h"
#include <QMouseEvent>
#include <qpainter.h>
ShDragSelectAction::ShDragSelectAction(ShGraphicView *graphicView, ShActionHandler *previousAction,
	double firstX, double firstY)
	:ShTemporaryAction(graphicView, previousAction), firstX(firstX), firstY(firstY), secondX(0), secondY(0) {

	
}

ShDragSelectAction::~ShDragSelectAction() {

}


//about to close dragRect , and back to previousAction
void ShDragSelectAction::MousePressEvent(QMouseEvent *event) {

	this->graphicView->setCursor(this->previousAction->GetCursorShape());
	this->graphicView->update(DrawType::DrawCaptureImage);

	this->ReturnToPrevious();
}

void ShDragSelectAction::MouseMoveEvent(QMouseEvent *event) {

	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), this->secondX, this->secondY);
	this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawActionHandler));
}

void ShDragSelectAction::KeyPressEvent(QKeyEvent *event) {

}



ActionType ShDragSelectAction::GetType() {

	return ActionType::ActionDragSelect;
}

QCursor ShDragSelectAction::GetCursorShape() {
	
	return QCursor(Qt::CursorShape::DragCopyCursor);
}

void ShDragSelectAction::Draw(QPainter *painter) {

	if (painter->isActive() == false)
		painter->begin(this->graphicView);

	int firstX, firstY, secondX, secondY;
	this->graphicView->ConvertEntityToDevice(this->firstX, this->firstY, firstX, firstY);
	this->graphicView->ConvertEntityToDevice(this->secondX, this->secondY, secondX, secondY);

	int width = abs(firstX - secondX);
	int height = abs(firstY - secondY);

	QPen oldPen = painter->pen();

	QPen pen;
	pen.setColor(QColor(255, 255, 255));
	painter->setPen(pen);

	//in this case, entity is selected when its all part is in dragRect.
	if (firstX <= secondX) {

		if (firstY >= secondY) {
			painter->drawRect(firstX, firstY - height, width, height);
			painter->fillRect(firstX, firstY - height, width, height, QColor(102, 102, 204, 125));
		}
		else {
			painter->drawRect(firstX, firstY, width, height);
			painter->fillRect(firstX, firstY, width, height, QColor(102, 102, 204, 125));
		}

	}
	//entity is selected when its any part of body is in dragRect.
	else {

		pen.setStyle(Qt::PenStyle::DotLine);
		painter->setPen(pen);
		if (firstY >= secondY) {
			painter->drawRect(secondX, secondY, width, height);
			painter->fillRect(secondX, secondY, width, height, QColor(102, 204, 102, 125));
		}
		else {
			painter->drawRect(secondX, firstY, width, height);
			painter->fillRect(secondX, firstY, width, height, QColor(102, 204, 102, 125));
		}

	}

	painter->setPen(oldPen);
	painter->end();
}

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
ShDragSelectAction::ShDragSelectAction(ShGraphicView *graphicView,
	double firstX, double firstY, Mode mode)
	:ShTemporaryAction(graphicView), firstX(firstX), firstY(firstY), secondX(0), secondY(0), mode(mode) {


}

ShDragSelectAction::~ShDragSelectAction() {

}


void ShDragSelectAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {









	this->graphicView->setCursor(this->previousAction->GetCursorShape());
	this->graphicView->update(DrawType::DrawCaptureImage);

	this->ReturnToPrevious();
}

void ShDragSelectAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), this->secondX, this->secondY);
	
	data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawActionHandler));
}

void ShDragSelectAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

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


	SelectMethod selectMethod;
	ShPoint3d topLeft, bottomRight;
	this->GetDragRectPoint(ShPoint3d(this->firstX, this->firstY), ShPoint3d(this->secondX, this->secondY),
		topLeft, bottomRight, selectMethod);

	int topLeftX, topLeftY, bottomRightX, bottomRightY, width, height;
	this->graphicView->ConvertEntityToDevice(topLeft.x, topLeft.y, topLeftX, topLeftY);
	this->graphicView->ConvertEntityToDevice(bottomRight.x, bottomRight.y, bottomRightX, bottomRightY);
	width = abs(topLeftX - bottomRightX);
	height = abs(topLeftY - bottomRightY);


	QPen oldPen = painter->pen();
	QPen pen;
	pen.setColor(QColor(255, 255, 255));
	painter->setPen(pen);


	if (selectMethod == SelectMethod::OnePart) {
		pen.setStyle(Qt::PenStyle::DotLine);
		painter->setPen(pen);
		painter->drawRect(topLeftX, topLeftY, width, height);
		painter->fillRect(topLeftX, topLeftY, width, height, QColor(102, 204, 102, 125));
	}
	else {
		painter->drawRect(topLeftX, topLeftY, width, height);
		painter->fillRect(topLeftX, topLeftY, width, height, QColor(102, 102, 204, 125));

	}

	
	painter->setPen(oldPen);
	painter->end();
}

void ShDragSelectAction::GetDragRectPoint(const ShPoint3d& first, const ShPoint3d& second,
	ShPoint3d &topLeft, ShPoint3d &bottomRight, SelectMethod &selectMethod) {

	if (first.x > second.x && first.y > second.y) {
		selectMethod = OnePart;
		topLeft.x = second.x;
		topLeft.y = first.y;
		bottomRight.x = first.x;
		bottomRight.y = second.y;
	}
	else if (first.x <= second.x && first.y > second.y) {
		selectMethod = AllPart;
		topLeft.x = first.x;
		topLeft.y = first.y;
		bottomRight.x = second.x;
		bottomRight.y = second.y;
	}
	else if (first.x > second.x && first.y <= second.y) {
		selectMethod = OnePart;
		topLeft.x = second.x;
		topLeft.y = second.y;
		bottomRight.x = first.x;
		bottomRight.y = first.y;
	}
	else if (first.x <= second.x && first.y <= second.y) {
		selectMethod = AllPart;
		topLeft.x = first.x;
		topLeft.y = second.y;
		bottomRight.x = second.x;
		bottomRight.y = first.y;
	}
}
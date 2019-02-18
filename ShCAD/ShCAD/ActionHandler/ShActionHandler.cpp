
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

#include "ShActionHandler.h"
#include "ActionHandler\SubActionHandler\ShSubActionHandler.h"
ShActionHandler::ShActionHandler(ShGraphicView *graphicView)
	:graphicView(graphicView), subActionHandler(0) {

}

ShActionHandler::~ShActionHandler() {

	if (this->subActionHandler != 0)
		delete this->subActionHandler;
}

#include <qpainter.h>
QCursor ShActionHandler::GetCursorShape() {

	QPixmap pix(48, 48);
	pix.fill(Qt::transparent);
	QPainter painter(&pix);
	painter.setPen(QColor(255, 255, 255));

	painter.drawLine(24, 0, 24, 48);
	painter.drawLine(0, 24, 48, 24);

	painter.drawRect(21, 21, 6, 6);

	return QCursor(pix);
}


bool ShActionHandler::UnSelectSelectedEntities() {

	if (this->graphicView->selectedEntityManager.GetSize() > 0) {
		this->graphicView->selectedEntityManager.UnSelectAll();
		this->graphicView->update(DrawType::DrawAll);
		this->graphicView->CaptureImage();
		return true;
	}

	return false;
}

void ShActionHandler::ChangeSubActionHandler(ShSubActionHandler *subActionHandler) {

	if (this->subActionHandler != 0)
		delete this->subActionHandler;

	this->subActionHandler = subActionHandler;
}


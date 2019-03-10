
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

ShActionHandler::ShActionHandler(ShGraphicView *graphicView)
	:graphicView(graphicView) {

}

ShActionHandler::~ShActionHandler() {

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

void ShActionHandler::Draw(QPainter *painter) {

	
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

void ShActionHandler::IsAllowedDraftOperation(ShAllowedDraftData &data) {

	data.SetAllowOrthogonal(false);
	data.SetAllowtSnap(false);

}



#include "ShMath.h"
void ShActionHandler::GetOrthogonal(double x, double y, double mouseX, double mouseY, double &orthX, double &orthY) {

	double disVertical, disHorizontal;

	disVertical = Math::GetDistance(x, y, x, mouseY);

	disHorizontal = Math::GetDistance(x, y, mouseX, y);

	if (Math::Compare(disVertical, disHorizontal) == 1) {

		orthX = x;
		orthY = mouseY;

	}
	else {

		orthX = mouseX;
		orthY = y;
	}
}

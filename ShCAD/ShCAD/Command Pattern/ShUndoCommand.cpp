
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

#include "ShUndoCommand.h"
#include "Interface\ShGraphicView.h"
#include "Entity\Composite\ShEntityTable.h"
#include "Memento Pattern\ShMemento.h"

ShUndoCommand::ShUndoCommand(ShGraphicView *view, ShMemento *memento) {

	this->graphicView = view;
	this->memento = memento;
}

ShUndoCommand::~ShUndoCommand() {

}


void ShUndoCommand::Execute() {

	if (this->memento->type == MementoType::MementoCreated) {
		
		this->graphicView->entityTable.Delete(memento->entity);
		this->graphicView->update();
		this->graphicView->CaptureImage();

		//Now that undo executed, push memento into redoTaker
		memento->type = MementoType::MementoDeleted;
		memento->entity = 0;

		this->graphicView->redoTaker.Push(memento);

	}
	else if (this->memento->type == MementoType::MementoPanMoved) {
	
		if (dynamic_cast<ShPanMemento*>(this->memento)) {
			double x = this->graphicView->GetX();
			double y = this->graphicView->GetY();
			double zoomRate = this->graphicView->GetZoomRate();
			int dx, dy;
			this->graphicView->ConvertEntityToDevice(x, y, dx, dy);
			

			ShPanMemento* panMemento = dynamic_cast<ShPanMemento*>(this->memento);
			this->graphicView->MoveView(panMemento->ex, panMemento->ey, panMemento->zoomRate,
				panMemento->dx, panMemento->dy);

			panMemento->ex = x;
			panMemento->ey = y;
			panMemento->zoomRate = zoomRate;
			panMemento->dx = dx;
			panMemento->dy = dy;

			this->graphicView->redoTaker.Push(panMemento);
		}
	}



	
}
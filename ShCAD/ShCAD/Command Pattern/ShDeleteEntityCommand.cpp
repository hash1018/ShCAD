
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

#include "ShDeleteEntityCommand.h"
#include "Memento Pattern\ShMemento.h"
#include "Interface\ShGraphicView.h"
ShDeleteEntityCommand::ShDeleteEntityCommand(ShGraphicView *view, ShCompositeEntityMemento *memento) {

	this->graphicView = view;
	this->memento = memento;

	this->commandText = "Delete";
}

ShDeleteEntityCommand::~ShDeleteEntityCommand() {

}

void ShDeleteEntityCommand::Execute() {
	qDebug("ShDeleteEntityCommand->Execute()");

	ShCompositeEntityMemento *memento = dynamic_cast<ShCompositeEntityMemento*>(this->memento);

	QLinkedList<ShEntityMemento*>::iterator itr;

	for (itr = memento->list.begin(); itr != memento->list.end(); ++itr) {
	
		this->graphicView->entityTable.Remove((*itr)->entity);
		(*itr)->mustDeallocateEntity = true;
	}

	this->graphicView->update(DrawType::DrawAll);
	this->graphicView->CaptureImage();
	

}

void ShDeleteEntityCommand::UnExecute() {
	qDebug("ShDeleteEntityCommand->UnExecute()");

	ShCompositeEntityMemento *memento = dynamic_cast<ShCompositeEntityMemento*>(this->memento);

	QLinkedList<ShEntityMemento*>::iterator itr;
	

	QLinkedList<ShEntity*> list;

	for (itr = memento->list.begin(); itr != memento->list.end(); ++itr) {
		list.append((*itr)->entity);
		(*itr)->mustDeallocateEntity = false;
	}

	this->graphicView->entityTable.Add(list);

	this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawAddedEntities));
	this->graphicView->CaptureImage();

}

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
#include "Interface\ShGraphicView.h"
#include "Entity\ShEntity.h"
ShDeleteEntityCommand::ShDeleteEntityCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& entities)
	:graphicView(view), entities(entities), ShCommand("Delete"),mustDeallocateEntity(true) {


}

ShDeleteEntityCommand::~ShDeleteEntityCommand() {

	if (this->mustDeallocateEntity == true) {
	
		while (!this->entities.empty())
			delete this->entities.takeFirst();
	}
}

void ShDeleteEntityCommand::Execute() {
	qDebug("ShDeleteEntityCommand->Execute()");

	

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->entities.begin(); itr != this->entities.end(); ++itr)
		this->graphicView->entityTable.Remove((*itr));
		
	this->mustDeallocateEntity = true;
	

	this->graphicView->update(DrawType::DrawAll);
	this->graphicView->CaptureImage();
	

}

void ShDeleteEntityCommand::UnExecute() {
	qDebug("ShDeleteEntityCommand->UnExecute()");

	
	this->graphicView->entityTable.Add(this->entities);
	this->mustDeallocateEntity = false;

	this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawAddedEntities));
	this->graphicView->CaptureImage();

}
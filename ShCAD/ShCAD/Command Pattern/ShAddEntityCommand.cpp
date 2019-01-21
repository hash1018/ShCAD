
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

#include "ShAddEntityCommand.h"
#include "Entity\ShEntity.h"
#include "Memento Pattern\ShMemento.h"
#include "Interface\ShGraphicView.h"

ShAddEntityCommand::ShAddEntityCommand(ShGraphicView *view, ShEntityMemento *memento, const QString& commandText){

	this->graphicView = view;
	this->memento = memento;
	this->commandText = commandText;

}

ShAddEntityCommand::~ShAddEntityCommand() {

}

void ShAddEntityCommand::Execute() {
	qDebug("ShAddEntityCommand->Excute()");
	

	ShEntityMemento *entityMemento = dynamic_cast<ShEntityMemento*>(this->memento);

	this->graphicView->entityTable.Add(entityMemento->entity);
	entityMemento->mustDeallocateEntity = false;

	this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawAddedEntities));
	this->graphicView->CaptureImage();
	

}

void ShAddEntityCommand::UnExecute() {
	qDebug("ShAddEntityCommand->UnExecute");

	ShEntityMemento *entityMemento = dynamic_cast<ShEntityMemento*>(this->memento);

	this->graphicView->entityTable.Remove(entityMemento->entity);
	entityMemento->mustDeallocateEntity = true;

	this->graphicView->update();
	this->graphicView->CaptureImage();

}
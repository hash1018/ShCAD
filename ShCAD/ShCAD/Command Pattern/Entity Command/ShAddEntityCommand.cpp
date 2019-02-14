
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
#include "Interface\ShGraphicView.h"

ShAddEntityCommand::ShAddEntityCommand(ShGraphicView *view, ShEntity *entity, const QString& commandText)
	:ShCommand(commandText), graphicView(view), entity(entity),mustDeallocateEntity(false) {

}

ShAddEntityCommand::~ShAddEntityCommand() {

	if (this->mustDeallocateEntity == true) {
		delete this->entity;
	}
}

void ShAddEntityCommand::Execute() {
	qDebug("ShAddEntityCommand->Excute()");
	

	this->graphicView->entityTable.Add(this->entity);
	this->mustDeallocateEntity = false;

	this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawAddedEntities | DrawType::DrawPreviewEntities));
	this->graphicView->CaptureImage();
	

}

void ShAddEntityCommand::UnExecute() {
	qDebug("ShAddEntityCommand->UnExecute");

	

	this->graphicView->entityTable.Remove(this->entity);
	this->mustDeallocateEntity = true;

	this->graphicView->update();
	this->graphicView->CaptureImage();

}
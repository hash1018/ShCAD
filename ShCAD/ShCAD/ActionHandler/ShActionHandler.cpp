
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
#include "ShNotifyEvent.h"
ShActionHandler::ShActionHandler(ShGraphicView *graphicView) {

	this->graphicView = graphicView;
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


#include "Command Pattern\ShDeleteEntityCommand.h"
void ShActionHandler::DeleteSelectedEntities() {

	ShDeletedEntitiesMemento *memento = new ShDeletedEntitiesMemento;

	this->graphicView->selectedEntityManager.UnSelectAll();

	ShSelectedEntityManager::Iterator itr = this->graphicView->selectedEntityManager.GetJustUnSelectedBegin();

	while (!itr.IsEnd()) {
		memento->list.append(itr.Current()->CreateMemento());
		itr.Next();
	}

	ShDeleteEntityCommand *command = new ShDeleteEntityCommand(this->graphicView, memento);
	command->Execute();

	this->graphicView->undoTaker.Push(command);

	if (!this->graphicView->redoTaker.IsEmpty())
		this->graphicView->redoTaker.DeleteAll();

}

bool ShActionHandler::UnSelectSelectedEntities() {

	if (this->graphicView->selectedEntityManager.GetSize() > 0) {
		this->graphicView->selectedEntityManager.UnSelectAll();
		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawJustUnSelectedEntities));
		this->graphicView->CaptureImage();
		return true;
	}

	return false;
}


void ShActionHandler::KeyEscPressed() {

	this->UnSelectSelectedEntities();

	ShUpdateListTextEvent event("<Cancel>");
	this->graphicView->Notify(&event);


}

void ShActionHandler::KeyDeletePressed() {

	int size = this->graphicView->selectedEntityManager.GetSize();

	this->DeleteSelectedEntities();

	ShUpdateListTextEvent event("<Delete>",
		ShUpdateListTextEvent::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	ShUpdateListTextEvent event2("All Entities (" + QString::number(size) + ") is deleted.",
		ShUpdateListTextEvent::TextWithoutAnything);
	this->graphicView->Notify(&event2);


}

void ShActionHandler::KeyCtrlAPressed() {

	this->graphicView->selectedEntityManager.SelectAll(&(this->graphicView->entityTable));

	this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
	this->graphicView->CaptureImage();

	ShUpdateListTextEvent event("<SelectAll>",
		ShUpdateListTextEvent::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	int size = this->graphicView->selectedEntityManager.GetSize();

	ShUpdateListTextEvent event2("All Entities (" + QString::number(size) + ") is selected.",
		ShUpdateListTextEvent::TextWithoutAnything);
	this->graphicView->Notify(&event2);

}

void ShActionHandler::KeyCtrlZPressed() {

	QString first, second;

	if (this->graphicView->undoTaker.IsEmpty() == false) {
		ShCommand *command = this->graphicView->undoTaker.Pop();
		command->UnExecute();

		this->graphicView->redoTaker.Push(command);

		first = "<Undo>";
		second = command->GetCommandText() + " UnExecuted.";
	}
	else {

		first = "<Undo>";
		second = "No remaining Undo Command.";
	}

	ShUpdateListTextEvent event(first,
		ShUpdateListTextEvent::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	ShUpdateListTextEvent event2(second,
		ShUpdateListTextEvent::TextWithoutAnything);
	this->graphicView->Notify(&event2);

}

void ShActionHandler::KeyCtrlYPressed() {

	QString first, second;

	if (this->graphicView->redoTaker.IsEmpty() == false) {

		ShCommand *command = this->graphicView->redoTaker.Pop();
		command->Execute();

		this->graphicView->undoTaker.Push(command);

		first = "<Redo>";
		second = command->GetCommandText() + " Executed.";
	}
	else {

		first = "<Redo>";
		second = "No remaining Redo Command.";
	}


	ShUpdateListTextEvent event(first,
		ShUpdateListTextEvent::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	ShUpdateListTextEvent event2(second,
		ShUpdateListTextEvent::TextWithoutAnything);
	this->graphicView->Notify(&event2);

}
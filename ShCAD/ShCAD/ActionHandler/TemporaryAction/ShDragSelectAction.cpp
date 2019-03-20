
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
#include "ShNotifyEvent.h"
ShDragSelectAction::ShDragSelectAction(ShGraphicView *graphicView,
	double firstX, double firstY, Mode mode)
	:ShTemporaryAction(graphicView), firstX(firstX), firstY(firstY), secondX(0), secondY(0), mode(mode) {

	ShUpdateCommandEditHeadTitle event(this->GetActionHeadTitle());
	this->graphicView->Notify(&event);
}

ShDragSelectAction::ShDragSelectAction(ShGraphicView *graphicView, ShActionHandler *previousAction,
	double firstX, double firstY, Mode mode)
	:ShTemporaryAction(graphicView, previousAction), firstX(firstX), firstY(firstY),
	secondX(0), secondY(0), mode(mode) {

	ShUpdateCommandEditHeadTitle event(this->GetActionHeadTitle());
	this->graphicView->Notify(&event);
}

ShDragSelectAction::~ShDragSelectAction() {

}


#include "Visitor Pattern\ShFinder.h"
void ShDragSelectAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {

	
	QLinkedList<ShEntity*> foundList;
	this->FindEntities(ShPoint3d(this->firstX, this->firstY), ShPoint3d(this->secondX, this->secondY), foundList);
	

	if (this->mode == Mode::SelectMode) {

		this->graphicView->selectedEntityManager.Push(foundList);

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
		this->graphicView->CaptureImage();

	}
	else if (this->mode == Mode::UnSelectMode) {

		this->graphicView->selectedEntityManager.Pop(foundList);

		this->graphicView->update(DrawType::DrawAll);
		this->graphicView->CaptureImage();
	}


	ShUpdateCommandEditHeadTitle event2(this->previousAction->GetActionHeadTitle());
	this->graphicView->Notify(&event2);
	this->ReturnToPrevious();
}

void ShDragSelectAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), this->secondX, this->secondY);
	
	data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawActionHandler));
}

#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
void ShDragSelectAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

	if (event->key() == Qt::Key::Key_Escape) {

		ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);

	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
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

QString ShDragSelectAction::GetActionHeadTitle() {
	
	return QString("Specify opposite corner: ");
}

void ShDragSelectAction::FindEntities(const ShPoint3d& first, const ShPoint3d& second, QLinkedList<ShEntity*>& foundList) {

	ShPoint3d topLeft, bottomRight;
	SelectMethod selectMethod;
	this->GetDragRectPoint(first, second, topLeft, bottomRight, selectMethod);

	ShRectFinder::FindMethod findMethod;
	if (selectMethod == SelectMethod::AllPart)
		findMethod = ShRectFinder::AllPartLiesInsideRect;
	else
		findMethod = ShRectFinder::OnePartLiesInsideRect;


	ShEntity *entity;
	ShRectFinder rectFinder(topLeft, bottomRight, &entity, findMethod);

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->graphicView->entityTable.TurnOnLayerBegin(); itr != this->graphicView->entityTable.TurnOnLayerEnd(); ++itr) {

		entity = 0;
		(*itr)->Accept(&rectFinder);

		if (entity != 0)
			foundList.append((*itr));
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShModifyDragSelectAction::ShModifyDragSelectAction(ShGraphicView *graphicView, double firstX, double firstY, Mode mode)
	:ShDragSelectAction(graphicView, firstX, firstY, mode) {

}

ShModifyDragSelectAction::ShModifyDragSelectAction(ShGraphicView *graphicView, ShActionHandler *previousAction,
	double firstX, double firstY, Mode mode)
	: ShDragSelectAction(graphicView, previousAction, firstX, firstY, mode) {

	ShUpdateCommandEditHeadTitle event(this->GetActionHeadTitle());
	this->graphicView->Notify(&event);
}

ShModifyDragSelectAction::~ShModifyDragSelectAction() {


}

void ShModifyDragSelectAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {

	QLinkedList<ShEntity*> foundList;
	this->FindEntities(ShPoint3d(this->firstX, this->firstY), ShPoint3d(this->secondX, this->secondY), foundList);

	int foundCount = foundList.count();

	if (this->mode == Mode::SelectMode) {
		
		int duplicateCount = this->AlreadySelectedCount(foundList);

		this->graphicView->selectedEntityManager.Push(foundList);
		int totalCount = this->graphicView->selectedEntityManager.GetSize();

		this->UpdateListTextSelectMode(foundCount, duplicateCount, totalCount);

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
		this->graphicView->CaptureImage();

	}
	else if (this->mode == Mode::UnSelectMode) {

		int removeCount = this->AlreadySelectedCount(foundList);

		this->graphicView->selectedEntityManager.Pop(foundList);
		int totalCount = this->graphicView->selectedEntityManager.GetSize();

		this->UpdateListTextUnSelectMode(foundCount, removeCount, totalCount);

	
		this->graphicView->update(DrawType::DrawAll);
		this->graphicView->CaptureImage();

	}

	ShUpdateCommandEditHeadTitle event2(this->previousAction->GetActionHeadTitle());
	this->graphicView->Notify(&event2);
	this->ReturnToPrevious();
}

void ShModifyDragSelectAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

	if (event->key() == Qt::Key::Key_Escape) {
		ShUpdateCommandEditHeadTitle event2(this->previousAction->GetActionHeadTitle());
		this->graphicView->Notify(&event2);
		this->graphicView->update((DrawType)DrawCaptureImage);
		this->ReturnToPrevious();
		

	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}

QString ShModifyDragSelectAction::GetActionHeadTitle() {

	return this->previousAction->GetActionHeadTitle() + ShDragSelectAction::GetActionHeadTitle();
}

void ShModifyDragSelectAction::UpdateListTextSelectMode(int foundCount, int duplicateCount, int totalCount) {

	if (duplicateCount == 0) {

		ShUpdateListTextEvent event2(QString::number(foundCount) +
			" found, " + QString::number(totalCount) + " total",
			ShUpdateListTextEvent::UpdateType::editTextWithText);

		this->graphicView->Notify(&event2);
	}
	else {
		ShUpdateListTextEvent event2(QString::number(foundCount) +
			" found (" + QString::number(duplicateCount) + " duplicate), " +
			QString::number(totalCount) + " total",
			ShUpdateListTextEvent::UpdateType::editTextWithText);

		this->graphicView->Notify(&event2);
	}
}

void ShModifyDragSelectAction::UpdateListTextUnSelectMode(int foundCount, int removedCount, int totalCount) {

	if (removedCount == 0) {
		ShUpdateListTextEvent event(QString::number(foundCount) + " found, " +
			QString::number(totalCount) + " total",
			ShUpdateListTextEvent::UpdateType::editTextWithText);

		this->graphicView->Notify(&event);
	}
	else {
		ShUpdateListTextEvent event(QString::number(foundCount) + " found, " +
			QString::number(removedCount) + " removed, " + QString::number(totalCount) + " total",
			ShUpdateListTextEvent::UpdateType::editTextWithText);

		this->graphicView->Notify(&event);
	}
}

int ShModifyDragSelectAction::AlreadySelectedCount(const QLinkedList<ShEntity*>& foundList) {
	
	int duplicateCount = 0;

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = const_cast<QLinkedList<ShEntity*>&>(foundList).begin(); itr !=
		const_cast<QLinkedList<ShEntity*>&>(foundList).end(); ++itr) {

		if ((*itr)->IsSelected() == true)
			duplicateCount++;
	}

	return duplicateCount;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////


ShModifyStretchDragSelectAction::ShModifyStretchDragSelectAction(ShGraphicView *graphicView,
	double firstX, double firstY,
	QLinkedList<ShEntity*> *stretchList, QLinkedList<VertexPoint> *vertexList, Mode mode)
	:ShModifyDragSelectAction(graphicView, firstX, firstY, mode), stretchList(stretchList), vertexList(vertexList) {

}

ShModifyStretchDragSelectAction::ShModifyStretchDragSelectAction(ShGraphicView *graphicView, ShActionHandler *previousAction,
	QLinkedList<ShEntity*> *stretchList, QLinkedList<VertexPoint> *vertexList,
	double firstX, double firstY, Mode mode)
	: ShModifyDragSelectAction(graphicView, previousAction, firstX, firstY, mode), stretchList(stretchList), vertexList(vertexList) {

}


ShModifyStretchDragSelectAction::~ShModifyStretchDragSelectAction() {

}


void ShModifyStretchDragSelectAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {

	QLinkedList<ShEntity*> foundList;
	this->FindEntities(ShPoint3d(this->firstX, this->firstY), ShPoint3d(this->secondX, this->secondY), foundList);

	int foundCount = foundList.count();

	if (this->mode == Mode::SelectMode) {

		QLinkedList<ShEntity*> unSelectedList;
		this->GetUnSelectedList(foundList, unSelectedList);
		this->FindStretchPointAndAddList(unSelectedList);



		int duplicateCount = this->AlreadySelectedCount(foundList);
		
		this->graphicView->selectedEntityManager.Push(foundList);
		int totalCount = this->graphicView->selectedEntityManager.GetSize();

		this->UpdateListTextSelectMode(foundCount, duplicateCount, totalCount);

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
		this->graphicView->CaptureImage();

	}
	else if (this->mode == Mode::UnSelectMode) {

		QLinkedList<ShEntity*> selectedList;
		this->GetAlreadySelectedList(foundList, selectedList);
		this->RemoveStretchPointAndList(selectedList);


		int removeCount = this->AlreadySelectedCount(foundList);

		this->graphicView->selectedEntityManager.Pop(foundList);
		int totalCount = this->graphicView->selectedEntityManager.GetSize();

		this->UpdateListTextUnSelectMode(foundCount, removeCount, totalCount);


		this->graphicView->update(DrawType::DrawAll);
		this->graphicView->CaptureImage();

	}

	ShUpdateCommandEditHeadTitle event2(this->previousAction->GetActionHeadTitle());
	this->graphicView->Notify(&event2);
	this->ReturnToPrevious();
}

void ShModifyStretchDragSelectAction::GetUnSelectedList(const QLinkedList<ShEntity*>& foundList, QLinkedList<ShEntity*>& unSelectedList) {

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = const_cast<QLinkedList<ShEntity*>&>(foundList).begin();
		itr != const_cast<QLinkedList<ShEntity*>&>(foundList).end(); ++itr) {

		if ((*itr)->IsSelected() == false)
			unSelectedList.append((*itr));
	}

}

void ShModifyStretchDragSelectAction::GetAlreadySelectedList(const QLinkedList<ShEntity*>& foundList, QLinkedList<ShEntity*>& selectedList) {
	
	QLinkedList<ShEntity*>::iterator itr;
	for (itr = const_cast<QLinkedList<ShEntity*>&>(foundList).begin();
		itr != const_cast<QLinkedList<ShEntity*>&>(foundList).end(); ++itr) {

		if ((*itr)->IsSelected() == true)
			selectedList.append((*itr));
	}

}

#include "Visitor Pattern\ShStretchVisitor.h"
void ShModifyStretchDragSelectAction::FindStretchPointAndAddList(const QLinkedList<ShEntity*>& unSelectedList) {
	//unselected Entities, that is about to be selected. 
	//Find Stretch Point and store into list.

	ShPoint3d topLeft, bottomRight;
	SelectMethod selectMethod;
	this->GetDragRectPoint(ShPoint3d(this->firstX, this->firstY), ShPoint3d(this->secondX, this->secondY),
		topLeft, bottomRight, selectMethod);

	VertexPoint vertexPoint;
	
	if (selectMethod == SelectMethod::AllPart) {
		ShFindStretchMovePointVisitor visitor(vertexPoint);
		QLinkedList<ShEntity*>::iterator itr;
		for (itr = const_cast<QLinkedList<ShEntity*>&>(unSelectedList).begin();
			itr != const_cast<QLinkedList<ShEntity*>&>(unSelectedList).end(); ++itr) {

			(*itr)->Accept(&visitor);
			this->stretchList->append((*itr));
			this->vertexList->append(vertexPoint);
		}
	}
	else {
		ShFindStretchPointWithRectVisitor visitor(vertexPoint, topLeft, bottomRight);
		QLinkedList<ShEntity*>::iterator itr;
		for (itr = const_cast<QLinkedList<ShEntity*>&>(unSelectedList).begin();
			itr != const_cast<QLinkedList<ShEntity*>&>(unSelectedList).end(); ++itr) {

			(*itr)->Accept(&visitor);
			this->stretchList->append((*itr));
			this->vertexList->append(vertexPoint);
		}

	}

}

void ShModifyStretchDragSelectAction::RemoveStretchPointAndList(const QLinkedList<ShEntity*>& selectedList) {
	
	QLinkedList<VertexPoint>::iterator verItr;
	QLinkedList<ShEntity*>::iterator subItr;
	int index = 0;
	int i = 0;
	QLinkedList<ShEntity*>::iterator itr;
	for (itr = const_cast<QLinkedList<ShEntity*>&>(selectedList).begin();
		itr != const_cast<QLinkedList<ShEntity*>&>(selectedList).end(); ++itr) {

		index = 0;
		subItr = this->stretchList->begin();
		while (subItr != this->stretchList->end() && (*subItr) != (*itr)) {
			index++;
			++subItr;
		}

		this->stretchList->removeOne((*itr));

		verItr = this->vertexList->begin();
		i = 0;
		while (i < index) {
			++verItr;
			i++;
		}
		this->vertexList->erase(verItr);
	}

}
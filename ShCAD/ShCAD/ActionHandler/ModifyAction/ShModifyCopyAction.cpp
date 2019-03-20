
#include "ShModifyCopyAction.h"
#include <QKeyEvent>
#include "ShNotifyEvent.h"
#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Entity\Composite\ShPreview.h"
ShModifyCopyAction::ShModifyCopyAction(ShGraphicView *graphicView)
	:ShModifyAction(graphicView), status(SelectingEntities) {

	ShUpdateListTextEvent event("_Copy", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	QString headTitle = this->GetActionHeadTitle();

	ShUpdateCommandEditHeadTitle event2(headTitle);
	this->graphicView->Notify(&event2);
}

#include "Command Pattern\Entity Command\ShCopyEntityCommand.h"
ShModifyCopyAction::~ShModifyCopyAction() {

	if (this->copiedEntityList.count() != 0) {
	
		ShCopyEntityCommand *command = new ShCopyEntityCommand(this->graphicView, this->copiedEntityList);

		this->graphicView->undoTaker.Push(command);

		if (!this->graphicView->redoTaker.IsEmpty())
			this->graphicView->redoTaker.DeleteAll();
	}
}


#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
void ShModifyCopyAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {

	if (this->status == SelectingEntities) {

		ShPoint3d point = this->graphicView->GetCursorPoint();
		ShEntity* entity = this->graphicView->entityTable.FindEntity(point.x, point.y, this->graphicView->GetZoomRate());

		if (entity == 0) {

			if (event->modifiers() == Qt::ShiftModifier)
				this->graphicView->SetTemporaryAction(new ShModifyDragSelectAction(this->graphicView, this, point.x, point.y,
					ShDragSelectAction::Mode::UnSelectMode));
			else
				this->graphicView->SetTemporaryAction(new ShModifyDragSelectAction(this->graphicView, this, point.x, point.y));

			return;
		}

		this->DoFollowUpWithFoundEntity(entity, event->modifiers());

	}
	else if (this->status == FinishedSelectingEntities) {

		this->status = PickedBasePoint;
		this->base = data.GetPoint();

		this->graphicView->rubberBand = new ShRubberBand(ShLineData(this->base, data.GetNextPoint()));

		QLinkedList<ShEntity*>::iterator itr;
		for (itr = this->graphicView->selectedEntityManager.Begin();
			itr != this->graphicView->selectedEntityManager.End();
			++itr) {
			this->graphicView->preview.Add((*itr)->Clone());
		}

		double disX = data.GetNextPoint().x - data.GetPoint().x;
		double disY = data.GetNextPoint().y - data.GetPoint().y;

		for (itr = this->graphicView->preview.Begin();
			itr != this->graphicView->preview.End();
			++itr) {
			(*itr)->Move(disX, disY);
		}

		this->previous.x = data.GetNextPoint().x;
		this->previous.y = data.GetNextPoint().y;

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		this->UpdateNextListText();
	}
	else if (this->status == PickedBasePoint) {

		double disX = data.GetPoint().x - this->previous.x;
		double disY = data.GetPoint().y - this->previous.y;

		QLinkedList<ShEntity*> list;
		QLinkedList<ShEntity*>::iterator itr;
		for (itr = this->graphicView->preview.Begin();
			itr != this->graphicView->preview.End();
			++itr) {
			(*itr)->Move(disX, disY);
			ShEntity *copiedEntity = (*itr)->Clone();
			list.append(copiedEntity);
			this->copiedEntityList.append(copiedEntity);
		}

		this->graphicView->entityTable.Add(list);

		for (itr = this->graphicView->preview.Begin();
			itr != this->graphicView->preview.End();
			++itr) {
			(*itr)->Move(-disX, -disY);
		}

		

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawAddedEntities));
		this->graphicView->CaptureImage();

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));


	}
}

void ShModifyCopyAction::RMousePressEvent(QMouseEvent *event, ShActionData& data) {

	if (this->status == SelectingEntities) {

		if (this->graphicView->selectedEntityManager.GetSize() != 0) {

			this->status = FinishedSelectingEntities;

			this->UpdateNextListText();

			this->graphicView->setCursor(this->GetCursorShape());

		}
		else {
			ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
			this->graphicView->ChangeCurrentAction(strategy);
		}
	}


}

void ShModifyCopyAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	if (this->status == PickedBasePoint) {

		this->graphicView->rubberBand->SetEnd(data.GetPoint());

		QLinkedList<ShEntity*>::iterator itr;
		double disX = data.GetPoint().x - this->previous.x;
		double disY = data.GetPoint().y - this->previous.y;

		for (itr = this->graphicView->preview.Begin();
			itr != this->graphicView->preview.End();
			++itr) {
			(*itr)->Move(disX, disY);
		}

		this->previous.x = data.GetPoint().x;
		this->previous.y = data.GetPoint().y;


		data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}


void ShModifyCopyAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

	if (event->key() == Qt::Key::Key_Escape) {

		ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);

	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}

ActionType ShModifyCopyAction::GetType() {

	return ActionType::ActionModifyCopy;
}

#include <qpainter.h>
QCursor ShModifyCopyAction::GetCursorShape() {

	if (this->status == Status::SelectingEntities) {
		QPixmap pix(32, 32);
		pix.fill(Qt::transparent); // Otherwise you get a black background :(
		QPainter painter(&pix);
		painter.setPen(QColor(255, 255, 255));
		painter.drawRect(13, 13, 6, 6);

		return QCursor(pix);
	}

	return QCursor(Qt::CursorShape::CrossCursor);
}

QString ShModifyCopyAction::GetActionHeadTitle() {

	QString str = "";

	if (this->status == SelectingEntities) {
		str = "Copy >> Select objects: ";
	}
	else if (this->status == FinishedSelectingEntities) {
		str = "Copy >> Specify base point: ";
	}
	else if (this->status == PickedBasePoint) {
		str = "Copy >> Specify second point: ";
	}

	return str;
}

void ShModifyCopyAction::IsAllowedDraftOperation(ShAllowedDraftData &data) {

	if (this->status == Status::SelectingEntities)
		return;

	if (this->status == Status::FinishedSelectingEntities) {
		data.SetAllowOrthogonal(true);
		data.SetAllowtSnap(true);

		ShPoint3d mouse = this->graphicView->GetCursorPoint();
		data.SetOrthogonalBasePoint(mouse);
		data.SetSnapBasePoint(mouse);
	}
	else if (this->status == Status::PickedBasePoint) {

		data.SetAllowOrthogonal(true);
		data.SetAllowtSnap(true);

		ShPoint3d point = this->graphicView->rubberBand->GetStart();
		data.SetOrthogonalBasePoint(point);
		data.SetSnapBasePoint(point);
	}

}

void ShModifyCopyAction::ApplyOrthogonalShape(bool on) {

	if (this->status == Status::PickedBasePoint) {

		ShPoint3d mouse = this->graphicView->GetCursorPoint();

		if (on == true) {
			ShPoint3d orth;
			ShPoint3d start = this->graphicView->rubberBand->GetStart();
			this->GetOrthogonal(start.x, start.y, mouse.x, mouse.y, orth.x, orth.y);
			this->graphicView->rubberBand->SetEnd(orth);
		}
		else
			this->graphicView->rubberBand->SetEnd(mouse);

		ShPoint3d end = this->graphicView->rubberBand->GetEnd();

		QLinkedList<ShEntity*>::iterator itr;
		double disX = end.x - this->previous.x;
		double disY = end.y - this->previous.y;

		for (itr = this->graphicView->preview.Begin();
			itr != this->graphicView->preview.End();
			++itr) {
			(*itr)->Move(disX, disY);
		}

		this->previous.x = end.x;
		this->previous.y = end.y;

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}

}

void ShModifyCopyAction::UpdateNextListText() {

	ShUpdateListTextEvent event("");
	this->graphicView->Notify(&event);

	ShUpdateCommandEditHeadTitle event2(this->GetActionHeadTitle());
	this->graphicView->Notify(&event2);
}


#include "ShModifyRotateAction.h"
#include <QKeyEvent>
#include "ShNotifyEvent.h"
#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Entity\Composite\ShPreview.h"
#include "ShMath.h"
#include "Visitor Pattern\ShRotater.h"
ShModifyRotateAction::ShModifyRotateAction(ShGraphicView *graphicView)
	:ShModifyAction(graphicView), status(SelectingEntities) {

	ShUpdateListTextEvent event("_Rotate", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	QString headTitle = this->GetActionHeadTitle();

	ShUpdateCommandEditHeadTitle event2(headTitle);
	this->graphicView->Notify(&event2);
}

ShModifyRotateAction::~ShModifyRotateAction() {

}

#include "Command Pattern\Entity Command\ShRotateEntityCommand.h"
#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
void ShModifyRotateAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {

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

		double angle = Math::GetAbsAngle(this->base.x, this->base.y, data.GetNextPoint().x, data.GetNextPoint().y);

		ShRotater rotater(this->base, angle);
		for (itr = this->graphicView->preview.Begin();
			itr != this->graphicView->preview.End();
			++itr) {
			(*itr)->Accept(&rotater);
		}

		this->previousAngle = angle;

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		this->UpdateNextListText();
	}
	else if (this->status == PickedBasePoint) {

		double angle = Math::GetAbsAngle(this->base.x, this->base.y, data.GetPoint().x, data.GetPoint().y);
		ShRotater rotater(this->base, angle);

		QLinkedList<ShEntity*> list;
		QLinkedList<ShEntity*>::iterator itr;
		for (itr = this->graphicView->selectedEntityManager.Begin();
			itr != this->graphicView->selectedEntityManager.End();
			++itr) {

			(*itr)->Accept(&rotater);
			list.append((*itr));
		}

		ShRotateEntityCommand *command = new ShRotateEntityCommand(this->graphicView, list, this->base, angle);
		this->graphicView->undoTaker.Push(command);

		if (!this->graphicView->redoTaker.IsEmpty())
			this->graphicView->redoTaker.DeleteAll();
		

		ShChangeCurrentActionCurrentFinished strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);

	}
}

void ShModifyRotateAction::RMousePressEvent(QMouseEvent *event, ShActionData& data) {

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

void ShModifyRotateAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	if (this->status == PickedBasePoint) {

		this->graphicView->rubberBand->SetEnd(data.GetPoint());

		double angle = Math::GetAbsAngle(this->base.x, this->base.y, data.GetPoint().x, data.GetPoint().y);

		ShRotater rotater(this->base, angle - this->previousAngle);

		QLinkedList<ShEntity*>::iterator itr;
		for (itr = this->graphicView->preview.Begin();
			itr != this->graphicView->preview.End();
			++itr) {
			(*itr)->Accept(&rotater);
		}

		this->previousAngle = angle;
	


		data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}


void ShModifyRotateAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

	if (event->key() == Qt::Key::Key_Escape) {

		ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);

	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}

ActionType ShModifyRotateAction::GetType() {

	return ActionType::ActionModifyRotate;
}

#include <qpainter.h>
QCursor ShModifyRotateAction::GetCursorShape() {

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

QString ShModifyRotateAction::GetActionHeadTitle() {

	QString str = "";

	if (this->status == SelectingEntities) {
		str = "Rotate >> Select objects: ";
	}
	else if (this->status == FinishedSelectingEntities) {
		str = "Rotate >> Specify base point: ";
	}
	else if (this->status == PickedBasePoint) {
		str = "Rotate >> Specify rotation angle: ";
	}

	return str;
}

void ShModifyRotateAction::IsAllowedDraftOperation(ShAllowedDraftData &data) {

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

void ShModifyRotateAction::ApplyOrthogonalShape(bool on) {

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

		double angle = Math::GetAbsAngle(this->base.x, this->base.y, end.x, end.y);

		ShRotater rotater(this->base, angle - this->previousAngle);

		QLinkedList<ShEntity*>::iterator itr;
		for (itr = this->graphicView->preview.Begin();
			itr != this->graphicView->preview.End();
			++itr) {
			(*itr)->Accept(&rotater);
		}

		this->previousAngle = angle;

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}

}

void ShModifyRotateAction::UpdateNextListText() {

	ShUpdateListTextEvent event("");
	this->graphicView->Notify(&event);

	ShUpdateCommandEditHeadTitle event2(this->GetActionHeadTitle());
	this->graphicView->Notify(&event2);
}

#include "ShModifyExtendAction.h"
#include <QKeyEvent>
#include "ShNotifyEvent.h"
#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
ShModifyExtendAction::ShModifyExtendAction(ShGraphicView *graphicView)
	:ShModifyAction(graphicView), status(SelectingEntities) {

	ShUpdateListTextEvent event("_Extend", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	QString headTitle = this->GetActionHeadTitle();

	ShUpdateCommandEditHeadTitle event2(headTitle);
	this->graphicView->Notify(&event2);
}

ShModifyExtendAction::~ShModifyExtendAction() {

}

#include "Visitor Pattern\ShExtender.h"
#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
#include "Strategy Pattern\ShSearchEntityStrategy.h"
#include "Command Pattern\Entity Command\ShExtendEntityCommand.h"
void ShModifyExtendAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {

	if (this->status == SelectingEntities) {

		ShPoint3d point = this->graphicView->GetCursorPoint();
		ShEntity *entity;
		ShSearchEntityUniqueStrategy strategy(&entity, point.x, point.y, this->graphicView->GetZoomRate());
		this->graphicView->entityTable.Search(strategy);

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

		ShPoint3d point = this->graphicView->GetCursorPoint();

		ShEntity *entity;
		ShSearchEntityUniqueStrategy strategy(&entity, point.x, point.y, this->graphicView->GetZoomRate());
		this->graphicView->entityTable.Search(strategy);

		if (entity == 0)
			return;
		
		if (entity->IsSelected() == true)
			return;

		QLinkedList<ShEntity*> baseEntities;
		QLinkedList<ShEntity*>::iterator itr;
		for (itr = this->graphicView->selectedEntityManager.Begin();
			itr != this->graphicView->selectedEntityManager.End();
			++itr)
			baseEntities.append((*itr));


		ShEntity *original = 0;
		ShEntity *extendedEntity;
		bool isValid = false;

		ShExtender visitor(this->graphicView, baseEntities, point, &original, &extendedEntity, isValid);
		entity->Accept(&visitor);

		if (isValid == true) {

			ShExtendEntityCommand *command = new ShExtendEntityCommand(this->graphicView, original, extendedEntity);

			this->graphicView->undoTaker.Push(command);

			if (!this->graphicView->redoTaker.IsEmpty())
				this->graphicView->redoTaker.DeleteAll();
		}
		
	}
}

void ShModifyExtendAction::RMousePressEvent(QMouseEvent *event, ShActionData& data) {

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

void ShModifyExtendAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	
}


void ShModifyExtendAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

	if (event->key() == Qt::Key::Key_Escape) {

		ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);

	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}

ActionType ShModifyExtendAction::GetType() {

	return ActionType::ActionModifyExtend;
}

#include <qpainter.h>
QCursor ShModifyExtendAction::GetCursorShape() {

	
	QPixmap pix(32, 32);
	pix.fill(Qt::transparent); // Otherwise you get a black background :(
	QPainter painter(&pix);
	painter.setPen(QColor(255, 255, 255));
	painter.drawRect(13, 13, 6, 6);

	return QCursor(pix);

}

QString ShModifyExtendAction::GetActionHeadTitle() {

	QString str = "";

	if (this->status == SelectingEntities) {
		str = "Extend >> Select objects: ";
	}
	else if (this->status == FinishedSelectingEntities) {
		str = "Extend >> Select object to extend: ";
	}

	return str;
}



void ShModifyExtendAction::UpdateNextListText() {

	ShUpdateListTextEvent event("");
	this->graphicView->Notify(&event);

	ShUpdateCommandEditHeadTitle event2(this->GetActionHeadTitle());
	this->graphicView->Notify(&event2);
}
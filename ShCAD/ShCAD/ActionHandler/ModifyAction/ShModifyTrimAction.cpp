
#include "ShModifyTrimAction.h"
#include <QKeyEvent>
#include "ShNotifyEvent.h"
#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
ShModifyTrimAction::ShModifyTrimAction(ShGraphicView *graphicView)
	:ShModifyAction(graphicView), status(SelectingEntities) {

	ShUpdateListTextEvent event("_Trim", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	QString headTitle = this->GetActionHeadTitle();

	ShUpdateCommandEditHeadTitle event2(headTitle);
	this->graphicView->Notify(&event2);
}

ShModifyTrimAction::~ShModifyTrimAction() {

}

#include "Visitor Pattern\ShTrimer.h"
#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
#include "Strategy Pattern\ShSearchEntityStrategy.h"
void ShModifyTrimAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {

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

		ShTrimer visitor(this->graphicView, baseEntities, point);
		entity->Accept(&visitor);

	}
}

void ShModifyTrimAction::RMousePressEvent(QMouseEvent *event, ShActionData& data) {

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

void ShModifyTrimAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {


}


void ShModifyTrimAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

	if (event->key() == Qt::Key::Key_Escape) {

		ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);

	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}

ActionType ShModifyTrimAction::GetType() {

	return ActionType::ActionModifyTrim;
}

#include <qpainter.h>
QCursor ShModifyTrimAction::GetCursorShape() {


	QPixmap pix(32, 32);
	pix.fill(Qt::transparent); // Otherwise you get a black background :(
	QPainter painter(&pix);
	painter.setPen(QColor(255, 255, 255));
	painter.drawRect(13, 13, 6, 6);

	return QCursor(pix);

}

QString ShModifyTrimAction::GetActionHeadTitle() {

	QString str = "";

	if (this->status == SelectingEntities) {
		str = "Trim >> Select objects: ";
	}
	else if (this->status == FinishedSelectingEntities) {
		str = "Trim >> Select object to trim: ";
	}

	return str;
}



void ShModifyTrimAction::UpdateNextListText() {

	ShUpdateListTextEvent event("");
	this->graphicView->Notify(&event);

	ShUpdateCommandEditHeadTitle event2(this->GetActionHeadTitle());
	this->graphicView->Notify(&event2);
}
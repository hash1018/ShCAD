


#include "ShModifyEraseAction.h"
#include <QKeyEvent>
#include "ShNotifyEvent.h"
#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Entity\Composite\ShPreview.h"
#include "ShMath.h"

ShModifyEraseAction::ShModifyEraseAction(ShGraphicView *graphicView)
	:ShModifyAction(graphicView), status(SelectingEntities) {

	ShUpdateListTextEvent event("_Erase", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	QString headTitle = this->GetActionHeadTitle();

	ShUpdateCommandEditHeadTitle event2(headTitle);
	this->graphicView->Notify(&event2);
}

ShModifyEraseAction::~ShModifyEraseAction() {

}

#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
void ShModifyEraseAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {

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
	
}

#include "Facade Pattern\ShCadFacade.h"
void ShModifyEraseAction::RMousePressEvent(QMouseEvent *event, ShActionData& data) {

	if (this->status == SelectingEntities) {

		if (this->graphicView->selectedEntityManager.GetSize() != 0) {

			this->UpdateNextListText();

			ShCadFacade::Delete(this->graphicView);

			ShChangeCurrentActionCurrentFinished strategy(ActionType::ActionDefault);
			this->graphicView->ChangeCurrentAction(strategy);

		}
		else {
			ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
			this->graphicView->ChangeCurrentAction(strategy);
		}
	}


}

void ShModifyEraseAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

}


void ShModifyEraseAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

	if (event->key() == Qt::Key::Key_Escape) {

		ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);

	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}

ActionType ShModifyEraseAction::GetType() {

	return ActionType::ActionModifyErase;
}

#include <qpainter.h>
QCursor ShModifyEraseAction::GetCursorShape() {

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

QString ShModifyEraseAction::GetActionHeadTitle() {

	QString str = "";

	if (this->status == SelectingEntities) {
		str = "Erase >> Select objects: ";
	}
	

	return str;
}

void ShModifyEraseAction::IsAllowedDraftOperation(ShAllowedDraftData &data) {

	if (this->status == Status::SelectingEntities)
		return;

}

void ShModifyEraseAction::ApplyOrthogonalShape(bool on) {

}

void ShModifyEraseAction::UpdateNextListText() {

	ShUpdateListTextEvent event("");
	this->graphicView->Notify(&event);

	ShUpdateCommandEditHeadTitle event2(this->GetActionHeadTitle());
	this->graphicView->Notify(&event2);
}
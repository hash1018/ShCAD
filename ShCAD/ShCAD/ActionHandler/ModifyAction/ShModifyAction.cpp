
#include "ShModifyAction.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include <QMouseEvent>
#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include <qpainter.h>
#include "Base\ShCursorShape.h"


ShModifyAction::ShModifyAction(ShCADWidget *widget)
	:ShActionHandler(widget), status(Status::SelectingEntities) {

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowKey(KeyType::Enter).
		allowKey(KeyType::Return).
		allowKey(KeyType::Control_A).
		allowKey(KeyType::EscCancelCurrent).
		allowInput().
		build();
}

ShModifyAction::~ShModifyAction() {

}

QCursor ShModifyAction::getCursorShape() {

	QCursor cursor;

	if (this->status == Status::SelectingEntities ||
		this->status == Status::SelectingEntityToModify) {
		
		cursor = ShCursorShape::getCursor(ShCursorShape::CursorType::Selecting);
	}

	else if (this->status == Status::PickingBasePoint ||
		this->status == Status::PickingSecondPoint ||
		this->status == Status::InputtingNumber) {

		cursor = ShCursorShape::getCursor(ShCursorShape::CursorType::Drawing);
	}
	

	return cursor;
}

ShAvailableDraft ShModifyAction::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->status == Status::PickingBasePoint) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->widget->getMousePoint());
		draft.setSnapBasePoint(this->widget->getMousePoint());
	}
	else if (this->status == Status::PickingSecondPoint) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->widget->getRubberBand().getStart());
		draft.setSnapBasePoint(this->widget->getRubberBand().getStart());
	}

	return draft;
}


void ShModifyAction::selectFoundEntity(ShEntity *foundEntity, Qt::KeyboardModifiers modifier) {

	if (modifier == Qt::Modifier::SHIFT) {
	
		if (foundEntity->isSelected() == true) {
		
			this->widget->getSelectedEntities()->remove(foundEntity);
			int size = this->widget->getSelectedEntities()->getSize();

			shCommandLogManager->appendListEditTextWith("1 found, 1 removed, " + QString::number(size) + " total");

			this->widget->update(DrawType::DrawAll);
			this->widget->captureImage();
		}
		else {
		
			int size = this->widget->getSelectedEntities()->getSize();

			shCommandLogManager->appendListEditTextWith("1 found, " + QString::number(size) + " total");
			
		}
	}
	else {
	
		if (foundEntity->isSelected() == true) {
		
			int size = this->widget->getSelectedEntities()->getSize();

			shCommandLogManager->appendListEditTextWith("1 found (1 duplicate), " + QString::number(size) + " total");

		}
		else {
		
			this->widget->getSelectedEntities()->add(foundEntity);
			int size = this->widget->getSelectedEntities()->getSize();

			shCommandLogManager->appendListEditTextWith("1 found, " + QString::number(size) + " total");

			this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
			this->widget->captureImage();
		}

	}
}

void ShModifyAction::triggerSelectingEntities(QMouseEvent *event) {

	ShPoint3d point = this->widget->getMousePoint();

	ShEntity *entity = nullptr;
	ShSearchEntityUniqueStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr) {
	
		if (event->modifiers() == Qt::ShiftModifier) {
			ShChangeTemporaryStrategy strategy(new ShModifyDragSelectAction(this->widget, point.x, point.y, ShDragSelectAction::Mode::UnSelectMode), this);
			this->widget->changeAction(strategy);
		}
		else {
			ShChangeTemporaryStrategy strategy(new ShModifyDragSelectAction(this->widget, point.x, point.y), this);
			this->widget->changeAction(strategy);
		}
			
	}
	else {
	
		this->selectFoundEntity(entity, event->modifiers());
	}

}

void ShModifyAction::finishSelectingEntities() {

	this->keyHandler->disAllowKey(KeyType::Control_A);
}

#include "ShModifyCopyAction.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "Entity\Private\ShMover.h"
#include "UnRedo\ShEntityTransaction.h"
#include "Base\ShGlobal.h"
#include "Command\ShAvailableCommands.h"
#include "Base\ShCursorShape.h"
#include "KeyHandler\ShKeyHandler.h"

ShModifyCopyAction::ShModifyCopyAction(ShCADWidget *widget)
	:ShModifyAction(widget), transaction(nullptr), status(Status::SelectingEntities) {

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowKey(KeyType::Enter).
		allowKey(KeyType::Return).
		allowKey(KeyType::Control_A).
		allowKey(KeyType::EscCancelCurrent).
		allowInput().
		build();

}

ShModifyCopyAction::~ShModifyCopyAction() {

}

void ShModifyCopyAction::mouseLeftPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {

		this->triggerSelectingEntities(data.mouseEvent);
	}
	else {
	
		this->trigger(data.point);
	}
	
}

void ShModifyCopyAction::mouseRightPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {
		this->finishSelectingEntities();
	}
	
}

void ShModifyCopyAction::mouseMoveEvent(ShActionData &data) {

	if (this->status == Status::PickingSecondPoint) {

		this->invalidate(data.point);
	}
}

ActionType ShModifyCopyAction::getType() {

	return ActionType::ActionModifyCopy;
}

QString ShModifyCopyAction::getHeadTitle() {

	QString text;

	if (this->status == Status::SelectingEntities) {
		text = "Copy >> " + shGetLanValue_command("Command/Select objects") + ": ";
	}
	else if (this->status == Status::PickingBasePoint) {
		text = "Copy >> " + shGetLanValue_command("Command/Specify base point") + ": ";
	}
	else if (this->status == Status::PickingSecondPoint) {
		text = "Copy >> " + shGetLanValue_command("Command/Specify second point") + ": ";
	}

	return text;
}

QCursor ShModifyCopyAction::getCursorShape() {

	QCursor cursor;

	if (this->status == Status::SelectingEntities){

		cursor = ShCursorShape::getCursor(ShCursorShape::CursorType::Selecting);
	}

	else if (this->status == Status::PickingBasePoint ||
		this->status == Status::PickingSecondPoint) {

		cursor = ShCursorShape::getCursor(ShCursorShape::CursorType::Drawing);
	}


	return cursor;
}

ShAvailableDraft ShModifyCopyAction::getAvailableDraft() {

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


void ShModifyCopyAction::trigger(const ShPoint3d &point) {

	if (this->status == Status::PickingBasePoint) {

		this->status = PickingSecondPoint;
		this->base = point;

		this->widget->getRubberBand().create(ShLineData(this->base, this->base));

		auto itr = this->widget->getSelectedEntities()->begin();

		for (itr; itr != this->widget->getSelectedEntities()->end(); ++itr) {

			this->widget->getPreview().add((*itr)->clone());
		}


		this->previous = this->base;

		this->setLastBasePoint(point);
		this->triggerSucceeded();

	}
	else if (this->status == Status::PickingSecondPoint) {

		double disX = point.x - this->previous.x;
		double disY = point.y - this->previous.y;

		ShMover mover(disX, disY);

		QLinkedList<ShEntity*> list;
		ShEntity *copiedEntity;

		auto itr = this->widget->getPreview().begin();
		for (itr; itr != this->widget->getPreview().end(); ++itr) {

			(*itr)->accept(&mover);
			copiedEntity = (*itr)->clone();
			list.append(copiedEntity);
		}

		ShMover mover2(-disX, -disY);
		for (itr = this->widget->getPreview().begin(); itr != this->widget->getPreview().end(); ++itr)
			(*itr)->accept(&mover2);


		this->addCopiedEntities(list);

		
		this->triggerSucceeded();
	}
}

void ShModifyCopyAction::invalidate(ShPoint3d &point) {

	if (this->status == Status::PickingSecondPoint) {

		this->widget->getRubberBand().setEnd(point);

		double disX = point.x - this->previous.x;
		double disY = point.y - this->previous.y;

		ShMover mover(disX, disY);

		auto itr = this->widget->getPreview().begin();

		for (itr; itr != this->widget->getPreview().end(); ++itr) {

			(*itr)->accept(&mover);
		}

		this->previous = point;

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

void ShModifyCopyAction::finishSelectingEntities() {

	if (this->widget->getSelectedEntities()->getSize() != 0) {

		this->status = Status::PickingBasePoint;

		shCommandLogManager->appendListEditTextWith("");
		this->updateCommandEditHeadTitle();

		this->widget->setCursor(this->getCursorShape());

		this->availableCommands = ShAvailableCommands::ShBuilder(this->widget, this).
			addAvailableCommand(CommandType::AbsoluteCoordinate).
			addAvailableCommand(CommandType::Empty_Cancel).
			addAvailableCommand(CommandType::RelativeCoordinate).
			addAvailableCommand(CommandType::PolarCoordinate).
			addAvailableCommand(CommandType::DistanceFromBase).
			build();

		this->keyHandler->disAllowKey(KeyType::Control_A);
	}
	else {

		this->actionCanceled();
	}

}

void ShModifyCopyAction::addCopiedEntities(const QLinkedList<ShEntity*> &list) {

	if (this->transaction == nullptr) {
		this->transaction = new ShAddEntityTransaction(this->widget, "Copy");
		ShGlobal::pushNewTransaction(this->widget, this->transaction);
	}

	this->widget->getEntityTable().add(list);
	this->transaction->add(list);

	this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawAddedEntities));
	this->widget->captureImage();
}
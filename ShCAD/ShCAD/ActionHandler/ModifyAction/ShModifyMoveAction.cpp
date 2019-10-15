
#include "ShModifyMoveAction.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "Entity\Private\ShMover.h"
#include "UnRedo\ShEntityTransaction.h"
#include "Base\ShGlobal.h"
#include "Command\ShAvailableCommands.h"


ShModifyMoveAction::ShModifyMoveAction(ShCADWidget *widget)
	:ShModifyAction(widget) {


}

ShModifyMoveAction::~ShModifyMoveAction() {

}

void ShModifyMoveAction::mouseLeftPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {

		this->triggerSelectingEntities(data.mouseEvent);
	}
	else {
	
		this->trigger(data.point);
	}
}

void ShModifyMoveAction::mouseRightPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {
		this->finishSelectingEntities();
	}

}

void ShModifyMoveAction::mouseMoveEvent(ShActionData &data) {

	if (this->status == Status::PickingSecondPoint) {
	
		this->invalidate(data.point);
	}
}

ActionType ShModifyMoveAction::getType() {

	return ActionType::ActionModifyMove;
}

QString ShModifyMoveAction::getHeadTitle() {

	QString text;

	if (this->status == Status::SelectingEntities) {
		text = "Move >> " + shGetLanValue_command("Command/Select objects") + ": ";
	}
	else if (this->status == Status::PickingBasePoint) {
		text = "Move >> " + shGetLanValue_command("Command/Specify base point") + ": ";
	}
	else if (this->status == Status::PickingSecondPoint) {
		text = "Move >> " + shGetLanValue_command("Command/Specify second point") + ": ";
	}

	return text;
}

void ShModifyMoveAction::trigger(const ShPoint3d &point) {

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

		double disX = point.x - this->base.x;
		double disY = point.y - this->base.y;

		ShMover mover(disX, disY);

		QLinkedList<ShEntity*> list;
		auto itr = this->widget->getSelectedEntities()->begin();
		for (itr; itr != this->widget->getSelectedEntities()->end(); ++itr) {

			(*itr)->accept(&mover);
			list.append((*itr));
		}

		ShMoveEntityTransaction *transaction = new ShMoveEntityTransaction(this->widget, list, disX, disY);
		ShGlobal::pushNewTransaction(this->widget, transaction);

		this->setLastBasePoint(point);
		this->actionFinished();
		
	}
}

void ShModifyMoveAction::invalidate(ShPoint3d &point) {

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

void ShModifyMoveAction::finishSelectingEntities() {

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

		ShModifyAction::finishSelectingEntities();
	}
	else {
	
		this->actionCanceled();
	}

}
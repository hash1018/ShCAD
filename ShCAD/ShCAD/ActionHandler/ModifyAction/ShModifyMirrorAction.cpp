
#include "ShModifyMirrorAction.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "UnRedo\ShEntityTransaction.h"
#include "Base\ShGlobal.h"
#include "Base\ShMath.h"
#include "Entity\Private\Algorithm\ShMirror.h"
#include "Command\ShAvailableCommands.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Base\ShCursorShape.h"

ShModifyMirrorAction::ShModifyMirrorAction(ShCADWidget *widget)
	:ShModifyAction(widget), status(Status::SelectingEntities) {

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowKey(KeyType::Enter).
		allowKey(KeyType::Return).
		allowKey(KeyType::Control_A).
		allowKey(KeyType::EscCancelCurrent).
		allowInput().
		build();
}

ShModifyMirrorAction::~ShModifyMirrorAction() {

}

void ShModifyMirrorAction::mouseLeftPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {

		this->triggerSelectingEntities(data.mouseEvent);
	}
	else {

		this->trigger(data.point);
	}

}

void ShModifyMirrorAction::mouseRightPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {
		this->finishSelectingEntities();
	}

}

void ShModifyMirrorAction::mouseMoveEvent(ShActionData &data) {

	if (this->status == Status::PickingSecondPoint) {

		this->invalidate(data.point);
	}
}

ActionType ShModifyMirrorAction::getType() {

	return ActionType::ActionModifyRotate;
}

QString ShModifyMirrorAction::getHeadTitle() {

	QString text;

	if (this->status == Status::SelectingEntities) {
		text = "Mirror >> " + shGetLanValue_command("Command/Select objects") + ": ";
	}
	else if (this->status == Status::PickingBasePoint) {
		text = "Mirror >> " + shGetLanValue_command("Command/Specify base point") + ": ";
	}
	else if (this->status == Status::PickingSecondPoint) {
		text = "Mirror >> " + shGetLanValue_command("Command/Specify rotation angle") + ": ";
	}

	return text;
}

QCursor ShModifyMirrorAction::getCursorShape() {

	QCursor cursor;

	if (this->status == Status::SelectingEntities) {

		cursor = ShCursorShape::getCursor(ShCursorShape::CursorType::Selecting);
	}

	else if (this->status == Status::PickingBasePoint ||
		this->status == Status::PickingSecondPoint) {

		cursor = ShCursorShape::getCursor(ShCursorShape::CursorType::Drawing);
	}


	return cursor;
}

ShAvailableDraft ShModifyMirrorAction::getAvailableDraft() {

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

void ShModifyMirrorAction::trigger(const ShPoint3d &point) {

	if (this->status == Status::PickingBasePoint) {

		this->status = PickingSecondPoint;
		this->base = point;

		this->widget->getRubberBand().create(ShLineData(this->base, this->base));

		auto itr = this->widget->getSelectedEntities()->begin();

		for (itr; itr != this->widget->getSelectedEntities()->end(); ++itr) {

			this->widget->getPreview().add((*itr)->clone());
		}

		this->availableCommands->remove(CommandType::DistanceFromBase);
		this->availableCommands->add(CommandType::AngleFromBase);

		this->setLastBasePoint(point);
		this->triggerSucceeded();

	}
	else if (this->status == Status::PickingSecondPoint) {

		double angle = math::getAbsAngle(this->base.x, this->base.y, point.x, point.y);

		ShMirror mirror(this->base, angle);

		QLinkedList<ShEntity*> list;
		auto itr = this->widget->getSelectedEntities()->begin();
		for (itr; itr != this->widget->getSelectedEntities()->end(); ++itr) {

			mirror.setOriginal((*itr));
			(*itr)->accept(&mirror);
			list.append((*itr));
		}

		ShMirrorEntityTransaction *transaction = new ShMirrorEntityTransaction(this->widget, list, this->base, angle);
		ShGlobal::pushNewTransaction(this->widget, transaction);

		this->setLastBasePoint(point);
		this->actionFinished();

	}
}

void ShModifyMirrorAction::invalidate(ShPoint3d &point) {

	if (this->status == Status::PickingSecondPoint) {

		this->widget->getRubberBand().setEnd(point);

		double angle = math::getAbsAngle(this->base.x, this->base.y, point.x, point.y);

		ShMirror mirror(this->base, angle);

		auto itr = this->widget->getPreview().begin();
		auto originalItr = this->widget->getSelectedEntities()->begin();

		for (itr; itr != this->widget->getPreview().end(); ++itr) {

			mirror.setOriginal((*originalItr));
			(*itr)->accept(&mirror);
			++originalItr;
		}

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

void ShModifyMirrorAction::finishSelectingEntities() {

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
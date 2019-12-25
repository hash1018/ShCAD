
#include "ShModifyOffsetAction.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "Command\ShAvailableCommands.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Base\ShCursorShape.h"
#include "Base\ShMath.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Private\Algorithm\ShOffsetVisitor.h"
#include "Base\ShGlobal.h"
#include "UnRedo\ShEntityTransaction.h"


ShModifyOffsetAction::ShModifyOffsetAction(ShCADWidget *widget)
	:ShModifyAction(widget), status(Status::InputtingNumber), transaction(nullptr) {

	if (this->widget->getSelectedEntities()->getSize() != 0)
		this->widget->getSelectedEntities()->unSelectAll();

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowKey(KeyType::Enter).
		allowKey(KeyType::Return).
		allowKey(KeyType::EscCancelCurrent).
		allowInput().
		build();

	this->command = new ShOnlyNumberCommand<ShModifyOffsetAction>(this, &ShModifyOffsetAction::inputNumber);

	this->availableCommands = ShAvailableCommands::ShBuilder(this->widget, this).
		addAvailableCommand(this->command).
		build();

}

ShModifyOffsetAction::~ShModifyOffsetAction() {

}

void ShModifyOffsetAction::mouseLeftPressEvent(ShActionData &data) {

	if (this->status == Status::InputtingNumber) {
	
		this->status = Status::PickingSecondPoint;
		this->firstPickPoint = data.point;
		
		this->widget->getRubberBand().create(ShLineData(data.point, data.point));

		this->availableCommands->remove(this->command);
		delete this->command;
		this->command = nullptr;

		this->availableCommands->add(CommandType::AbsoluteCoordinate);
		this->availableCommands->add(CommandType::DistanceFromBase);
		this->availableCommands->add(CommandType::RelativeCoordinate);
		this->availableCommands->add(CommandType::PolarCoordinate);
		this->availableCommands->add(CommandType::Empty_Cancel);
		

		this->setLastBasePoint(data.point);
		this->widget->setCursor(this->getCursorShape());
		this->triggerSucceeded();
	}
	else {

		this->trigger(data.point);
	}
}

void ShModifyOffsetAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShModifyOffsetAction::getType() {

	return ActionType::ActionModifyOffset;
}

QString ShModifyOffsetAction::getHeadTitle() {

	QString text;

	if (this->status == Status::InputtingNumber) {
		text = "Offset >> " + shGetLanValue_command("Command/Specify offset distance") + ": ";
	}
	else if (this->status == Status::PickingSecondPoint) {
		text = "Offset >> " + shGetLanValue_command("Command/Specify second point") + ": ";
	}
	else if (this->status == Status::SelectingEntityToModify) {
		text = "Offset >> " + shGetLanValue_command("Command/Select object to offset") + ": ";
	}
	else if (this->status == Status::PickingPointOnSideToOffset) {
		text = "Offset >> " + shGetLanValue_command("Command/Specify point on side to offset") + ": ";
	}
	

	return text;
}

QCursor ShModifyOffsetAction::getCursorShape() {

	QCursor cursor;

	if (this->status == Status::InputtingNumber ||
		this->status == Status::PickingSecondPoint ||
		this->status == PickingPointOnSideToOffset) {

		cursor = ShCursorShape::getCursor(ShCursorShape::CursorType::Drawing);
	}
	else if (this->status == Status::SelectingEntityToModify) {
	
		cursor = ShCursorShape::getCursor(ShCursorShape::CursorType::Selecting);
	}


	return cursor;
}

ShAvailableDraft ShModifyOffsetAction::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->status == Status::InputtingNumber) {

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

void ShModifyOffsetAction::finishSelectingEntities() {


}

void ShModifyOffsetAction::invalidate(ShPoint3d &point) {

	if (this->status == Status::PickingSecondPoint) {
	
		this->widget->getRubberBand().setEnd(point);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->status == Status::PickingPointOnSideToOffset) {
	
		ShOffsetVisitor visitor(this->offsetDistance, point, this->entityToOffset);
		(*this->widget->getPreview().begin())->accept(&visitor);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

void ShModifyOffsetAction::trigger(const ShPoint3d &point) {

	if (this->status == Status::PickingSecondPoint) {
	
		this->offsetDistance = math::getDistance(this->firstPickPoint.x, this->firstPickPoint.y, point.x, point.y);

		if (this->offsetDistance <= 0) {
		
			this->triggerFailed(ShActionTriggerFailureReason::ValueMustBeGreaterThanZero);
			return;
		}

		this->status = Status::SelectingEntityToModify;

		this->widget->getRubberBand().clear();
		this->widget->update((DrawType)(DrawType::DrawCaptureImage));

		this->availableCommands->remove(CommandType::AbsoluteCoordinate);
		this->availableCommands->remove(CommandType::DistanceFromBase);
		this->availableCommands->remove(CommandType::RelativeCoordinate);
		this->availableCommands->remove(CommandType::PolarCoordinate);

		this->setLastBasePoint(point);
		this->widget->setCursor(this->getCursorShape());
		this->triggerSucceeded();

	}
	else if (this->status == Status::SelectingEntityToModify) {
	
		ShPoint3d mouse = this->widget->getMousePoint();

		ShEntity *entity;
		ShSearchEntityUniqueStrategy strategy(&entity, mouse.x, mouse.y, this->widget->getZoomRate());
		this->widget->getEntityTable().search(strategy);

		if (entity == nullptr)
			return;

		if (!dynamic_cast<ShLine*>(entity) && !dynamic_cast<ShCircle*>(entity) && !dynamic_cast<ShArc*>(entity))
			return;

		this->entityToOffset = entity;
		this->widget->getPreview().add(entity->clone());

		this->widget->getSelectedEntities()->add(entity);

		this->widget->update(DrawType::DrawAll);
		this->widget->captureImage();

		this->status = Status::PickingPointOnSideToOffset;

		this->widget->setCursor(this->getCursorShape());
		this->triggerSucceeded();
	}
	else if (this->status == Status::PickingPointOnSideToOffset) {
	
		ShOffsetVisitor visitor(this->offsetDistance, point, this->entityToOffset);
		(*this->widget->getPreview().begin())->accept(&visitor);

		this->addEntity((*this->widget->getPreview().begin())->clone());

		this->widget->getPreview().clear();
		this->widget->getSelectedEntities()->unSelectAll();

		this->widget->update((DrawType)(DrawType::DrawAll));
		this->widget->captureImage();

		this->status = Status::SelectingEntityToModify;
		this->widget->setCursor(this->getCursorShape());
		this->triggerSucceeded();
	}
}

void ShModifyOffsetAction::inputNumber(void *number) {

	if (this->status != Status::InputtingNumber)
		return;

	double num = *(double*)(number);

	if (num <= 0) {
	
		this->triggerFailed(ShActionTriggerFailureReason::ValueMustBeGreaterThanZero);
	}
	else {
	
		this->status = Status::SelectingEntityToModify;
		this->offsetDistance = num;

		this->availableCommands->remove(this->command);

		delete this->command;
		this->command = nullptr;

		this->availableCommands->add(CommandType::Empty_Cancel);

		this->widget->setCursor(this->getCursorShape());
		this->triggerSucceeded();
	}
}

void ShModifyOffsetAction::addEntity(ShEntity *entity) {

	if (this->transaction == nullptr) {
		this->transaction = new ShAddEntityTransaction(this->widget, "Offset");
		ShGlobal::pushNewTransaction(this->widget, this->transaction);
	}

	this->widget->getEntityTable().add(entity);
	this->transaction->add(entity);

}
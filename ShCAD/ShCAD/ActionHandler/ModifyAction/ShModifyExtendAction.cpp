
#include "ShModifyExtendAction.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Private\ShExtender.h"
#include "UnRedo\ShEntityTransaction.h"
#include "Base\ShGlobal.h"


ShModifyExtendAction::ShModifyExtendAction(ShCADWidget *widget)
	:ShModifyAction(widget), transaction(nullptr) {

}

ShModifyExtendAction::~ShModifyExtendAction() {

}

void ShModifyExtendAction::mouseLeftPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {

		this->triggerSelectingEntities(data.mouseEvent);
	}
	else {

		this->trigger(data.point);
	}
}

void ShModifyExtendAction::mouseRightPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {
		this->finishSelectingEntities();
	}
}

void ShModifyExtendAction::mouseMoveEvent(ShActionData &data) {

}

ActionType ShModifyExtendAction::getType() {

	return ActionType::ActionModifyExtend;
}

QString ShModifyExtendAction::getHeadTitle() {

	QString text;

	if (this->status == Status::SelectingEntities) {
		text = "Extend >> " + shGetLanValue_command("Command/Select objects") + ": ";
	}
	else if (this->status == Status::SelectingEntityToModify) {
		text = "Extend >> " + shGetLanValue_command("Command/Select object to extend") + ": ";
	}

	return text;
}

void ShModifyExtendAction::invalidate(ShPoint3d &point) {

}

void ShModifyExtendAction::finishSelectingEntities() {

	if (this->widget->getSelectedEntities()->getSize() != 0) {

		this->status = Status::SelectingEntityToModify;

		shCommandLogManager->appendListEditTextWith("");
		this->updateCommandEditHeadTitle();

		this->widget->setCursor(this->getCursorShape());

	}
	else {

		this->actionCanceled();
	}
}

void ShModifyExtendAction::trigger(const ShPoint3d &point) {

	if (this->status == Status::SelectingEntityToModify) {
	
		ShPoint3d mouse = this->widget->getMousePoint();

		ShEntity *entity;
		ShSearchEntityUniqueStrategy strategy(&entity, mouse.x, mouse.y, this->widget->getZoomRate());
		this->widget->getEntityTable().search(strategy);

		if (entity == nullptr)
			return;
	
		if (entity->isSelected() == true)
			return;
		

		QLinkedList<ShEntity*> baseEntities;
		auto itr = this->widget->getSelectedEntities()->begin();

		for (itr; itr != this->widget->getSelectedEntities()->end(); ++itr)
			baseEntities.append((*itr));
		
		ShEntity *extendedEntity;
		bool valid = false;

		ShExtender extender(baseEntities, mouse, &extendedEntity, valid);
		entity->accept(&extender);

		if (valid == true) {

			this->extend(entity, extendedEntity);
			this->triggerSucceeded();
		}
		else {
		
			this->triggerFailed(NoEdgeInThatDirection);
		}

	}

}

void ShModifyExtendAction::extend(ShEntity *original, ShEntity *extendedEntity) {

	if (this->transaction == nullptr) {
	
		this->transaction = new ShExtendEntityTransaction(this->widget);
		ShGlobal::pushNewTransaction(this->widget, this->transaction);
	}

	if (this->transaction->containsInExtendedList(original) == true) {
	
		this->transaction->removeExtendedList(original);
		this->transaction->addExtendedList(extendedEntity);

		this->widget->getEntityTable().deleteEntity(original);
		this->widget->getEntityTable().add(extendedEntity);

	}
	else {
	
		this->transaction->addOriginalList(original);
		this->transaction->addExtendedList(extendedEntity);

		this->widget->getEntityTable().add(extendedEntity);
		this->widget->getEntityTable().remove(original);
	}


	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}
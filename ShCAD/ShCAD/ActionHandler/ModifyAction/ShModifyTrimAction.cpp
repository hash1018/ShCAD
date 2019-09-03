
#include "ShModifyTrimAction.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Private\ShTrimer.h"
#include "UnRedo\ShEntityTransaction.h"
#include "Base\ShGlobal.h"


ShModifyTrimAction::ShModifyTrimAction(ShCADWidget *widget)
	:ShModifyAction(widget), transaction(nullptr) {

}

ShModifyTrimAction::~ShModifyTrimAction() {

}

void ShModifyTrimAction::mouseLeftPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {

		this->triggerSelectingEntities(data.mouseEvent);
	}
	else {

		this->trigger(data.point);
	}
}

void ShModifyTrimAction::mouseRightPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {
		this->finishSelectingEntities();
	}
}

void ShModifyTrimAction::mouseMoveEvent(ShActionData &data) {

}

ActionType ShModifyTrimAction::getType() {

	return ActionType::ActionModifyExtend;
}

QString ShModifyTrimAction::getHeadTitle() {

	QString text;

	if (this->status == Status::SelectingEntities) {
		text = "Trim >> " + shGetLanValue_command("Command/Select objects") + ": ";
	}
	else if (this->status == Status::SelectingEntityToModify) {
		text = "Trim >> " + shGetLanValue_command("Command/Select object to trim") + ": ";
	}

	return text;
}

void ShModifyTrimAction::invalidate(ShPoint3d &point) {

}

void ShModifyTrimAction::finishSelectingEntities() {

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

void ShModifyTrimAction::trigger(const ShPoint3d &point) {

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

		QLinkedList<ShEntity*> trimedEntities;
		bool valid = false;

		ShTrimer trimer(baseEntities, mouse, trimedEntities, valid);
		entity->accept(&trimer);

		if (valid == true) {

			this->trim(entity, trimedEntities);
			this->triggerSucceeded();
		}
		else {

			this->triggerFailed(NoEdgeInThatDirection);
		}

	}

}

void ShModifyTrimAction::trim(ShEntity *original, const QLinkedList<ShEntity*> &trimedEntities) {

	if (this->transaction == nullptr) {

		this->transaction = new ShTrimEntityTransaction(this->widget);
		ShGlobal::pushNewTransaction(this->widget, this->transaction);
	}

	auto itr = const_cast<QLinkedList<ShEntity*>&>(trimedEntities).begin();
	auto end = const_cast<QLinkedList<ShEntity*>&>(trimedEntities).end();

	if (this->transaction->containsInTrimedList(original) == true) {

		this->transaction->removeTrimedList(original);
		this->widget->getEntityTable().deleteEntity(original);

		for (itr; itr != end; ++itr) {
		
			this->transaction->addTrimedList((*itr));
			this->widget->getEntityTable().add((*itr));
		}
	}
	else {

		this->transaction->addOriginalList(original);
		this->widget->getEntityTable().remove(original);


		for (itr; itr != end; ++itr) {

			this->transaction->addTrimedList((*itr));
			this->widget->getEntityTable().add((*itr));
		}
	}


	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}
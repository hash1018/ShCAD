
#include "ShModifyEraseAction.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "UnRedo\ShEntityTransaction.h"
#include "Base\ShGlobal.h"


ShModifyEraseAction::ShModifyEraseAction(ShCADWidget *widget)
	:ShModifyAction(widget) {

}

ShModifyEraseAction::~ShModifyEraseAction() {

}

void ShModifyEraseAction::mouseLeftPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {
	
		this->triggerSelectingEntities(data.mouseEvent);
	}
}

void ShModifyEraseAction::mouseRightPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {
	
		this->finishSelectingEntities();
	}
}


ActionType ShModifyEraseAction::getType() {

	return ActionType::ActionModifyErase;
}

QString ShModifyEraseAction::getHeadTitle() {

	QString text;

	if (this->status == Status::SelectingEntities) {
		text = "Erase >> " + shGetLanValue_command("Command/Select objects") + ": ";
	}

	return text;
}

void ShModifyEraseAction::finishSelectingEntities() {

	if (this->widget->getSelectedEntities()->getSize() != 0) {

		this->status = Status::PickingBasePoint;

		QLinkedList<ShEntity*> list;
		auto itr = this->widget->getSelectedEntities()->begin();
		for (itr; itr != this->widget->getSelectedEntities()->end(); ++itr) {
		
			this->widget->getEntityTable().remove((*itr));
			list.append((*itr));
		}

		this->widget->getSelectedEntities()->unSelectAll();

		this->widget->update(DrawType::DrawAll);
		this->widget->captureImage();

		ShRemoveEntityTransaction *transaction = new ShRemoveEntityTransaction(this->widget, list);
		ShGlobal::pushNewTransaction(this->widget, transaction);

		this->actionFinished();

	}
	else {

		this->actionCanceled();
	}
}

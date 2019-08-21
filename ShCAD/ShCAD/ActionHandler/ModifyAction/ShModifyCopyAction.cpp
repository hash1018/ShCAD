
#include "ShModifyCopyAction.h"
#include "Manager\ShLanguageManager.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "Event\ShNotifyEvent.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "Entity\Private\ShMover.h"
#include "UnRedo\ShEntityTransaction.h"
#include "Base\ShGlobal.h"

ShModifyCopyAction::ShModifyCopyAction(ShCADWidget *widget)
	:ShModifyAction(widget), transaction(nullptr) {


}

ShModifyCopyAction::~ShModifyCopyAction() {

}

void ShModifyCopyAction::mouseLeftPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {

		this->triggerSelectingEntities(data.mouseEvent);
	}
	else if (this->status == Status::PickingBasePoint) {

		this->status = PickingSecondPoint;
		this->base = data.point;

		this->widget->getRubberBand().create(ShLineData(this->base, data.nextPoint));

		auto itr = this->widget->getSelectedEntities()->begin();

		for (itr; itr != this->widget->getSelectedEntities()->end(); ++itr) {

			this->widget->getPreview().add((*itr)->clone());
		}

		double disX = data.nextPoint.x - data.point.x;
		double disY = data.nextPoint.y - data.point.y;

		ShMover mover(disX, disY);

		for (itr = this->widget->getPreview().begin();
			itr != this->widget->getPreview().end();
			++itr) {

			(*itr)->accept(&mover);
		}

		this->previous = data.nextPoint;

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		ShUpdateTextToCommandListEvent event("");
		this->widget->notify(&event);

		this->updateCommandEditHeadTitle();

	}
	else if (this->status == Status::PickingSecondPoint) {

		double disX = data.point.x - this->previous.x;
		double disY = data.point.y - this->previous.y;

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

		ShUpdateTextToCommandListEvent event("");
		this->widget->notify(&event);

		this->updateCommandEditHeadTitle();
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

	return ActionType::ActionModifyMove;
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



void ShModifyCopyAction::invalidate(ShPoint3d point) {

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

		ShUpdateTextToCommandListEvent event("");
		this->widget->notify(&event);

		this->updateCommandEditHeadTitle();

		this->widget->setCursor(this->getCursorShape());

	}
	else {

		ShChangeDefaultAfterCancelingCurrentStrategy strategy;
		this->widget->changeAction(strategy);
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
	this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
}
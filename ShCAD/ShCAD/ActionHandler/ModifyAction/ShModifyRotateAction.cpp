
#include "ShModifyRotateAction.h"
#include "Manager\ShLanguageManager.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "Event\ShNotifyEvent.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "UnRedo\ShEntityTransaction.h"
#include "Base\ShGlobal.h"
#include "Entity\Private\ShRotater.h"
#include "Base\ShMath.h"

ShModifyRotateAction::ShModifyRotateAction(ShCADWidget *widget)
	:ShModifyAction(widget) {


}

ShModifyRotateAction::~ShModifyRotateAction() {

}

void ShModifyRotateAction::mouseLeftPressEvent(ShActionData &data) {

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

		double angle = math::getAbsAngle(this->base.x, this->base.y, data.nextPoint.x, data.nextPoint.y);

		ShRotater rotater(this->base, angle);

		for (itr = this->widget->getPreview().begin(); itr != this->widget->getPreview().end(); ++itr) {

			(*itr)->accept(&rotater);
		}

		this->prevAngle = angle;

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		ShUpdateTextToCommandListEvent event("");
		this->widget->notify(&event);

		this->updateCommandEditHeadTitle();

	}
	else if (this->status == Status::PickingSecondPoint) {

		double angle = math::getAbsAngle(this->base.x, this->base.y, data.point.x, data.point.y);

		ShRotater rotater(this->base, angle);

		QLinkedList<ShEntity*> list;
		auto itr = this->widget->getSelectedEntities()->begin();
		for (itr; itr != this->widget->getSelectedEntities()->end(); ++itr) {

			(*itr)->accept(&rotater);
			list.append((*itr));
		}

		ShRotateEntityTransaction *transaction = new ShRotateEntityTransaction(this->widget, list, this->base, angle);
		ShGlobal::pushNewTransaction(this->widget, transaction);

		ShChangeDefaultAfterFinishingCurrentStrategy strategy;
		this->widget->changeAction(strategy);

	}
}

void ShModifyRotateAction::mouseRightPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {
		this->finishSelectingEntities();
	}

}

void ShModifyRotateAction::mouseMoveEvent(ShActionData &data) {

	if (this->status == Status::PickingSecondPoint) {

		this->invalidate(data.point);
	}
}

ActionType ShModifyRotateAction::getType() {

	return ActionType::ActionModifyRotate;
}

QString ShModifyRotateAction::getHeadTitle() {

	QString text;

	if (this->status == Status::SelectingEntities) {
		text = "Rotate >> " + shGetLanValue_command("Command/Select objects") + ": ";
	}
	else if (this->status == Status::PickingBasePoint) {
		text = "Rotate >> " + shGetLanValue_command("Command/Specify base point") + ": ";
	}
	else if (this->status == Status::PickingSecondPoint) {
		text = "Rotate >> " + shGetLanValue_command("Command/Specify second point") + ": ";
	}

	return text;
}



void ShModifyRotateAction::invalidate(ShPoint3d point) {

	if (this->status == Status::PickingSecondPoint) {

		this->widget->getRubberBand().setEnd(point);

		double angle = math::getAbsAngle(this->base.x, this->base.y, point.x, point.y);

		ShRotater rotater(this->base, angle - this->prevAngle);

		auto itr = this->widget->getPreview().begin();

		for (itr; itr != this->widget->getPreview().end(); ++itr) {

			(*itr)->accept(&rotater);
		}

		this->prevAngle = angle;

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

void ShModifyRotateAction::finishSelectingEntities() {

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
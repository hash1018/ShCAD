
#include "ShModifyStretchAction.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "UnRedo\ShEntityTransaction.h"
#include "Base\ShGlobal.h"
#include "Command\ShAvailableCommands.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include <QMouseEvent>
#include "Entity\Private\ShStretchVisitor.h"
#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"


ShModifyStretchAction::ShModifyStretchAction(ShCADWidget *widget)
	:ShModifyAction(widget) {


}

ShModifyStretchAction::~ShModifyStretchAction() {

	while (!this->stretchDatas.isEmpty())
		delete this->stretchDatas.takeFirst();
}

void ShModifyStretchAction::mouseLeftPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {

		this->triggerSelectingEntities(data.mouseEvent);
	}
	else {

		this->trigger(data.point);
	}
}

void ShModifyStretchAction::mouseRightPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {
		this->finishSelectingEntities();
	}

}

void ShModifyStretchAction::mouseMoveEvent(ShActionData &data) {

	if (this->status == Status::PickingSecondPoint) {

		this->invalidate(data.point);
	}
}

ActionType ShModifyStretchAction::getType() {

	return ActionType::ActionModifyStretch;
}

QString ShModifyStretchAction::getHeadTitle() {

	QString text;

	if (this->status == Status::SelectingEntities) {
		text = "Stretch >> " + shGetLanValue_command("Command/Select objects") + ": ";
	}
	else if (this->status == Status::PickingBasePoint) {
		text = "Stretch >> " + shGetLanValue_command("Command/Specify base point") + ": ";
	}
	else if (this->status == Status::PickingSecondPoint) {
		text = "Stretch >> " + shGetLanValue_command("Command/Specify second point") + ": ";
	}

	return text;
}

void ShModifyStretchAction::trigger(const ShPoint3d &point) {

	if (this->status == Status::PickingBasePoint) {

		this->status = PickingSecondPoint;
		this->base = point;

		this->widget->getRubberBand().create(ShLineData(this->base, this->base));

		auto itr = this->widget->getSelectedEntities()->begin();

		for (itr; itr != this->widget->getSelectedEntities()->end(); ++itr) {

			this->widget->getPreview().add((*itr)->clone());
		}

		this->setLastBasePoint(point);
		this->triggerSucceeded();

	}
	else if (this->status == Status::PickingSecondPoint) {

		QLinkedList<ShEntity*> stretchedEntities;

		auto itr = this->possibleStretchEntities.begin();

		for (itr; itr != this->possibleStretchEntities.end(); ++itr)
			stretchedEntities.append((*itr)->clone());

		ShStretchVisitor visitor(this->base, point);

		auto originalItr = this->possibleStretchEntities.begin();
		auto dataItr = this->stretchDatas.begin();
		itr = stretchedEntities.begin();

		for (itr; itr != stretchedEntities.end(); ++itr) {

			this->widget->getSelectedEntities()->remove(*originalItr);
			this->widget->getEntityTable().remove(*originalItr);
			this->widget->getSelectedEntities()->add(*itr);
			this->widget->getEntityTable().add(*itr);

			visitor.setOriginal(*originalItr);
			visitor.setStretchData(*dataItr);
			(*itr)->accept(&visitor);

			++originalItr;
			++dataItr;
		}

		ShGlobal::pushNewTransaction(this->widget, new ShStretchEntityTransaction(this->widget, this->possibleStretchEntities, stretchedEntities));

		this->setLastBasePoint(point);
		this->actionFinished();

	}
}

void ShModifyStretchAction::invalidate(ShPoint3d &point) {

	if (this->status == Status::PickingSecondPoint) {

		this->widget->getRubberBand().setEnd(point);

		ShStretchVisitor visitor(this->base, point);

		auto itr = this->widget->getPreview().begin();
		auto originalItr = this->possibleStretchEntities.begin();
		auto dataItr = this->stretchDatas.begin();

		for (itr; itr != this->widget->getPreview().end(); ++itr) {
		
			visitor.setOriginal(*originalItr);
			visitor.setStretchData(*dataItr);
			(*itr)->accept(&visitor);
			++originalItr;
			++dataItr;
		}

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

void ShModifyStretchAction::finishSelectingEntities() {

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

	}
	else {

		this->actionCanceled();
	}

}

void ShModifyStretchAction::triggerSelectingEntities(QMouseEvent *event) {

	ShPoint3d point = this->widget->getMousePoint();

	ShEntity *entity = nullptr;
	ShSearchEntityUniqueStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr) {
		
		if (event->modifiers() == Qt::ShiftModifier) {
			ShChangeTemporaryStrategy strategy(new ShModifyStretchDragSelectAction(this->widget, point.x, point.y,
				this->possibleStretchEntities, this->stretchDatas, ShDragSelectAction::Mode::UnSelectMode), this);
			this->widget->changeAction(strategy);
		}
		else {
			ShChangeTemporaryStrategy strategy(new ShModifyStretchDragSelectAction(this->widget, point.x, point.y,
				this->possibleStretchEntities, this->stretchDatas), this);
			this->widget->changeAction(strategy);
		}
		
	}
	else {

		this->selectFoundEntity(entity, event->modifiers());
	}
}

void ShModifyStretchAction::selectFoundEntity(ShEntity *foundEntity, Qt::KeyboardModifiers modifier) {

	if (modifier == Qt::Modifier::SHIFT) {
	
		if (foundEntity->isSelected() == true) {
		
			auto itr = this->possibleStretchEntities.begin();
			auto dataItr = this->stretchDatas.begin();

			while (itr != this->possibleStretchEntities.end()) {
			
				if ((*itr) == foundEntity) {
					this->possibleStretchEntities.removeOne((*itr));
					ShStretchData *data = *dataItr;
					this->stretchDatas.removeOne(*dataItr);
					delete data;
					break;
				}

				++dataItr;
				++itr;
			}
		}
	}
	else {
	
		if (foundEntity->isSelected() == false) {
		
			ShStretchData *stretchData;
			ShStretchDataForMoveCreator visitor(&stretchData);
			foundEntity->accept(&visitor);

			this->possibleStretchEntities.append(foundEntity);
			this->stretchDatas.append(stretchData);
		}
	}

	ShModifyAction::selectFoundEntity(foundEntity, modifier);
}
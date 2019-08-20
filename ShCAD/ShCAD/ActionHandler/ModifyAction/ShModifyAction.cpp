
#include "ShModifyAction.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include <QMouseEvent>
#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "Event\ShNotifyEvent.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"

ShModifyAction::ShModifyAction(ShCADWidget *widget)
	:ShActionHandler(widget){

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowKey(KeyType::Enter).
		allowKey(KeyType::Return).
		allowKey(KeyType::EscCancelCurrent).
		allowInput().
		build();
}

ShModifyAction::~ShModifyAction() {

}

void ShModifyAction::selectFoundEntity(ShEntity *foundEntity, Qt::KeyboardModifiers modifier) {

	if (modifier == Qt::Modifier::SHIFT) {
	
		if (foundEntity->isSelected() == true) {
		
			this->widget->getSelectedEntities()->remove(foundEntity);
			int size = this->widget->getSelectedEntities()->getSize();

			ShUpdateTextToCommandListEvent event("1 found, 1 removed, " + QString::number(size) + " total");
			this->widget->notify(&event);

			this->widget->update(DrawType::DrawAll);
			this->widget->captureImage();
		}
		else {
		
			int size = this->widget->getSelectedEntities()->getSize();

			ShUpdateTextToCommandListEvent event("1 found, " + QString::number(size) + " total");
			this->widget->notify(&event);
		}
	}
	else {
	
		if (foundEntity->isSelected() == true) {
		
			int size = this->widget->getSelectedEntities()->getSize();

			ShUpdateTextToCommandListEvent event("1 found (1 duplicate), " + QString::number(size) + " total");
			this->widget->notify(&event);
		}
		else {
		
			this->widget->getSelectedEntities()->add(foundEntity);
			int size = this->widget->getSelectedEntities()->getSize();

			ShUpdateTextToCommandListEvent event("1 found, " + QString::number(size) + " total");
			this->widget->notify(&event);

			this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
			this->widget->captureImage();
		}

	}
}

void ShModifyAction::triggerSelectingEntities(QMouseEvent *event) {

	ShPoint3d point = this->widget->getMousePoint();

	ShEntity *entity = nullptr;
	ShSearchEntityUniqueStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr) {
	
		if (event->modifiers() == Qt::ShiftModifier) {
			ShChangeTemporaryStrategy strategy(new ShModifyDragSelectAction(this->widget, point.x, point.y, ShDragSelectAction::Mode::UnSelectMode), this);
			this->widget->changeAction(strategy);
		}
		else {
			ShChangeTemporaryStrategy strategy(new ShModifyDragSelectAction(this->widget, point.x, point.y), this);
			this->widget->changeAction(strategy);
		}
			
	}
	else {
	
		this->selectFoundEntity(entity, event->modifiers());
	}

}
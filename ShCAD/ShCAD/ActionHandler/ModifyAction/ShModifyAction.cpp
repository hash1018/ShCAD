
#include "ShModifyAction.h"
#include "Entity\ShEntity.h"
#include "ShNotifyEvent.h"
ShModifyAction::ShModifyAction(ShGraphicView *graphicView)
	:ShActionHandler(graphicView) {

}

ShModifyAction::~ShModifyAction() {

}


void ShModifyAction::DoFollowUpWithFoundEntity(ShEntity* foundEntity, Qt::KeyboardModifiers modifier) {

	if (modifier == Qt::Modifier::SHIFT) {
	
		if (foundEntity->IsSelected() == true) {
		
			this->graphicView->selectedEntityManager.Pop(foundEntity);
			int size = this->graphicView->selectedEntityManager.GetSize();

			ShUpdateListTextEvent event("1 found, 1 removed, " + QString::number(size) + " total", 
				ShUpdateListTextEvent::UpdateType::editTextWithText);

			this->graphicView->Notify(&event);

			this->graphicView->update(DrawType::DrawAll);
			this->graphicView->CaptureImage();
		}
		else {
		
			int size = this->graphicView->selectedEntityManager.GetSize();

			ShUpdateListTextEvent event("1 found, " + QString::number(size) + " total",
				ShUpdateListTextEvent::UpdateType::editTextWithText);

			this->graphicView->Notify(&event);
		}
	}
	else {

		if (foundEntity->IsSelected() == true) {
			
			int size = this->graphicView->selectedEntityManager.GetSize();

			ShUpdateListTextEvent event("1 found (1 duplicate), " + QString::number(size) + " total",
				ShUpdateListTextEvent::UpdateType::editTextWithText);

			this->graphicView->Notify(&event);
		}
		else {
		
			this->graphicView->selectedEntityManager.Push(foundEntity);

			int size = this->graphicView->selectedEntityManager.GetSize();

			ShUpdateListTextEvent event("1 found, " + QString::number(size) + " total",
				ShUpdateListTextEvent::UpdateType::editTextWithText);

			this->graphicView->Notify(&event);

			this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
			this->graphicView->CaptureImage();

		}
	}
}


#include "ShDefaultAction.h"
#include <QKeyEvent>
#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"

ShDefaultAction::ShDefaultAction(ShGraphicView *graphicView)
	:ShActionHandler(graphicView) {

}

ShDefaultAction::~ShDefaultAction() {

}


void ShDefaultAction::MousePressEvent(QMouseEvent *event) {
	
	
	ShEntity *entity = this->graphicView->entityTable.FindEntity(this->graphicView->GetX(),
		this->graphicView->GetY(), this->graphicView->GetZoomRate());

	if (entity == NULL) {

		double firstX, firstY;
		this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), firstX, firstY);
		this->graphicView->SetTemporaryAction(new ShDragSelectAction(this->graphicView, this, firstX, firstY));
		return;
	}
	
	
	if (event->modifiers() == Qt::ShiftModifier) {
		if (this->graphicView->selectedEntityManager.Pop(entity) == true) {
			this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawJustUnSelectedEntities));
			this->graphicView->CaptureImage();
		}
		
	}
	else {
		if (this->graphicView->selectedEntityManager.Push(entity) == true){
			this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
			//this->graphicView->update(DrawType::DrawAll);
			this->graphicView->CaptureImage();
		}
	}
	

}

void ShDefaultAction::MouseMoveEvent(QMouseEvent *event) {


}

#include "Command Pattern\ShCommand.h"
void ShDefaultAction::KeyPressEvent(QKeyEvent *event) {


	if (event->modifiers()==Qt::Modifier::CTRL && event->key() == Qt::Key::Key_Z) {
	
		if (this->graphicView->selectedEntityManager.GetSize() > 0) {
			this->graphicView->selectedEntityManager.UnSelectAll();
			this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawJustUnSelectedEntities));
			this->graphicView->CaptureImage();
			return;
		}

		if (this->graphicView->undoTaker.IsEmpty()==false) {
			ShCommand *command = this->graphicView->undoTaker.Pop();
			command->UnExecute();

			this->graphicView->redoTaker.Push(command);

		}	
	}
	else if (event->modifiers()==Qt::Modifier::CTRL && event->key() == Qt::Key::Key_Y) {
		
		if (this->graphicView->selectedEntityManager.GetSize() > 0) {
			this->graphicView->selectedEntityManager.UnSelectAll();
			this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawJustUnSelectedEntities));
			this->graphicView->CaptureImage();
			return;
		}

		if (this->graphicView->redoTaker.IsEmpty() == false) {
			
		
			ShCommand *command = this->graphicView->redoTaker.Pop();
			command->Execute();

			this->graphicView->undoTaker.Push(command);

		}
	}
	else if (event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key::Key_A) {
		
		this->graphicView->selectedEntityManager.SelectAll(&(this->graphicView->entityTable));

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
		this->graphicView->CaptureImage();
	}

	else if (event->key() == Qt::Key::Key_Delete) {
	
		ShActionHandler::DeleteSelectedEntities();
	}

}


ActionType ShDefaultAction::GetType() {

	return ActionType::ActionDefault;
}


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
			this->graphicView->update(DrawType::DrawAll);
			this->graphicView->CaptureImage();
		}
		
	}
	else {
		if (this->graphicView->selectedEntityManager.Push(entity) == true){
			qDebug("correct");
			//this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
			this->graphicView->update(DrawType::DrawAll);
			this->graphicView->CaptureImage();
		}
	}
	

}

void ShDefaultAction::MouseMoveEvent(QMouseEvent *event) {


}

#include "Command Pattern\ShCommand.h"
void ShDefaultAction::KeyPressEvent(QKeyEvent *event) {


	if (event->modifiers()==Qt::Modifier::CTRL && event->key() == Qt::Key::Key_Z) {
	
		if (this->graphicView->undoTaker.IsEmpty()==false) {

			ShCommand *command = this->graphicView->undoTaker.Pop();
			command->UnExecute();

			this->graphicView->redoTaker.Push(command);

		}	
	}
	else if (event->modifiers()==Qt::Modifier::CTRL && event->key() == Qt::Key::Key_Y) {
	
		if (this->graphicView->redoTaker.IsEmpty() == false) {
		
			ShCommand *command = this->graphicView->redoTaker.Pop();
			command->Execute();

			this->graphicView->undoTaker.Push(command);

		}
	}
	else if (event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key::Key_A) {
		ShComposite::Iterator itr=this->graphicView->entityTable.Begin();

		while (!itr.IsEnd()) {
			this->graphicView->selectedEntityManager.Push(itr.Current());
			itr.Next();
		}
		this->graphicView->update((DrawType)DrawType::DrawAll);
		this->graphicView->CaptureImage();
	}

}


ActionType ShDefaultAction::GetType() {

	return ActionType::ActionDefault;
}
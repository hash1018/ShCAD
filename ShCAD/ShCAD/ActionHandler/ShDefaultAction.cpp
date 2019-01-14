

#include "ShDefaultAction.h"
#include <QKeyEvent>
ShDefaultAction::ShDefaultAction(ShGraphicView *graphicView)
	:ShActionHandler(graphicView) {

}

ShDefaultAction::~ShDefaultAction() {

}


void ShDefaultAction::MousePressEvent(QMouseEvent *event) {
	
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

}


ActionType ShDefaultAction::GetType() {

	return ActionType::ActionDefault;
}
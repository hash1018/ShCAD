

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

#include "Memento Pattern\ShMemento.h"
#include "Command Pattern\ShRedoCommand.h"
#include "Command Pattern\ShUndoCommand.h"
void ShDefaultAction::KeyPressEvent(QKeyEvent *event) {


	if (event->modifiers()==Qt::Modifier::CTRL && event->key() == Qt::Key::Key_Z) {
	
		if (this->graphicView->undoTaker.IsEmpty()==false) {

			ShMemento *memento = this->graphicView->undoTaker.Pop();
			ShUndoCommand command(this->graphicView, memento);
			command.Execute();

		}	
	}
	else if (event->modifiers()==Qt::Modifier::CTRL && event->key() == Qt::Key::Key_Y) {
	
		if (this->graphicView->redoTaker.IsEmpty() == false) {
		
			ShMemento *memento = this->graphicView->redoTaker.Pop();
			ShRedoCommand command(this->graphicView, memento);
			command.Execute();

		}

	}

}


ActionType ShDefaultAction::GetType() {

	return ActionType::ActionDefault;
}
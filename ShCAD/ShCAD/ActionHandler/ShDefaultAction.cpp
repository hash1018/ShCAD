

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
#include "Memento Pattern\ShUndoCommand.h"
void ShDefaultAction::KeyPressEvent(QKeyEvent *event) {


	if (event->key() == Qt::Key::Key_Z) {
	
		if (this->graphicView->GetUndoTaker()->IsEmpty()==false) {

			ShMemento *memento = this->graphicView->GetUndoTaker()->pop();
			ShUndoCommand command(this->graphicView);
			memento->Accept(&command);

			delete memento;

		}



		
	}

}


ActionType ShDefaultAction::GetType() {

	return ActionType::ActionDefault;
}
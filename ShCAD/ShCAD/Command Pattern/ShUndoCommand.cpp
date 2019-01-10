

#include "ShUndoCommand.h"
#include "Interface\ShGraphicView.h"
#include "Entity\Composite\ShEntityTable.h"
#include "Memento Pattern\ShMemento.h"

ShUndoCommand::ShUndoCommand(ShGraphicView *view, ShMemento *memento) {

	this->graphicView = view;
	this->memento = memento;
}

ShUndoCommand::~ShUndoCommand() {

}


void ShUndoCommand::Execute() {

	if (this->memento->type == MementoType::MementoCreated) {
		
		this->graphicView->GetEntityTable()->Delete(memento->entity);
		this->graphicView->update();

		//Now that undo executed, push memento into redoTaker
		memento->type = MementoType::MementoDeleted;
		memento->entity = 0;

		this->graphicView->GetRedoTaker()->Push(memento);

	}


	
}
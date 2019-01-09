

#include "ShUndoCommand.h"
#include "ShMemento.h"
#include "Interface\ShGraphicView.h"
#include "Entity\Composite\ShEntityTable.h"

ShUndoCommand::ShUndoCommand(ShGraphicView *view) {

	this->graphicView = view;
}

ShUndoCommand::~ShUndoCommand() {

}


void ShUndoCommand::Undo(ShLineMemento *memento) {

	if (memento->status == MementoStatus::MementoCreated) {
	
		this->graphicView->GetEntityTable()->Delete(memento->entity);
		this->graphicView->update();

	}
}
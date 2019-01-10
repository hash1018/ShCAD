



#include "ShRedoCommand.h"
#include "Interface\ShGraphicView.h"
#include "Entity\Composite\ShEntityTable.h"
#include "Entity\Leaf\ShLine.h"
#include "Memento Pattern\ShMemento.h"

ShRedoCommand::ShRedoCommand(ShGraphicView *view,ShMemento *memento) {

	this->graphicView = view;
	this->memento = memento;
}

ShRedoCommand::~ShRedoCommand() {

}


void ShRedoCommand::Execute() {

	
	if (this->memento->type == MementoType::MementoDeleted) {
		
		ShEntity *entity;

		if (dynamic_cast<ShLineMemento*>(this->memento)) {

			ShLineMemento *lineMemento = dynamic_cast<ShLineMemento*>(this->memento);

			ShLine *line = new ShLine(*(lineMemento->data));
			entity = line;

			//Now that redo executed, memento goes into undoTaker again.
			this->memento->entity = line;
			

		}
		



		this->memento->type = MementoType::MementoCreated;
		this->graphicView->GetUndoTaker()->Push(this->memento);
		this->graphicView->GetEntityTable()->Add(entity);
		this->graphicView->update();

	}








	

}


#include "ShAddEntityCommand.h"
#include "Entity\ShEntity.h"
#include "Memento Pattern\ShMemento.h"
#include "Entity\Composite\ShEntityTable.h"
#include "Interface\ShGraphicView.h"

ShAddEntityCommand::ShAddEntityCommand(ShGraphicView *view, ShEntity *newEntity) {

	this->graphicView = view;
	this->newEntity = newEntity;
}

ShAddEntityCommand::~ShAddEntityCommand() {

}

void ShAddEntityCommand::Execute() {

	ShMemento *memento = this->newEntity->CreateMemento();
	memento->SetType(MementoType::MementoCreated);

	this->graphicView->GetUndoTaker()->Push(memento);
	
	if (!this->graphicView->GetRedoTaker()->IsEmpty())
		this->graphicView->GetRedoTaker()->DeleteAll();


	this->graphicView->GetEntityTable()->Add(this->newEntity);
	this->graphicView->update();
}
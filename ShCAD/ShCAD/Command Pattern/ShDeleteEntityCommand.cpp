

#include "ShDeleteEntityCommand.h"
#include "Memento Pattern\ShMemento.h"
#include "Interface\ShGraphicView.h"
ShDeleteEntityCommand::ShDeleteEntityCommand(ShGraphicView *view, ShDeletedEntitiesMemento *memento) {

	this->graphicView = view;
	this->memento = memento;

}

ShDeleteEntityCommand::~ShDeleteEntityCommand() {

}

void ShDeleteEntityCommand::Execute() {
	qDebug("ShDeleteEntityCommand->Execute()");

	ShDeletedEntitiesMemento *memento = dynamic_cast<ShDeletedEntitiesMemento*>(this->memento);

	QLinkedList<ShEntityMemento*>::iterator itr;

	for (itr = memento->list.begin(); itr != memento->list.end(); ++itr) {
	
		this->graphicView->entityTable.Remove((*itr)->entity);
		(*itr)->mustDeallocateEntity = true;
	}

	this->graphicView->update(DrawType::DrawAll);
	this->graphicView->CaptureImage();
	

}

void ShDeleteEntityCommand::UnExecute() {
	qDebug("ShDeleteEntityCommand->UnExecute()");

	ShDeletedEntitiesMemento *memento = dynamic_cast<ShDeletedEntitiesMemento*>(this->memento);

	QLinkedList<ShEntityMemento*>::iterator itr;
	

	QLinkedList<ShEntity*> list;

	for (itr = memento->list.begin(); itr != memento->list.end(); ++itr) {
		list.append((*itr)->entity);
		(*itr)->mustDeallocateEntity = false;
	}

	this->graphicView->entityTable.Add(list);

	this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawAddedEntities));
	this->graphicView->CaptureImage();

}
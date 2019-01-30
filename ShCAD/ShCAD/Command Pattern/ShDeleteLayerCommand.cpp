
#include "ShDeleteLayerCommand.h"
#include "Memento Pattern\ShMemento.h"
#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
#include "Singleton Pattern\ShChangeManager.h"
ShDeleteLayerCommand::ShDeleteLayerCommand(ShGraphicView *view, ShLayerMemento *memento)
	:ShCommand(memento, "Delete Layer"), view(view) {


}

ShDeleteLayerCommand::~ShDeleteLayerCommand() {

}

void ShDeleteLayerCommand::Execute() {

	ShLayerMemento *memento = dynamic_cast<ShLayerMemento*>(this->memento);

	this->view->entityTable.GetLayerTable()->Remove(memento->layer);
	memento->museDeallocateLayer = true;

	ShLayerDeletedEvent event(memento->layer);

	ShChangeManager *manager = ShChangeManager::GetInstance();
	manager->Notify(this, &event);

}

void ShDeleteLayerCommand::UnExecute() {

	ShLayerMemento *memento = dynamic_cast<ShLayerMemento*>(this->memento);

	this->view->entityTable.GetLayerTable()->Add(memento->layer);
	memento->museDeallocateLayer = false;

	ShLayerCreatedEvent event(memento->layer);

	ShChangeManager *manager = ShChangeManager::GetInstance();
	manager->Notify(this, &event);

}

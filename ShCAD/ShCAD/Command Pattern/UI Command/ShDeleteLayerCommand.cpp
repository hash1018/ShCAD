
#include "ShDeleteLayerCommand.h"
#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
#include "Singleton Pattern\ShChangeManager.h"


ShDeleteLayerCommand::ShDeleteLayerCommand(ShGraphicView *view, ShLayer *layer)
	:ShCommand("Delete Layer"), view(view),layer(layer),mustDeallocateLayer(true) {

	
}

ShDeleteLayerCommand::~ShDeleteLayerCommand() {

	if (this->mustDeallocateLayer == true)
		delete this->layer;
}

void ShDeleteLayerCommand::Execute() {

	

	this->view->entityTable.GetLayerTable()->Remove(this->layer);
	this->mustDeallocateLayer = true;

	ShLayerDeletedEvent event(this->layer);

	ShChangeManager *manager = ShChangeManager::GetInstance();
	manager->Notify(this, &event);

}

void ShDeleteLayerCommand::UnExecute() {

	

	this->view->entityTable.GetLayerTable()->Add(this->layer);
	this->mustDeallocateLayer = false;

	ShLayerCreatedEvent event(this->layer);

	ShChangeManager *manager = ShChangeManager::GetInstance();
	manager->Notify(this, &event);

}


#include "ShCreateLayerCommand.h"
#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
#include "Singleton Pattern\ShChangeManager.h"

ShCreateLayerCommand::ShCreateLayerCommand(ShGraphicView *view, ShLayer *layer)
	:ShCommand("Create Layer"), view(view), layer(layer), mustDeallocateLayer(false) {


}

ShCreateLayerCommand::~ShCreateLayerCommand() {

	if (this->mustDeallocateLayer == true)
		delete this->layer;
}

void ShCreateLayerCommand::Execute() {

	

	this->view->entityTable.GetLayerTable()->Add(this->layer);
	this->mustDeallocateLayer = false;

	ShLayerCreatedEvent event(this->layer);

	ShChangeManager *manager = ShChangeManager::GetInstance();
	manager->Notify(this, &event);

}

void ShCreateLayerCommand::UnExecute() {

	

	this->view->entityTable.GetLayerTable()->Remove(this->layer);
	this->mustDeallocateLayer = true;

	ShLayerDeletedEvent event(this->layer);
	
	ShChangeManager *manager = ShChangeManager::GetInstance();
	manager->Notify(this, &event);
	
}

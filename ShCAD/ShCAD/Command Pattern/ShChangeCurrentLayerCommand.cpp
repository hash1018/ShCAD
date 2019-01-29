

#include "ShChangeCurrentLayerCommand.h"
#include "Interface\ShGraphicView.h"
#include "Singleton Pattern\ShChangeManager.h"
#include "ShNotifyEvent.h"
ShChangeCurrentLayerCommand::ShChangeCurrentLayerCommand(ShGraphicView *view, ShLayer *previousLayer, ShLayer *currentLayer)
	:ShCommand("Layer"), view(view), previousLayer(previousLayer), currentLayer(currentLayer) {

}

ShChangeCurrentLayerCommand::~ShChangeCurrentLayerCommand() {

}


void ShChangeCurrentLayerCommand::Execute() {
	qDebug("ShChangeCurrentLayerCommand->Execute()");

	this->view->entityTable.GetLayerTable()->SetCurrentLayer(this->currentLayer);

	*(this->view->GetData()->GetLayerData()) = this->currentLayer->GetData().propertyData;

	if (this->view->GetData()->GetPropertyData()->color.type == ShColor::Type::ByLayer) {
		this->view->GetData()->GetPropertyData()->color = this->view->GetData()->GetLayerData()->color;
	}
	if (this->view->GetData()->GetPropertyData()->lineStyle.type == ShLineStyle::ByLayer) {
		this->view->GetData()->GetPropertyData()->lineStyle = this->view->GetData()->GetLayerData()->lineStyle;
	}

	ShCurrentLayerChangedEvent event(this->previousLayer, this->currentLayer);

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, &event);

}

void ShChangeCurrentLayerCommand::UnExecute() {
	qDebug("ShChangeCurrentLayerCommand->UnExecute()");

	this->view->entityTable.GetLayerTable()->SetCurrentLayer(this->previousLayer);


	*(this->view->GetData()->GetLayerData()) = this->previousLayer->GetData().propertyData;

	if (this->view->GetData()->GetPropertyData()->color.type == ShColor::Type::ByLayer) {
		this->view->GetData()->GetPropertyData()->color = this->view->GetData()->GetLayerData()->color;
	}
	if (this->view->GetData()->GetPropertyData()->lineStyle.type == ShLineStyle::ByLayer) {
		this->view->GetData()->GetPropertyData()->lineStyle = this->view->GetData()->GetLayerData()->lineStyle;
	}

	ShCurrentLayerChangedEvent event(this->currentLayer, this->previousLayer);

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, &event);
	

}
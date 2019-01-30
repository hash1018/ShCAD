

#include "ShChangeLayerDataCommand.h"
#include "Memento Pattern\ShMemento.h"
#include "ShLayer.h"
#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
#include "Singleton Pattern\ShChangeManager.h"
ShChangeLayerDataCommand::ShChangeLayerDataCommand(ShGraphicView *view, ShLayer *changedLayer, ShLayerMemento *memento)
	:ShCommand(memento, "Modify Layer Data"), view(view), changedLayer(changedLayer) {


}

ShChangeLayerDataCommand::~ShChangeLayerDataCommand() {

}

void ShChangeLayerDataCommand::Execute() {
	qDebug("ShChangeLayerDataCommand->Execute()");

	ShLayerMemento* memento = dynamic_cast<ShLayerMemento*>(this->memento);

	ShLayerData data = this->changedLayer->GetData();

	this->changedLayer->SetMemento(memento);

	*memento->data = data;
	
	//currentLayer info changed...
	if (this->changedLayer == this->view->entityTable.GetLayerTable()->GetCurrentLayer()) {
		*this->view->GetData()->GetLayerData() = this->changedLayer->GetData().propertyData;

		if (this->view->GetData()->GetPropertyData()->color.type == ShColor::Type::ByLayer) {
			this->view->GetData()->GetPropertyData()->color = this->view->GetData()->GetLayerData()->color;
		}
		if (this->view->GetData()->GetPropertyData()->lineStyle.type == ShLineStyle::ByLayer) {
			this->view->GetData()->GetPropertyData()->lineStyle = this->view->GetData()->GetLayerData()->lineStyle;
		}
	}


	ShLayerDataChangedEvent event(this->changedLayer, 0, ShLayerDataChangedEvent::ChangedType::Color);
	event.SetCurrentLayer(this->view->entityTable.GetLayerTable()->GetCurrentLayer());


	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notfiy(this, &event);

}

void ShChangeLayerDataCommand::UnExecute() {
	qDebug("ShChangeLayerDataCommand->UnExecute()");

	ShLayerMemento* memento = dynamic_cast<ShLayerMemento*>(this->memento);
	ShLayerData data = this->changedLayer->GetData();

	this->changedLayer->SetMemento(memento);

	*memento->data = data;
	

	//currentLayer info changed...
	if (this->changedLayer == this->view->entityTable.GetLayerTable()->GetCurrentLayer()) {
		*this->view->GetData()->GetLayerData() = this->changedLayer->GetData().propertyData;

		if (this->view->GetData()->GetPropertyData()->color.type == ShColor::Type::ByLayer) {
			this->view->GetData()->GetPropertyData()->color = this->view->GetData()->GetLayerData()->color;
		}
		if (this->view->GetData()->GetPropertyData()->lineStyle.type == ShLineStyle::ByLayer) {
			this->view->GetData()->GetPropertyData()->lineStyle = this->view->GetData()->GetLayerData()->lineStyle;
		}
	}


	ShLayerDataChangedEvent event(this->changedLayer, 0, ShLayerDataChangedEvent::ChangedType::Color);
	event.SetCurrentLayer(this->view->entityTable.GetLayerTable()->GetCurrentLayer());


	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notfiy(this, &event);

}
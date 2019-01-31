

#include "ShChangeLayerDataCommand.h"
#include "Memento Pattern\ShMemento.h"
#include "ShLayer.h"
#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
#include "Singleton Pattern\ShChangeManager.h"
ShChangeLayerDataCommand::ShChangeLayerDataCommand(ShGraphicView *view, ShLayer *changedLayer, ShLayerMemento *memento,
	ShChangeLayerDataCommand::ChangedType type)
	:ShCommand(memento, "Modify Layer Data"), view(view), changedLayer(changedLayer), type(type) {


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
		*this->view->GetData()->GetLayerData() = this->changedLayer->GetData().GetPropertyData();

		if (this->view->GetData()->GetPropertyData()->GetColor().GetType() == ShColor::Type::ByLayer) {
			this->view->GetData()->GetPropertyData()->SetColor(this->view->GetData()->GetLayerData()->GetColor());
		}
		if (this->view->GetData()->GetPropertyData()->GetLineStyle().GetType() == ShLineStyle::ByLayer) {
			this->view->GetData()->GetPropertyData()->SetLineStyle(this->view->GetData()->GetLayerData()->GetLineStyle());
		}
	}


	ShLayerDataChangedEvent event(this->changedLayer, 0, (ShLayerDataChangedEvent::ChangedType)this->type);
	event.SetCurrentLayer(this->view->entityTable.GetLayerTable()->GetCurrentLayer());


	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notfiy(this, &event);

	if (this->type == ChangedType::Color)
		this->view->update(DrawType::DrawAll);

	else if (this->type == ChangedType::LineStyle)
		this->view->update(DrawType::DrawAll);

	else if (this->type == ChangedType::TurnOnOff) {

		this->view->entityTable.GetLayerTable()->UpdateTurnOnLayerList();

		if (this->changedLayer->GetData().IsTurnOn() == true) {
			this->view->entityTable.GetLayerTable()->SetJustTurnOnLayer(this->changedLayer);
			this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawJustTurnOnLayer));
		}
		else {

			this->view->update(DrawType::DrawAll);
		}

	}

	this->view->CaptureImage();

}

void ShChangeLayerDataCommand::UnExecute() {
	qDebug("ShChangeLayerDataCommand->UnExecute()");

	ShLayerMemento* memento = dynamic_cast<ShLayerMemento*>(this->memento);
	ShLayerData data = this->changedLayer->GetData();

	this->changedLayer->SetMemento(memento);

	*memento->data = data;
	

	//currentLayer info changed...
	if (this->changedLayer == this->view->entityTable.GetLayerTable()->GetCurrentLayer()) {
		*this->view->GetData()->GetLayerData() = this->changedLayer->GetData().GetPropertyData();

		if (this->view->GetData()->GetPropertyData()->GetColor().GetType() == ShColor::Type::ByLayer) {
			this->view->GetData()->GetPropertyData()->SetColor(this->view->GetData()->GetLayerData()->GetColor());
		}
		if (this->view->GetData()->GetPropertyData()->GetLineStyle().GetType() == ShLineStyle::ByLayer) {
			this->view->GetData()->GetPropertyData()->SetLineStyle(this->view->GetData()->GetLayerData()->GetLineStyle());
		}
	}


	ShLayerDataChangedEvent event(this->changedLayer, 0, (ShLayerDataChangedEvent::ChangedType)this->type);
	event.SetCurrentLayer(this->view->entityTable.GetLayerTable()->GetCurrentLayer());


	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notfiy(this, &event);


	if (this->type == ChangedType::Color)
		this->view->update(DrawType::DrawAll);
		
	else if (this->type == ChangedType::LineStyle)
		this->view->update(DrawType::DrawAll);
		
	else if (this->type == ChangedType::TurnOnOff) {

		this->view->entityTable.GetLayerTable()->UpdateTurnOnLayerList();

		if (this->changedLayer->GetData().IsTurnOn() == true) {
			this->view->entityTable.GetLayerTable()->SetJustTurnOnLayer(this->changedLayer);
			this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawJustTurnOnLayer));
		}
		else {

			this->view->update(DrawType::DrawAll);
		}


		
	}

	this->view->CaptureImage();
}


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

	DrawType type = DrawType::DrawNone;

	if (this->type == ChangedType::Color)
		type = (DrawType)(type | DrawType::DrawAll);
	else if (this->type == ChangedType::LineStyle)
		type = (DrawType)(type | DrawType::DrawAll);
	else if (this->type == ChangedType::TurnOnOff) {
		

		this->view->entityTable.GetLayerTable()->UpdateTurnOnLayerList();

		if (this->view->selectedEntityManager.GetSize() > 0) {
			this->view->selectedEntityManager.UnSelectAll();
			type = (DrawType)(type | DrawType::DrawAll);
		}
		else if (this->changedLayer->GetData().IsTurnOn() == true) {

			this->view->entityTable.GetLayerTable()->SetJustTurnOnLayer(this->changedLayer);
			type = (DrawType)(type | DrawType::DrawCaptureImage | DrawType::DrawJustTurnOnLayer);
		}
		else {

			type = (DrawType)(type | DrawType::DrawAll);
		}
	}


	this->view->update(type);
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


	DrawType type = DrawType::DrawNone;

	if (this->type == ChangedType::Color)
		type = (DrawType)(type | DrawType::DrawAll);
	else if (this->type == ChangedType::LineStyle)
		type = (DrawType)(type | DrawType::DrawAll);
	else if (this->type == ChangedType::TurnOnOff) {


		this->view->entityTable.GetLayerTable()->UpdateTurnOnLayerList();

		if (this->view->selectedEntityManager.GetSize() > 0) {
			this->view->selectedEntityManager.UnSelectAll();
			type = (DrawType)(type | DrawType::DrawAll);
		}
		else if (this->changedLayer->GetData().IsTurnOn() == true) {

			this->view->entityTable.GetLayerTable()->SetJustTurnOnLayer(this->changedLayer);
			type = (DrawType)(type | DrawType::DrawCaptureImage | DrawType::DrawJustTurnOnLayer);
		}
		else {

			type = (DrawType)(type | DrawType::DrawAll);
		}
	}


	this->view->update(type);
	this->view->CaptureImage();
}
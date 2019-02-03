

#include "ShLayerToolBar.h"
#include "Interface\Items\ShLayerComboBox.h"
#include "Singleton Pattern\ShChangeManager.h"
#include <qpushbutton.h>
ShLayerToolBar::ShLayerToolBar(QWidget *parent)
	:QToolBar(parent) {

	ShChangeManager *manager = ShChangeManager::GetInstance();
	manager->Register(this);


	this->layerButton = new QPushButton("Layer", this);
	this->addWidget(this->layerButton);

	connect(this->layerButton, SIGNAL(released()), this, SLOT(LayerButtonClicked()));

	this->layerCombo = new ShLayerComboBox(this);
	this->addWidget(this->layerCombo);


	connect(this->layerCombo, SIGNAL(CurrentIndexChanged(int)), this, SLOT(CurrentIndexChanged(int)));
	connect(this->layerCombo, SIGNAL(LayerTurnChanged(ShLayer*, bool)), this, SLOT(LayerTurnChanged(ShLayer*, bool)));
	connect(this->layerCombo, SIGNAL(LayerColorChanged(ShLayer*, const ShColor&)), this, SLOT(LayerColorChanged(ShLayer*, const ShColor&)));

}

ShLayerToolBar::~ShLayerToolBar() {

}

#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
void ShLayerToolBar::Update(ShActivatedWidgetChangedEvent *event) {
	

	this->layerCombo->SetLayerTable(event->GetNewWidget()->entityTable.GetLayerTable());
	this->layerCombo->Synchronize();

	////////////////////////////////////////////////////////////


	if (event->GetNewWidget()->GetCurrentActionType() == ActionType::ActionDefault)
		this->layerCombo->setDisabled(false);
	else
		this->layerCombo->setDisabled(true);



}

void ShLayerToolBar::Update(ShCurrentActionChangedEvent *event) {

	if (event->GetActionType() == ActionType::ActionDefault)
		this->layerCombo->setDisabled(false);
	else 
		this->layerCombo->setDisabled(true);
	

}

void ShLayerToolBar::Update(ShSelectedEntityCountChangedEvent *event) {

	this->layerCombo->SetLayerTable(event->GetView()->entityTable.GetLayerTable());

	if (event->GetCount() == 0)
		this->layerCombo->Synchronize();
	else {
	
		if (event->IsAllSameLayer() == true) {
			int index = event->GetView()->entityTable.GetLayerTable()->GetIndex(event->GetLayer());
			this->layerCombo->Synchronize(index);

		}
		else {
			this->layerCombo->Synchronize(-1);
		}

	}
}


void ShLayerToolBar::Notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, event);

}

void ShLayerToolBar::CurrentIndexChanged(int index) {

	ShLayerComboSelChangedEvent event(index);
	this->Notify(&event);
}

#include "Memento Pattern\ShMemento.h"
void ShLayerToolBar::LayerTurnChanged(ShLayer *layer, bool previous) {
	
	ShLayerMemento* memento = layer->CreateMemento();
	//memento->data->isTurnOn = previous;
	memento->data->SetTurn(previous);
	
	ShLayerDataChangedEvent event(layer, memento, ShLayerDataChangedEvent::ChangedType::TurnOnOff);
	this->Notify(&event);
}

void ShLayerToolBar::LayerColorChanged(ShLayer *layer,const ShColor& previous) {
	
	ShLayerMemento* memento = layer->CreateMemento();
	
	ShPropertyData data = memento->data->GetPropertyData();
	data.SetColor(previous);

	memento->data->SetPropertyData(data);

	ShLayerDataChangedEvent event(layer, memento, ShLayerDataChangedEvent::ChangedType::Color);
	this->Notify(&event);
}

void ShLayerToolBar::SynchronizeLayerCombo() {

	this->layerCombo->Synchronize();
}

void ShLayerToolBar::SynchronizeLayerCombo(int index) {

	this->layerCombo->Synchronize(index);
}

int ShLayerToolBar::GetCurrentComboIndex() {

	return this->layerCombo->GetCurrentComboIndex();

}

#include "Interface\Dialog\ShLayerDialog.h"
#include "Singleton Pattern\ShWidgetManager.h"
void ShLayerToolBar::LayerButtonClicked() {
	
	ShWidgetManager *manager = ShWidgetManager::GetInstance();
	
	if (manager->GetActivatedWidget() == 0)
		return;

	ShLayerDialog dlg(manager->GetActivatedWidget()->entityTable.GetLayerTable(), this);

	dlg.exec();
}


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


	connect(this->layerCombo, SIGNAL(CurrentLayerChanged()), this, SLOT(CurrentLayerChanged()));
	connect(this->layerCombo, SIGNAL(LayerTurnChanged(ShLayer*)), this, SLOT(LayerTurnChanged(ShLayer*)));
	connect(this->layerCombo, SIGNAL(LayerColorChanged(ShLayer*)), this, SLOT(LayerColorChanged(ShLayer*)));

}

ShLayerToolBar::~ShLayerToolBar() {

}

#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
void ShLayerToolBar::Update(ShActivatedWidgetChangedEvent *event) {
	

	this->layerCombo->SetLayerTable(event->GetNewWidget()->entityTable.GetLayerTable());

	this->layerCombo->Synchronize();
}

void ShLayerToolBar::Notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, event);

}

void ShLayerToolBar::CurrentLayerChanged() {

	ShCurrentLayerChangedEvent event;
	this->Notify(&event);
}

void ShLayerToolBar::LayerTurnChanged(ShLayer *layer) {

	ShLayerDataChangedEvent event(layer, ShLayerDataChangedEvent::ChangedType::TurnOnOff);
	this->Notify(&event);
}

void ShLayerToolBar::LayerColorChanged(ShLayer *layer) {

	ShLayerDataChangedEvent event(layer, ShLayerDataChangedEvent::ChangedType::Color);
	this->Notify(&event);
}

void ShLayerToolBar::SynchronizeLayerCombo() {

	this->layerCombo->Synchronize();
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
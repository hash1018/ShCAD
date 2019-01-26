

#include "ShLayerToolBar.h"
#include "Interface\Items\ShLayerComboBox.h"
#include "Singleton Pattern\ShChangeManager.h"
ShLayerToolBar::ShLayerToolBar(QWidget *parent)
	:QToolBar(parent) {

	ShChangeManager *manager = ShChangeManager::GetInstance();
	manager->Register(this);

	this->layerCombo = new ShLayerComboBox(this);
	this->addWidget(this->layerCombo);


}

ShLayerToolBar::~ShLayerToolBar() {

}

#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
void ShLayerToolBar::Update(ShActivatedWidgetChangedEvent *event) {
	

	this->layerCombo->SetLayerTable(event->GetNewWidget()->entityTable.GetLayerTable());

	this->layerCombo->Synchronize();
}
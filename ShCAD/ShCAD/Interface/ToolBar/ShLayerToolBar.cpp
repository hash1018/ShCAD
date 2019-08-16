
#include "ShLayerToolBar.h"
#include "Interface\Item\ShLayerComboBox.h"
#include "Event\ShToolBarContainerEventFilter.h"
#include "Event\ShNotifyEvent.h"
#include "Chain of Responsibility\ShRequest.h"
#include "Interface\Dialog\ShLayerDialog.h"
#include <qpushbutton.h>
#include "Manager\ShCADWidgetManager.h"
#include "Interface\ShCADWidget.h"


ShLayerToolBar::ShLayerToolBar(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractToolBar(title, chain, parent) {

	this->setObjectName("LayerToolBar");

	this->layerButton = new QPushButton("Layer", this);
	this->addWidget(this->layerButton);

	this->layerCombo = new ShLayerComboBox(this);
	this->addWidget(this->layerCombo);

	connect(this->layerButton, &QPushButton::released, this, &ShLayerToolBar::layerButtonClicked);
	connect(this->layerCombo, &ShLayerComboBox::currentLayerChanged, this, &ShLayerToolBar::currentLayerChanged);
	connect(this->layerCombo, &ShLayerComboBox::layerColorChanged, this, &ShLayerToolBar::layerColorChanged);
	connect(this->layerCombo, &ShLayerComboBox::layerTurnChanged, this, &ShLayerToolBar::layerTurnChanged);
	
}

ShLayerToolBar::~ShLayerToolBar() {

}

void ShLayerToolBar::update(ShNotifyEvent *event) {

	ShLayerToolBarEventFilter filter(this, event);
	filter.update();
}

void ShLayerToolBar::currentLayerChanged(ShLayer *layer) {

	ShCurrentLayerChangedEvent event(layer);
	ShRequestSendNotifyEvent request(&event);
	this->request(&request);
}

void ShLayerToolBar::layerTurnChanged(ShLayer *layer, bool turnOn) {

	ShLayerDataChangedEvent event(layer, turnOn);
	ShRequestSendNotifyEvent request(&event);
	this->request(&request);
}

void ShLayerToolBar::layerColorChanged(ShLayer *layer, const ShColor &color) {

	ShLayerDataChangedEvent event(layer, color);
	ShRequestSendNotifyEvent request(&event);
	this->request(&request);
}

void ShLayerToolBar::layerButtonClicked() {

	ShCADWidgetManager *manager = ShCADWidgetManager::getInstance();

	if (manager->getActivatedWidget() == nullptr)
		return;

	ShLayerDialog dialog(manager->getActivatedWidget()->getLayerTable(), this, this);
	dialog.exec();
}
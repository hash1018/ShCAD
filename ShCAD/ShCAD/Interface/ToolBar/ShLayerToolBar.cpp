
#include "ShLayerToolBar.h"
#include "Interface\Item\ShLayerComboBox.h"
#include "Event\ShToolBarContainerEventFilter.h"

ShLayerToolBar::ShLayerToolBar(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractToolBar(title, chain, parent) {

	this->setObjectName("LayerToolBar");

	this->layerCombo = new ShLayerComboBox(this);
	this->addWidget(this->layerCombo);

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

}

void ShLayerToolBar::layerTurnChanged(ShLayer *layer, bool turnOn) {

}

void ShLayerToolBar::layerColorChanged(ShLayer *layer, const ShColor &color) {

}
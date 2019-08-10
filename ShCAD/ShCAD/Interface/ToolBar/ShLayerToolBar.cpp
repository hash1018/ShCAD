
#include "ShLayerToolBar.h"

ShLayerToolBar::ShLayerToolBar(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractToolBar(title, chain, parent) {

	this->setObjectName("LayerToolBar");
}

ShLayerToolBar::~ShLayerToolBar() {

}

void ShLayerToolBar::update(ShNotifyEvent *event) {


}


#include "ShPropertyToolBar.h"
#include "Interface\Item\ShColorComboBox.h"

ShPropertyToolBar::ShPropertyToolBar(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractToolBar(title, chain, parent) {

	this->colorCombo = new ShColorComboBox(this);
	this->addWidget(this->colorCombo);

	connect(this->colorCombo, &ShColorComboBox::colorChanged, this, &ShPropertyToolBar::colorChanged);

}

ShPropertyToolBar::~ShPropertyToolBar() {

}

void ShPropertyToolBar::colorChanged(const ShColor &color) {


}
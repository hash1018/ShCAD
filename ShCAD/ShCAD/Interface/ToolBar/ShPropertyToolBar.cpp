

#include "ShPropertyToolBar.h"
#include "Interface\Item\ShColorComboBox.h"
#include "Event\ShToolBarContainerEventFilter.h"
#include "Event\ShNotifyEvent.h"
#include "Chain of Responsibility\ShRequest.h"
#include "Interface\Item\ShLineStyleComboBox.h"

ShPropertyToolBar::ShPropertyToolBar(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractToolBar(title, chain, parent) {

	this->colorCombo = new ShColorComboBox(this);
	this->colorCombo->setMinimumWidth(150);
	this->addWidget(this->colorCombo);

	this->addSeparator();

	this->lineStyleCombo = new ShLineStyleComboBox(this);
	this->lineStyleCombo->setMinimumWidth(150);
	this->addWidget(this->lineStyleCombo);

	connect(this->colorCombo, &ShColorComboBox::colorChanged, this, &ShPropertyToolBar::colorChanged);
	connect(this->lineStyleCombo, &ShLineStyleComboBox::lineStyleChanged, this, &ShPropertyToolBar::lineStyleChanged);

}

ShPropertyToolBar::~ShPropertyToolBar() {

}

void ShPropertyToolBar::update(ShNotifyEvent *event) {

	ShPropertyToolBarEventFilter filter(this, event);
	filter.update();
}


void ShPropertyToolBar::colorChanged(const ShColor &color) {

	ShCurrentColorChangedEvent notifyEvent(color);
	ShRequestSendNotifyEvent request(&notifyEvent);
	this->request(&request);
}

void ShPropertyToolBar::lineStyleChanged(const ShLineStyle &lineStyle) {

}

#include "ShHomeTab.h"
#include "Interface\Item\ShButton.h"
#include "Interface\Item\ShIcon.h"
#include "Interface\Ribbon\Button\ShRibbonButton.h"
#include "Manager\ShLanguageManager.h"
#include "Interface\Item\ShColorComboBox.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "Chain of Responsibility\ShRequest.h"
#include "Event\ShHomeTabEventFilter.h"
#include "Event\ShNotifyEvent.h"
#include "Interface\Item\ShLineStyleComboBox.h"
#include "Interface\Item\ShLayerComboBox.h"

ShHomeTab::ShHomeTab(ShChain *chain, const QString &title, QWidget *parent)
	:ShRibbonTab(title, chain, parent) {

	this->drawPanel = new ShDrawPanel(this, this, shGetLanValue_ui("Home/Draw"), 250);
	this->addPanel(this->drawPanel);

	this->modifyPanel = new ShModifyPanel(this, this, shGetLanValue_ui("Home/Modify"), 250);
	this->addPanel(this->modifyPanel);

	this->propertyPanel = new ShPropertyPanel(this, this, shGetLanValue_ui("Home/Property"), 250);
	this->addPanel(this->propertyPanel);

	this->layerPanel = new ShLayerPanel(this, this, shGetLanValue_ui("Home/Layer"), 250);
	this->addPanel(this->layerPanel);
}

ShHomeTab::~ShHomeTab() {

}

void ShHomeTab::update(ShNotifyEvent *event) {

	this->propertyPanel->update(event);
	this->layerPanel->update(event);
}


/////////////////////////////////////////////////////////////////////////

ShDrawPanel::ShDrawPanel(ShChain *chain, QWidget *parent, const QString &title, int width)
	:ShPanelInRibbonTab(chain, parent, title, width) {

	this->lineButton = new ShButtonWithText(this->layoutWidget);
	this->lineButton->setIcon(ShIcon(":/Image/Draw/Line"));
	this->lineButton->setText(shGetLanValue_ui("Draw/Line"));
	this->lineButton->setTextDirection(ShButtonWithText::TextDirection::South);
	this->lineButton->setIconSize(QSize(this->lineButton->width(), this->lineButton->height()));

	this->circleButton = new ShRibbonCircleButton(this->layoutWidget);
	this->arcButton = new ShRibbonArcButton(this->layoutWidget);
	this->polyButton = new ShRibbonPolyLineButton(this->layoutWidget);

	connect(this->lineButton, &ShButtonWithText::pressed, this, &ShDrawPanel::lineButtonClicked);
}

ShDrawPanel::~ShDrawPanel() {


}

void ShDrawPanel::resizeEvent(QResizeEvent *event) {

	ShPanelInRibbonTab::resizeEvent(event);

	int width = this->layoutWidget->width() / 5;
	int height = this->layoutWidget->height();

	this->lineButton->setGeometry(0, 0, width, height);
	this->circleButton->setGeometry(width, 0, width, height);
	this->arcButton->setGeometry(width * 2, 0, width, height);
	this->polyButton->setGeometry(width * 3, 0, width, height);

}

void ShDrawPanel::lineButtonClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawLine);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////

ShModifyPanel::ShModifyPanel(ShChain *chain, QWidget *parent, const QString &title, int width)
	:ShPanelInRibbonTab(chain, parent, title, width) {

	this->moveButton = new ShButtonWithText(this->layoutWidget);
	this->moveButton->setIcon(ShIcon(":/Image/Modify/Move.png"));
	this->moveButton->setText(shGetLanValue_ui("Modify/Move"));

	this->copyButton = new ShButtonWithText(this->layoutWidget);
	this->copyButton->setIcon(ShIcon(":/Image/Modify/Copy.png"));
	this->copyButton->setText(shGetLanValue_ui("Modify/Copy"));

	this->stretchButton = new ShButtonWithText(this->layoutWidget);
	this->stretchButton->setIcon(ShIcon(":/Image/Modify/Stretch.png"));
	this->stretchButton->setText(shGetLanValue_ui("Modify/Stretch"));

	this->rotateButton = new ShButtonWithText(this->layoutWidget);
	this->rotateButton->setIcon(ShIcon(":/Image/Modify/Rotate.png"));
	this->rotateButton->setText(shGetLanValue_ui("Modify/Rotate"));

	this->mirrorButton = new ShButtonWithText(this->layoutWidget);
	this->mirrorButton->setIcon(ShIcon(":/Image/Modify/Mirror.png"));
	this->mirrorButton->setText(shGetLanValue_ui("Modify/Mirror"));

	this->scaleButton = new ShButtonWithText(this->layoutWidget);
	this->scaleButton->setIcon(ShIcon(":/Image/Modify/Scale.png"));
	this->scaleButton->setText(shGetLanValue_ui("Modify/Scale"));

	this->eraseButton = new ShButtonWithText(this->layoutWidget);
	this->eraseButton->setIcon(ShIcon(":/Image/Modify/Erase.png"));
	this->eraseButton->setText(shGetLanValue_ui("Modify/Erase"));

	this->extendButton = new ShButtonWithText(this->layoutWidget);
	this->extendButton->setIcon(ShIcon(":/Image/Modify/Extend.png"));
	this->extendButton->setText(shGetLanValue_ui("Modify/Extend"));

	this->trimButton = new ShButtonWithText(this->layoutWidget);
	this->trimButton->setIcon(ShIcon(":/Image/Modify/Trim.png"));
	this->trimButton->setText(shGetLanValue_ui("Modify/Trim"));


	connect(this->moveButton, &ShButtonWithText::pressed, this, &ShModifyPanel::moveButtonClicked);
	connect(this->copyButton, &ShButtonWithText::pressed, this, &ShModifyPanel::copyButtonClicked);
	connect(this->stretchButton, &ShButtonWithText::pressed, this, &ShModifyPanel::stretchButtonClicked);
	connect(this->rotateButton, &ShButtonWithText::pressed, this, &ShModifyPanel::rotateButtonClicked);
	connect(this->mirrorButton, &ShButtonWithText::pressed, this, &ShModifyPanel::mirrorButtonClicked);
	connect(this->scaleButton, &ShButtonWithText::pressed, this, &ShModifyPanel::scaleButtonClicked);
	connect(this->eraseButton, &ShButtonWithText::pressed, this, &ShModifyPanel::eraseButtonClicked);
	connect(this->extendButton, &ShButtonWithText::pressed, this, &ShModifyPanel::extendButtonClicked);
	connect(this->trimButton, &ShButtonWithText::pressed, this, &ShModifyPanel::trimButtonClicked);
}

ShModifyPanel::~ShModifyPanel() {


}

void ShModifyPanel::resizeEvent(QResizeEvent *event) {

	ShPanelInRibbonTab::resizeEvent(event);

	//3row 3column
	int width = this->layoutWidget->width() / 3;
	int height = this->layoutWidget->height() / 3;

	this->moveButton->setGeometry(0, 0, width, height);
	this->copyButton->setGeometry(0, height, width, height);
	this->stretchButton->setGeometry(0, height * 2, width, height);

	this->rotateButton->setGeometry(width, 0, width, height);
	this->mirrorButton->setGeometry(width, height, width, height);
	this->scaleButton->setGeometry(width, height * 2, width, height);

	this->eraseButton->setGeometry(width * 2, 0, width, height);
	this->extendButton->setGeometry(width * 2, height, width, height);
	this->trimButton->setGeometry(width * 2, height * 2, width, height);
}


void ShModifyPanel::moveButtonClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionModifyMove);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShModifyPanel::copyButtonClicked() {


}

void ShModifyPanel::stretchButtonClicked() {


}

void ShModifyPanel::rotateButtonClicked() {


}

void ShModifyPanel::mirrorButtonClicked() {


}

void ShModifyPanel::scaleButtonClicked() {


}

void ShModifyPanel::eraseButtonClicked() {


}

void ShModifyPanel::extendButtonClicked() {


}

void ShModifyPanel::trimButtonClicked() {



}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

ShPropertyPanel::ShPropertyPanel(ShChain *chain, QWidget *parent, const QString &title, int width)
	:ShPanelInRibbonTab(chain, parent, title, width) {

	this->colorButton = new ShButton(this);
	this->colorButton->setIcon(ShIcon(":/Image/SelectColor.png"));
	this->colorCombo = new ShColorComboBox(this);
	this->lineStyleCombo = new ShLineStyleComboBox(this);

	connect(this->colorButton, &ShButton::pressed, this, &ShPropertyPanel::colorButtonClicked);
	connect(this->colorCombo, &ShColorComboBox::colorChanged, this, &ShPropertyPanel::colorChanged);
	connect(this->lineStyleCombo, &ShLineStyleComboBox::lineStyleChanged, this, &ShPropertyPanel::lineStyleChanged);

}

ShPropertyPanel::~ShPropertyPanel() {


}


void ShPropertyPanel::resizeEvent(QResizeEvent *event) {

	ShPanelInRibbonTab::resizeEvent(event);

	int height = this->layoutWidget->height();

	this->colorButton->setGeometry(0, 0, height / 3 - 2, height / 3 - 2);
	this->colorCombo->setGeometry(height / 3 + 2, 3, 150, height / 3 - 8);
	this->lineStyleCombo->setGeometry(height / 3 + 2, height / 3, 150, height / 3 - 8);
}

void ShPropertyPanel::update(ShNotifyEvent *event) {

	ShPropertyPanelEventFilter filter(this, event);
	filter.update();
}

void ShPropertyPanel::colorButtonClicked() {

	this->colorCombo->openColorPickDialog();
}

void ShPropertyPanel::colorChanged(const ShColor &color) {

	ShCurrentColorChangedEvent notifyEvent(color);
	ShRequestSendNotifyEvent request(&notifyEvent);
	this->request(&request);
}

void ShPropertyPanel::lineStyleChanged(const ShLineStyle &lineStyle) {

	ShCurrentLineStyleChangedEvent notifyEvent(lineStyle);
	ShRequestSendNotifyEvent request(&notifyEvent);
	this->request(&request);
}



////////////////////////////////////////////////////////////////////////////////////////////


ShLayerPanel::ShLayerPanel(ShChain *chain, QWidget *parent, const QString &title, int width)
	:ShPanelInRibbonTab(chain, parent, title, width) {

	this->layerCombo = new ShLayerComboBox(this);

	connect(this->layerCombo, &ShLayerComboBox::currentLayerChanged, this, &ShLayerPanel::currentLayerChanged);
	connect(this->layerCombo, &ShLayerComboBox::layerColorChanged, this, &ShLayerPanel::layerColorChanged);
	connect(this->layerCombo, &ShLayerComboBox::layerTurnChanged, this, &ShLayerPanel::layerTurnChanged);

}

ShLayerPanel::~ShLayerPanel() {

}

void ShLayerPanel::resizeEvent(QResizeEvent *event) {

	ShPanelInRibbonTab::resizeEvent(event);

	int height = this->layoutWidget->height();

	this->layerCombo->setGeometry(height / 3 + 2, height / 3, 150, height / 3 - 8);
}

void ShLayerPanel::update(ShNotifyEvent *event) {

	ShLayerPanelEventFilter filter(this, event);
	filter.update();
}

void ShLayerPanel::currentLayerChanged(ShLayer *layer) {

	ShCurrentLayerChangedEvent event(layer);
	ShRequestSendNotifyEvent request(&event);
	this->request(&request);
}

void ShLayerPanel::layerTurnChanged(ShLayer *layer, bool turnOn) {

	ShLayerDataChangedEvent event(layer, turnOn);
	ShRequestSendNotifyEvent request(&event);
	this->request(&request);
}

void ShLayerPanel::layerColorChanged(ShLayer *layer, const ShColor &color) {

	ShLayerDataChangedEvent event(layer, color);
	ShRequestSendNotifyEvent request(&event);
	this->request(&request);
}
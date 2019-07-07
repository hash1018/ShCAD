
#include "ShHomeTab.h"
#include "Interface\Item\ShButton.h"
#include "Interface\Item\ShIcon.h"
#include "Interface\Ribbon\Button\ShRibbonButton.h"

ShHomeTab::ShHomeTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

	this->drawPanel = new ShDrawPanel(this, "Draw", 100);
	this->addPanel(this->drawPanel);

	this->modifyPanel = new ShModifyPanel(this, "Modify", 150);
	this->addPanel(this->modifyPanel);

	this->propertyPanel = new ShPropertyPanel(this, "Property", 250);
	this->addPanel(this->propertyPanel);

	this->layerPanel = new ShLayerPanel(this, "Layer", 250);
	this->addPanel(this->layerPanel);
}

ShHomeTab::~ShHomeTab() {

}



/////////////////////////////////////////////////////////////////////////

ShDrawPanel::ShDrawPanel(QWidget *parent, const QString &title, int width)
	:ShPanelInRibbonTab(parent, title, width) {

	this->circleButton = new ShRibbonCircleButton(this->layoutWidget);
	this->arcButton = new ShRibbonArcButton(this->layoutWidget);
	this->polyButton = new ShRibbonPolyLineButton(this->layoutWidget);

}

ShDrawPanel::~ShDrawPanel() {


}

void ShDrawPanel::resizeEvent(QResizeEvent *event) {

	ShPanelInRibbonTab::resizeEvent(event);

	int width = this->layoutWidget->width() / 2;
	int height = this->layoutWidget->height() / 3;

	this->circleButton->setGeometry(width, 0, width, height);

	this->arcButton->setGeometry(0, height, width, height);
	this->polyButton->setGeometry(width, height, width, height);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////

ShModifyPanel::ShModifyPanel(QWidget *parent, const QString &title, int width)
	:ShPanelInRibbonTab(parent, title, width) {

	this->moveButton = new ShButton(this->layoutWidget);
	this->moveButton->setIcon(ShIcon(":/Image/Modify/Move.png"));

	this->copyButton = new ShButton(this->layoutWidget);
	this->copyButton->setIcon(ShIcon(":/Image/Modify/Copy.png"));

	this->stretchButton = new ShButton(this->layoutWidget);
	this->stretchButton->setIcon(ShIcon(":/Image/Modify/Stretch.png"));

	this->rotateButton = new ShButton(this->layoutWidget);
	this->rotateButton->setIcon(ShIcon(":/Image/Modify/Rotate.png"));

	this->mirrorButton = new ShButton(this->layoutWidget);
	this->mirrorButton->setIcon(ShIcon(":/Image/Modify/Mirror.png"));

	this->scaleButton = new ShButton(this->layoutWidget);
	this->scaleButton->setIcon(ShIcon(":/Image/Modify/Scale.png"));

	this->eraseButton = new ShButton(this->layoutWidget);
	this->eraseButton->setIcon(ShIcon(":/Image/Modify/Erase.png"));

	this->extendButton = new ShButton(this->layoutWidget);
	this->extendButton->setIcon(ShIcon(":/Image/Modify/Extend.png"));

	this->trimButton = new ShButton(this->layoutWidget);
	this->trimButton->setIcon(ShIcon(":/Image/Modify/Trim.png"));


	connect(this->moveButton, &ShButton::released, this, &ShModifyPanel::moveButtonClicked);
	connect(this->copyButton, &ShButton::released, this, &ShModifyPanel::copyButtonClicked);
	connect(this->stretchButton, &ShButton::released, this, &ShModifyPanel::stretchButtonClicked);
	connect(this->rotateButton, &ShButton::released, this, &ShModifyPanel::rotateButtonClicked);
	connect(this->mirrorButton, &ShButton::released, this, &ShModifyPanel::mirrorButtonClicked);
	connect(this->scaleButton, &ShButton::released, this, &ShModifyPanel::scaleButtonClicked);
	connect(this->eraseButton, &ShButton::released, this, &ShModifyPanel::eraseButtonClicked);
	connect(this->extendButton, &ShButton::released, this, &ShModifyPanel::extendButtonClicked);
	connect(this->trimButton, &ShButton::released, this, &ShModifyPanel::trimButtonClicked);
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

ShPropertyPanel::ShPropertyPanel(QWidget *parent, const QString &title, int width)
	:ShPanelInRibbonTab(parent, title, width) {


}

ShPropertyPanel::~ShPropertyPanel() {


}


void ShPropertyPanel::resizeEvent(QResizeEvent *event) {


	ShPanelInRibbonTab::resizeEvent(event);

}


////////////////////////////////////////////////////////////////////////////////////////////


ShLayerPanel::ShLayerPanel(QWidget *parent, const QString &title, int width)
	:ShPanelInRibbonTab(parent, title, width) {



}

ShLayerPanel::~ShLayerPanel() {

}

void ShLayerPanel::resizeEvent(QResizeEvent *event) {

	ShPanelInRibbonTab::resizeEvent(event);

}

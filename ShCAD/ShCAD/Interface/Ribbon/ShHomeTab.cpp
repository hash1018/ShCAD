
#include "ShHomeTab.h"
#include "Interface\Item\ShButton.h"
#include "Interface\Item\ShIcon.h"
#include "Interface\Ribbon\Button\ShRibbonButton.h"
#include "Manager\ShLanguageManager.h"
#include "Manager\ShCADWidgetManager.h"
#include "Interface\Item\ShColorComboBox.h"

ShHomeTab::ShHomeTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

	this->drawPanel = new ShDrawPanel(this, shGetLanValue_ui("Home/Draw"), 250);
	this->addPanel(this->drawPanel);

	this->modifyPanel = new ShModifyPanel(this, shGetLanValue_ui("Home/Modify"), 250);
	this->addPanel(this->modifyPanel);

	this->propertyPanel = new ShPropertyPanel(this, shGetLanValue_ui("Home/Property"), 250);
	this->addPanel(this->propertyPanel);

	this->layerPanel = new ShLayerPanel(this, shGetLanValue_ui("Home/Layer"), 250);
	this->addPanel(this->layerPanel);
}

ShHomeTab::~ShHomeTab() {

}



/////////////////////////////////////////////////////////////////////////

ShDrawPanel::ShDrawPanel(QWidget *parent, const QString &title, int width)
	:ShPanelInRibbonTab(parent, title, width) {

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

#include "Interface\ShCADWidget.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
void ShDrawPanel::lineButtonClicked() {

	ShCADWidgetManager *manager = ShCADWidgetManager::getInstance();

	if (manager->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawLine);

	manager->getActivatedWidget()->changeAction(strategy);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////

ShModifyPanel::ShModifyPanel(QWidget *parent, const QString &title, int width)
	:ShPanelInRibbonTab(parent, title, width) {

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

	this->colorCombo = new ShColorComboBox(this);
	connect(this->colorCombo, &ShColorComboBox::colorChanged, this, &ShPropertyPanel::colorChanged);

}

ShPropertyPanel::~ShPropertyPanel() {


}


void ShPropertyPanel::resizeEvent(QResizeEvent *event) {

	ShPanelInRibbonTab::resizeEvent(event);

	int height = this->layoutWidget->height();

	this->colorCombo->setGeometry(height / 3 + 2, 3, 150, height / 3 - 8);
}

void ShPropertyPanel::colorChanged(const ShColor &color) {


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

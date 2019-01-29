

#include "ShHomeTab.h"
#include "ShDirectoryManager.h"
#include <qpixmap.h>
#include <qbitmap.h>
#include <qmenu.h>
#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
#include "Singleton Pattern\ShWidgetManager.h"
#include "Singleton Pattern\ShChangeManager.h"


ShHomeTab::ShHomeTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

	this->drawColumn = new ShDrawColumn(this, "Draw", 100);
	this->AddColumn(this->drawColumn);

	this->propertyColumn = new ShPropertyColumn(this, "Property", 250);
	this->AddColumn(this->propertyColumn);

	this->layerColumn = new ShLayerColumn(this, "Layer", 250);
	this->AddColumn(this->layerColumn);
}

ShHomeTab::~ShHomeTab() {

}



/////////////////////////////////////////////////////////////////////////

ShDrawColumn::ShDrawColumn(QWidget *parent, const QString &title, int width)
	:ShColumnInRibbonTab(parent, title, width) {



	this->InitLineButton();
	this->InitCircleButton();
	this->InitArcButton();


}

ShDrawColumn::~ShDrawColumn() {


}

void ShDrawColumn::resizeEvent(QResizeEvent *event) {

	ShColumnInRibbonTab::resizeEvent(event);

	int width = this->layoutWidget->width();
	int height = this->layoutWidget->height();

	this->lineButton->setGeometry(0, 0, width / 2, height / 3);
	this->circleButton->setGeometry(width / 2, 0, width / 2, height / 3);

	this->arcButton->setGeometry(0, height / 3, width / 2, height / 3);

}


void ShDrawColumn::LineButtonClicked() {
	qDebug("LineButtonClicked");

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}


	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(ActionType::ActionDrawLine);


}

void ShDrawColumn::CircleButtonClicked() {
	qDebug("CircleButtonClicked");

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(ActionType::ActionDefault);

}

void ShDrawColumn::ArcButtonClicked() {


}



void ShDrawColumn::InitLineButton() {

	QString path = ShDirectoryManager::GetImageUiPath();

	QPixmap pix(path + "\\Line.png");
	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);


	QIcon icon(pix);
	this->lineButton = new ShButtonWithMenuPopup(this->layoutWidget);
	this->lineButton->SetIcon(icon);

	QMenu *menu = new QMenu(this->lineButton);
	menu->addAction("sdsad");
	menu->addAction("kkkk");
	this->lineButton->SetMenu(menu);




	connect(this->lineButton, &ShButtonWithMenuPopup::pressed, this, &ShDrawColumn::LineButtonClicked);

}

void ShDrawColumn::InitCircleButton() {

	QString path = ShDirectoryManager::GetImageUiPath();

	QPixmap pix(path + "\\Circle.png");
	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	QIcon icon(pix);
	this->circleButton = new ShButtonWithMenuPopup(this->layoutWidget);
	this->circleButton->SetIcon(icon);

	QMenu *menu = new QMenu(this->circleButton);
	menu->addAction("sdsad");
	menu->addAction("kkkk");
	this->circleButton->SetMenu(menu);


	connect(this->circleButton, &ShButtonWithMenuPopup::pressed, this, &ShDrawColumn::CircleButtonClicked);
}

void ShDrawColumn::InitArcButton() {

	QString path = ShDirectoryManager::GetImageUiPath();

	QPixmap pix(path + "\\Arc.png");
	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	QIcon icon(pix);
	this->arcButton = new ShButtonWithMenuPopup(this->layoutWidget);
	this->arcButton->SetIcon(icon);

	QMenu *menu = new QMenu(this->arcButton);
	menu->addAction("sdsad");
	menu->addAction("kkkk");
	this->arcButton->SetMenu(menu);


	connect(this->arcButton, &ShButtonWithMenuPopup::pressed, this, &ShDrawColumn::ArcButtonClicked);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Interface\Items\ShColorComboBox.h"
#include "Singleton Pattern\ShColorComboList.h"
#include "Interface\Items\ShLineStyleComboBox.h"
#include "Singleton Pattern\ShLineStyleComboList.h"
ShPropertyColumn::ShPropertyColumn(QWidget *parent, const QString &title, int width)
	:ShColumnInRibbonTab(parent, title, width){

	ShChangeManager *manager = ShChangeManager::GetInstance();
	manager->Register(this);


	this->colorCustomButton = new QPushButton(this);
	this->colorCustomButton->setStyleSheet("QPushButton {background : transparent}"
		"QPushButton:hover {background :lightSkyBlue}"
		"QPushButton:pressed {background : steelBlue}");

	QString path = ShDirectoryManager::GetImageUiPath();
	QPixmap pix(path + "\\SelectColor.png");
	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	this->colorCustomButton->setIcon(QIcon(pix));

	connect(this->colorCustomButton, &QPushButton::released, this, &ShPropertyColumn::ColorCustomButtonClicked);


	this->colorCombo = new ShColorComboBox(this);

	connect(this->colorCombo, SIGNAL(ColorChanged(const ShColor&)), this, SLOT(ColorSelChanged(const ShColor&)));


	this->lineStyleCombo = new ShLineStyleComboBox(this);

	connect(this->lineStyleCombo, SIGNAL(LineStyleChanged(const ShLineStyle&)), this, SLOT(LineStyleSelChanged(const ShLineStyle&)));

}

ShPropertyColumn::~ShPropertyColumn() {


}


void ShPropertyColumn::resizeEvent(QResizeEvent *event) {


	ShColumnInRibbonTab::resizeEvent(event);

	int height = this->layoutWidget->height();


	this->colorCustomButton->setGeometry(0, 0, height / 3 - 2, height / 3 - 2);

	this->colorCombo->setGeometry(height / 3 + 2, 3, 150, height / 3 - 8);


	this->lineStyleCombo->setGeometry(height / 3 + 2, height / 3, 150, height / 3 - 8);

}


void ShPropertyColumn::ColorCustomButtonClicked() {

	this->colorCombo->OpenColorPickDialog();
}




void ShPropertyColumn::SynchronizeColorCombo(int colorComboIndex) {

	this->colorCombo->Synchronize(colorComboIndex);
}


void ShPropertyColumn::Update(ShActivatedWidgetChangedEvent *event) {

	ShGraphicView *newWidget = event->GetNewWidget();

	/////////////////////////////////////////////////////////////////////////
	this->colorCombo->SetBlockColor(newWidget->GetData()->GetBlockData()->color);
	this->colorCombo->SetLayerColor(newWidget->GetData()->GetLayerData()->color);

	ShColor color = newWidget->GetData()->GetPropertyData()->color;

	if (color.type == ShColor::Type::ByBlock)
		this->colorCombo->Synchronize(0);
	else if (color.type == ShColor::Type::ByLayer)
		this->colorCombo->Synchronize(1);
	else {
		ShColorComboList *list = ShColorComboList::GetInstance();

		int index = list->Search(color);
		this->colorCombo->Synchronize(index + 2);
	}
	//////////////////////////////////////////////////////////////////////////

	this->lineStyleCombo->SetBlockLineStyle(newWidget->GetData()->GetBlockData()->lineStyle);
	this->lineStyleCombo->SetLayerLineStyle(newWidget->GetData()->GetLayerData()->lineStyle);

	ShLineStyle lineStyle = newWidget->GetData()->GetPropertyData()->lineStyle;

	if (lineStyle.type == ShLineStyle::Type::ByBlock)
		this->lineStyleCombo->Synchronize(0);
	else if (lineStyle.type == ShLineStyle::Type::ByLayer)
		this->lineStyleCombo->Synchronize(1);
	else {
		ShLineStyleComboList *list = ShLineStyleComboList::GetInstance();
		int index = list->Search(lineStyle);
		this->lineStyleCombo->Synchronize(index + 2);

	}

}

void ShPropertyColumn::Update(ShCurrentLayerChangedEvent *event) {

	this->colorCombo->SetLayerColor(event->GetCurrentLayer()->GetData().propertyData.color);
	int index = this->colorCombo->GetColorComboIndex();
	this->colorCombo->Synchronize(index);



	this->lineStyleCombo->SetLayerLineStyle(event->GetCurrentLayer()->GetData().propertyData.lineStyle);
	index = this->lineStyleCombo->GetLineStyleComboIndex();
	this->lineStyleCombo->Synchronize(index);

}

void ShPropertyColumn::Update(ShLayerDataChangedEvent *event) {
	
	this->colorCombo->SetLayerColor(event->GetCurrentLayer()->GetData().propertyData.color);
	int index = this->colorCombo->GetColorComboIndex();
	this->colorCombo->Synchronize(index);



	this->lineStyleCombo->SetLayerLineStyle(event->GetCurrentLayer()->GetData().propertyData.lineStyle);
	index = this->lineStyleCombo->GetLineStyleComboIndex();
	this->lineStyleCombo->Synchronize(index);

}

void ShPropertyColumn::Notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, event);

}

void ShPropertyColumn::ColorSelChanged(const ShColor& color) {

	ShPropertyColorComboSelChangedEvent event(color);
	this->Notify(&event);
}

int ShPropertyColumn::GetColorComboIndex() {

	return this->colorCombo->GetColorComboIndex();
}


void ShPropertyColumn::SynchronizeLineStyleCombo(int lineStyleComboIndex) {

	this->lineStyleCombo->Synchronize(lineStyleComboIndex);
}

int ShPropertyColumn::GetLineStyleComboIndex() {

	return this->lineStyleCombo->GetLineStyleComboIndex();
}

void ShPropertyColumn::LineStyleSelChanged(const ShLineStyle& lineStyle) {

	ShPropertyLineStyleComboSelChangedEvent event(lineStyle);
	this->Notify(&event);
}


////////////////////////////////////////////////////////////////////////////////////////////

#include "Interface\Items\ShLayerComboBox.h"
ShLayerColumn::ShLayerColumn(QWidget *parent, const QString &title, int width)
	:ShColumnInRibbonTab(parent, title, width) {

	ShChangeManager *manager = ShChangeManager::GetInstance();
	manager->Register(this);

	this->layerCombo = new ShLayerComboBox(this);

	connect(this->layerCombo, SIGNAL(CurrentLayerChanged(ShLayer*, ShLayer*)), this, SLOT(CurrentLayerChanged(ShLayer*, ShLayer*)));
	connect(this->layerCombo, SIGNAL(LayerTurnChanged(ShLayer*, bool)), this, SLOT(LayerTurnChanged(ShLayer*, bool)));
	connect(this->layerCombo, SIGNAL(LayerColorChanged(ShLayer*, const ShColor&)), this, SLOT(LayerColorChanged(ShLayer*, const ShColor&)));

}

ShLayerColumn::~ShLayerColumn() {

}

void ShLayerColumn::resizeEvent(QResizeEvent *event) {
	
	ShColumnInRibbonTab::resizeEvent(event);

	int height = this->layoutWidget->height();

	this->layerCombo->setGeometry(height / 3 + 2, height / 3, 150, height / 3 - 8);
}

void ShLayerColumn::Update(ShActivatedWidgetChangedEvent *event) {

	this->layerCombo->SetLayerTable(event->GetNewWidget()->entityTable.GetLayerTable());

	this->layerCombo->Synchronize();
}

void ShLayerColumn::Notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, event);
}

void ShLayerColumn::CurrentLayerChanged(ShLayer *previousLayer, ShLayer *currentLayer) {

	ShCurrentLayerChangedEvent event(previousLayer, currentLayer);
	this->Notify(&event);
}

#include "Memento Pattern\ShMemento.h"
void ShLayerColumn::LayerTurnChanged(ShLayer *layer,bool previous) {

	ShLayerMemento *memento = layer->CreateMemento();
	memento->data->isTurnOn = previous;

	ShLayerDataChangedEvent event(layer, memento, ShLayerDataChangedEvent::ChangedType::TurnOnOff);
	this->Notify(&event);
}

void ShLayerColumn::LayerColorChanged(ShLayer *layer,const ShColor& previous) {
	
	ShLayerMemento *memento = layer->CreateMemento();
	memento->data->propertyData.color = previous;

	ShLayerDataChangedEvent event(layer, memento, ShLayerDataChangedEvent::ChangedType::Color);
	this->Notify(&event);
}

void ShLayerColumn::SynchronizeLayerCombo() {

	this->layerCombo->Synchronize();
}
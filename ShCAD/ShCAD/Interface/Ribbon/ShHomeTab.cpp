

#include "ShHomeTab.h"
#include "ShDirectoryManager.h"
#include <qpixmap.h>
#include <qbitmap.h>
#include <qmenu.h>
#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
#include "Singleton Pattern\ShWidgetManager.h"
#include "Interface\Items\ShColorComboBox.h"
#include "Singleton Pattern\ShColorComboList.h"
#include "Singleton Pattern\ShChangeManager.h"


ShHomeTab::ShHomeTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

	this->drawColumn = new ShDrawColumn(this, "Draw", 100);
	this->AddColumn(this->drawColumn);

	this->propertyColumn = new ShPropertyColumn(this, "Property", 250);
	this->AddColumn(this->propertyColumn);

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

}

ShPropertyColumn::~ShPropertyColumn() {


}


void ShPropertyColumn::resizeEvent(QResizeEvent *event) {


	ShColumnInRibbonTab::resizeEvent(event);

	int height = this->layoutWidget->height();


	this->colorCustomButton->setGeometry(0, 0, height / 3 - 2, height / 3 - 2);

	this->colorCombo->setGeometry(height / 3 + 2, 3, 150, height / 3 - 8);


}


void ShPropertyColumn::ColorCustomButtonClicked() {

	this->colorCombo->OpenColorPickDialog();
}




void ShPropertyColumn::SynchronizeColorCombo(int colorComboIndex) {

	this->colorCombo->Synchronize(colorComboIndex);
}


void ShPropertyColumn::Update(ShActivatedWidgetChangedEvent *event) {

	ShGraphicView *newWidget = event->GetNewWidget();

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
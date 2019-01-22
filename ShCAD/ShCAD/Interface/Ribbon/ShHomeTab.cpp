

#include "ShHomeTab.h"
#include "ShDirectoryManager.h"
#include <qpixmap.h>
#include <qbitmap.h>
#include <qmenu.h>
#include <qpainter.h>
#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
#include "Singleton Pattern\ShWidgetManager.h"
#include <qcombobox.h>
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
	:ShColumnInRibbonTab(parent, title, width), colorComboSelChangedByUser(true),colorComboIndex(0) {

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


	this->colorCombo = new QComboBox(this);


	this->UpdateColorCombo();

	connect(this->colorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(ColorComboIndexChanged(int)));

}

ShPropertyColumn::~ShPropertyColumn() {


}

void ShPropertyColumn::UpdateColorCombo() {
	
	this->colorComboSelChangedByUser = false;

	this->colorCombo->clear();

	ShColorComboList *list = ShColorComboList::GetInstance();
	
	this->colorCombo->addItem(QIcon(list->GetBlockColorImage(10, 10)), list->GetBlockColorText());
	this->colorCombo->addItem(QIcon(list->GetLayerColorImage(10, 10)), list->GetLayerColorText());
	
	for (int i = 0; i < list->GetSize(); i++) {

		this->colorCombo->addItem(QIcon(list->GetColorImage(10, 10, i)), list->GetColorText(i));
	}


	QPixmap pix(10, 10);
	QPainter painter(&pix);
	QLinearGradient linearGrad(0, 0, 10, 10);
	linearGrad.setColorAt(0, QColor(Qt::white));
	linearGrad.setColorAt(1, QColor(Qt::black));

	painter.fillRect(0, 0, 10, 10, linearGrad);

	this->colorCombo->addItem(QIcon(pix), "Custom");


	this->colorComboSelChangedByUser = true;
}

void ShPropertyColumn::resizeEvent(QResizeEvent *event) {


	ShColumnInRibbonTab::resizeEvent(event);

	int height = this->layoutWidget->height();


	this->colorCustomButton->setGeometry(0, 0, height / 3 - 2, height / 3 - 2);

	this->colorCombo->setGeometry(height / 3 + 2, 3, 150, height / 3 - 8);


}

void ShPropertyColumn::ColorComboIndexChanged(int index) {

	if (this->colorComboSelChangedByUser == false)
		return;

	if (index == this->colorCombo->count() - 1) {
	//means select custom item list.


		this->OpenColorPickDialog();
	}
	else {
		this->colorComboIndex = index;
		
		ShColorComboList *list = ShColorComboList::GetInstance();

		//Here pass notifyEvent.
		ShColor color = list->GetColorUsingComboBoxIndex(this->colorComboIndex);

		ShPropertyColorComboSelChangedEvent event(color);
		this->Notify(&event);
			
	}


	

}

void ShPropertyColumn::ColorCustomButtonClicked() {

	this->OpenColorPickDialog();
}







#include <qcolordialog.h>
void ShPropertyColumn::OpenColorPickDialog() {

	QColorDialog dialog;
	
	if (QDialog::Accepted == dialog.exec()) {
	
		ShColor color = ShColor(dialog.currentColor().red(), dialog.currentColor().green(), 
			dialog.currentColor().blue());

		ShColorComboList *list = ShColorComboList::GetInstance();

		int index = list->Search(color);

		if (index!=-1) {
			this->SetColorComboCurrentIndex(index + 2); //ByLayer,ByBlock are not in the list.
		}
		else {
			list->Add(color);
			this->UpdateColorCombo();
			this->SetColorComboCurrentIndex(this->colorCombo->count() - 2);
		}

		//Here pass NotifyEvent.
		color = list->GetColorUsingComboBoxIndex(this->colorComboIndex);

		ShPropertyColorComboSelChangedEvent event(color);
		this->Notify(&event);

	}
	else {
		//Nothing changed.
		this->SetColorComboCurrentIndex(this->colorComboIndex);
	}


	

}

void ShPropertyColumn::SetColorComboCurrentIndex(int index) {

	this->colorComboSelChangedByUser = false;
	this->colorCombo->setCurrentIndex(index);
	this->colorComboSelChangedByUser = true;
	this->colorComboIndex = index;
}




void ShPropertyColumn::Update(ShActivatedWidgetChangedEvent *event) {

	ShGraphicView *newWidget = event->GetNewWidget();

	ShColor color = newWidget->GetData()->GetPropertyData()->color;

	if (color.type == ShColor::Type::ByBlock)
		this->SetColorComboCurrentIndex(0);
	else if (color.type == ShColor::Type::ByLayer)
		this->SetColorComboCurrentIndex(1);
	else {
		ShColorComboList *list = ShColorComboList::GetInstance();

		int index = list->Search(color);
		this->SetColorComboCurrentIndex(index + 2);
	}


}

void ShPropertyColumn::Notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, event);

}
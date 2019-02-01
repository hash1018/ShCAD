

#include "ShPropertyToolBar.h"
#include "Interface\Items\ShColorComboBox.h"
#include "Singleton Pattern\ShColorComboList.h"
#include "ShNotifyEvent.h"
#include "Interface\ShGraphicView.h"
#include "Singleton Pattern\ShChangeManager.h"
#include "Interface\Items\ShLineStyleComboBox.h"
#include "Singleton Pattern\ShLineStyleComboList.h"


ShPropertyToolBar::ShPropertyToolBar(QWidget *parent)
	:QToolBar(parent){

	ShChangeManager *manager = ShChangeManager::GetInstance();
	manager->Register(this);


	this->colorCombo = new ShColorComboBox(this);
	this->colorCombo->setMinimumWidth(150);
	this->addWidget(this->colorCombo);

	
	connect(this->colorCombo, SIGNAL(ColorChanged(const ShColor&)), this, SLOT(ColorSelChanged(const ShColor&)));

	this->addSeparator();

	this->lineStyleCombo = new ShLineStyleComboBox(this);
	this->lineStyleCombo->setMaximumWidth(150);
	this->addWidget(this->lineStyleCombo);

	connect(this->lineStyleCombo, SIGNAL(LineStyleChanged(const ShLineStyle&)), this, SLOT(LineStyleSelChanged(const ShLineStyle&)));


	
}

ShPropertyToolBar::~ShPropertyToolBar() {

}

void ShPropertyToolBar::SynchronizeColorCombo(int colorComboIndex) {

	this->colorCombo->Synchronize(colorComboIndex);

}

void ShPropertyToolBar::Update(ShActivatedWidgetChangedEvent *event) {

	ShGraphicView *newWidget = event->GetNewWidget();

	///////////////////////////////////////////////////////////////////////////////////
	this->colorCombo->SetBlockColor(newWidget->GetData()->GetBlockData()->GetColor());
	this->colorCombo->SetLayerColor(newWidget->GetData()->GetLayerData()->GetColor());

	ShColor color = newWidget->GetData()->GetPropertyData()->GetColor();

	if (color.GetType() == ShColor::Type::ByBlock)
		this->colorCombo->Synchronize(0);
	else if (color.GetType() == ShColor::Type::ByLayer)
		this->colorCombo->Synchronize(1);
	else {
		ShColorComboList *list = ShColorComboList::GetInstance();

		int index = list->Search(color);
		this->colorCombo->Synchronize(index + 2);
	}
	////////////////////////////////////////////////////////////////////////////////////

	this->lineStyleCombo->SetBlockLineStyle(newWidget->GetData()->GetBlockData()->GetLineStyle());
	this->lineStyleCombo->SetLayerLineStyle(newWidget->GetData()->GetLayerData()->GetLineStyle());

	ShLineStyle lineStyle = newWidget->GetData()->GetPropertyData()->GetLineStyle();

	if (lineStyle.GetType() == ShLineStyle::Type::ByBlock)
		this->lineStyleCombo->Synchronize(0);
	else if (lineStyle.GetType() == ShLineStyle::Type::ByLayer)
		this->lineStyleCombo->Synchronize(1);
	else {
		ShLineStyleComboList *list = ShLineStyleComboList::GetInstance();
		int index = list->Search(lineStyle);
		this->lineStyleCombo->Synchronize(index + 2);
	}

	////////////////////////////////////////////////////////////////////////////////////

	if (newWidget->GetCurrentActionType() == ActionType::ActionDefault) {
		this->colorCombo->setDisabled(false);
		this->lineStyleCombo->setDisabled(false);
	}
	else {
		this->colorCombo->setDisabled(true);
		this->lineStyleCombo->setDisabled(true);
	}

}

void ShPropertyToolBar::Update(ShCurrentLayerChangedEvent *event) {

	this->colorCombo->SetLayerColor(event->GetCurrentLayer()->GetData().GetPropertyData().GetColor());
	int index = this->colorCombo->GetColorComboIndex();
	this->colorCombo->Synchronize(index);



	this->lineStyleCombo->SetLayerLineStyle(event->GetCurrentLayer()->GetData().GetPropertyData().GetLineStyle());
	index = this->lineStyleCombo->GetLineStyleComboIndex();
	this->lineStyleCombo->Synchronize(index);

}

void ShPropertyToolBar::Update(ShLayerDataChangedEvent *event) {

	this->colorCombo->SetLayerColor(event->GetCurrentLayer()->GetData().GetPropertyData().GetColor());
	int index = this->colorCombo->GetColorComboIndex();
	this->colorCombo->Synchronize(index);



	this->lineStyleCombo->SetLayerLineStyle(event->GetCurrentLayer()->GetData().GetPropertyData().GetLineStyle());
	index = this->lineStyleCombo->GetLineStyleComboIndex();
	this->lineStyleCombo->Synchronize(index);

}

void ShPropertyToolBar::Update(ShCurrentActionChangedEvent *event) {

	if (event->GetActionType() == ActionType::ActionDefault) {
		this->colorCombo->setDisabled(false);
		this->lineStyleCombo->setDisabled(false);
	}
	else {
		this->colorCombo->setDisabled(true);
		this->lineStyleCombo->setDisabled(true);
	}
	
}

void ShPropertyToolBar::Notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, event);

}


void ShPropertyToolBar::ColorSelChanged(const ShColor& color) {

	ShPropertyColorComboSelChangedEvent event(color);
	this->Notify(&event);
}


void ShPropertyToolBar::LineStyleSelChanged(const ShLineStyle& lineStyle) {

	ShPropertyLineStyleComboSelChangedEvent event(lineStyle);
	this->Notify(&event);
	
}

int ShPropertyToolBar::GetColorComboIndex() {

	return this->colorCombo->GetColorComboIndex();
}

void ShPropertyToolBar::SynchronizeLineStyleCombo(int lineStyleComboIndex) {

	this->lineStyleCombo->Synchronize(lineStyleComboIndex);
}

int ShPropertyToolBar::GetLineStyleComboIndex() {

	return this->lineStyleCombo->GetLineStyleComboIndex();
}
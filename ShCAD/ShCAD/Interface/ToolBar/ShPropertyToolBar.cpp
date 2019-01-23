

#include "ShPropertyToolBar.h"
#include "Interface\Items\ShColorComboBox.h"
#include "Singleton Pattern\ShColorComboList.h"
#include "ShNotifyEvent.h"
#include "Interface\ShGraphicView.h"
#include "Singleton Pattern\ShChangeManager.h"
#include "Interface\Items\ShLineStyleComboBox.h"
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
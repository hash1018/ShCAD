

#include "ShPropertyToolBar.h"
#include "Interface\Items\ShColorComboBox.h"
#include "Singleton Pattern\ShColorComboList.h"
#include "ShNotifyEvent.h"
#include "Interface\ShGraphicView.h"
#include "Singleton Pattern\ShChangeManager.h"
#include "Interface\Items\ShLineStyleComboBox.h"
#include "Singleton Pattern\ShLineStyleComboList.h"


ShPropertyToolBar::ShPropertyToolBar(const QString &title, QWidget *parent)
	:ShAbstractToolBar(title, parent) {

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

void ShPropertyToolBar::SetColorComboInfo(const ShColor& blockColor, const ShColor& layerColor, const ShColor& current) {

	this->colorCombo->SetBlockColor(blockColor);
	this->colorCombo->SetLayerColor(layerColor);

	if (current.GetType() == ShColor::Type::ByBlock)
		this->colorCombo->Synchronize(0);
	else if (current.GetType() == ShColor::Type::ByLayer)
		this->colorCombo->Synchronize(1);
	else {
		ShColorComboList *list = ShColorComboList::GetInstance();

		int index = list->Search(current);
		this->colorCombo->Synchronize(index + 2);
	}

}

void ShPropertyToolBar::SetLineStyleComboInfo(const ShLineStyle& blockLineStyle, const ShLineStyle& layerLineStyle,
	const ShLineStyle& current) {

	this->lineStyleCombo->SetBlockLineStyle(blockLineStyle);
	this->lineStyleCombo->SetLayerLineStyle(layerLineStyle);

	if (current.GetType() == ShLineStyle::Type::ByBlock)
		this->lineStyleCombo->Synchronize(0);
	else if (current.GetType() == ShLineStyle::Type::ByLayer)
		this->lineStyleCombo->Synchronize(1);
	else {
		ShLineStyleComboList *list = ShLineStyleComboList::GetInstance();
		int index = list->Search(current);
		this->lineStyleCombo->Synchronize(index + 2);
	}

}

void ShPropertyToolBar::SynchronizeColorCombo(int colorComboIndex) {

	this->colorCombo->Synchronize(colorComboIndex);

}

void ShPropertyToolBar::SynchronizeColorCombo(const ShColor& color) {

	if (color.GetType() == ShColor::Type::ByBlock)
		this->colorCombo->Synchronize(0);
	else if (color.GetType() == ShColor::Type::ByLayer)
		this->colorCombo->Synchronize(1);
	else {
		ShColorComboList *list = ShColorComboList::GetInstance();

		int index = list->Search(color);
		this->colorCombo->Synchronize(index + 2);
	}
}

void ShPropertyToolBar::Update(ShActivatedWidgetChangedEvent *event) {

	ShGraphicView *newWidget = event->GetNewWidget();

	this->SetColorComboInfo(newWidget->GetData()->GetBlockData()->GetColor(),
		newWidget->GetData()->GetLayerData()->GetColor(),
		newWidget->GetData()->GetPropertyData()->GetColor());
	
	this->SetLineStyleComboInfo(newWidget->GetData()->GetBlockData()->GetLineStyle(),
		newWidget->GetData()->GetLayerData()->GetLineStyle(),
		newWidget->GetData()->GetPropertyData()->GetLineStyle());

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

void ShPropertyToolBar::Update(ShLayerComboSelChangedEvent *event) {

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

void ShPropertyToolBar::Update(ShSelectedEntityCountChangedEvent *event) {

	ShGraphicView *view = event->GetView();

	if (event->GetCount() == 0) {
	
		this->SetColorComboInfo(view->GetData()->GetBlockData()->GetColor(),
			view->GetData()->GetLayerData()->GetColor(),
			view->GetData()->GetPropertyData()->GetColor());


		this->SetLineStyleComboInfo(view->GetData()->GetBlockData()->GetLineStyle(),
			view->GetData()->GetLayerData()->GetLineStyle(),
			view->GetData()->GetPropertyData()->GetLineStyle());
	
	}
	else {
	
		if (event->IsAllSameColor() == true) {

			this->SetColorComboInfo(view->GetData()->GetBlockData()->GetColor(),
				event->GetLayerData().GetColor(), event->GetData().GetColor());
		}
		else {
			this->colorCombo->Synchronize(-1);
		}


		if (event->IsAllSameLineStyle() == true) {

			this->SetLineStyleComboInfo(view->GetData()->GetBlockData()->GetLineStyle(),
				event->GetLayerData().GetLineStyle(), event->GetData().GetLineStyle());

		}
		else {
			this->lineStyleCombo->Synchronize(-1);
		}
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

void ShPropertyToolBar::SynchronizeLineStyleCombo(const ShLineStyle& lineStyle) {

	if (lineStyle.GetType() == ShLineStyle::Type::ByBlock)
		this->lineStyleCombo->Synchronize(0);
	else if (lineStyle.GetType() == ShLineStyle::Type::ByLayer)
		this->lineStyleCombo->Synchronize(1);
	else {
		ShLineStyleComboList *list = ShLineStyleComboList::GetInstance();
		int index = list->Search(lineStyle);
		this->lineStyleCombo->Synchronize(index + 2);
	}

}

int ShPropertyToolBar::GetLineStyleComboIndex() {

	return this->lineStyleCombo->GetLineStyleComboIndex();
}
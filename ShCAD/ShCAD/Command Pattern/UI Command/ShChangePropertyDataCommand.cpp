

#include "ShChangePropertyDataCommand.h"
#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
#include "Singleton Pattern\ShChangeManager.h"
ShChangePropertyDataCommand::ShChangePropertyDataCommand(ShGraphicView *view, const ShPropertyData& prev, const ShPropertyData& current, ChangedType type)
	:view(view), prev(prev), current(current), type(type), ShCommand("Modify Property") {

}

ShChangePropertyDataCommand::~ShChangePropertyDataCommand() {

}


void ShChangePropertyDataCommand::Execute() {

	if (this->type == ChangedType::Color) {

		this->view->GetData()->GetPropertyData()->SetColor(this->current.GetColor());

		ShPropertyColorComboSelChangedEvent event(this->current.GetColor());
		ShChangeManager *manager = ShChangeManager::GetInstance();

		manager->Notify(this, &event);
	}
	else if (this->type == ChangedType::LineStyle) {
	
		this->view->GetData()->GetPropertyData()->SetLineStyle(this->current.GetLineStyle());

		ShPropertyLineStyleComboSelChangedEvent event(this->current.GetLineStyle());
		ShChangeManager *manager = ShChangeManager::GetInstance();

		manager->Notify(this, &event);

	}

}


void ShChangePropertyDataCommand::UnExecute() {

	if (this->type == ChangedType::Color) {

		this->view->GetData()->GetPropertyData()->SetColor(this->prev.GetColor());

		ShPropertyColorComboSelChangedEvent event(this->prev.GetColor());
		ShChangeManager *manager = ShChangeManager::GetInstance();

		manager->Notify(this, &event);
	}
	else if (this->type == ChangedType::LineStyle) {
	
		this->view->GetData()->GetPropertyData()->SetLineStyle(this->prev.GetLineStyle());

		ShPropertyLineStyleComboSelChangedEvent event(this->prev.GetLineStyle());
		ShChangeManager *manager = ShChangeManager::GetInstance();

		manager->Notify(this, &event);
	}

}
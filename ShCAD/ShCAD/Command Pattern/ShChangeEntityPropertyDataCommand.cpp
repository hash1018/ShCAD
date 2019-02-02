

#include "ShChangeEntityPropertyDataCommand.h"
#include "Memento Pattern\ShMemento.h"
#include "Entity\ShEntity.h"
#include "Interface\ShGraphicView.h"
ShChangeEntityPropertyDataCommand::ShChangeEntityPropertyDataCommand(ShGraphicView *view, ShCompositeEntityMemento *memento,
	const ShColor& color)
	:view(view), color(color), type(ChangedType::Color), ShCommand(memento, "Modify Entity Property") {

}

ShChangeEntityPropertyDataCommand::ShChangeEntityPropertyDataCommand(ShGraphicView *view, ShCompositeEntityMemento *memento,
	const ShLineStyle& lineStyle)
	: view(view), lineStyle(lineStyle), type(ChangedType::LineStyle), ShCommand(memento, "Modify Entity Property") {

}

ShChangeEntityPropertyDataCommand::~ShChangeEntityPropertyDataCommand() {


}

void ShChangeEntityPropertyDataCommand::Execute() {
	
	ShPropertyData data;
	QLinkedList<ShEntity*>::iterator itr;

	ShCompositeEntityMemento *memento = dynamic_cast<ShCompositeEntityMemento*>(this->memento);

	if (this->type == ChangedType::Color) {

		QLinkedList<ShEntityMemento*>::iterator itr;
		
		for (itr = memento->list.begin(); itr != memento->list.end(); ++itr) {

			data = (*itr)->entity->GetPropertyData();

			if (this->color.GetType() == ShColor::Type::ByBlock)
				data.SetColor(this->view->GetData()->GetBlockData()->GetColor());
			else if (this->color.GetType() == ShColor::Type::ByLayer)
				data.SetColor((*itr)->entity->GetLayer()->GetPropertyData().GetColor());
			else
				data.SetColor(this->color);

			(*itr)->entity->SetPropertyData(data);

		}
	}
	else if (this->type == ChangedType::LineStyle) {
	

	}

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}

void ShChangeEntityPropertyDataCommand::UnExecute() {

	ShPropertyData data;
	QLinkedList<ShEntity*>::iterator itr;

	ShCompositeEntityMemento *memento = dynamic_cast<ShCompositeEntityMemento*>(this->memento);

	if (this->type == ChangedType::Color) {

		QLinkedList<ShEntityMemento*>::iterator itr;

		for (itr = memento->list.begin(); itr != memento->list.end(); ++itr) {

			data = (*itr)->entity->GetPropertyData();

			data.SetColor((*itr)->propertyData->GetColor());

			(*itr)->entity->SetPropertyData(data);

		}
	}
	else if (this->type == ChangedType::LineStyle) {


	}

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}
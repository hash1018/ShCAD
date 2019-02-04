

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
	qDebug("asdsdsad Execute");
	ShPropertyData data;
	ShCompositeEntityMemento *memento = dynamic_cast<ShCompositeEntityMemento*>(this->memento);

	QLinkedList<ShEntityMemento*>::iterator itr;

	for (itr = memento->list.begin(); itr != memento->list.end(); ++itr) {

		data = (*itr)->entity->GetPropertyData();

		if (this->type == ChangedType::Color) {

			if (this->color.GetType() == ShColor::Type::ByBlock)
				data.SetColor(this->view->GetData()->GetBlockData()->GetColor());
			else if (this->color.GetType() == ShColor::Type::ByLayer)
				data.SetColor((*itr)->entity->GetLayer()->GetPropertyData().GetColor());
			else
				data.SetColor(this->color);

		}
		else if (this->type == ChangedType::LineStyle) {

			if (this->lineStyle.GetType() == ShLineStyle::Type::ByBlock)
				data.SetLineStyle(this->view->GetData()->GetBlockData()->GetLineStyle());
			else if (this->lineStyle.GetType() == ShLineStyle::Type::ByLayer)
				data.SetLineStyle((*itr)->entity->GetLayer()->GetPropertyData().GetLineStyle());
			else
				data.SetLineStyle(this->lineStyle);

		}
		

		(*itr)->entity->SetPropertyData(data);

	}


	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}

void ShChangeEntityPropertyDataCommand::UnExecute() {
	qDebug("asdsdsad UnExecute");

	ShPropertyData data;
	ShCompositeEntityMemento *memento = dynamic_cast<ShCompositeEntityMemento*>(this->memento);

	QLinkedList<ShEntityMemento*>::iterator itr;

	for (itr = memento->list.begin(); itr != memento->list.end(); ++itr) {

		data = (*itr)->entity->GetPropertyData();

		if (this->type == ChangedType::Color)
			data.SetColor((*itr)->propertyData->GetColor());
		else if (this->type == ChangedType::LineStyle)
			data.SetLineStyle((*itr)->propertyData->GetLineStyle());
		
		(*itr)->entity->SetPropertyData(data);

	}

	
	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();

}
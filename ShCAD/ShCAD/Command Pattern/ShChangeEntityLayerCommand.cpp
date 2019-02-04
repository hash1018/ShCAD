

#include "ShChangeEntityLayerCommand.h"
#include "Memento Pattern\ShMemento.h"
#include "ShLayer.h"
#include "Entity\ShEntity.h"
#include "Interface\ShGraphicView.h"
ShChangeEntityLayerCommand::ShChangeEntityLayerCommand(ShGraphicView *view, ShCompositeEntityMemento *memento, ShLayer *changedLayer)
	:ShCommand(memento, "Change Entity Layer"), changedLayer(changedLayer),view(view) {


}


ShChangeEntityLayerCommand::~ShChangeEntityLayerCommand() {


}

void ShChangeEntityLayerCommand::Execute() {

	ShCompositeEntityMemento *memento = dynamic_cast<ShCompositeEntityMemento*>(this->memento);

	ShPropertyData data;
	QLinkedList<ShEntityMemento*>::iterator itr;

	for (itr = memento->list.begin(); itr != memento->list.end(); ++itr) {

		(*itr)->entity->GetLayer()->Remove((*itr)->entity);

		this->changedLayer->Add((*itr)->entity);
		(*itr)->entity->SetLayer(this->changedLayer);

		data = (*itr)->entity->GetPropertyData();

		if (data.GetColor().GetType() == ShColor::Type::ByLayer) {
			data.SetColor(this->changedLayer->GetPropertyData().GetColor());
			(*itr)->entity->SetPropertyData(data);
		}

		if (data.GetLineStyle().GetType() == ShLineStyle::Type::ByLayer) {
			data.SetLineStyle(this->changedLayer->GetPropertyData().GetLineStyle());
			(*itr)->entity->SetPropertyData(data);
		}

	}

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();

}

void ShChangeEntityLayerCommand::UnExecute() {

	ShCompositeEntityMemento *memento = dynamic_cast<ShCompositeEntityMemento*>(this->memento);
	
	ShPropertyData data;
	QLinkedList<ShEntityMemento*>::iterator itr;

	for (itr = memento->list.begin(); itr != memento->list.end(); ++itr) {
	
		this->changedLayer->Remove((*itr)->entity);

		(*itr)->layer->Add((*itr)->entity);
		(*itr)->entity->SetLayer((*itr)->layer);

		data = (*itr)->entity->GetPropertyData();

		if (data.GetColor().GetType() == ShColor::Type::ByLayer) {
			data.SetColor((*itr)->layer->GetPropertyData().GetColor());
			(*itr)->entity->SetPropertyData(data);
		}

		if (data.GetLineStyle().GetType() == ShLineStyle::Type::ByLayer) {
			data.SetLineStyle((*itr)->layer->GetPropertyData().GetLineStyle());
			(*itr)->entity->SetPropertyData(data);
		}

	}

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();


}



	


#include "ShChangeEntityLayerCommand.h"
#include "ShLayer.h"
#include "Entity\ShEntity.h"
#include "Interface\ShGraphicView.h"
ShChangeEntityLayerCommand::ShChangeEntityLayerCommand(ShGraphicView *view, QLinkedList<ShEntity*>& selectedEntities,
	QLinkedList<ShLayer*>& previousLayers, ShLayer *changedLayer)
	:ShCommand("Change Entity Layer"), changedLayer(changedLayer), view(view), selectedEntities(selectedEntities),
	previousLayers(previousLayers) {



}


ShChangeEntityLayerCommand::~ShChangeEntityLayerCommand() {


}

void ShChangeEntityLayerCommand::Execute() {

	

	ShPropertyData data;
	QLinkedList<ShEntity*>::iterator itr;
	

	for (itr = this->selectedEntities.begin(); itr !=this->selectedEntities.end(); ++itr) {

		(*itr)->GetLayer()->Remove((*itr));

		this->changedLayer->Add((*itr));
		(*itr)->SetLayer(this->changedLayer);

		data = (*itr)->GetPropertyData();

		if (data.GetColor().GetType() == ShColor::Type::ByLayer) {
			data.SetColor(this->changedLayer->GetPropertyData().GetColor());
			(*itr)->SetPropertyData(data);
		}

		if (data.GetLineStyle().GetType() == ShLineStyle::Type::ByLayer) {
			data.SetLineStyle(this->changedLayer->GetPropertyData().GetLineStyle());
			(*itr)->SetPropertyData(data);
		}

	}

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();

}

void ShChangeEntityLayerCommand::UnExecute() {

	
	
	ShPropertyData data;
	QLinkedList<ShEntity*>::iterator itr;
	QLinkedList<ShLayer*>::iterator itrLayer = this->previousLayers.begin();

	for (itr = this->selectedEntities.begin(); itr != this->selectedEntities.end(); ++itr) {
	
		this->changedLayer->Remove((*itr));
		(*itrLayer)->Add((*itr));
		(*itr)->SetLayer((*itrLayer));
		
		data = (*itr)->GetPropertyData();

		if (data.GetColor().GetType() == ShColor::Type::ByLayer) {
			data.SetColor((*itrLayer)->GetPropertyData().GetColor());
			(*itr)->SetPropertyData(data);
		}

		if (data.GetLineStyle().GetType() == ShLineStyle::Type::ByLayer) {
			data.SetLineStyle((*itrLayer)->GetPropertyData().GetLineStyle());
			(*itr)->SetPropertyData(data);
		}

		++itrLayer;
	}

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();


}



	
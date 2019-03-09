
#include "ShViewNotifyEventUpdateStrategy.h"
#include "ShNotifyEvent.h"
#include "FactoryMethod\ShCreatorViewUpdateFactory.h"

ShViewNotifyEventUpdateStrategy::ShViewNotifyEventUpdateStrategy(ShGraphicView *view,ShNotifyEvent *event) {

	this->strategy = ShCreatorViewUpdateFactory::Create(view, event);

}

ShViewNotifyEventUpdateStrategy::~ShViewNotifyEventUpdateStrategy() {

	if (this->strategy != 0)
		delete this->strategy;

}

void ShViewNotifyEventUpdateStrategy::Update() {

	this->strategy->Update();
}

/////////////////////////////////////////////////////////////////////////

ShViewUpdateStrategy::ShViewUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event)
	:view(view), event(event) {

}

ShViewUpdateStrategy::~ShViewUpdateStrategy() {

}

/////////////////////////////////////////////////////////////////////////

ShKeyPressedEventUpdateStrategy::ShKeyPressedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateStrategy(view, event) {

}

ShKeyPressedEventUpdateStrategy::~ShKeyPressedEventUpdateStrategy() {

}

#include "ActionHandler\ShActionHandlerManager.h"
#include "Interface\ShGraphicView.h"
void ShKeyPressedEventUpdateStrategy::Update() {

	ShKeyPressedEvent *event = dynamic_cast<ShKeyPressedEvent*>(this->event);

	this->view->actionHandlerManager->KeyPressEvent(event->GetEvent());

}

///////////////////////////////////////////////////////////////////////



ShPropertyColorComboSelChangedEventUpdateStrategy::ShPropertyColorComboSelChangedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateStrategy(view, event) {

}

ShPropertyColorComboSelChangedEventUpdateStrategy::~ShPropertyColorComboSelChangedEventUpdateStrategy() {

}

#include "Command Pattern\Entity Command\ShChangeEntityPropertyDataCommand.h"
void ShPropertyColorComboSelChangedEventUpdateStrategy::Update() {
	
	ShPropertyColorComboSelChangedEvent *event = 
		dynamic_cast<ShPropertyColorComboSelChangedEvent*>(this->event);

	QLinkedList<ShEntity*> selectedEntities;
	QLinkedList<ShColor> previousColors;
	QLinkedList<ShEntity*>::iterator itr;
	ShPropertyData data;

	

	for (itr = this->view->selectedEntityManager.Begin();
		itr != this->view->selectedEntityManager.End();
		++itr) {

		selectedEntities.append((*itr));
		previousColors.append((*itr)->GetPropertyData().GetColor());

		data = (*itr)->GetPropertyData();


		if (event->GetColor().GetType() == ShColor::Type::ByBlock)
			data.SetColor(this->view->GetData()->GetBlockData()->GetColor());
		else if (event->GetColor().GetType() == ShColor::Type::ByLayer)
			data.SetColor((*itr)->GetLayer()->GetPropertyData().GetColor());
		else
			data.SetColor(event->GetColor());

		(*itr)->SetPropertyData(data);
	}

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();



	ShChangeEntityPropertyDataCommand *command = new ShChangeEntityPropertyDataCommand(this->view,
		selectedEntities, previousColors, event->GetColor());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}

//////////////////////////////////////////////////////////////////////////

ShPropertyColorComboSelChangedEventUpdateStrategySelectedEntity0::
ShPropertyColorComboSelChangedEventUpdateStrategySelectedEntity0(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateStrategy(view, event) {

}

ShPropertyColorComboSelChangedEventUpdateStrategySelectedEntity0::
~ShPropertyColorComboSelChangedEventUpdateStrategySelectedEntity0() {

}

#include "Command Pattern\UI Command\ShChangePropertyDataCommand.h"
void ShPropertyColorComboSelChangedEventUpdateStrategySelectedEntity0::Update() {

	ShPropertyColorComboSelChangedEvent *event =
		dynamic_cast<ShPropertyColorComboSelChangedEvent*>(this->event);

	ShPropertyData prev = *(this->view->GetData()->GetPropertyData());
	this->view->GetData()->GetPropertyData()->SetColor(event->GetColor());

	ShChangePropertyDataCommand *command = new ShChangePropertyDataCommand(this->view, prev,
		(*this->view->GetData()->GetPropertyData()), ShChangePropertyDataCommand::ChangedType::Color);

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}


///////////////////////////////////////////////////////////////////////////////////

ShPropertyLineStyleComboSelChangedEventUpdateStrategy::ShPropertyLineStyleComboSelChangedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateStrategy(view, event) {

}

ShPropertyLineStyleComboSelChangedEventUpdateStrategy::~ShPropertyLineStyleComboSelChangedEventUpdateStrategy() {

}

void ShPropertyLineStyleComboSelChangedEventUpdateStrategy::Update() {

	ShPropertyLineStyleComboSelChangedEvent *event =
		dynamic_cast<ShPropertyLineStyleComboSelChangedEvent*>(this->event);

	QLinkedList<ShEntity*> selectedEntities;
	QLinkedList<ShLineStyle> previousLineStyles;
	QLinkedList<ShEntity*>::iterator itr;
	ShPropertyData data;

	for (itr = this->view->selectedEntityManager.Begin();
		itr != this->view->selectedEntityManager.End();
		++itr) {

		selectedEntities.append((*itr));
		previousLineStyles.append((*itr)->GetPropertyData().GetLineStyle());

		data = (*itr)->GetPropertyData();


		if (event->GetLineStyle().GetType() == ShLineStyle::Type::ByBlock)
			data.SetLineStyle(this->view->GetData()->GetBlockData()->GetLineStyle());
		else if (event->GetLineStyle().GetType() == ShLineStyle::Type::ByLayer)
			data.SetLineStyle((*itr)->GetLayer()->GetPropertyData().GetLineStyle());
		else
			data.SetLineStyle(event->GetLineStyle());
		

		(*itr)->SetPropertyData(data);
	}


	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();



	ShChangeEntityPropertyDataCommand *command = new ShChangeEntityPropertyDataCommand(this->view,
		selectedEntities, previousLineStyles, event->GetLineStyle());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
	
}


///////////////////////////////////////////////////////////////////////////////////////

ShPropertyLineStyleComboSelChangedEventUpdateStrategySelectedEntity0::
ShPropertyLineStyleComboSelChangedEventUpdateStrategySelectedEntity0(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateStrategy(view, event) {


}

ShPropertyLineStyleComboSelChangedEventUpdateStrategySelectedEntity0::
~ShPropertyLineStyleComboSelChangedEventUpdateStrategySelectedEntity0() {


}

void ShPropertyLineStyleComboSelChangedEventUpdateStrategySelectedEntity0::Update() {
	
	ShPropertyLineStyleComboSelChangedEvent *event =
		dynamic_cast<ShPropertyLineStyleComboSelChangedEvent*>(this->event);

	ShPropertyData prev = *(this->view->GetData()->GetPropertyData());
	this->view->GetData()->GetPropertyData()->SetLineStyle(event->GetLineStyle());

	ShChangePropertyDataCommand *command = new ShChangePropertyDataCommand(this->view, prev,
		(*this->view->GetData()->GetPropertyData()), ShChangePropertyDataCommand::ChangedType::LineStyle);

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}


////////////////////////////////////////////////////////////////////////////////////////////////

ShLayerComboSelChangedEventUpdateStrategy::ShLayerComboSelChangedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateStrategy(view, event) {

}

ShLayerComboSelChangedEventUpdateStrategy::~ShLayerComboSelChangedEventUpdateStrategy() {

}

#include "Command Pattern\Entity Command\ShChangeEntityLayerCommand.h"
void ShLayerComboSelChangedEventUpdateStrategy::Update() {
	
	ShLayerComboSelChangedEvent *event = dynamic_cast<ShLayerComboSelChangedEvent*>(this->event);

	QLinkedList<ShEntity*>::iterator itr;
	QLinkedList<ShEntity*> selectedEntities;
	QLinkedList<ShLayer*> previousLayers;
	ShLayer* layer = this->view->entityTable.GetLayerTable()->GetLayer(event->GetIndex());
	ShPropertyData data;

	for (itr = this->view->selectedEntityManager.Begin();
		itr != this->view->selectedEntityManager.End();
		++itr) {
	
		selectedEntities.append((*itr));
		previousLayers.append((*itr)->GetLayer());


		(*itr)->GetLayer()->Remove((*itr));

		layer->Add((*itr));
		(*itr)->SetLayer(layer);

		data = (*itr)->GetPropertyData();

		if (data.GetColor().GetType() == ShColor::Type::ByLayer) {
			data.SetColor(layer->GetPropertyData().GetColor());
			(*itr)->SetPropertyData(data);
		}

		if (data.GetLineStyle().GetType() == ShLineStyle::Type::ByLayer) {
			data.SetLineStyle(layer->GetPropertyData().GetLineStyle());
			(*itr)->SetPropertyData(data);
		}
	}

	event->SetCurrentLayer(layer);

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();

	ShChangeEntityLayerCommand *command = new ShChangeEntityLayerCommand(this->view, selectedEntities, previousLayers, layer);

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////

ShLayerComboSelChangedEventUpdateStrategySelectedEntity0::
ShLayerComboSelChangedEventUpdateStrategySelectedEntity0(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateStrategy(view, event) {

}

ShLayerComboSelChangedEventUpdateStrategySelectedEntity0::~ShLayerComboSelChangedEventUpdateStrategySelectedEntity0() {

}

#include "Command Pattern\UI Command\ShChangeCurrentLayerCommand.h"
void ShLayerComboSelChangedEventUpdateStrategySelectedEntity0::Update() {

	ShLayerComboSelChangedEvent *event = dynamic_cast<ShLayerComboSelChangedEvent*>(this->event);

	ShLayerTable *layerTable = this->view->entityTable.GetLayerTable();

	ShLayer* prev = layerTable->GetCurrentLayer();

	layerTable->SetCurrentLayerIndex(event->GetIndex());
	ShLayer *current = layerTable->GetCurrentLayer();


	this->view->GetData()->SetLayerData(current->GetData().GetPropertyData());

	if (this->view->GetData()->GetPropertyData()->GetColor().GetType() == ShColor::Type::ByLayer)
		this->view->GetData()->GetPropertyData()->SetColor(this->view->GetData()->GetLayerData()->GetColor());
	

	if (this->view->GetData()->GetPropertyData()->GetLineStyle().GetType() == ShLineStyle::ByLayer) 
		this->view->GetData()->GetPropertyData()->SetLineStyle(this->view->GetData()->GetLayerData()->GetLineStyle());
	

	event->SetCurrentLayer(current);

	if (prev == current)
		return;

	
	ShChangeCurrentLayerCommand *command = new ShChangeCurrentLayerCommand(this->view, prev, current);

	
	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}


////////////////////////////////////////////////////////////////////////////////////////////////////


ShLayerDataChangedEventUpdateStrategy::ShLayerDataChangedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateStrategy(view, event) {

}

ShLayerDataChangedEventUpdateStrategy::~ShLayerDataChangedEventUpdateStrategy() {

}

#include "Command Pattern\UI Command\ShChangeLayerDataCommand.h"
void ShLayerDataChangedEventUpdateStrategy::Update() {

	ShLayerDataChangedEvent *event = dynamic_cast<ShLayerDataChangedEvent*>(this->event);


	//All Entity that references to changed Layer, 
	//already is modified data in the function SetPropertyData in layer. 

	if (event->GetChangedLayer() == this->view->entityTable.GetLayerTable()->GetCurrentLayer()) {
	
		this->view->GetData()->GetLayerData()->SetColor(event->GetChangedLayer()->GetPropertyData().GetColor());
		this->view->GetData()->GetLayerData()->SetLineStyle(event->GetChangedLayer()->GetPropertyData().GetLineStyle());
	}


	event->SetCurrentLayer(this->view->entityTable.GetLayerTable()->GetCurrentLayer());

	DrawType type = DrawType::DrawNone;

	if (event->GetChangedType() == ShLayerDataChangedEvent::ChangedType::Color)
		type = (DrawType)(type | DrawType::DrawAll);
	else if (event->GetChangedType() == ShLayerDataChangedEvent::ChangedType::LineStyle)
		type = (DrawType)(type | DrawType::DrawAll);
	else if (event->GetChangedType() == ShLayerDataChangedEvent::ChangedType::TurnOnOff) {

		this->view->entityTable.GetLayerTable()->UpdateTurnOnLayerList();

		if (this->view->selectedEntityManager.GetSize() > 0) {
			this->view->selectedEntityManager.UnSelectAll();
			type = (DrawType)(type | DrawType::DrawAll);
		}
		else if (event->GetChangedLayer()->GetData().IsTurnOn() == true) {

			this->view->entityTable.GetLayerTable()->SetJustTurnOnLayer(event->GetChangedLayer());
			type = (DrawType)(type | DrawType::DrawCaptureImage | DrawType::DrawJustTurnOnLayer);
		}
		else {

			type = (DrawType)(type | DrawType::DrawAll);
		}
	}


	this->view->update(type);
	this->view->CaptureImage();


	

	ShChangeLayerDataCommand *command = new ShChangeLayerDataCommand(this->view, event->GetChangedLayer(),
		event->GetPreviousData(), (ShChangeLayerDataCommand::ChangedType)event->GetChangedType());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
}


//////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////

ShLayerCreatedEventUpdateStrategy::ShLayerCreatedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateStrategy(view, event) {

}

ShLayerCreatedEventUpdateStrategy::~ShLayerCreatedEventUpdateStrategy() {


}

#include "Command Pattern\UI Command\ShCreateLayerCommand.h"
void ShLayerCreatedEventUpdateStrategy::Update() {

	ShLayerCreatedEvent *event = dynamic_cast<ShLayerCreatedEvent*>(this->event);

	ShCreateLayerCommand *command = new ShCreateLayerCommand(this->view,
		event->GetNewLayer());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Command Pattern\UI Command\ShDeleteLayerCommand.h"
ShLayerDeletedEventUpdateStrategy::ShLayerDeletedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateStrategy(view, event) {

}
ShLayerDeletedEventUpdateStrategy::~ShLayerDeletedEventUpdateStrategy() {

}


void ShLayerDeletedEventUpdateStrategy::Update() {

	ShLayerDeletedEvent *event = dynamic_cast<ShLayerDeletedEvent*>(this->event);

	ShDeleteLayerCommand *command = new ShDeleteLayerCommand(this->view,
		event->GetDeletedLayer());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


ShCurrentLayerChangedEventUpdateStrategy::ShCurrentLayerChangedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateStrategy(view, event) {

}

ShCurrentLayerChangedEventUpdateStrategy::~ShCurrentLayerChangedEventUpdateStrategy() {

}


void ShCurrentLayerChangedEventUpdateStrategy::Update() {

	ShCurrentLayerChangedEvent *event = dynamic_cast<ShCurrentLayerChangedEvent*>(this->event);

	ShLayerTable *layerTable = this->view->entityTable.GetLayerTable();

	ShLayer* prev = event->GetPreviousLayer();
	ShLayer *current = event->GetCurrentLayer();


	this->view->GetData()->SetLayerData(current->GetData().GetPropertyData());

	if (this->view->GetData()->GetPropertyData()->GetColor().GetType() == ShColor::Type::ByLayer)
		this->view->GetData()->GetPropertyData()->SetColor(this->view->GetData()->GetLayerData()->GetColor());


	if (this->view->GetData()->GetPropertyData()->GetLineStyle().GetType() == ShLineStyle::ByLayer)
		this->view->GetData()->GetPropertyData()->SetLineStyle(this->view->GetData()->GetLayerData()->GetLineStyle());

	event->SetSelectedEntityCount(this->view->selectedEntityManager.GetSize());

	if (event->GetPreviousLayer() == event->GetCurrentLayer())
		return;

	ShChangeCurrentLayerCommand *command = new ShChangeCurrentLayerCommand(this->view, prev, current);

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////




#include "ShNotifyEventUpdateHandler.h"
#include "ShNotifyEvent.h"
#include "FactoryMethod\ShCreatorViewUpdateFactory.h"

ShNotifyEventUpdateHandler::ShNotifyEventUpdateHandler(ShGraphicView *view,ShNotifyEvent *event) {

	this->updateHandler = ShCreatorViewUpdateFactory::Create(view, event);

}

ShNotifyEventUpdateHandler::~ShNotifyEventUpdateHandler() {

	if (this->updateHandler != 0)
		delete this->updateHandler;

}

void ShNotifyEventUpdateHandler::Update() {

	this->updateHandler->Update();
}

/////////////////////////////////////////////////////////////////////////

ShViewUpdateHandler::ShViewUpdateHandler(ShGraphicView *view, ShNotifyEvent *event)
	:view(view), event(event) {

}

ShViewUpdateHandler::~ShViewUpdateHandler() {

}

/////////////////////////////////////////////////////////////////////////

ShKeyPressedEventUpdateHandler::ShKeyPressedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateHandler(view, event) {

}

ShKeyPressedEventUpdateHandler::~ShKeyPressedEventUpdateHandler() {

}

#include "ActionHandler\ShActionHandler.h"
void ShKeyPressedEventUpdateHandler::Update() {

	ShKeyPressedEvent *event = dynamic_cast<ShKeyPressedEvent*>(this->event);

	this->view->currentAction->KeyPressEvent(event->GetEvent());

}

///////////////////////////////////////////////////////////////////////



ShPropertyColorComboSelChangedEventUpdateHandler::ShPropertyColorComboSelChangedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateHandler(view, event) {

}

ShPropertyColorComboSelChangedEventUpdateHandler::~ShPropertyColorComboSelChangedEventUpdateHandler() {

}

#include "Command Pattern\ShChangeEntityPropertyDataCommand.h"
void ShPropertyColorComboSelChangedEventUpdateHandler::Update() {
	
	ShPropertyColorComboSelChangedEvent *event = 
		dynamic_cast<ShPropertyColorComboSelChangedEvent*>(this->event);

	//previous data.
	ShCompositeEntityMemento *memento = this->view->selectedEntityManager.CreateSelectedEntityMemento();

	QLinkedList<ShEntity*>::iterator itr;
	ShPropertyData data;

	

	for (itr = this->view->selectedEntityManager.Begin();
		itr != this->view->selectedEntityManager.End();
		++itr) {

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
		memento, event->GetColor());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}

//////////////////////////////////////////////////////////////////////////

ShPropertyColorComboSelChangedEventUpdateHandlerSelectedEntity0::
ShPropertyColorComboSelChangedEventUpdateHandlerSelectedEntity0(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateHandler(view, event) {

}

ShPropertyColorComboSelChangedEventUpdateHandlerSelectedEntity0::
~ShPropertyColorComboSelChangedEventUpdateHandlerSelectedEntity0() {

}

#include "Command Pattern\ShChangePropertyDataCommand.h"
void ShPropertyColorComboSelChangedEventUpdateHandlerSelectedEntity0::Update() {

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

ShPropertyLineStyleComboSelChangedEventUpdateHandler::ShPropertyLineStyleComboSelChangedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateHandler(view, event) {

}

ShPropertyLineStyleComboSelChangedEventUpdateHandler::~ShPropertyLineStyleComboSelChangedEventUpdateHandler() {

}

void ShPropertyLineStyleComboSelChangedEventUpdateHandler::Update() {

	ShPropertyLineStyleComboSelChangedEvent *event =
		dynamic_cast<ShPropertyLineStyleComboSelChangedEvent*>(this->event);

	//previous data.
	ShCompositeEntityMemento *memento = this->view->selectedEntityManager.CreateSelectedEntityMemento();

	QLinkedList<ShEntity*>::iterator itr;
	ShPropertyData data;

	for (itr = this->view->selectedEntityManager.Begin();
		itr != this->view->selectedEntityManager.End();
		++itr) {


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
		memento, event->GetLineStyle());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
	
}


///////////////////////////////////////////////////////////////////////////////////////

ShPropertyLineStyleComboSelChangedEventUpdateHandlerSelectedEntity0::
ShPropertyLineStyleComboSelChangedEventUpdateHandlerSelectedEntity0(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateHandler(view, event) {


}

ShPropertyLineStyleComboSelChangedEventUpdateHandlerSelectedEntity0::
~ShPropertyLineStyleComboSelChangedEventUpdateHandlerSelectedEntity0() {


}

void ShPropertyLineStyleComboSelChangedEventUpdateHandlerSelectedEntity0::Update() {
	
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

ShLayerComboSelChangedEventUpdateHandler::ShLayerComboSelChangedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateHandler(view, event) {

}

ShLayerComboSelChangedEventUpdateHandler::~ShLayerComboSelChangedEventUpdateHandler() {

}

#include "Command Pattern\ShChangeEntityLayerCommand.h"
void ShLayerComboSelChangedEventUpdateHandler::Update() {
	
	ShLayerComboSelChangedEvent *event = dynamic_cast<ShLayerComboSelChangedEvent*>(this->event);

	//previous data
	ShCompositeEntityMemento *memento = this->view->selectedEntityManager.CreateSelectedEntityMemento();

	QLinkedList<ShEntity*>::iterator itr;

	ShLayer* layer = this->view->entityTable.GetLayerTable()->GetLayer(event->GetIndex());
	ShPropertyData data;

	for (itr = this->view->selectedEntityManager.Begin();
		itr != this->view->selectedEntityManager.End();
		++itr) {
	
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

	ShChangeEntityLayerCommand *command = new ShChangeEntityLayerCommand(this->view, memento, layer);

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////

ShLayerComboSelChangedEventUpdateHandlerSelectedEntity0::
ShLayerComboSelChangedEventUpdateHandlerSelectedEntity0(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateHandler(view, event) {

}

ShLayerComboSelChangedEventUpdateHandlerSelectedEntity0::~ShLayerComboSelChangedEventUpdateHandlerSelectedEntity0() {

}

#include "Command Pattern\ShChangeCurrentLayerCommand.h"
void ShLayerComboSelChangedEventUpdateHandlerSelectedEntity0::Update() {

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

ShLayerDataChangedEventUpdateHandler::ShLayerDataChangedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateHandler(view, event) {

}

ShLayerDataChangedEventUpdateHandler::~ShLayerDataChangedEventUpdateHandler() {

}

#include "Command Pattern\ShChangeLayerDataCommand.h"
void ShLayerDataChangedEventUpdateHandler::Update() {

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
		event->GetPreviousMemento(), (ShChangeLayerDataCommand::ChangedType)event->GetChangedType());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
}


//////////////////////////////////////////////////////////////////////////////////////////////////

/*
ShLayerDataChangedEventUpdateHandlerSelectedEntity0::
ShLayerDataChangedEventUpdateHandlerSelectedEntity0(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateHandler(view, event) {

}

ShLayerDataChangedEventUpdateHandlerSelectedEntity0::~ShLayerDataChangedEventUpdateHandlerSelectedEntity0() {

}

void ShLayerDataChangedEventUpdateHandlerSelectedEntity0::Update() {

	ShLayerDataChangedEvent *event = dynamic_cast<ShLayerDataChangedEvent*>(this->event);

	if (event->GetChangedLayer() == this->view->entityTable.GetLayerTable()->GetCurrentLayer()) {
		this->view->GetData()->SetLayerData(event->GetChangedLayer()->GetData().GetPropertyData());

		if (this->view->GetData()->GetPropertyData()->GetColor().GetType() == ShColor::Type::ByLayer) {
			this->view->GetData()->GetPropertyData()->SetColor(this->view->GetData()->GetLayerData()->GetColor());
		}
		if (this->view->GetData()->GetPropertyData()->GetLineStyle().GetType() == ShLineStyle::ByLayer) {
			this->view->GetData()->GetPropertyData()->SetLineStyle(this->view->GetData()->GetLayerData()->GetLineStyle());
		}
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
		event->GetPreviousMemento(), (ShChangeLayerDataCommand::ChangedType)event->GetChangedType());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}

*/
////////////////////////////////////////////////////////////////////////////////////////////////////

ShLayerCreatedEventUpdateHandler::ShLayerCreatedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateHandler(view, event) {

}

ShLayerCreatedEventUpdateHandler::~ShLayerCreatedEventUpdateHandler() {


}

#include "Command Pattern\ShCreateLayerCommand.h"
void ShLayerCreatedEventUpdateHandler::Update() {

	ShLayerCreatedEvent *event = dynamic_cast<ShLayerCreatedEvent*>(this->event);

	ShCreateLayerCommand *command = new ShCreateLayerCommand(this->view,
		event->GetNewLayer()->CreateMemento());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Command Pattern\ShDeleteLayerCommand.h"
ShLayerDeletedEventUpdateHandler::ShLayerDeletedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateHandler(view, event) {

}
ShLayerDeletedEventUpdateHandler::~ShLayerDeletedEventUpdateHandler() {

}


void ShLayerDeletedEventUpdateHandler::Update() {

	ShLayerDeletedEvent *event = dynamic_cast<ShLayerDeletedEvent*>(this->event);

	ShDeleteLayerCommand *command = new ShDeleteLayerCommand(this->view,
		event->GetDeletedLayer()->CreateMemento());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////


ShCurrentLayerChangedEventUpdateHandler::ShCurrentLayerChangedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event)
	:ShViewUpdateHandler(view, event) {

}

ShCurrentLayerChangedEventUpdateHandler::~ShCurrentLayerChangedEventUpdateHandler() {

}


void ShCurrentLayerChangedEventUpdateHandler::Update() {

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






















/////////////////////////////////////////////////////////////////////////////////

/*

#include "Interface\ShGraphicView.h"

ShViewUpdateHandlerSelectedEntityCount0::ShViewUpdateHandlerSelectedEntityCount0(ShGraphicView *view)
	:view(view) {

}

ShViewUpdateHandlerSelectedEntityCount0::~ShViewUpdateHandlerSelectedEntityCount0() {

}

void ShViewUpdateHandlerSelectedEntityCount0::Update(ShNotifyEvent *event) {

	if (dynamic_cast<ShKeyPressedEvent*>(event))
		this->Update(dynamic_cast<ShKeyPressedEvent*>(event));

	else if (dynamic_cast<ShPropertyColorComboSelChangedEvent*>(event))
		this->Update(dynamic_cast<ShPropertyColorComboSelChangedEvent*>(event));

	else if (dynamic_cast<ShPropertyLineStyleComboSelChangedEvent*>(event))
		this->Update(dynamic_cast<ShPropertyLineStyleComboSelChangedEvent*>(event));

	else if (dynamic_cast<ShLayerComboSelChangedEvent*>(event))
		this->Update(dynamic_cast<ShLayerComboSelChangedEvent*>(event));

	else if (dynamic_cast<ShLayerDataChangedEvent*>(event))
		this->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));

	else if (dynamic_cast<ShLayerCreatedEvent*>(event))
		this->Update(dynamic_cast<ShLayerCreatedEvent*>(event));

	else if (dynamic_cast<ShLayerDeletedEvent*>(event))
		this->Update(dynamic_cast<ShLayerDeletedEvent*>(event));

}

#include "ActionHandler\ShActionHandler.h"
void ShViewUpdateHandlerSelectedEntityCount0::Update(ShKeyPressedEvent *event) {

	this->view->currentAction->KeyPressEvent(event->GetEvent());
}

#include "Command Pattern\ShChangePropertyDataCommand.h"
#include "Memento Pattern\ShMemento.h"
#include "Command Pattern\ShChangeEntityPropertyDataCommand.h"
void ShViewUpdateHandlerSelectedEntityCount0::Update(ShPropertyColorComboSelChangedEvent *event) {

	ShPropertyData prev = *(this->view->GetData()->GetPropertyData());
	this->view->GetData()->GetPropertyData()->SetColor(event->GetColor());

	
	ShChangePropertyDataCommand *command = new ShChangePropertyDataCommand(this->view, prev,
		(*this->view->GetData()->GetPropertyData()), ShChangePropertyDataCommand::ChangedType::Color);

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

		
}


void ShViewUpdateHandlerSelectedEntityCount0::Update(ShPropertyLineStyleComboSelChangedEvent *event) {



	ShPropertyData prev = *(this->view->GetData()->GetPropertyData());
	this->view->GetData()->GetPropertyData()->SetLineStyle(event->GetLineStyle());

	
	ShChangePropertyDataCommand *command = new ShChangePropertyDataCommand(this->view, prev,
		(*this->view->GetData()->GetPropertyData()), ShChangePropertyDataCommand::ChangedType::LineStyle);

	command->Execute();

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
		

}

#include "Command Pattern\ShChangeCurrentLayerCommand.h"
void ShViewUpdateHandlerSelectedEntityCount0::Update(ShLayerComboSelChangedEvent *event) {



	int prevIndex = this->view->entityTable.GetLayerTable()->GetCurrentLayerIndex();

	this->view->entityTable.GetLayerTable()->SetCurrentLayerIndex(event->GetIndex());

	this->view->GetData()->SetLayerData(this->view->entityTable.GetLayerTable()->GetCurrentLayer()->GetData().GetPropertyData());

	if (this->view->GetData()->GetPropertyData()->GetColor().GetType() == ShColor::Type::ByLayer) {

		this->view->GetData()->GetPropertyData()->SetColor(this->view->GetData()->GetLayerData()->GetColor());
	}
	if (this->view->GetData()->GetPropertyData()->GetLineStyle().GetType() == ShLineStyle::ByLayer) {
		this->view->GetData()->GetPropertyData()->SetLineStyle(this->view->GetData()->GetLayerData()->GetLineStyle());
	}

	if (prevIndex == event->GetIndex())
		return;


	
	ShChangeCurrentLayerCommand *command = new ShChangeCurrentLayerCommand(this->view,
		this->view->entityTable.GetLayerTable()->GetLayer(prevIndex),
		this->view->entityTable.GetLayerTable()->GetLayer(event->GetIndex()));

	command->Execute();

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
		


}

#include "Command Pattern\ShChangeLayerDataCommand.h"
void ShViewUpdateHandlerSelectedEntityCount0::Update(ShLayerDataChangedEvent *event) {

	//currentLayer info changed...
	if (event->GetChangedLayer() == this->view->entityTable.GetLayerTable()->GetCurrentLayer()) {
		this->view->GetData()->SetLayerData(event->GetChangedLayer()->GetData().GetPropertyData());

		if (this->view->GetData()->GetPropertyData()->GetColor().GetType() == ShColor::Type::ByLayer) {
			this->view->GetData()->GetPropertyData()->SetColor(this->view->GetData()->GetLayerData()->GetColor());
		}
		if (this->view->GetData()->GetPropertyData()->GetLineStyle().GetType() == ShLineStyle::ByLayer) {
			this->view->GetData()->GetPropertyData()->SetLineStyle(this->view->GetData()->GetLayerData()->GetLineStyle());
		}
	}
	
	event->SetCurrentLayer(this->view->entityTable.GetLayerTable()->GetCurrentLayer());
	

	
	ShChangeLayerDataCommand *command = new ShChangeLayerDataCommand(this->view,
		event->GetChangedLayer(), event->GetPreviousMemento(), (ShChangeLayerDataCommand::ChangedType)event->GetChangedType());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
		

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
}

#include "Command Pattern\ShCreateLayerCommand.h"
void ShViewUpdateHandlerSelectedEntityCount0::Update(ShLayerCreatedEvent *event) {

	
	ShCreateLayerCommand *command = new ShCreateLayerCommand(this->view,
		event->GetNewLayer()->CreateMemento());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
		
}

#include "Command Pattern\ShDeleteLayerCommand.h"
void ShViewUpdateHandlerSelectedEntityCount0::Update(ShLayerDeletedEvent *event) {
	
	
	ShDeleteLayerCommand *command = new ShDeleteLayerCommand(this->view,
		event->GetDeletedLayer()->CreateMemento());



	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
	

}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


ShViewUpdateHandler::ShViewUpdateHandler(ShGraphicView *view)
	:view(view) {

}

ShViewUpdateHandler::~ShViewUpdateHandler() {

}

void ShViewUpdateHandler::Update(ShNotifyEvent *event) {

	if (dynamic_cast<ShKeyPressedEvent*>(event))
		this->Update(dynamic_cast<ShKeyPressedEvent*>(event));

	else if (dynamic_cast<ShPropertyColorComboSelChangedEvent*>(event))
		this->Update(dynamic_cast<ShPropertyColorComboSelChangedEvent*>(event));

	else if (dynamic_cast<ShPropertyLineStyleComboSelChangedEvent*>(event))
		this->Update(dynamic_cast<ShPropertyLineStyleComboSelChangedEvent*>(event));

	else if (dynamic_cast<ShLayerComboSelChangedEvent*>(event))
		this->Update(dynamic_cast<ShLayerComboSelChangedEvent*>(event));

	else if (dynamic_cast<ShLayerDataChangedEvent*>(event))
		this->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));

	else if (dynamic_cast<ShLayerCreatedEvent*>(event))
		this->Update(dynamic_cast<ShLayerCreatedEvent*>(event));

	else if (dynamic_cast<ShLayerDeletedEvent*>(event))
		this->Update(dynamic_cast<ShLayerDeletedEvent*>(event));

}

#include "ActionHandler\ShActionHandler.h"
void ShViewUpdateHandler::Update(ShKeyPressedEvent *event) {

	this->view->currentAction->KeyPressEvent(event->GetEvent());
}

#include "Command Pattern\ShChangePropertyDataCommand.h"
#include "Memento Pattern\ShMemento.h"
#include "Command Pattern\ShChangeEntityPropertyDataCommand.h"
void ShViewUpdateHandler::Update(ShPropertyColorComboSelChangedEvent *event) {





	

	QLinkedList<ShEntity*>::iterator itr;
	ShCompositeEntityMemento *memento = new ShCompositeEntityMemento;

	for (itr = this->view->selectedEntityManager.Begin();
		itr != this->view->selectedEntityManager.End();
		++itr) {

		memento->list.append((*itr)->CreateMemento());

	}

	ShChangeEntityPropertyDataCommand *command = new ShChangeEntityPropertyDataCommand(this->view,
	memento, event->GetColor());


	command->Execute();

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
	
}

void ShViewUpdateHandler::Update(ShPropertyLineStyleComboSelChangedEvent *event) {


	
	QLinkedList<ShEntity*>::iterator itr;

	ShCompositeEntityMemento *memento = new ShCompositeEntityMemento;

	for (itr = this->view->selectedEntityManager.Begin();
		itr != this->view->selectedEntityManager.End();
		++itr) {

		memento->list.append((*itr)->CreateMemento());

	}

	ShChangeEntityPropertyDataCommand *command = new ShChangeEntityPropertyDataCommand(this->view,
		memento, event->GetLineStyle());


	command->Execute();

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

		
}

#include "Command Pattern\ShChangeCurrentLayerCommand.h"
void ShViewUpdateHandler::Update(ShLayerComboSelChangedEvent *event) {

	


}

#include "Command Pattern\ShChangeLayerDataCommand.h"
void ShViewUpdateHandler::Update(ShLayerDataChangedEvent *event) {

	//currentLayer info changed...
	if (event->GetChangedLayer() == this->view->entityTable.GetLayerTable()->GetCurrentLayer()) {
		this->view->GetData()->SetLayerData(event->GetChangedLayer()->GetData().GetPropertyData());

		if (this->view->GetData()->GetPropertyData()->GetColor().GetType() == ShColor::Type::ByLayer) {
			this->view->GetData()->GetPropertyData()->SetColor(this->view->GetData()->GetLayerData()->GetColor());
		}
		if (this->view->GetData()->GetPropertyData()->GetLineStyle().GetType() == ShLineStyle::ByLayer) {
			this->view->GetData()->GetPropertyData()->SetLineStyle(this->view->GetData()->GetLayerData()->GetLineStyle());
		}
	}

	event->SetCurrentLayer(this->view->entityTable.GetLayerTable()->GetCurrentLayer());

	

	ShChangeLayerDataCommand *command = new ShChangeLayerDataCommand(this->view,
		event->GetChangedLayer(), event->GetPreviousMemento(), (ShChangeLayerDataCommand::ChangedType)event->GetChangedType());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

		

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
}

#include "Command Pattern\ShCreateLayerCommand.h"
void ShViewUpdateHandler::Update(ShLayerCreatedEvent *event) {

	
	ShCreateLayerCommand *command = new ShCreateLayerCommand(this->view,
		event->GetNewLayer()->CreateMemento());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
		
}

#include "Command Pattern\ShDeleteLayerCommand.h"
void ShViewUpdateHandler::Update(ShLayerDeletedEvent *event) {
	
	ShDeleteLayerCommand *command = new ShDeleteLayerCommand(this->view,
		event->GetDeletedLayer()->CreateMemento());



	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
		
}

*/
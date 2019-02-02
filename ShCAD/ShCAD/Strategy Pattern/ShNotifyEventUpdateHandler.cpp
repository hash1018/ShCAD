
#include "ShNotifyEventUpdateHandler.h"
#include "ShNotifyEvent.h"
ShNotifyEventUpdateHandler::ShNotifyEventUpdateHandler()
	:updateHandler(0) {

}



ShNotifyEventUpdateHandler::ShNotifyEventUpdateHandler(ShGraphicView *view) {

	this->updateHandler = new ShGraphicViewUpdateHandler(view);

}

ShNotifyEventUpdateHandler::~ShNotifyEventUpdateHandler() {

	if (this->updateHandler != 0)
		delete this->updateHandler;

}

void ShNotifyEventUpdateHandler::Update(ShNotifyEvent *event) {

	this->updateHandler->Update(event);
}

/////////////////////////////////////////////////////////////////////////////////

#include "Interface\ShGraphicView.h"

ShGraphicViewUpdateHandler::ShGraphicViewUpdateHandler(ShGraphicView *view)
	:view(view) {

}

ShGraphicViewUpdateHandler::~ShGraphicViewUpdateHandler() {

}

void ShGraphicViewUpdateHandler::Update(ShNotifyEvent *event) {

	if (dynamic_cast<ShKeyPressedEvent*>(event))
		this->Update(dynamic_cast<ShKeyPressedEvent*>(event));

	else if (dynamic_cast<ShPropertyColorComboSelChangedEvent*>(event))
		this->Update(dynamic_cast<ShPropertyColorComboSelChangedEvent*>(event));

	else if (dynamic_cast<ShPropertyLineStyleComboSelChangedEvent*>(event))
		this->Update(dynamic_cast<ShPropertyLineStyleComboSelChangedEvent*>(event));

	else if (dynamic_cast<ShCurrentLayerChangedEvent*>(event))
		this->Update(dynamic_cast<ShCurrentLayerChangedEvent*>(event));

	else if (dynamic_cast<ShLayerDataChangedEvent*>(event))
		this->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));

	else if (dynamic_cast<ShLayerCreatedEvent*>(event))
		this->Update(dynamic_cast<ShLayerCreatedEvent*>(event));

	else if (dynamic_cast<ShLayerDeletedEvent*>(event))
		this->Update(dynamic_cast<ShLayerDeletedEvent*>(event));

}

#include "ActionHandler\ShActionHandler.h"
void ShGraphicViewUpdateHandler::Update(ShKeyPressedEvent *event) {

	this->view->currentAction->KeyPressEvent(event->GetEvent());
}

#include "Command Pattern\ShChangePropertyDataCommand.h"
#include "Memento Pattern\ShMemento.h"
#include "Command Pattern\ShChangeEntityPropertyDataCommand.h"
void ShGraphicViewUpdateHandler::Update(ShPropertyColorComboSelChangedEvent *event) {
	

	if (this->view->selectedEntityManager.GetSize() == 0) {

		ShPropertyData prev = *(this->view->GetData()->GetPropertyData());
		this->view->GetData()->GetPropertyData()->SetColor(event->GetColor());

		ShChangePropertyDataCommand *command = new ShChangePropertyDataCommand(this->view, prev,
			(*this->view->GetData()->GetPropertyData()), ShChangePropertyDataCommand::ChangedType::Color);

		this->view->undoTaker.Push(command);

		if (!this->view->redoTaker.IsEmpty())
			this->view->redoTaker.DeleteAll();
	}
	else {

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

}

void ShGraphicViewUpdateHandler::Update(ShPropertyLineStyleComboSelChangedEvent *event) {
	
	ShPropertyData prev = *(this->view->GetData()->GetPropertyData());
	this->view->GetData()->GetPropertyData()->SetLineStyle(event->GetLineStyle());

	ShChangePropertyDataCommand *command = new ShChangePropertyDataCommand(this->view, prev,
		(*this->view->GetData()->GetPropertyData()), ShChangePropertyDataCommand::ChangedType::LineStyle);

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}

#include "Command Pattern\ShChangeCurrentLayerCommand.h"
void ShGraphicViewUpdateHandler::Update(ShCurrentLayerChangedEvent *event) {

	this->view->GetData()->SetLayerData(this->view->entityTable.GetLayerTable()->GetCurrentLayer()->GetData().GetPropertyData());

	if (this->view->GetData()->GetPropertyData()->GetColor().GetType() == ShColor::Type::ByLayer) {

		this->view->GetData()->GetPropertyData()->SetColor(this->view->GetData()->GetLayerData()->GetColor());
	}
	if (this->view->GetData()->GetPropertyData()->GetLineStyle().GetType() == ShLineStyle::ByLayer) {
		this->view->GetData()->GetPropertyData()->SetLineStyle(this->view->GetData()->GetLayerData()->GetLineStyle());
	}

	if (event->GetPreviousLayer() == event->GetCurrentLayer())
		return;



	ShChangeCurrentLayerCommand *command = new ShChangeCurrentLayerCommand(this->view, 
		event->GetPreviousLayer(), event->GetCurrentLayer());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();
	

}

#include "Command Pattern\ShChangeLayerDataCommand.h"
void ShGraphicViewUpdateHandler::Update(ShLayerDataChangedEvent *event) {

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
void ShGraphicViewUpdateHandler::Update(ShLayerCreatedEvent *event) {

	ShCreateLayerCommand *command = new ShCreateLayerCommand(this->view,
		event->GetNewLayer()->CreateMemento());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}

#include "Command Pattern\ShDeleteLayerCommand.h"
void ShGraphicViewUpdateHandler::Update(ShLayerDeletedEvent *event) {

	ShDeleteLayerCommand *command = new ShDeleteLayerCommand(this->view,
		event->GetDeletedLayer()->CreateMemento());



	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

}
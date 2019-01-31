
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

void ShGraphicViewUpdateHandler::Update(ShPropertyColorComboSelChangedEvent *event) {
	
	this->view->GetData()->GetPropertyData()->SetColor(event->GetColor());
}

void ShGraphicViewUpdateHandler::Update(ShPropertyLineStyleComboSelChangedEvent *event) {
	
	this->view->GetData()->GetPropertyData()->SetLineStyle(event->GetLineStyle());
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


	if (event->GetChangedType() == ShLayerDataChangedEvent::ChangedType::Color) {
		this->view->update(DrawType::DrawAll);
		this->view->CaptureImage();

	}
	else if (event->GetChangedType() == ShLayerDataChangedEvent::ChangedType::LineStyle) {
		this->view->update(DrawType::DrawAll);
		this->view->CaptureImage();
	}

	else if (event->GetChangedType() == ShLayerDataChangedEvent::ChangedType::TurnOnOff) {

		this->view->entityTable.GetLayerTable()->UpdateTurnOnLayerList();

		if (event->GetChangedLayer()->GetData().IsTurnOn() == true) {
			qDebug("Handler ->  %d", event->GetChangedLayer()->GetSize());
			this->view->entityTable.GetLayerTable()->SetJustTurnOnLayer(event->GetChangedLayer());
			this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawJustTurnOnLayer));
		}
		else {
		
			this->view->update(DrawType::DrawAll);
		}

		
		this->view->CaptureImage();
	}
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
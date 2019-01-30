
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
	
	this->view->GetData()->propertyData.color = event->GetColor();
}

void ShGraphicViewUpdateHandler::Update(ShPropertyLineStyleComboSelChangedEvent *event) {
	
	this->view->GetData()->propertyData.lineStyle = event->GetLineStyle();
}

#include "Command Pattern\ShChangeCurrentLayerCommand.h"
void ShGraphicViewUpdateHandler::Update(ShCurrentLayerChangedEvent *event) {

	this->view->GetData()->layerData = this->view->entityTable.GetLayerTable()->GetCurrentLayer()->GetData().propertyData;

	if (this->view->GetData()->propertyData.color.type == ShColor::Type::ByLayer) {
		this->view->GetData()->propertyData.color = this->view->GetData()->layerData.color;
	}
	if (this->view->GetData()->propertyData.lineStyle.type == ShLineStyle::ByLayer) {
		this->view->GetData()->propertyData.lineStyle = this->view->GetData()->layerData.lineStyle;
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
		this->view->GetData()->layerData = event->GetChangedLayer()->GetData().propertyData;

		if (this->view->GetData()->propertyData.color.type == ShColor::Type::ByLayer) {
			this->view->GetData()->propertyData.color = this->view->GetData()->layerData.color;
		}
		if (this->view->GetData()->propertyData.lineStyle.type == ShLineStyle::ByLayer) {
			this->view->GetData()->propertyData.lineStyle = this->view->GetData()->layerData.lineStyle;
		}
	}
	
	event->SetCurrentLayer(this->view->entityTable.GetLayerTable()->GetCurrentLayer());
	

	ShChangeLayerDataCommand *command = new ShChangeLayerDataCommand(this->view,
		event->GetChangedLayer(), event->GetPreviousMemento());

	this->view->undoTaker.Push(command);

	if (!this->view->redoTaker.IsEmpty())
		this->view->redoTaker.DeleteAll();

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
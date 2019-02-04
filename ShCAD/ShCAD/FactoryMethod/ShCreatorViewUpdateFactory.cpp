
#include "ShCreatorViewUpdateFactory.h"
#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
#include "State Pattern\ShNotifyEventUpdateHandler.h"
ShCreatorViewUpdateFactory::ShCreatorViewUpdateFactory() {

}

ShCreatorViewUpdateFactory::~ShCreatorViewUpdateFactory() {

}

ShViewUpdateHandler* ShCreatorViewUpdateFactory::Create(ShGraphicView *view, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::Type::KeyPressed)
		return new ShKeyPressedEventUpdateHandler(view, event);

	if (event->GetType() == ShNotifyEvent::Type::PropertyColorComboSelChanged) {
	
		if (view->selectedEntityManager.GetSize() == 0)
			return new ShPropertyColorComboSelChangedEventUpdateHandlerSelectedEntity0(view, event);
		else
			return new ShPropertyColorComboSelChangedEventUpdateHandler(view, event);
	}

	if (event->GetType() == ShNotifyEvent::Type::PropertyLineStyleComboSelChanged) {
	
		if (view->selectedEntityManager.GetSize() == 0)
			return new ShPropertyLineStyleComboSelChangedEventUpdateHandlerSelectedEntity0(view, event);
		else
			return new ShPropertyLineStyleComboSelChangedEventUpdateHandler(view, event);
	}

	if (event->GetType() == ShNotifyEvent::Type::LayerComboSelChanged) {
	
		if (view->selectedEntityManager.GetSize() == 0)
			return new ShLayerComboSelChangedEventUpdateHandlerSelectedEntity0(view, event);
		else
			return new ShLayerComboSelChangedEventUpdateHandler(view, event);
	}

	if (event->GetType() == ShNotifyEvent::Type::LayerDataChanged) {
	
		//if (view->selectedEntityManager.GetSize() == 0)
		//	return new ShLayerDataChangedEventUpdateHandlerSelectedEntity0(view, event);
		//else
		return new ShLayerDataChangedEventUpdateHandler(view, event);
	}

	if (event->GetType() == ShNotifyEvent::Type::LayerCreated)
		return new ShLayerCreatedEventUpdateHandler(view, event);

	if (event->GetType() == ShNotifyEvent::Type::LayerDeleted)
		return new ShLayerDeletedEventUpdateHandler(view, event);


	if (event->GetType() == ShNotifyEvent::Type::CurrentLayerChanged)
		return new ShCurrentLayerChangedEventUpdateHandler(view, event);


	return 0;

}
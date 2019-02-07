
#include "ShCreatorViewUpdateFactory.h"
#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
#include "Strategy Pattern\ShViewNotifyEventUpdateStrategy.h"
ShCreatorViewUpdateFactory::ShCreatorViewUpdateFactory() {

}

ShCreatorViewUpdateFactory::~ShCreatorViewUpdateFactory() {

}

ShViewUpdateStrategy* ShCreatorViewUpdateFactory::Create(ShGraphicView *view, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::Type::KeyPressed)
		return new ShKeyPressedEventUpdateStrategy(view, event);

	if (event->GetType() == ShNotifyEvent::Type::PropertyColorComboSelChanged) {
	
		if (view->selectedEntityManager.GetSize() == 0)
			return new ShPropertyColorComboSelChangedEventUpdateStrategySelectedEntity0(view, event);
		else
			return new ShPropertyColorComboSelChangedEventUpdateStrategy(view, event);
	}

	if (event->GetType() == ShNotifyEvent::Type::PropertyLineStyleComboSelChanged) {
	
		if (view->selectedEntityManager.GetSize() == 0)
			return new ShPropertyLineStyleComboSelChangedEventUpdateStrategySelectedEntity0(view, event);
		else
			return new ShPropertyLineStyleComboSelChangedEventUpdateStrategy(view, event);
	}

	if (event->GetType() == ShNotifyEvent::Type::LayerComboSelChanged) {
	
		if (view->selectedEntityManager.GetSize() == 0)
			return new ShLayerComboSelChangedEventUpdateStrategySelectedEntity0(view, event);
		else
			return new ShLayerComboSelChangedEventUpdateStrategy(view, event);
	}

	if (event->GetType() == ShNotifyEvent::Type::LayerDataChanged) {
	
		//if (view->selectedEntityManager.GetSize() == 0)
		//	return new ShLayerDataChangedEventUpdateStrategySelectedEntity0(view, event);
		//else
		return new ShLayerDataChangedEventUpdateStrategy(view, event);
	}

	if (event->GetType() == ShNotifyEvent::Type::LayerCreated)
		return new ShLayerCreatedEventUpdateStrategy(view, event);

	if (event->GetType() == ShNotifyEvent::Type::LayerDeleted)
		return new ShLayerDeletedEventUpdateStrategy(view, event);


	if (event->GetType() == ShNotifyEvent::Type::CurrentLayerChanged)
		return new ShCurrentLayerChangedEventUpdateStrategy(view, event);


	return 0;

}
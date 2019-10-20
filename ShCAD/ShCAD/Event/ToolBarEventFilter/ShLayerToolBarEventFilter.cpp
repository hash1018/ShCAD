
#include "ShLayerToolBarEventFilter.h"
#include "Event\ShNotifyEvent.h"
#include "Interface\ShCADWidget.h"
#include "Base\ShLayer.h"
#include "Base\ShLayerTable.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "Interface\Item\ShLayerComboBox.h"
#include "Interface\ToolBar\ShLayerToolBar.h"

ShLayerToolBarEventFilter::ShLayerToolBarEventFilter(ShLayerToolBar *layerToolBar, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::ActivatedWidgetChanged)
		this->strategy = new ShLayerToolBarActivatedWidgetChangedEventFilterStrategy(layerToolBar, event);
	else if (event->getType() == ShNotifyEvent::CurrentLayerChanged)
		this->strategy = new ShLayerToolBarCurrentLayerChangedEventFilterStrategy(layerToolBar, event);
	else if (event->getType() == ShNotifyEvent::LayerDataChanged)
		this->strategy = new ShLayerToolBarLayerDataChangedEventFilterStrategy(layerToolBar, event);
	else if (event->getType() == ShNotifyEvent::LayerCreated)
		this->strategy = new ShLayerToolBarLayerCreatedEventFilterStrategy(layerToolBar, event);
	else if (event->getType() == ShNotifyEvent::LayerDeleted)
		this->strategy = new ShLayerToolBarLayerDeletedEventFilterStrategy(layerToolBar, event);
	else if (event->getType() == ShNotifyEvent::ActionChanged)
		this->strategy = new ShLayerToolBarActionChangedEventFilterStrategy(layerToolBar, event);
	else if (event->getType() == ShNotifyEvent::SelectedEntityCountChanged)
		this->strategy = new ShLayerToolBarSelectedEntityCountChangedEventFilterStrategy(layerToolBar, event);


}

ShLayerToolBarEventFilter::~ShLayerToolBarEventFilter() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShLayerToolBarEventFilter::update() {

	if (this->strategy != nullptr)
		this->strategy->update();
}

///////////////////////////////////////////////////////


ShLayerToolBarEventFilterStrategy::ShLayerToolBarEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event)
	:layerToolBar(layerToolBar), event(event) {

}

ShLayerToolBarEventFilterStrategy::~ShLayerToolBarEventFilterStrategy() {

}

///////////////////////////////////////////////////////

ShLayerToolBarActivatedWidgetChangedEventFilterStrategy::ShLayerToolBarActivatedWidgetChangedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event)
	:ShLayerToolBarEventFilterStrategy(layerToolBar, event) {

}

ShLayerToolBarActivatedWidgetChangedEventFilterStrategy::~ShLayerToolBarActivatedWidgetChangedEventFilterStrategy() {

}

void ShLayerToolBarActivatedWidgetChangedEventFilterStrategy::update() {

	ShActivatedWidgetChangedEvent *event = dynamic_cast<ShActivatedWidgetChangedEvent*>(this->event);

	this->layerToolBar->getLayerCombo()->setLayerTable(event->getNewWidget()->getLayerTable());
	this->layerToolBar->getLayerCombo()->updateLayerCombo();
	this->layerToolBar->getLayerCombo()->setLayerComboCurrentIndex(event->getNewWidget()->getLayerTable()->getCurrentLayerIndex());

	ShActionChangedEvent event2(event->getNewWidget()->getCurrentActionType());
	ShLayerToolBarActionChangedEventFilterStrategy strategy2(this->layerToolBar, &event2);
	strategy2.update();

	ShSelectedEntityCountChangedEvent event3(event->getNewWidget(), event->getNewWidget()->getSelectedEntities()->getSelectedList());
	ShLayerToolBarSelectedEntityCountChangedEventFilterStrategy strategy3(this->layerToolBar, &event3);
	strategy3.update();

}

//////////////////////////////////////////////////////////


ShLayerToolBarCurrentLayerChangedEventFilterStrategy::ShLayerToolBarCurrentLayerChangedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event)
	:ShLayerToolBarEventFilterStrategy(layerToolBar, event) {

}

ShLayerToolBarCurrentLayerChangedEventFilterStrategy::~ShLayerToolBarCurrentLayerChangedEventFilterStrategy() {

}

void ShLayerToolBarCurrentLayerChangedEventFilterStrategy::update() {

	this->layerToolBar->getLayerCombo()->setLayerComboCurrentIndex(dynamic_cast<ShCurrentLayerChangedEvent*>(this->event)->getCurrentLayer());
}

///////////////////////////////////////////////////////////

ShLayerToolBarLayerDataChangedEventFilterStrategy::ShLayerToolBarLayerDataChangedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event)
	:ShLayerToolBarEventFilterStrategy(layerToolBar, event) {

}

ShLayerToolBarLayerDataChangedEventFilterStrategy::~ShLayerToolBarLayerDataChangedEventFilterStrategy() {

}

void ShLayerToolBarLayerDataChangedEventFilterStrategy::update() {

	this->layerToolBar->getLayerCombo()->updateLayerCombo();
}

/////////////////////////////////////////////////////////////

ShLayerToolBarLayerCreatedEventFilterStrategy::ShLayerToolBarLayerCreatedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event)
	:ShLayerToolBarEventFilterStrategy(layerToolBar, event) {

}

ShLayerToolBarLayerCreatedEventFilterStrategy::~ShLayerToolBarLayerCreatedEventFilterStrategy() {

}

void ShLayerToolBarLayerCreatedEventFilterStrategy::update() {

	this->layerToolBar->getLayerCombo()->updateLayerCombo();
}

/////////////////////////////////////////////////////////////////

ShLayerToolBarLayerDeletedEventFilterStrategy::ShLayerToolBarLayerDeletedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event)
	:ShLayerToolBarEventFilterStrategy(layerToolBar, event) {

}

ShLayerToolBarLayerDeletedEventFilterStrategy::~ShLayerToolBarLayerDeletedEventFilterStrategy() {

}

void ShLayerToolBarLayerDeletedEventFilterStrategy::update() {

	this->layerToolBar->getLayerCombo()->updateLayerCombo();
}

//////////////////////////////////////////////////////////////////

ShLayerToolBarActionChangedEventFilterStrategy::ShLayerToolBarActionChangedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event)
	:ShLayerToolBarEventFilterStrategy(layerToolBar, event) {

}

ShLayerToolBarActionChangedEventFilterStrategy::~ShLayerToolBarActionChangedEventFilterStrategy() {

}

void ShLayerToolBarActionChangedEventFilterStrategy::update() {

	ShActionChangedEvent *event = dynamic_cast<ShActionChangedEvent*>(this->event);

	if (event->getNewType() == ActionType::ActionDefault)
		this->layerToolBar->getLayerCombo()->setDisabled(false);
	else
		this->layerToolBar->getLayerCombo()->setDisabled(true);
}


/////////////////////////////////////////////////////////////////////

ShLayerToolBarSelectedEntityCountChangedEventFilterStrategy::ShLayerToolBarSelectedEntityCountChangedEventFilterStrategy(ShLayerToolBar *layerToolBar, ShNotifyEvent *event)
	:ShLayerToolBarEventFilterStrategy(layerToolBar, event) {

}

ShLayerToolBarSelectedEntityCountChangedEventFilterStrategy::~ShLayerToolBarSelectedEntityCountChangedEventFilterStrategy() {

}

void ShLayerToolBarSelectedEntityCountChangedEventFilterStrategy::update() {

	ShSelectedEntityCountChangedEvent *event = dynamic_cast<ShSelectedEntityCountChangedEvent*>(this->event);

	ShLayer *layer;
	ShLayer temp("none", ShPropertyData());

	if (event->getWidget()->getSelectedEntities()->getSize() == 0) {

		layer = event->getWidget()->getCurrentLayer();
	}
	else {

		auto itr = const_cast<QLinkedList<ShEntity*>&>(event->getList()).begin();
		layer = (*itr)->getLayer();
		++itr;

		for (itr; itr != const_cast<QLinkedList<ShEntity*>&>(event->getList()).end(); ++itr) {

			if ((*itr)->getLayer() != layer) {
				layer = &temp;
				break;
			}
		}

	}

	ShCurrentLayerChangedEvent event2(layer);
	ShLayerToolBarCurrentLayerChangedEventFilterStrategy strategy2(this->layerToolBar, &event2);
	strategy2.update();
}



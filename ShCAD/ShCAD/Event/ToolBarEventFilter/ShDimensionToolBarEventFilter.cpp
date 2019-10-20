
#include "ShDimensionToolBarEventFilter.h"
#include "Event\ShNotifyEvent.h"
#include "Interface\Item\ShDimensionStyleComboBox.h"
#include "Interface\ToolBar\ShDimensionToolBar.h"
#include "Interface\ShCADWidget.h"
#include "Base\ShDimensionStyleTable.h"

ShDimensionToolBarEventFilter::ShDimensionToolBarEventFilter(ShDimensionToolBar *dimensionToolBar, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::ActivatedWidgetChanged)
		this->strategy = new ShDimensionToolBarActivatedWidgetChangedEventFilterStrategy(dimensionToolBar, event);

}

ShDimensionToolBarEventFilter::~ShDimensionToolBarEventFilter() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShDimensionToolBarEventFilter::update() {

	if (this->strategy != nullptr)
		this->strategy->update();
}



////////////////////////////////////////////////

ShDimensionToolBarEventFilterStrategy::ShDimensionToolBarEventFilterStrategy(ShDimensionToolBar *dimensionToolBar, ShNotifyEvent *event)
	:dimensionToolBar(dimensionToolBar), event(event) {

}

ShDimensionToolBarEventFilterStrategy::~ShDimensionToolBarEventFilterStrategy() {

}


//////////////////////////////////////////////////


ShDimensionToolBarActivatedWidgetChangedEventFilterStrategy::ShDimensionToolBarActivatedWidgetChangedEventFilterStrategy(ShDimensionToolBar *dimensionToolBar, ShNotifyEvent *event)
	:ShDimensionToolBarEventFilterStrategy(dimensionToolBar, event) {

}

ShDimensionToolBarActivatedWidgetChangedEventFilterStrategy::~ShDimensionToolBarActivatedWidgetChangedEventFilterStrategy() {

}

void ShDimensionToolBarActivatedWidgetChangedEventFilterStrategy::update() {

	ShActivatedWidgetChangedEvent *event = dynamic_cast<ShActivatedWidgetChangedEvent*>(this->event);

	this->dimensionToolBar->getDimensionStyleComboBox()->setDimensionStyleTable(event->getNewWidget()->getDimensionStyleTable());
	this->dimensionToolBar->getDimensionStyleComboBox()->updateDimensionStyleCombo();
	this->dimensionToolBar->getDimensionStyleComboBox()->setDimensionStyleComboCurrentIndex(event->getNewWidget()->getDimensionStyleTable()->getCurrentDimensionStyleIndex());

}



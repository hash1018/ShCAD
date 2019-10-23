
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
	else if (event->getType() == ShNotifyEvent::ActionChanged)
		this->strategy = new ShDimensionToolBarActionChangedEventFilterStrategy(dimensionToolBar, event);
	else if (event->getType() == ShNotifyEvent::CurrentDimensionStyleChanged)
		this->strategy = new ShDimensionToolBarCurrentDimensionStyleChangedEventFilterStrategy(dimensionToolBar, event);

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

	ShActionChangedEvent event2(event->getNewWidget()->getCurrentActionType());
	ShDimensionToolBarActionChangedEventFilterStrategy strategy2(this->dimensionToolBar, &event2);
	strategy2.update();
}


/////////////////////////////////////////////////

ShDimensionToolBarActionChangedEventFilterStrategy::ShDimensionToolBarActionChangedEventFilterStrategy(ShDimensionToolBar *dimensionToolBar, ShNotifyEvent *event)
	:ShDimensionToolBarEventFilterStrategy(dimensionToolBar, event) {

}

ShDimensionToolBarActionChangedEventFilterStrategy::~ShDimensionToolBarActionChangedEventFilterStrategy() {

}

void ShDimensionToolBarActionChangedEventFilterStrategy::update() {

	ShActionChangedEvent *event = dynamic_cast<ShActionChangedEvent*>(this->event);

	if (event->getNewType() == ActionType::ActionDefault)
		this->dimensionToolBar->getDimensionStyleComboBox()->setDisabled(false);
	else
		this->dimensionToolBar->getDimensionStyleComboBox()->setDisabled(true);
}


////////////////////////////////////////////////

ShDimensionToolBarCurrentDimensionStyleChangedEventFilterStrategy::ShDimensionToolBarCurrentDimensionStyleChangedEventFilterStrategy(ShDimensionToolBar *dimensionToolBar, ShNotifyEvent *event)
	:ShDimensionToolBarEventFilterStrategy(dimensionToolBar, event) {

}

ShDimensionToolBarCurrentDimensionStyleChangedEventFilterStrategy::~ShDimensionToolBarCurrentDimensionStyleChangedEventFilterStrategy() {

}

void ShDimensionToolBarCurrentDimensionStyleChangedEventFilterStrategy::update() {

	ShCurrentDimensionStyleChangedEvent *event = dynamic_cast<ShCurrentDimensionStyleChangedEvent*>(this->event);
	this->dimensionToolBar->getDimensionStyleComboBox()->setDimensionStyleComboCurrentIndex(event->getCurrentDimensionStyle());
}
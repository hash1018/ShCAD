
#include "ShQuickAccessToolBarEventFilter.h"
#include "Interface\ToolBar\ShQuickAccessToolBar.h"
#include "Event\ShNotifyEvent.h"
#include "Interface\ShCADWidget.h"
#include "UnRedo\ShTransactionStack.h"


ShQuickAccessToolBarEventFilter::ShQuickAccessToolBarEventFilter(ShQuickAccessToolBar *quickAccessToolBar, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::ActivatedWidgetChanged)
		this->strategy = new ShQuickAccessToolBarActivatedWidgetChangedEventFilterStrategy(quickAccessToolBar, event);
	else if (event->getType() == ShNotifyEvent::TransactionStackSizeChanged)
		this->strategy = new ShQuickAccessToolBarTransactionSizeChangedEventFilterStrategy(quickAccessToolBar, event);
}

ShQuickAccessToolBarEventFilter::~ShQuickAccessToolBarEventFilter() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShQuickAccessToolBarEventFilter::update() {

	if (this->strategy != nullptr)
		this->strategy->update();
}

//////////////////////////////////////////////////////////////////////////

ShQuickAccessToolBarEventFilterStrategy::ShQuickAccessToolBarEventFilterStrategy(ShQuickAccessToolBar *quickAccessToolBar, ShNotifyEvent *event)
	:quickAccessToolBar(quickAccessToolBar), event(event) {

}

ShQuickAccessToolBarEventFilterStrategy::~ShQuickAccessToolBarEventFilterStrategy() {

}

//////////////////////////////////////////////////////////////////////////

ShQuickAccessToolBarActivatedWidgetChangedEventFilterStrategy::ShQuickAccessToolBarActivatedWidgetChangedEventFilterStrategy(ShQuickAccessToolBar *quickAccessToolBar, ShNotifyEvent *event)
	:ShQuickAccessToolBarEventFilterStrategy(quickAccessToolBar, event) {

}

ShQuickAccessToolBarActivatedWidgetChangedEventFilterStrategy::~ShQuickAccessToolBarActivatedWidgetChangedEventFilterStrategy() {

}

void ShQuickAccessToolBarActivatedWidgetChangedEventFilterStrategy::update() {

	ShActivatedWidgetChangedEvent *event = dynamic_cast<ShActivatedWidgetChangedEvent*>(this->event);

	ShCADWidget *widget = event->getNewWidget();

	if (widget->getUndoStack()->getSize() == 0)
		this->quickAccessToolBar->setUndoButtonEnabled(false);
	else
		this->quickAccessToolBar->setUndoButtonEnabled(true);

	if (widget->getRedoStack()->getSize() == 0)
		this->quickAccessToolBar->setRedoButtonEnabled(false);
	else
		this->quickAccessToolBar->setRedoButtonEnabled(true);
}

//////////////////////////////////////////////////////////////////////////////
ShQuickAccessToolBarTransactionSizeChangedEventFilterStrategy::ShQuickAccessToolBarTransactionSizeChangedEventFilterStrategy(ShQuickAccessToolBar *quickAccessToolBar, ShNotifyEvent *event)
	:ShQuickAccessToolBarEventFilterStrategy(quickAccessToolBar, event) {

}

ShQuickAccessToolBarTransactionSizeChangedEventFilterStrategy::~ShQuickAccessToolBarTransactionSizeChangedEventFilterStrategy() {

}

void ShQuickAccessToolBarTransactionSizeChangedEventFilterStrategy::update() {

	ShTransactionStackSizeChangedEvent *event = dynamic_cast<ShTransactionStackSizeChangedEvent*>(this->event);

	if (event->getUndoSize() == 0)
		this->quickAccessToolBar->setUndoButtonEnabled(false);
	else
		this->quickAccessToolBar->setUndoButtonEnabled(true);

	if (event->getRedoSize() == 0)
		this->quickAccessToolBar->setRedoButtonEnabled(false);
	else
		this->quickAccessToolBar->setRedoButtonEnabled(true);

}

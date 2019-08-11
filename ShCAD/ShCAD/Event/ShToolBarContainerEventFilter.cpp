

#include "ShToolBarContainerEventFilter.h"
#include "Event\ShNotifyEvent.h"
#include "Data\ShColorList.h"
#include "Interface\Item\ShColorComboBox.h"
#include "Interface\ToolBar\ShPropertyToolBar.h"
#include "Interface\ShCADWidget.h"
#include "Interface\Item\ShLineStyleComboBox.h"
#include "Data\ShLineStyleList.h"
#include "Interface\ToolBar\ShQuickAccessToolBar.h"
#include "UnRedo\ShTransactionStack.h"

ShPropertyToolBarEventFilter::ShPropertyToolBarEventFilter(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::CurrentColorChanged)
		this->strategy = new ShPropertyToolBarCurrentColorChangedEventFilterStrategy(propertyToolBar, event);
	else if (event->getType() == ShNotifyEvent::ActivatedWidgetChanged)
		this->strategy = new ShPropertyToolBarActivatedWidgetChangedEventFilterStrategy(propertyToolBar, event);
	else if (event->getType() == ShNotifyEvent::CurrentLineStyleChanged)
		this->strategy = new ShPropertyToolBarCurrentLineStyleChangedEventFilterStrategy(propertyToolBar, event);

}

ShPropertyToolBarEventFilter::~ShPropertyToolBarEventFilter() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShPropertyToolBarEventFilter::update() {

	if (this->strategy != nullptr)
		this->strategy->update();

}


///////////////////////////////////////////////////

ShPropertyToolBarEventFilterStrategy::ShPropertyToolBarEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event)
	:propertyToolBar(propertyToolBar), event(event) {

}

ShPropertyToolBarEventFilterStrategy::~ShPropertyToolBarEventFilterStrategy() {

}

///////////////////////////////////////////////////////////

ShPropertyToolBarCurrentColorChangedEventFilterStrategy::ShPropertyToolBarCurrentColorChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event)
	:ShPropertyToolBarEventFilterStrategy(propertyToolBar, event) {

}

ShPropertyToolBarCurrentColorChangedEventFilterStrategy::~ShPropertyToolBarCurrentColorChangedEventFilterStrategy() {

}

void ShPropertyToolBarCurrentColorChangedEventFilterStrategy::update() {

	ShColor color = dynamic_cast<ShCurrentColorChangedEvent*>(this->event)->getColor();
	int index = 0;

	if (color.getType() == ShColor::Type::ByBlock) {
		this->propertyToolBar->getColorCombo()->setBlockColor(color);
		index = 0;
	}
	else if (color.getType() == ShColor::Type::ByLayer) {
		this->propertyToolBar->getColorCombo()->setLayerColor(color);
		index = 1;
	}
	else {
		ShColorList *list = ShColorList::getInstance();
		index = list->search(color);
		index += 2;
	}

	this->propertyToolBar->getColorCombo()->updateColorCombo();
	this->propertyToolBar->getColorCombo()->setColorComboCurrentIndex(index);
}


//////////////////////////////////////////////////////////

ShPropertyToolBarActivatedWidgetChangedEventFilterStrategy::ShPropertyToolBarActivatedWidgetChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event)
	:ShPropertyToolBarEventFilterStrategy(propertyToolBar, event) {

}

ShPropertyToolBarActivatedWidgetChangedEventFilterStrategy::~ShPropertyToolBarActivatedWidgetChangedEventFilterStrategy() {

}

void ShPropertyToolBarActivatedWidgetChangedEventFilterStrategy::update() {

	ShActivatedWidgetChangedEvent *event = dynamic_cast<ShActivatedWidgetChangedEvent*>(this->event);

	ShCADWidget *widget = event->getNewWidget();

	ShColorComboBox *colorCombo = this->propertyToolBar->getColorCombo();

	//colorCombo->setBlockColor()
	//colorCombo->setLayerColor(view->getLayerTable()->getCurrentLayer()->getPropertyData().getColor());

	ShCurrentColorChangedEvent event2(widget->getPropertyData().getColor());
	ShPropertyToolBarCurrentColorChangedEventFilterStrategy strategy2(this->propertyToolBar, &event2);
	strategy2.update();

	ShCurrentLineStyleChangedEvent event3(widget->getPropertyData().getLineStyle());
	ShPropertyToolBarCurrentLineStyleChangedEventFilterStrategy strategy3(this->propertyToolBar, &event3);
	strategy3.update();
}

///////////////////////////////////////////////////////////////////////////////


ShPropertyToolBarCurrentLineStyleChangedEventFilterStrategy::ShPropertyToolBarCurrentLineStyleChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event)
	:ShPropertyToolBarEventFilterStrategy(propertyToolBar, event) {

}

ShPropertyToolBarCurrentLineStyleChangedEventFilterStrategy::~ShPropertyToolBarCurrentLineStyleChangedEventFilterStrategy() {

}

void ShPropertyToolBarCurrentLineStyleChangedEventFilterStrategy::update() {

	ShLineStyle lineStyle = dynamic_cast<ShCurrentLineStyleChangedEvent*>(this->event)->getLineStyle();
	int index = 0;

	if (lineStyle.getType() == ShLineStyle::Type::ByBlock) {
		this->propertyToolBar->getLineStyleCombo()->setBlockLineStyle(lineStyle);
		index = 0;
	}
	else if (lineStyle.getType() == ShLineStyle::Type::ByLayer) {
		this->propertyToolBar->getLineStyleCombo()->setLayerLineStyle(lineStyle);
		index = 1;
	}
	else {
		ShLineStyleList *list = ShLineStyleList::getInstance();
		index = list->search(lineStyle);
		index += 2;
	}

	this->propertyToolBar->getLineStyleCombo()->updateLineStyleCombo();
	this->propertyToolBar->getLineStyleCombo()->setLineStyleComboCurrentIndex(index);
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


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
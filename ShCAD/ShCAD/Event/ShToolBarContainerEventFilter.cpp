

#include "ShToolBarContainerEventFilter.h"
#include "Event\ShNotifyEvent.h"
#include "Data\ShColorList.h"
#include "Interface\Item\ShColorComboBox.h"
#include "Interface\ToolBar\ShPropertyToolBar.h"
#include "Interface\ShCADWidget.h"


ShPropertyToolBarEventFilter::ShPropertyToolBarEventFilter(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::CurrentColorChanged)
		this->strategy = new ShPropertyToolBarCurrentColorChangedEventFilterStrategy(propertyToolBar, event);
	else if (event->getType() == ShNotifyEvent::ActivatedWidgetChanged)
		this->strategy = new ShPropertyToolBarActivatedWidgetChangedEventFilterStrategy(propertyToolBar, event);
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


	//colorCombo->SetBlockColor()
	//colorCombo->SetLayerColor(view->GetLayerTable()->GetCurrentLayer()->GetPropertyData().GetColor());

	ShColor color = widget->getPropertyData().getColor();

	int index = 0;

	if (color.getType() == ShColor::Type::ByBlock) {
		index = 0;
	}
	else if (color.getType() == ShColor::Type::ByLayer) {
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
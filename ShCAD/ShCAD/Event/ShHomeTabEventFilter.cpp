
#include "ShHomeTabEventFilter.h"
#include "Event\ShNotifyEvent.h"
#include "Data\ShColorList.h"
#include "Interface\Item\ShColorComboBox.h"
#include "Interface\Ribbon\ShHomeTab.h"
#include "Interface\ShCADWidget.h"


ShPropertyPanelEventFilter::ShPropertyPanelEventFilter(ShPropertyPanel *propertyPanel, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::CurrentColorChanged)
		this->strategy = new ShPropertyPanelCurrentColorChangedEventFilterStrategy(propertyPanel, event);
	else if (event->getType() == ShNotifyEvent::ActivatedWidgetChanged)
		this->strategy = new ShPropertyPanelActivatedWidgetChangedEventFilterStrategy(propertyPanel, event);
}

ShPropertyPanelEventFilter::~ShPropertyPanelEventFilter() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShPropertyPanelEventFilter::update() {

	if (this->strategy != nullptr)
		this->strategy->update();
		
}


///////////////////////////////////////////////////

ShPropertyPanelEventFilterStrategy::ShPropertyPanelEventFilterStrategy(ShPropertyPanel *propertyPanel, ShNotifyEvent *event)
	:propertyPanel(propertyPanel), event(event) {

}

ShPropertyPanelEventFilterStrategy::~ShPropertyPanelEventFilterStrategy() {

}

///////////////////////////////////////////////////////////

ShPropertyPanelCurrentColorChangedEventFilterStrategy::ShPropertyPanelCurrentColorChangedEventFilterStrategy(ShPropertyPanel *propertyPanel, ShNotifyEvent *event)
	:ShPropertyPanelEventFilterStrategy(propertyPanel, event) {

}

ShPropertyPanelCurrentColorChangedEventFilterStrategy::~ShPropertyPanelCurrentColorChangedEventFilterStrategy() {

}

void ShPropertyPanelCurrentColorChangedEventFilterStrategy::update() {

	ShColor color = dynamic_cast<ShCurrentColorChangedEvent*>(this->event)->getColor();
	int index = 0;

	if (color.getType() == ShColor::Type::ByBlock) {
		this->propertyPanel->getColorCombo()->setBlockColor(color);
		index = 0;
	}
	else if (color.getType() == ShColor::Type::ByLayer) {
		this->propertyPanel->getColorCombo()->setLayerColor(color);
		index = 1;
	}
	else {
		ShColorList *list = ShColorList::getInstance();
		index = list->search(color);
		index += 2;
	}

	this->propertyPanel->getColorCombo()->updateColorCombo();
	this->propertyPanel->getColorCombo()->setColorComboCurrentIndex(index);
}


//////////////////////////////////////////////////////////

ShPropertyPanelActivatedWidgetChangedEventFilterStrategy::ShPropertyPanelActivatedWidgetChangedEventFilterStrategy(ShPropertyPanel *propertyPanel, ShNotifyEvent *event)
	:ShPropertyPanelEventFilterStrategy(propertyPanel, event) {

}

ShPropertyPanelActivatedWidgetChangedEventFilterStrategy::~ShPropertyPanelActivatedWidgetChangedEventFilterStrategy() {

}

void ShPropertyPanelActivatedWidgetChangedEventFilterStrategy::update() {

	ShActivatedWidgetChangedEvent *event = dynamic_cast<ShActivatedWidgetChangedEvent*>(this->event);

	ShCADWidget *widget = event->getNewWidget();

	ShColorComboBox *colorCombo = this->propertyPanel->getColorCombo();


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

	this->propertyPanel->getColorCombo()->updateColorCombo();
	this->propertyPanel->getColorCombo()->setColorComboCurrentIndex(index);
}
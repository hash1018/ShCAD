
#include "ShHomeTabEventFilter.h"
#include "Event\ShNotifyEvent.h"
#include "Data\ShColorList.h"
#include "Interface\Item\ShColorComboBox.h"
#include "Interface\Ribbon\ShHomeTab.h"
#include "Interface\ShCADWidget.h"
#include "Interface\Item\ShLineStyleComboBox.h"
#include "Data\ShLineStyleList.h"
#include "Interface\Item\ShLayerComboBox.h"
#include "Base\ShLayerTable.h"


ShPropertyPanelEventFilter::ShPropertyPanelEventFilter(ShPropertyPanel *propertyPanel, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::CurrentColorChanged)
		this->strategy = new ShPropertyPanelCurrentColorChangedEventFilterStrategy(propertyPanel, event);
	else if (event->getType() == ShNotifyEvent::ActivatedWidgetChanged)
		this->strategy = new ShPropertyPanelActivatedWidgetChangedEventFilterStrategy(propertyPanel, event);
	else if (event->getType() == ShNotifyEvent::CurrentLineStyleChanged)
		this->strategy = new ShPropertyPanelCurrentLineStyleChangedEventFilterStrategy(propertyPanel, event);
	else if (event->getType() == ShNotifyEvent::CurrentLayerChanged)
		this->strategy = new ShPropertyPanelCurrentLayerChangedEventFilterStrategy(propertyPanel, event);
	else if (event->getType() == ShNotifyEvent::LayerDataChanged)
		this->strategy = new ShPropertyPanelLayerDataChangedEventFilterStrategy(propertyPanel, event);

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

	//colorCombo->setBlockColor()
	colorCombo->setLayerColor(widget->getLayerTable()->getCurrentLayer()->getPropertyData().getColor());

	ShCurrentColorChangedEvent event2(widget->getPropertyData().getColor());
	ShPropertyPanelCurrentColorChangedEventFilterStrategy strategy2(this->propertyPanel, &event2);
	strategy2.update();


	ShLineStyleComboBox *lineStyleCombo = this->propertyPanel->getLineStyleCombo();

	lineStyleCombo->setLayerLineStyle(widget->getLayerTable()->getCurrentLayer()->getPropertyData().getLineStyle());

	ShCurrentLineStyleChangedEvent event3(widget->getPropertyData().getLineStyle());
	ShPropertyPanelCurrentLineStyleChangedEventFilterStrategy strategy3(this->propertyPanel, &event3);
	strategy3.update();
}

//////////////////////////////////////////////////////////////////////////////

ShPropertyPanelCurrentLineStyleChangedEventFilterStrategy::ShPropertyPanelCurrentLineStyleChangedEventFilterStrategy(ShPropertyPanel *propertyPanel, ShNotifyEvent *event)
	:ShPropertyPanelEventFilterStrategy(propertyPanel, event) {

}

ShPropertyPanelCurrentLineStyleChangedEventFilterStrategy::~ShPropertyPanelCurrentLineStyleChangedEventFilterStrategy() {

}

void ShPropertyPanelCurrentLineStyleChangedEventFilterStrategy::update() {

	ShLineStyle lineStyle = dynamic_cast<ShCurrentLineStyleChangedEvent*>(this->event)->getLineStyle();
	int index = 0;

	if (lineStyle.getType() == ShLineStyle::Type::ByBlock) {
		this->propertyPanel->getLineStyleCombo()->setBlockLineStyle(lineStyle);
		index = 0;
	}
	else if (lineStyle.getType() == ShLineStyle::Type::ByLayer) {
		this->propertyPanel->getLineStyleCombo()->setLayerLineStyle(lineStyle);
		index = 1;
	}
	else {
		ShLineStyleList *list = ShLineStyleList::getInstance();
		index = list->search(lineStyle);
		index += 2;
	}

	this->propertyPanel->getLineStyleCombo()->updateLineStyleCombo();
	this->propertyPanel->getLineStyleCombo()->setLineStyleComboCurrentIndex(index);
}


////////////////////////////////////////////////////////////

ShPropertyPanelCurrentLayerChangedEventFilterStrategy::ShPropertyPanelCurrentLayerChangedEventFilterStrategy(ShPropertyPanel *propertyPanel, ShNotifyEvent *event)
	:ShPropertyPanelEventFilterStrategy(propertyPanel, event) {

}

ShPropertyPanelCurrentLayerChangedEventFilterStrategy::~ShPropertyPanelCurrentLayerChangedEventFilterStrategy() {

}

void ShPropertyPanelCurrentLayerChangedEventFilterStrategy::update() {

	ShCurrentLayerChangedEvent *event = dynamic_cast<ShCurrentLayerChangedEvent*>(this->event);

	this->propertyPanel->getColorCombo()->setLayerColor(event->getCurrentLayer()->getPropertyData().getColor());
	this->propertyPanel->getColorCombo()->updateColorCombo();
	this->propertyPanel->getColorCombo()->setColorComboCurrentIndex(this->propertyPanel->getColorCombo()->getColorComboIndex());

}

/////////////////////////////////////////////////////////

ShPropertyPanelLayerDataChangedEventFilterStrategy::ShPropertyPanelLayerDataChangedEventFilterStrategy(ShPropertyPanel *propertyPanel, ShNotifyEvent *event)
	:ShPropertyPanelEventFilterStrategy(propertyPanel, event) {

}

ShPropertyPanelLayerDataChangedEventFilterStrategy::~ShPropertyPanelLayerDataChangedEventFilterStrategy() {

}


void ShPropertyPanelLayerDataChangedEventFilterStrategy::update() {

	ShLayerDataChangedEvent *event = dynamic_cast<ShLayerDataChangedEvent*>(this->event);

	if (event->isCurrent() == false)
		return;

	if (event->getChangedType() == ShLayerDataChangedEvent::ChangedType::Color) {

		this->propertyPanel->getColorCombo()->setLayerColor(*event->getColor());
		this->propertyPanel->getColorCombo()->updateColorCombo();
		this->propertyPanel->getColorCombo()->setColorComboCurrentIndex(this->propertyPanel->getColorCombo()->getColorComboIndex());
	}

}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

ShLayerPanelEventFilter::ShLayerPanelEventFilter(ShLayerPanel *layerPanel, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::ActivatedWidgetChanged)
		this->strategy = new ShLayerPanelActivatedWidgetChangedEventFilterStrategy(layerPanel, event);
	else if (event->getType() == ShNotifyEvent::CurrentLayerChanged)
		this->strategy = new ShLayerPanelCurrentLayerChangedEventFilterStrategy(layerPanel, event);
	else if (event->getType() == ShNotifyEvent::LayerDataChanged)
		this->strategy = new ShLayerPanelLayerDataChangedEventFilterStrategy(layerPanel, event);
	

}

ShLayerPanelEventFilter::~ShLayerPanelEventFilter() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShLayerPanelEventFilter::update() {

	if (this->strategy != nullptr)
		this->strategy->update();
}

///////////////////////////////////////////////////////


ShLayerPanelEventFilterStrategy::ShLayerPanelEventFilterStrategy(ShLayerPanel *layerPanel, ShNotifyEvent *event)
	:layerPanel(layerPanel), event(event) {

}

ShLayerPanelEventFilterStrategy::~ShLayerPanelEventFilterStrategy() {

}

///////////////////////////////////////////////////////

ShLayerPanelActivatedWidgetChangedEventFilterStrategy::ShLayerPanelActivatedWidgetChangedEventFilterStrategy(ShLayerPanel *layerPanel, ShNotifyEvent *event)
	:ShLayerPanelEventFilterStrategy(layerPanel, event) {

}

ShLayerPanelActivatedWidgetChangedEventFilterStrategy::~ShLayerPanelActivatedWidgetChangedEventFilterStrategy() {

}

void ShLayerPanelActivatedWidgetChangedEventFilterStrategy::update() {

	ShActivatedWidgetChangedEvent *event = dynamic_cast<ShActivatedWidgetChangedEvent*>(this->event);

	this->layerPanel->getLayerCombo()->setLayerTable(event->getNewWidget()->getLayerTable());
	this->layerPanel->getLayerCombo()->updateLayerCombo();
	this->layerPanel->getLayerCombo()->setLayerComboCurrentIndex(event->getNewWidget()->getLayerTable()->getCurrentLayerIndex());
}

//////////////////////////////////////////////////////////

ShLayerPanelCurrentLayerChangedEventFilterStrategy::ShLayerPanelCurrentLayerChangedEventFilterStrategy(ShLayerPanel *layerPanel, ShNotifyEvent *event)
	:ShLayerPanelEventFilterStrategy(layerPanel, event) {

}

ShLayerPanelCurrentLayerChangedEventFilterStrategy::~ShLayerPanelCurrentLayerChangedEventFilterStrategy() {

}

void ShLayerPanelCurrentLayerChangedEventFilterStrategy::update() {

	this->layerPanel->getLayerCombo()->setLayerComboCurrentIndex(dynamic_cast<ShCurrentLayerChangedEvent*>(this->event)->getCurrentLayer());
}

/////////////////////////////////////////////////////////////

ShLayerPanelLayerDataChangedEventFilterStrategy::ShLayerPanelLayerDataChangedEventFilterStrategy(ShLayerPanel *layerPanel, ShNotifyEvent *event)
	:ShLayerPanelEventFilterStrategy(layerPanel, event) {

}

ShLayerPanelLayerDataChangedEventFilterStrategy::~ShLayerPanelLayerDataChangedEventFilterStrategy() {

}

void ShLayerPanelLayerDataChangedEventFilterStrategy::update() {

	this->layerPanel->getLayerCombo()->updateLayerCombo();
}
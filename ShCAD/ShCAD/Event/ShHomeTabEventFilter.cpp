
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
#include "Interface\Item\ShButton.h"
#include "Entity\ShEntity.h"
#include "Entity\Composite\ShSelectedEntities.h"


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
	else if (event->getType() == ShNotifyEvent::ActionChanged)
		this->strategy = new ShPropertyPanelActionChangedEventFilterStrategy(propertyPanel, event);
	else if (event->getType() == ShNotifyEvent::SelectedEntityCountChanged)
		this->strategy = new ShPropertyPanelSelectedEntityCountChangedEventFilterStrategy(propertyPanel, event);

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

	if (color.getType() == ShColor::Type::Invalid) {
	
		index = -1;
	}
	else if (color.getType() == ShColor::Type::ByBlock) {
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

	colorCombo->setLayerColor(widget->getLayerTable()->getCurrentLayer()->getPropertyData().getColor());

	ShCurrentColorChangedEvent event2(widget->getPropertyData().getColor());
	ShPropertyPanelCurrentColorChangedEventFilterStrategy strategy2(this->propertyPanel, &event2);
	strategy2.update();


	ShLineStyleComboBox *lineStyleCombo = this->propertyPanel->getLineStyleCombo();

	lineStyleCombo->setLayerLineStyle(widget->getLayerTable()->getCurrentLayer()->getPropertyData().getLineStyle());

	ShCurrentLineStyleChangedEvent event3(widget->getPropertyData().getLineStyle());
	ShPropertyPanelCurrentLineStyleChangedEventFilterStrategy strategy3(this->propertyPanel, &event3);
	strategy3.update();

	ShActionChangedEvent event4(widget->getCurrentActionType());
	ShPropertyPanelActionChangedEventFilterStrategy strategy4(this->propertyPanel, &event4);
	strategy4.update();

	ShSelectedEntityCountChangedEvent event5(widget, widget->getSelectedEntities()->getSelectedList());
	ShPropertyPanelSelectedEntityCountChangedEventFilterStrategy strategy5(this->propertyPanel, &event5);
	strategy5.update();
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

	if (lineStyle.getType() == ShLineStyle::Type::Invalid) {
	
		index = -1;
	}
	else if (lineStyle.getType() == ShLineStyle::Type::ByBlock) {
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

	this->propertyPanel->getLineStyleCombo()->setLayerLineStyle(event->getCurrentLayer()->getPropertyData().getLineStyle());
	this->propertyPanel->getLineStyleCombo()->updateLineStyleCombo();
	this->propertyPanel->getLineStyleCombo()->setLineStyleComboCurrentIndex(this->propertyPanel->getLineStyleCombo()->getLineStyleComboIndex());
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
	else if (event->getChangedType() == ShLayerDataChangedEvent::ChangedType::LineStyle) {
	
		this->propertyPanel->getLineStyleCombo()->setLayerLineStyle(*event->getLineStyle());
		this->propertyPanel->getLineStyleCombo()->updateLineStyleCombo();
		this->propertyPanel->getLineStyleCombo()->setLineStyleComboCurrentIndex(this->propertyPanel->getLineStyleCombo()->getLineStyleComboIndex());
	}

}

/////////////////////////////////////////////////////////////////////////////

ShPropertyPanelActionChangedEventFilterStrategy::ShPropertyPanelActionChangedEventFilterStrategy(ShPropertyPanel *propertyPanel, ShNotifyEvent *event)
	:ShPropertyPanelEventFilterStrategy(propertyPanel, event) {

}

ShPropertyPanelActionChangedEventFilterStrategy::~ShPropertyPanelActionChangedEventFilterStrategy() {

}

void ShPropertyPanelActionChangedEventFilterStrategy::update() {

	ShActionChangedEvent *event = dynamic_cast<ShActionChangedEvent*>(this->event);

	if (event->getNewType() == ActionType::ActionDefault) {
	
		this->propertyPanel->getColorCombo()->setDisabled(false);
		this->propertyPanel->getLineStyleCombo()->setDisabled(false);
		this->propertyPanel->getColorButton()->setDisabled(false);
	}
	else {
	
		this->propertyPanel->getColorCombo()->setDisabled(true);
		this->propertyPanel->getLineStyleCombo()->setDisabled(true);
		this->propertyPanel->getColorButton()->setDisabled(true);
	}

}

///////////////////////////////////////////////////////////////////////////////

ShPropertyPanelSelectedEntityCountChangedEventFilterStrategy::ShPropertyPanelSelectedEntityCountChangedEventFilterStrategy(ShPropertyPanel *propertyPanel, ShNotifyEvent *event)
	:ShPropertyPanelEventFilterStrategy(propertyPanel, event) {

}

ShPropertyPanelSelectedEntityCountChangedEventFilterStrategy::~ShPropertyPanelSelectedEntityCountChangedEventFilterStrategy() {

}

void ShPropertyPanelSelectedEntityCountChangedEventFilterStrategy::update() {

	ShSelectedEntityCountChangedEvent *event = dynamic_cast<ShSelectedEntityCountChangedEvent*>(this->event);

	////////////////
	ShColor color;

	if (event->getList().size() == 0) {

		color = event->getWidget()->getPropertyData().getColor();
	}
	else {


		auto itr = const_cast<QLinkedList<ShEntity*>&>(event->getList()).begin();
		color = (*itr)->getPropertyData().getColor();
		++itr;

		for (itr; itr != const_cast<QLinkedList<ShEntity*>&>(event->getList()).end(); ++itr) {

			if ((*itr)->getPropertyData().getColor() != color) {
				color.setType(ShColor::Type::Invalid);
				break;
			}
		}
	}

	ShCurrentColorChangedEvent event2(color);

	ShPropertyPanelCurrentColorChangedEventFilterStrategy strategy2(this->propertyPanel, &event2);
	strategy2.update();

	/////////////////

	ShLineStyle lineStyle;

	if (event->getList().size() == 0) {

		lineStyle = event->getWidget()->getPropertyData().getLineStyle();
	}
	else {


		auto itr = const_cast<QLinkedList<ShEntity*>&>(event->getList()).begin();
		lineStyle = (*itr)->getPropertyData().getLineStyle();
		++itr;

		for (itr; itr != const_cast<QLinkedList<ShEntity*>&>(event->getList()).end(); ++itr) {

			if ((*itr)->getPropertyData().getLineStyle() != lineStyle) {
				lineStyle.setType(ShLineStyle::Type::Invalid);
				break;
			}
		}
	}

	ShCurrentLineStyleChangedEvent event3(lineStyle);

	ShPropertyPanelCurrentLineStyleChangedEventFilterStrategy strategy3(this->propertyPanel, &event3);
	strategy3.update();
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
	else if (event->getType() == ShNotifyEvent::LayerCreated)
		this->strategy = new ShLayerPanelLayerCreatedEventFilterStrategy(layerPanel, event);
	else if (event->getType() == ShNotifyEvent::LayerDeleted)
		this->strategy = new ShLayerPanelLayerDeletedEventFilterStrategy(layerPanel, event);
	else if (event->getType() == ShNotifyEvent::ActionChanged)
		this->strategy = new ShLayerPanelActionChangedEventFilterStrategy(layerPanel, event);
	else if (event->getType() == ShNotifyEvent::SelectedEntityCountChanged)
		this->strategy = new ShLayerPanelSelectedEntityCountChangedEventFilterStrategy(layerPanel, event);

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

	ShActionChangedEvent event2(event->getNewWidget()->getCurrentActionType());
	ShLayerPanelActionChangedEventFilterStrategy strategy2(this->layerPanel, &event2);
	strategy2.update();

	ShSelectedEntityCountChangedEvent event3(event->getNewWidget(), event->getNewWidget()->getSelectedEntities()->getSelectedList());
	ShLayerPanelSelectedEntityCountChangedEventFilterStrategy strategy3(this->layerPanel, &event3);
	strategy3.update();
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

////////////////////////////////////////////////////////////////

ShLayerPanelLayerCreatedEventFilterStrategy::ShLayerPanelLayerCreatedEventFilterStrategy(ShLayerPanel *layerPanel, ShNotifyEvent *event)
	:ShLayerPanelEventFilterStrategy(layerPanel, event) {

}

ShLayerPanelLayerCreatedEventFilterStrategy::~ShLayerPanelLayerCreatedEventFilterStrategy() {

}

void ShLayerPanelLayerCreatedEventFilterStrategy::update() {

	this->layerPanel->getLayerCombo()->updateLayerCombo();
}

/////////////////////////////////////////////////////////////////

ShLayerPanelLayerDeletedEventFilterStrategy::ShLayerPanelLayerDeletedEventFilterStrategy(ShLayerPanel *layerPanel, ShNotifyEvent *event)
	:ShLayerPanelEventFilterStrategy(layerPanel, event) {

}

ShLayerPanelLayerDeletedEventFilterStrategy::~ShLayerPanelLayerDeletedEventFilterStrategy() {

}

void ShLayerPanelLayerDeletedEventFilterStrategy::update() {

	this->layerPanel->getLayerCombo()->updateLayerCombo();
}

//////////////////////////////////////////////////////////////////

ShLayerPanelActionChangedEventFilterStrategy::ShLayerPanelActionChangedEventFilterStrategy(ShLayerPanel *layerPanel, ShNotifyEvent *event)
	:ShLayerPanelEventFilterStrategy(layerPanel, event) {

}

ShLayerPanelActionChangedEventFilterStrategy::~ShLayerPanelActionChangedEventFilterStrategy() {

}

void ShLayerPanelActionChangedEventFilterStrategy::update() {

	ShActionChangedEvent *event = dynamic_cast<ShActionChangedEvent*>(this->event);

	if (event->getNewType() == ActionType::ActionDefault) 
		this->layerPanel->getLayerCombo()->setDisabled(false);
	else 
		this->layerPanel->getLayerCombo()->setDisabled(true);
	
}


////////////////////////////////////////////////////////////////////

ShLayerPanelSelectedEntityCountChangedEventFilterStrategy::ShLayerPanelSelectedEntityCountChangedEventFilterStrategy(ShLayerPanel *layerPanel, ShNotifyEvent *event)
	:ShLayerPanelEventFilterStrategy(layerPanel, event) {

}

ShLayerPanelSelectedEntityCountChangedEventFilterStrategy::~ShLayerPanelSelectedEntityCountChangedEventFilterStrategy() {

}

void ShLayerPanelSelectedEntityCountChangedEventFilterStrategy::update() {

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
	ShLayerPanelCurrentLayerChangedEventFilterStrategy strategy2(this->layerPanel, &event2);
	strategy2.update();
}
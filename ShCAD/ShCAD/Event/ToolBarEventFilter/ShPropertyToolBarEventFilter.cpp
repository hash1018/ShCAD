
#include "ShPropertyToolBarEventFilter.h"
#include "Interface\ToolBar\ShPropertyToolBar.h"
#include "Event\ShNotifyEvent.h"
#include "Interface\Item\ShColorComboBox.h"
#include "Interface\Item\ShLineStyleComboBox.h"
#include "Data\ShColorList.h"
#include "Data\ShLineStyleList.h"
#include "Interface\ShCADWidget.h"
#include "Base\ShLayerTable.h"
#include "Base\ShLayer.h"
#include "Entity\Composite\ShSelectedEntities.h"


ShPropertyToolBarEventFilter::ShPropertyToolBarEventFilter(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::CurrentColorChanged)
		this->strategy = new ShPropertyToolBarCurrentColorChangedEventFilterStrategy(propertyToolBar, event);
	else if (event->getType() == ShNotifyEvent::ActivatedWidgetChanged)
		this->strategy = new ShPropertyToolBarActivatedWidgetChangedEventFilterStrategy(propertyToolBar, event);
	else if (event->getType() == ShNotifyEvent::CurrentLineStyleChanged)
		this->strategy = new ShPropertyToolBarCurrentLineStyleChangedEventFilterStrategy(propertyToolBar, event);
	else if (event->getType() == ShNotifyEvent::CurrentLayerChanged)
		this->strategy = new ShPropertyToolBarCurrentLayerChangedEventFilterStrategy(propertyToolBar, event);
	else if (event->getType() == ShNotifyEvent::LayerDataChanged)
		this->strategy = new ShPropertyToolBarLayerDataChangedEventFilterStrategy(propertyToolBar, event);
	else if (event->getType() == ShNotifyEvent::ActionChanged)
		this->strategy = new ShPropertyToolBarActionChangedEventFilterStrategy(propertyToolBar, event);
	else if (event->getType() == ShNotifyEvent::SelectedEntityCountChanged)
		this->strategy = new ShPropertyToolBarSelectedEntityCountChangedEventFilterStrategy(propertyToolBar, event);

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

	if (color.getType() == ShColor::Type::Invalid) {

		index = -1;
	}

	else if (color.getType() == ShColor::Type::ByBlock) {
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
	colorCombo->setLayerColor(widget->getLayerTable()->getCurrentLayer()->getPropertyData().getColor());

	ShCurrentColorChangedEvent event2(widget->getPropertyData().getColor());
	ShPropertyToolBarCurrentColorChangedEventFilterStrategy strategy2(this->propertyToolBar, &event2);
	strategy2.update();



	ShLineStyleComboBox *lineStyleCombo = this->propertyToolBar->getLineStyleCombo();
	lineStyleCombo->setLayerLineStyle(widget->getLayerTable()->getCurrentLayer()->getPropertyData().getLineStyle());

	ShCurrentLineStyleChangedEvent event3(widget->getPropertyData().getLineStyle());
	ShPropertyToolBarCurrentLineStyleChangedEventFilterStrategy strategy3(this->propertyToolBar, &event3);
	strategy3.update();

	ShActionChangedEvent event4(widget->getCurrentActionType());
	ShPropertyToolBarActionChangedEventFilterStrategy strategy4(this->propertyToolBar, &event4);
	strategy4.update();


	ShSelectedEntityCountChangedEvent event5(widget, widget->getSelectedEntities()->getSelectedList());
	ShPropertyToolBarSelectedEntityCountChangedEventFilterStrategy strategy5(this->propertyToolBar, &event5);
	strategy5.update();
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

	if (lineStyle.getType() == ShLineStyle::Type::Invalid) {

		index = -1;
	}

	else if (lineStyle.getType() == ShLineStyle::Type::ByBlock) {
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

/////////////////////////////////////////////////////

ShPropertyToolBarCurrentLayerChangedEventFilterStrategy::ShPropertyToolBarCurrentLayerChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event)
	:ShPropertyToolBarEventFilterStrategy(propertyToolBar, event) {

}

ShPropertyToolBarCurrentLayerChangedEventFilterStrategy::~ShPropertyToolBarCurrentLayerChangedEventFilterStrategy() {

}

void ShPropertyToolBarCurrentLayerChangedEventFilterStrategy::update() {

	ShCurrentLayerChangedEvent *event = dynamic_cast<ShCurrentLayerChangedEvent*>(this->event);

	this->propertyToolBar->getColorCombo()->setLayerColor(event->getCurrentLayer()->getPropertyData().getColor());
	this->propertyToolBar->getColorCombo()->updateColorCombo();
	this->propertyToolBar->getColorCombo()->setColorComboCurrentIndex(this->propertyToolBar->getColorCombo()->getColorComboIndex());

	this->propertyToolBar->getLineStyleCombo()->setLayerLineStyle(event->getCurrentLayer()->getPropertyData().getLineStyle());
	this->propertyToolBar->getLineStyleCombo()->updateLineStyleCombo();
	this->propertyToolBar->getLineStyleCombo()->setLineStyleComboCurrentIndex(this->propertyToolBar->getLineStyleCombo()->getLineStyleComboIndex());

}

////////////////////////////////////////////////////////////////////

ShPropertyToolBarLayerDataChangedEventFilterStrategy::ShPropertyToolBarLayerDataChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event)
	:ShPropertyToolBarEventFilterStrategy(propertyToolBar, event) {

}

ShPropertyToolBarLayerDataChangedEventFilterStrategy::~ShPropertyToolBarLayerDataChangedEventFilterStrategy() {

}


void ShPropertyToolBarLayerDataChangedEventFilterStrategy::update() {

	ShLayerDataChangedEvent *event = dynamic_cast<ShLayerDataChangedEvent*>(this->event);

	if (event->isCurrent() == false)
		return;

	if (event->getChangedType() == ShLayerDataChangedEvent::ChangedType::Color) {

		this->propertyToolBar->getColorCombo()->setLayerColor(*event->getColor());
		this->propertyToolBar->getColorCombo()->updateColorCombo();
		this->propertyToolBar->getColorCombo()->setColorComboCurrentIndex(this->propertyToolBar->getColorCombo()->getColorComboIndex());
	}
	else if (event->getChangedType() == ShLayerDataChangedEvent::ChangedType::LineStyle) {

		this->propertyToolBar->getLineStyleCombo()->setLayerLineStyle(*event->getLineStyle());
		this->propertyToolBar->getLineStyleCombo()->updateLineStyleCombo();
		this->propertyToolBar->getLineStyleCombo()->setLineStyleComboCurrentIndex(this->propertyToolBar->getLineStyleCombo()->getLineStyleComboIndex());
	}

}

////////////////////////////////////////////////////////////////////////

ShPropertyToolBarActionChangedEventFilterStrategy::ShPropertyToolBarActionChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event)
	:ShPropertyToolBarEventFilterStrategy(propertyToolBar, event) {

}

ShPropertyToolBarActionChangedEventFilterStrategy::~ShPropertyToolBarActionChangedEventFilterStrategy() {

}

void ShPropertyToolBarActionChangedEventFilterStrategy::update() {

	ShActionChangedEvent *event = dynamic_cast<ShActionChangedEvent*>(this->event);

	if (event->getNewType() == ActionType::ActionDefault) {

		this->propertyToolBar->getColorCombo()->setDisabled(false);
		this->propertyToolBar->getLineStyleCombo()->setDisabled(false);
	}
	else {

		this->propertyToolBar->getColorCombo()->setDisabled(true);
		this->propertyToolBar->getLineStyleCombo()->setDisabled(true);
	}
}

/////////////////////////////////////////////////////////////////////////

ShPropertyToolBarSelectedEntityCountChangedEventFilterStrategy::ShPropertyToolBarSelectedEntityCountChangedEventFilterStrategy(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event)
	:ShPropertyToolBarEventFilterStrategy(propertyToolBar, event) {

}

ShPropertyToolBarSelectedEntityCountChangedEventFilterStrategy::~ShPropertyToolBarSelectedEntityCountChangedEventFilterStrategy() {

}

void ShPropertyToolBarSelectedEntityCountChangedEventFilterStrategy::update() {

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

			if (color != (*itr)->getPropertyData().getColor()) {
				color.setType(ShColor::Type::Invalid);
				break;
			}
		}
	}

	ShCurrentColorChangedEvent event2(color);

	ShPropertyToolBarCurrentColorChangedEventFilterStrategy strategy2(this->propertyToolBar, &event2);
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

			if (lineStyle != (*itr)->getPropertyData().getLineStyle()) {
				lineStyle.setType(ShLineStyle::Type::Invalid);
				break;
			}
		}
	}

	ShCurrentLineStyleChangedEvent event3(lineStyle);

	ShPropertyToolBarCurrentLineStyleChangedEventFilterStrategy strategy3(this->propertyToolBar, &event3);
	strategy3.update();

}
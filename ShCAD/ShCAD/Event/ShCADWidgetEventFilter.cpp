
#include "ShCADWidgetEventFilter.h"
#include "Event\ShNotifyEvent.h"
#include "Interface\ShCADWidget.h"
#include "ActionHandler\ShActionHandlerProxy.h"
#include "UnRedo\ShCADWidgetTransaction.h"
#include "Base\ShGlobal.h"
#include "Base\ShLayer.h"
#include "Base\ShLayerTable.h"
#include "UnRedo\ShLayerTransaction.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "UnRedo\ShEntityTransaction.h"

ShCADWidgetEventFilter::ShCADWidgetEventFilter(ShCADWidget *widget, ShNotifyEvent *event)
	:strategy(nullptr) {

	if (event->getType() == ShNotifyEvent::KeyPressed)
		this->strategy = new ShCADWidgetKeyPressedEventFilterStrategy(widget, event);
	else if (event->getType() == ShNotifyEvent::CurrentColorChanged)
		this->strategy = new ShCADWidgetCurrentColorChangedEventFilterStrategy(widget, event);
	else if (event->getType() == ShNotifyEvent::CurrentLineStyleChanged)
		this->strategy = new ShCADWidgetCurrentLineStyleChangedEventFilterStrategy(widget, event);
	else if (event->getType() == ShNotifyEvent::CurrentLayerChanged)
		this->strategy = new ShCADWidgetCurrentLayerChangedEventFilterStrategy(widget, event);
	else if (event->getType() == ShNotifyEvent::LayerDataChanged)
		this->strategy = new ShCADWidgetLayerDataChangedEventFilterStrategy(widget, event);
	else if (event->getType() == ShNotifyEvent::LayerCreated)
		this->strategy = new ShCADWidgetLayerCreatedEventFilterStrategy(widget, event);
	else if (event->getType() == ShNotifyEvent::LayerDeleted)
		this->strategy = new ShCADWidgetLayerDeletedEventFilterStrategy(widget, event);

}

ShCADWidgetEventFilter::~ShCADWidgetEventFilter() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShCADWidgetEventFilter::update() {

	if (this->strategy != nullptr)
		this->strategy->update();
}


////////////////////////////////////////////////////////////////////


ShCADWidgetEventFilterStrategy::ShCADWidgetEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event)
	:widget(widget), event(event) {

}

ShCADWidgetEventFilterStrategy::~ShCADWidgetEventFilterStrategy() {

}

////////////////////////////////////////////////////////////////////

ShCADWidgetKeyPressedEventFilterStrategy::ShCADWidgetKeyPressedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event)
	:ShCADWidgetEventFilterStrategy(widget, event) {

}

ShCADWidgetKeyPressedEventFilterStrategy::~ShCADWidgetKeyPressedEventFilterStrategy() {

}

void ShCADWidgetKeyPressedEventFilterStrategy::update() {

	ShKeyPressedEvent *event = dynamic_cast<ShKeyPressedEvent*>(this->event);

	this->widget->getActionHandlerProxy()->keyPressEvent(event->getEvent());
}

/////////////////////////////////////////////////////////////////////

ShCADWidgetCurrentColorChangedEventFilterStrategy::ShCADWidgetCurrentColorChangedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event)
	:ShCADWidgetEventFilterStrategy(widget, event) {

}

ShCADWidgetCurrentColorChangedEventFilterStrategy::~ShCADWidgetCurrentColorChangedEventFilterStrategy() {

}

void ShCADWidgetCurrentColorChangedEventFilterStrategy::update() {

	ShCurrentColorChangedEvent *event = dynamic_cast<ShCurrentColorChangedEvent*>(this->event);

	if (this->widget->getSelectedEntities()->getSize() == 0) {

		ShPropertyData prev = this->widget->getPropertyData();
		ShPropertyData current = prev;
		current.setColor(event->getColor());
		this->widget->setPropertyData(current);

		ShChangeColorTransaction *transaction = new ShChangeColorTransaction(this->widget, prev.getColor(), event->getColor());
		ShGlobal::pushNewTransaction(this->widget, transaction);
	}
	else {
	
		auto itr = this->widget->getSelectedEntities()->begin();
		ShPropertyData prev, current;

		ShChangeEntityPropertyDataTransaction *transaction = new ShChangeEntityPropertyDataTransaction(this->widget);

		for (itr; itr != this->widget->getSelectedEntities()->end(); ++itr) {
		
			prev = (*itr)->getPropertyData();
			current = prev;
			current.setColor(event->getColor());
			(*itr)->setPropertyData(current);

			transaction->add((*itr), prev, current);
		}

		ShGlobal::pushNewTransaction(this->widget, transaction);
	}

	ShCurrentColorChangedEvent notifyEvent(event->getColor());
	this->widget->notify(&notifyEvent);
	
}

///////////////////////////////////////////////////////////////////////

ShCADWidgetCurrentLineStyleChangedEventFilterStrategy::ShCADWidgetCurrentLineStyleChangedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event)
	:ShCADWidgetEventFilterStrategy(widget, event) {

}

ShCADWidgetCurrentLineStyleChangedEventFilterStrategy::~ShCADWidgetCurrentLineStyleChangedEventFilterStrategy() {

}

void ShCADWidgetCurrentLineStyleChangedEventFilterStrategy::update() {

	ShCurrentLineStyleChangedEvent *event = dynamic_cast<ShCurrentLineStyleChangedEvent*>(this->event);

	if (this->widget->getSelectedEntities()->getSize() == 0) {
		ShPropertyData prev = this->widget->getPropertyData();
		ShPropertyData current = prev;
		current.setLineStyle(event->getLineStyle());
		this->widget->setPropertyData(current);

		ShChangeLineStyleTransaction *transaction = new ShChangeLineStyleTransaction(this->widget, prev.getLineStyle(), event->getLineStyle());
		ShGlobal::pushNewTransaction(this->widget, transaction);
	}
	else {

		auto itr = this->widget->getSelectedEntities()->begin();
		ShPropertyData prev, current;

		ShChangeEntityPropertyDataTransaction *transaction = new ShChangeEntityPropertyDataTransaction(this->widget);

		for (itr; itr != this->widget->getSelectedEntities()->end(); ++itr) {

			prev = (*itr)->getPropertyData();
			current = prev;
			current.setLineStyle(event->getLineStyle());
			(*itr)->setPropertyData(current);

			transaction->add((*itr), prev, current);
		}

		ShGlobal::pushNewTransaction(this->widget, transaction);
	}

	ShCurrentLineStyleChangedEvent notifyEvent(event->getLineStyle());
	this->widget->notify(&notifyEvent);
}

///////////////////////////////////////////////////////////////////

ShCADWidgetCurrentLayerChangedEventFilterStrategy::ShCADWidgetCurrentLayerChangedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event)
	:ShCADWidgetEventFilterStrategy(widget, event) {

}

ShCADWidgetCurrentLayerChangedEventFilterStrategy::~ShCADWidgetCurrentLayerChangedEventFilterStrategy() {

}

void ShCADWidgetCurrentLayerChangedEventFilterStrategy::update() {

	ShCurrentLayerChangedEvent *event = dynamic_cast<ShCurrentLayerChangedEvent*>(this->event);

	ShLayer *prev = this->widget->getLayerTable()->getCurrentLayer();

	if (prev == event->getCurrentLayer())
		return;

	this->widget->getLayerTable()->setCurrentLayer(event->getCurrentLayer());

	ShPropertyData propertyData = this->widget->getPropertyData();

	if (propertyData.getColor().getType() == ShColor::Type::ByLayer)
		propertyData.setColor(event->getCurrentLayer()->getPropertyData().getColor());
	
	if (propertyData.getLineStyle().getType() == ShLineStyle::Type::ByLayer)
		propertyData.setLineStyle(event->getCurrentLayer()->getPropertyData().getLineStyle());

	this->widget->setPropertyData(propertyData);

	this->widget->notify(this->event);
	

	ShGlobal::pushNewTransaction(this->widget, new ShChangeCurrentLayerTransaction(this->widget, prev, event->getCurrentLayer()));

}

////////////////////////////////////////////////////////////////////

ShCADWidgetLayerDataChangedEventFilterStrategy::ShCADWidgetLayerDataChangedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event)
	:ShCADWidgetEventFilterStrategy(widget, event) {

}

ShCADWidgetLayerDataChangedEventFilterStrategy::~ShCADWidgetLayerDataChangedEventFilterStrategy() {

}


void ShCADWidgetLayerDataChangedEventFilterStrategy::update() {

	ShLayerDataChangedEvent *event = dynamic_cast<ShLayerDataChangedEvent*>(this->event);

	if (event->getChangedType() == ShLayerDataChangedEvent::ChangedType::Color)
		this->changeLayerColor();
	else if (event->getChangedType() == ShLayerDataChangedEvent::ChangedType::LineStyle)
		this->changeLayerLineStyle();
	else if (event->getChangedType() == ShLayerDataChangedEvent::ChangedType::Name)
		this->changeLayerName();
	else if (event->getChangedType() == ShLayerDataChangedEvent::ChangedType::Turn)
		this->changeLayerTurn();
		
}

void ShCADWidgetLayerDataChangedEventFilterStrategy::changeLayerColor() {

	ShLayerDataChangedEvent *event = dynamic_cast<ShLayerDataChangedEvent*>(this->event);

	ShPropertyData prev = event->getLayer()->getPropertyData();
	ShPropertyData current = prev;

	current.setColor(*event->getColor());
	event->getLayer()->setPropertyData(current);

	if (event->getLayer() == this->widget->getLayerTable()->getCurrentLayer()) {

		if (this->widget->getPropertyData().getColor().getType() == ShColor::Type::ByLayer) {

			ShPropertyData temp = this->widget->getPropertyData();
			temp.setColor(*event->getColor());
			this->widget->setPropertyData(temp);
		}

		ShLayerDataChangedEvent notifyEvent(event->getLayer(), *event->getColor(), true);
		this->widget->notify(&notifyEvent);

	}
	else {

		ShLayerDataChangedEvent notifyEvent(event->getLayer(), *event->getColor());
		this->widget->notify(&notifyEvent);
	}

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();

	ShChangeLayerDataTransaction *transaction = new ShChangeLayerDataTransaction(this->widget, event->getLayer(),
		prev, current, ShChangeLayerDataTransaction::ChangedType::Color);
	ShGlobal::pushNewTransaction(this->widget, transaction);
}

void ShCADWidgetLayerDataChangedEventFilterStrategy::changeLayerLineStyle() {

	ShLayerDataChangedEvent *event = dynamic_cast<ShLayerDataChangedEvent*>(this->event);

	ShPropertyData prev = event->getLayer()->getPropertyData();
	ShPropertyData current = prev;

	current.setLineStyle(*event->getLineStyle());
	event->getLayer()->setPropertyData(current);

	if (event->getLayer() == this->widget->getLayerTable()->getCurrentLayer()) {

		if (this->widget->getPropertyData().getLineStyle().getType() == ShLineStyle::Type::ByLayer) {

			ShPropertyData temp = this->widget->getPropertyData();
			temp.setLineStyle(*event->getLineStyle());
			this->widget->setPropertyData(temp);
		}

		ShLayerDataChangedEvent notifyEvent(event->getLayer(), *event->getLineStyle(), true);
		this->widget->notify(&notifyEvent);
	}
	else {
		ShLayerDataChangedEvent notifyEvent(event->getLayer(), *event->getLineStyle());
		this->widget->notify(&notifyEvent);
	}

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();

	ShChangeLayerDataTransaction *transaction = new ShChangeLayerDataTransaction(this->widget, event->getLayer(),
		prev, current, ShChangeLayerDataTransaction::ChangedType::LineStyle);
	ShGlobal::pushNewTransaction(this->widget, transaction);
}

void ShCADWidgetLayerDataChangedEventFilterStrategy::changeLayerName() {

	ShLayerDataChangedEvent *event = dynamic_cast<ShLayerDataChangedEvent*>(this->event);

	QString prev = event->getLayer()->getName();

	event->getLayer()->setName(*event->getName());

	this->widget->notify(event);

	ShChangeLayerDataTransaction *transaction = new ShChangeLayerDataTransaction(this->widget, event->getLayer(),
		prev, *event->getName());
	ShGlobal::pushNewTransaction(this->widget, transaction);
}

void ShCADWidgetLayerDataChangedEventFilterStrategy::changeLayerTurn() {

	ShLayerDataChangedEvent *event = dynamic_cast<ShLayerDataChangedEvent*>(this->event);

	bool prev = event->getLayer()->isTurnOn();
	

	if (event->getTurn() == true) {
		
		this->widget->getSelectedEntities()->unSelectAll();

		event->getLayer()->turnOnOff(true);

		this->widget->getLayerTable()->updateTurnOnLayerList();
		this->widget->getLayerTable()->setJustTurnOnLayer(event->getLayer());

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawJustTurnOnLayer));
		this->widget->captureImage();
	}
	else {
	
		this->widget->getSelectedEntities()->unSelectAll();

		event->getLayer()->turnOnOff(false);
		this->widget->getLayerTable()->updateTurnOnLayerList();

		this->widget->update(DrawType::DrawAll);
		this->widget->captureImage();
	}

	this->widget->notify(event);

	ShChangeLayerDataTransaction *transaction = new ShChangeLayerDataTransaction(this->widget, event->getLayer(),
		prev, event->getTurn());
	ShGlobal::pushNewTransaction(this->widget, transaction);

}

/////////////////////////////////////////////////////////////////////////////////

ShCADWidgetLayerCreatedEventFilterStrategy::ShCADWidgetLayerCreatedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event)
	:ShCADWidgetEventFilterStrategy(widget, event) {

}

ShCADWidgetLayerCreatedEventFilterStrategy::~ShCADWidgetLayerCreatedEventFilterStrategy() {

}

void ShCADWidgetLayerCreatedEventFilterStrategy::update() {

	ShLayerCreatedEvent *event = dynamic_cast<ShLayerCreatedEvent*>(this->event);

	this->widget->getLayerTable()->add(event->getCreatedLayer());

	this->widget->notify(event);

	ShCreateLayerTransaction *transaction = new ShCreateLayerTransaction(this->widget, event->getCreatedLayer());
	ShGlobal::pushNewTransaction(this->widget, transaction);
}

//////////////////////////////////////////////////////////////////////////////////

ShCADWidgetLayerDeletedEventFilterStrategy::ShCADWidgetLayerDeletedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event)
	:ShCADWidgetEventFilterStrategy(widget, event) {

}

ShCADWidgetLayerDeletedEventFilterStrategy::~ShCADWidgetLayerDeletedEventFilterStrategy() {

}

void ShCADWidgetLayerDeletedEventFilterStrategy::update() {

	ShLayerDeletedEvent *event = dynamic_cast<ShLayerDeletedEvent*>(this->event);

	this->widget->getLayerTable()->remove(event->getDeletedLayer());

	this->widget->notify(event);

	ShDeleteLayerTransaction *transaction = new ShDeleteLayerTransaction(this->widget, event->getDeletedLayer());
	ShGlobal::pushNewTransaction(this->widget, transaction);
}

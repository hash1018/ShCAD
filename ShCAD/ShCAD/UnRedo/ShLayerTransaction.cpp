
#include "ShLayerTransaction.h"
#include "Interface\ShCADWidget.h"
#include "Base\ShLayer.h"
#include "Base\ShLayerTable.h"
#include "Event\ShNotifyEvent.h"

ShChangeCurrentLayerTransaction::ShChangeCurrentLayerTransaction(ShCADWidget *widget, ShLayer *prev, ShLayer *current)
	:ShTransaction("Layer control"), widget(widget), prev(prev), current(current) {

}

ShChangeCurrentLayerTransaction::~ShChangeCurrentLayerTransaction() {

}

void ShChangeCurrentLayerTransaction::redo() {

	this->widget->getLayerTable()->setCurrentLayer(this->current);

	ShPropertyData propertyData = this->widget->getPropertyData();

	if (propertyData.getColor().getType() == ShColor::Type::ByLayer)
		propertyData.setColor(this->current->getPropertyData().getColor());

	if (propertyData.getLineStyle().getType() == ShLineStyle::Type::ByLayer)
		propertyData.setLineStyle(this->current->getPropertyData().getLineStyle());

	this->widget->setPropertyData(propertyData);

	ShCurrentLayerChangedEvent event(this->current);
	this->widget->notify(&event);
}

void ShChangeCurrentLayerTransaction::undo() {

	this->widget->getLayerTable()->setCurrentLayer(this->prev);

	ShPropertyData propertyData = this->widget->getPropertyData();

	if (propertyData.getColor().getType() == ShColor::Type::ByLayer)
		propertyData.setColor(this->prev->getPropertyData().getColor());

	if (propertyData.getLineStyle().getType() == ShLineStyle::Type::ByLayer)
		propertyData.setLineStyle(this->prev->getPropertyData().getLineStyle());

	this->widget->setPropertyData(propertyData);

	ShCurrentLayerChangedEvent event(this->prev);
	this->widget->notify(&event);
}


//////////////////////////////////////////////////////////////////////

ShChangeLayerDataTransaction::ShChangeLayerDataTransaction(ShCADWidget *widget, ShLayer *layer, const ShPropertyData &prev, const ShPropertyData &current, ChangedType changedType)
	: ShTransaction("Layer control"), widget(widget), layer(layer), prev(prev), current(current), changedType(changedType) {

}

ShChangeLayerDataTransaction::ShChangeLayerDataTransaction(ShCADWidget *widget, ShLayer *layer, const QString &prev, const QString &current)
	: ShTransaction("Layer control"), widget(widget), layer(layer), prevName(prev), currentName(current), changedType(ChangedType::Name) {

}

ShChangeLayerDataTransaction::~ShChangeLayerDataTransaction() {

}

void ShChangeLayerDataTransaction::redo() {

	if (this->changedType == ChangedType::Color)
		this->changeLayerColor(this->current);
	else if (this->changedType == ChangedType::LineStyle)
		this->changeLayerLineStyle(this->current);
	else if (this->changedType == ChangedType::Name)
		this->changeLayerName(this->currentName);

}

void ShChangeLayerDataTransaction::undo() {
	
	if (this->changedType == ChangedType::Color)
		this->changeLayerColor(this->prev);
	else if (this->changedType == ChangedType::LineStyle)
		this->changeLayerLineStyle(this->prev);
	else if (this->changedType == ChangedType::Name)
		this->changeLayerName(this->prevName);
	
}


void ShChangeLayerDataTransaction::changeLayerColor(const ShPropertyData &aboutToChange) {

	this->layer->setPropertyData(aboutToChange);

	if (this->layer == this->widget->getLayerTable()->getCurrentLayer()) {
	
		if (this->widget->getPropertyData().getColor().getType() == ShColor::ByLayer) {
			ShPropertyData temp = this->widget->getPropertyData();
			temp.setColor(aboutToChange.getColor());
			this->widget->setPropertyData(temp);
		}

		ShLayerDataChangedEvent event(this->layer, aboutToChange.getColor(), true);
		this->widget->notify(&event);
	}
	else {

		ShLayerDataChangedEvent event(this->layer, aboutToChange.getColor());
		this->widget->notify(&event);
	}

}

void ShChangeLayerDataTransaction::changeLayerLineStyle(const ShPropertyData &aboutToChange) {

	this->layer->setPropertyData(aboutToChange);

	if (this->layer == this->widget->getLayerTable()->getCurrentLayer()) {
	
		if (this->widget->getPropertyData().getLineStyle().getType() == ShLineStyle::ByLayer) {
			ShPropertyData temp = this->widget->getPropertyData();
			temp.setLineStyle(aboutToChange.getLineStyle());
			this->widget->setPropertyData(temp);
		}

		ShLayerDataChangedEvent event(this->layer, aboutToChange.getLineStyle(), true);
		this->widget->notify(&event);
	}
	else {
	
		ShLayerDataChangedEvent event(this->layer, aboutToChange.getLineStyle());
		this->widget->notify(&event);
	}
}

void ShChangeLayerDataTransaction::changeLayerName(const QString &aboutToChange) {

	this->layer->setName(aboutToChange);

	ShLayerDataChangedEvent event(this->layer, aboutToChange);
	this->widget->notify(&event);
	
}

////////////////////////////////////////////////////////////////////

ShCreateLayerTransaction::ShCreateLayerTransaction(ShCADWidget *widget, ShLayer *layer)
	:ShTransaction("Layer control"), widget(widget), layer(layer), mustDeleteLayer(false) {

}

ShCreateLayerTransaction::~ShCreateLayerTransaction() {

	if (this->mustDeleteLayer == true)
		delete this->layer;
}

void ShCreateLayerTransaction::redo() {

	this->widget->getLayerTable()->add(this->layer);
	this->mustDeleteLayer = false;

	ShLayerCreatedEvent event(this->layer);
	this->widget->notify(&event);
}

void ShCreateLayerTransaction::undo() {

	this->widget->getLayerTable()->remove(this->layer);
	this->mustDeleteLayer = true;

	ShLayerDeletedEvent event(this->layer);
	this->widget->notify(&event);

}

////////////////////////////////////////////////////////////////////////////

ShDeleteLayerTransaction::ShDeleteLayerTransaction(ShCADWidget *widget, ShLayer *layer)
	:ShTransaction("Layer control"), widget(widget), layer(layer), mustDeleteLayer(true) {

}

ShDeleteLayerTransaction::~ShDeleteLayerTransaction() {

	if (this->mustDeleteLayer == true)
		delete this->layer;
}

void ShDeleteLayerTransaction::redo() {

	this->widget->getLayerTable()->remove(this->layer);
	this->mustDeleteLayer = true;

	ShLayerDeletedEvent event(this->layer);
	this->widget->notify(&event);
}

void ShDeleteLayerTransaction::undo() {

	this->widget->getLayerTable()->add(this->layer);
	this->mustDeleteLayer = false;

	ShLayerCreatedEvent event(this->layer);
	this->widget->notify(&event);
}
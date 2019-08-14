
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
	:ShTransaction("Layer control"), widget(widget), layer(layer), prev(prev), current(current), changedType(changedType) {

}

ShChangeLayerDataTransaction::~ShChangeLayerDataTransaction() {

}

void ShChangeLayerDataTransaction::redo() {

	this->layer->setPropertyData(this->current);

	if (this->layer == this->widget->getLayerTable()->getCurrentLayer()) {
	
		if (this->changedType == ChangedType::Color) {
		
			if (this->widget->getPropertyData().getColor().getType() == ShColor::ByLayer) {
				ShPropertyData temp = this->widget->getPropertyData();
				temp.setColor(this->current.getColor());
				this->widget->setPropertyData(temp);
			}

			ShLayerDataChangedEvent event(this->layer, this->current.getColor(), true);
			this->widget->notify(&event);
		}
		else if (this->changedType == ChangedType::LineStyle) {
			
			if (this->widget->getPropertyData().getLineStyle().getType() == ShLineStyle::ByLayer) {
				ShPropertyData temp = this->widget->getPropertyData();
				temp.setLineStyle(this->current.getLineStyle());
				this->widget->setPropertyData(temp);
			}

			ShLayerDataChangedEvent event(this->layer, this->current.getLineStyle(), true);
			this->widget->notify(&event);
		}
	}
	else {
	
		if (this->changedType == ChangedType::Color) {
		
			ShLayerDataChangedEvent event(this->layer, this->current.getColor());
			this->widget->notify(&event);
		}
		else if (this->changedType == ChangedType::LineStyle) {
	
			ShLayerDataChangedEvent event(this->layer, this->current.getLineStyle());
			this->widget->notify(&event);
		}
	}
}

void ShChangeLayerDataTransaction::undo() {

	this->layer->setPropertyData(this->prev);

	if (this->layer == this->widget->getLayerTable()->getCurrentLayer()) {

		if (this->changedType == ChangedType::Color) {

			if (this->widget->getPropertyData().getColor().getType() == ShColor::ByLayer) {
				ShPropertyData temp = this->widget->getPropertyData();
				temp.setColor(this->prev.getColor());
				this->widget->setPropertyData(temp);
			}

			ShLayerDataChangedEvent event(this->layer, this->prev.getColor(), true);
			this->widget->notify(&event);
		}
		else if (this->changedType == ChangedType::LineStyle) {

			if (this->widget->getPropertyData().getLineStyle().getType() == ShLineStyle::ByLayer) {
				ShPropertyData temp = this->widget->getPropertyData();
				temp.setLineStyle(this->prev.getLineStyle());
				this->widget->setPropertyData(temp);
			}
			
			ShLayerDataChangedEvent event(this->layer, this->prev.getLineStyle(), true);
			this->widget->notify(&event);
		}
	}
	else {

		if (this->changedType == ChangedType::Color) {

			ShLayerDataChangedEvent event(this->layer, this->prev.getColor());
			this->widget->notify(&event);
		}
		else if (this->changedType == ChangedType::LineStyle) {

			ShLayerDataChangedEvent event(this->layer, this->prev.getLineStyle());
			this->widget->notify(&event);
		}
	}
}

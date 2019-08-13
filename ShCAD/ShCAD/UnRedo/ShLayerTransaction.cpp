
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

	ShCurrentLayerChangedEvent event(this->prev);
	this->widget->notify(&event);
}
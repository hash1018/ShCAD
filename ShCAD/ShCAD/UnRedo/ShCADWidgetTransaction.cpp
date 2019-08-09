
#include "ShCADWidgetTransaction.h"
#include "Interface\ShCADWidget.h"
#include "Event\ShNotifyEvent.h"

ShChangeColorTransaction::ShChangeColorTransaction(ShCADWidget *widget, const ShColor &prev, const ShColor &current)
	:ShTransaction("Color control"), widget(widget), prev(prev), current(current) {

}

ShChangeColorTransaction::~ShChangeColorTransaction() {

}

void ShChangeColorTransaction::redo() {

	ShPropertyData prev = this->widget->getPropertyData();
	ShPropertyData current = prev;
	current.setColor(this->current);
	this->widget->setPropertyData(current);

	ShCurrentColorChangedEvent notifyEvent(this->current);
	this->widget->notify(&notifyEvent);
}

void ShChangeColorTransaction::undo() {

	ShPropertyData prev = this->widget->getPropertyData();
	ShPropertyData current = prev;
	current.setColor(this->prev);
	this->widget->setPropertyData(current);

	ShCurrentColorChangedEvent notifyEvent(this->prev);
	this->widget->notify(&notifyEvent);
}

#include "ShDimensionStyleTransaction.h"
#include "Interface\ShCADWidget.h"
#include "Base\ShDimensionStyle.h"
#include "Base\ShDimensionStyleTable.h"
#include "Event\ShNotifyEvent.h"

ShChangeCurrentDimensionStyleTransaction::ShChangeCurrentDimensionStyleTransaction(ShCADWidget *widget, ShDimensionStyle *prev, ShDimensionStyle *current)
	:ShTransaction("Dimension control"), widget(widget), prev(prev), current(current) {

}

ShChangeCurrentDimensionStyleTransaction::~ShChangeCurrentDimensionStyleTransaction() {

}

void ShChangeCurrentDimensionStyleTransaction::redo() {

	this->widget->getDimensionStyleTable()->setCurrentStyle(this->current);

	ShCurrentDimensionStyleChangedEvent event(this->current);
	this->widget->notify(&event);
}

void ShChangeCurrentDimensionStyleTransaction::undo() {

	this->widget->getDimensionStyleTable()->setCurrentStyle(this->prev);

	ShCurrentDimensionStyleChangedEvent event(this->prev);
	this->widget->notify(&event);
}
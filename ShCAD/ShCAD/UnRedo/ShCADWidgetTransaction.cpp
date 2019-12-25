
#include "ShCADWidgetTransaction.h"
#include "Interface\ShCADWidget.h"
#include "Event\ShNotifyEvent.h"
#include "Data\ShPropertyData.h"
#include "Entity\Private\Algorithm\ShMover.h"
#include "Interface\Private\ShAxis.h"
#include "Entity\Composite\ShEntityTable.h"

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

///////////////////////////////////////////////////////////////////////

ShChangeLineStyleTransaction::ShChangeLineStyleTransaction(ShCADWidget *widget, const ShLineStyle &prev, const ShLineStyle &current)
	:ShTransaction("LineStyle control"), widget(widget), prev(prev), current(current) {

}

ShChangeLineStyleTransaction::~ShChangeLineStyleTransaction() {

}

void ShChangeLineStyleTransaction::redo() {

	ShPropertyData prev = this->widget->getPropertyData();
	ShPropertyData current = prev;
	current.setLineStyle(this->current);
	this->widget->setPropertyData(current);

	ShCurrentLineStyleChangedEvent notifyEvent(this->current);
	this->widget->notify(&notifyEvent);
}

void ShChangeLineStyleTransaction::undo() {

	ShPropertyData prev = this->widget->getPropertyData();
	ShPropertyData current = prev;
	current.setLineStyle(this->prev);
	this->widget->setPropertyData(current);

	ShCurrentLineStyleChangedEvent notifyEvent(this->prev);
	this->widget->notify(&notifyEvent);
}

////////////////////////////////////////////////////////////////////////

ShChangeAxisPositionTransaction::ShChangeAxisPositionTransaction(ShCADWidget *widget, const ShPoint3d &prevCenter, const ShPoint3d &currentCenter)
	:ShTransaction("Axis Control"), widget(widget), prevCenter(prevCenter), currentCenter(currentCenter) {

}

ShChangeAxisPositionTransaction::~ShChangeAxisPositionTransaction() {

}

void ShChangeAxisPositionTransaction::redo() {

	this->widget->getAxis().setCenter(this->currentCenter);

	ShMoverByAxis visitor(this->widget->getScrollPosition(), this->prevCenter, this->currentCenter, this->widget->getZoomRate());

	auto itr = this->widget->getEntityTable().begin();

	for (itr; itr != this->widget->getEntityTable().end(); ++itr)
		(*itr)->accept(&visitor);


	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

void ShChangeAxisPositionTransaction::undo() {

	this->widget->getAxis().setCenter(this->prevCenter);

	ShMoverByAxis visitor(this->widget->getScrollPosition(), this->currentCenter, this->prevCenter, this->widget->getZoomRate());

	auto itr = this->widget->getEntityTable().begin();

	for (itr; itr != this->widget->getEntityTable().end(); ++itr)
		(*itr)->accept(&visitor);


	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

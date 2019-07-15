
#include "ShPanTransaction.h"
#include "Interface\ShCADWidget.h"

ShPanTransaction::ShPanTransaction(ShCADWidget *widget, const ShPoint3d &coordinate, int dx, int dy)
	:ShTransaction("Pan"), widget(widget), coordinate(coordinate), dx(dx), dy(dy) {

}

ShPanTransaction::~ShPanTransaction() {

}

void ShPanTransaction::undo() {

	ShPoint3d coordinate = this->widget->getCoordinate();
	int dx, dy;
	this->widget->convertEntityToDevice(coordinate.x, coordinate.y, dx, dy);
	
	this->widget->shiftViewport(this->coordinate, this->dx, this->dy);

	this->coordinate = coordinate;
	this->dx = dx;
	this->dy = dy;
}

void ShPanTransaction::redo() {

	ShPoint3d coordinate = this->widget->getCoordinate();
	int dx, dy;
	this->widget->convertEntityToDevice(coordinate.x, coordinate.y, dx, dy);

	this->widget->shiftViewport(this->coordinate, this->dx, this->dy);

	this->coordinate = coordinate;
	this->dx = dx;
	this->dy = dy;
}
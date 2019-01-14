

#include "ShMoveViewCommand.h"
#include "Memento Pattern\ShMemento.h"
#include "Interface\ShGraphicView.h"
ShMoveViewCommand::ShMoveViewCommand(ShGraphicView *view, ShMoveViewMemento *memento) {

	this->view = view;
	this->memento = memento;
}

ShMoveViewCommand::~ShMoveViewCommand() {


}

void ShMoveViewCommand::Execute() {
	qDebug("ShMoveViewCommand->Execute()");

	double x = this->view->GetX();
	double y = this->view->GetY();
	double zoomRate = this->view->GetZoomRate();
	int dx, dy;
	this->view->ConvertEntityToDevice(x, y, dx, dy);


	ShMoveViewMemento* memento = dynamic_cast<ShMoveViewMemento*>(this->memento);
	this->view->MoveView(memento->ex, memento->ey, memento->zoomRate,
		memento->dx, memento->dy);

	memento->ex = x;
	memento->ey = y;
	memento->zoomRate = zoomRate;
	memento->dx = dx;
	memento->dy = dy;

}

void ShMoveViewCommand::UnExecute() {
	qDebug("ShMoveViewCommand->UnExecute()");
	
	double x = this->view->GetX();
	double y = this->view->GetY();
	double zoomRate = this->view->GetZoomRate();
	int dx, dy;
	this->view->ConvertEntityToDevice(x, y, dx, dy);


	ShMoveViewMemento* memento = dynamic_cast<ShMoveViewMemento*>(this->memento);
	this->view->MoveView(memento->ex, memento->ey, memento->zoomRate,
		memento->dx, memento->dy);

	memento->ex = x;
	memento->ey = y;
	memento->zoomRate = zoomRate;
	memento->dx = dx;
	memento->dy = dy;


}
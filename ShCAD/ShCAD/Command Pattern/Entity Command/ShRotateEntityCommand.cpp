
#include "ShRotateEntityCommand.h"
#include "Interface\ShGraphicView.h"
#include "Visitor Pattern\ShRotater.h"
ShRotateEntityCommand::ShRotateEntityCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& list, const ShPoint3d& center, double angle)
	:ShCommand("Rotate Entity"), view(view), list(list), center(center), angle(angle) {

}

ShRotateEntityCommand::~ShRotateEntityCommand() {

}

void ShRotateEntityCommand::Execute() {

	ShRotater rotater(this->center, this->angle);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		(*itr)->Accept(&rotater);

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}

void ShRotateEntityCommand::UnExecute() {

	ShRotater rotater(this->center, -this->angle);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		(*itr)->Accept(&rotater);

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}
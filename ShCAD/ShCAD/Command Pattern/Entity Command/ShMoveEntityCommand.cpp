
#include "ShMoveEntityCommand.h"
#include "Interface\ShGraphicView.h"

ShMoveEntityCommand::ShMoveEntityCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& list, const ShPoint3d& dis)
	:ShCommand("Move Entity"), view(view), list(list), dis(dis) {

}

ShMoveEntityCommand::~ShMoveEntityCommand() {

}

void ShMoveEntityCommand::Execute() {

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		(*itr)->Move(this->dis.x, this->dis.y);

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}

void ShMoveEntityCommand::UnExecute() {

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		(*itr)->Move(-this->dis.x, -this->dis.y);

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}
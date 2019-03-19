
#include "ShMirrorEntityCommand.h"
#include "Interface\ShGraphicView.h"
#include "Visitor Pattern\ShMirror.h"
ShMirrorEntityCommand::ShMirrorEntityCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& list, const ShPoint3d& center, double angle)
	:ShCommand("Mirror Entity"), view(view), list(list), center(center), angle(angle) {

}

ShMirrorEntityCommand::~ShMirrorEntityCommand() {

}

void ShMirrorEntityCommand::Execute() {

	ShMirror mirror(this->center, this->angle);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr) {
		mirror.SetOriginal((*itr));
		(*itr)->Accept(&mirror);
	}

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}

void ShMirrorEntityCommand::UnExecute() {

	ShMirror mirror(this->center, -this->angle);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr) {
		mirror.SetOriginal((*itr));
		(*itr)->Accept(&mirror);
	}

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}
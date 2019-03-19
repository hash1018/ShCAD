
#include "ShCopyEntityCommand.h"
#include "Interface\ShGraphicView.h"
#include "Entity\ShEntity.h"
ShCopyEntityCommand::ShCopyEntityCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& copiedEntityList)
	:ShCommand("Copy Entity"), view(view), copiedEntityList(copiedEntityList),mustDeallocateEntities(false) {

}

ShCopyEntityCommand::~ShCopyEntityCommand() {

	if (this->mustDeallocateEntities == true) {
		while (!this->copiedEntityList.empty())
			delete this->copiedEntityList.takeFirst();
	}

}

void ShCopyEntityCommand::Execute() {

	this->view->entityTable.Add(this->copiedEntityList);
	this->mustDeallocateEntities = false;

	this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawAddedEntities));
	this->view->CaptureImage();
}

void ShCopyEntityCommand::UnExecute() {

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->copiedEntityList.begin(); itr != this->copiedEntityList.end(); ++itr)
		this->view->entityTable.Remove((*itr));


	this->mustDeallocateEntities = true;

	this->view->update();
	this->view->CaptureImage();

}
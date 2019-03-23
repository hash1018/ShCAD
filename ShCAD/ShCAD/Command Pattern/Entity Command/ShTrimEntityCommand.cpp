

#include "ShTrimEntityCommand.h"
#include "Interface\ShGraphicView.h"
ShTrimEntityCommand::ShTrimEntityCommand(ShGraphicView *view, ShEntity *original, ShEntity *trimedEntity, ShEntity *trimedEntity2)
	:ShCommand("Trim Entity"), view(view), original(original), trimedEntity(trimedEntity), trimedEntity2(trimedEntity2),
	mustDeallocateOriginal(true), mustDeallocateTrimedEntity(false) {

}

ShTrimEntityCommand::~ShTrimEntityCommand() {

	if (this->mustDeallocateOriginal == true)
		delete this->original;

	if (this->mustDeallocateTrimedEntity == true) {
		delete this->trimedEntity;

		if (this->trimedEntity2 != 0)
			delete this->trimedEntity2;
	}
}

void ShTrimEntityCommand::Execute() {

	this->view->entityTable.Remove(this->original);
	this->view->entityTable.Add(trimedEntity);
	if (this->trimedEntity2 != 0)
		this->view->entityTable.Add(trimedEntity2);

	this->mustDeallocateOriginal = true;
	this->mustDeallocateTrimedEntity = false;


	this->view->update((DrawType)(DrawType::DrawAll));
	this->view->CaptureImage();
}

void ShTrimEntityCommand::UnExecute() {

	this->view->entityTable.Remove(this->trimedEntity);
	if (this->trimedEntity2 != 0)
		this->view->entityTable.Remove(this->trimedEntity2);

	this->view->entityTable.Add(this->original);

	this->mustDeallocateOriginal = false;
	this->mustDeallocateTrimedEntity = true;


	this->view->update((DrawType)(DrawType::DrawAll));
	this->view->CaptureImage();
}
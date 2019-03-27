
#include "ShExtendEntityCommand.h"
#include "Entity\ShEntity.h"
#include "Interface\ShGraphicView.h"
ShExtendEntityCommand::ShExtendEntityCommand(ShGraphicView *view, ShEntity *original, ShEntity *extendedEntity)
	:ShCommand("Extend Entity"), view(view), original(original), extendedEntity(extendedEntity),
	mustDeallocateExtended(false), mustDeallocateOriginal(true) {

}

ShExtendEntityCommand::~ShExtendEntityCommand() {

	if (this->mustDeallocateOriginal == true)
		delete this->original;

	if (this->mustDeallocateExtended == true)
		delete this->extendedEntity;
}

void ShExtendEntityCommand::Execute() {

	this->view->entityTable.Add(this->extendedEntity);
	this->view->entityTable.Remove(this->original);

	this->mustDeallocateExtended = false;
	this->mustDeallocateOriginal = true;

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}

void ShExtendEntityCommand::UnExecute() {

	this->view->entityTable.Remove(this->extendedEntity);
	this->view->entityTable.Add(this->original);

	this->mustDeallocateExtended = true;
	this->mustDeallocateOriginal = false;

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}




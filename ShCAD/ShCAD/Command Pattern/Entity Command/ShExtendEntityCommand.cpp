
#include "ShExtendEntityCommand.h"
#include "Entity\ShEntity.h"
#include "Interface\ShGraphicView.h"
ShExtendEntityCommand::ShExtendEntityCommand(ShGraphicView *view, ShEntity *entityToExtend,
	ShEntityData *original, ShEntityData *extendedData)
	:ShCommand("Extend Entity"), view(view), entityToExtend(entityToExtend), original(original),
	extendedData(extendedData) {

}

ShExtendEntityCommand::~ShExtendEntityCommand() {

	if (this->extendedData != 0)
		delete this->extendedData;
	if (this->original != 0)
		delete this->original;
}

void ShExtendEntityCommand::Execute() {

	this->entityToExtend->SetData(this->extendedData);

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}

void ShExtendEntityCommand::UnExecute() {

	this->entityToExtend->SetData(this->original);

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}




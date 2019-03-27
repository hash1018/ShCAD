

#include "ShStretchEntityCommand.h"
#include "Interface\ShGraphicView.h"

ShStretchEntityCommand::ShStretchEntityCommand(ShGraphicView *view,
	const QList<ShEntity*>& originalEntities, const QList<ShEntity*>& stretchedEntites)
	:ShCommand("Stretch Entity"), view(view), originalEntities(originalEntities), stretchedEntites(stretchedEntites)
	, mustDeallocateOriginal(true), mustDeallocateStretched(false) {

}

ShStretchEntityCommand::~ShStretchEntityCommand() {

	if (this->mustDeallocateOriginal == true) {
	
		while (!this->originalEntities.isEmpty())
			delete this->originalEntities.takeFirst();
	}

	if (this->mustDeallocateStretched == true) {
	
		while (!this->stretchedEntites.isEmpty())
			delete this->stretchedEntites.takeFirst();
	}
	
}



#include "Entity\ShEntity.h"
void ShStretchEntityCommand::Execute() {

	
	QList<ShEntity*>::iterator itr;
	QList<ShEntity*>::iterator itr2 = this->originalEntities.begin();
	for (itr = this->stretchedEntites.begin();
		itr != this->stretchedEntites.end();
		++itr) {
	
		this->view->entityTable.Remove((*itr2));
		this->view->entityTable.Add((*itr));
		++itr2;
	}

	this->mustDeallocateOriginal = true;
	this->mustDeallocateStretched = false;



	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();


}


void ShStretchEntityCommand::UnExecute() {
	
	QList<ShEntity*>::iterator itr;
	QList<ShEntity*>::iterator itr2 = this->originalEntities.begin();
	for (itr = this->stretchedEntites.begin();
		itr != this->stretchedEntites.end();
		++itr) {

		this->view->entityTable.Remove((*itr));
		this->view->entityTable.Add((*itr2));
		++itr2;
	}

	this->mustDeallocateOriginal = false;
	this->mustDeallocateStretched = true;


	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();

}

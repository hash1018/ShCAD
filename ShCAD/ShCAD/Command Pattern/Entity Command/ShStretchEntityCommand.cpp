

#include "ShStretchEntityCommand.h"
#include "Interface\ShGraphicView.h"
#include "Visitor Pattern\ShStretchVisitor.h"
ShStretchEntityCommand::ShStretchEntityCommand(ShGraphicView *view, const QList<ShEntity*>& entitiesToStretch,
	const QList<ShStretchData*>& stretchDataList,
	const ShPoint3d& base, const ShPoint3d& current)
	:ShCommand("Stretch Entity"), view(view), entitiesToStretch(entitiesToStretch), stretchDataList(stretchDataList),
	base(base), current(current) {

	this->StoreOriginal();
}

ShStretchEntityCommand::~ShStretchEntityCommand() {

	this->DeleteOriginalAll();

	while (!this->stretchDataList.isEmpty())
		delete this->stretchDataList.takeFirst();

}



#include "Entity\ShEntity.h"
void ShStretchEntityCommand::Execute() {

	ShStretchVisitor visitor(this->base, this->current);

	QList<ShEntity*>::iterator itr;
	QList<ShEntity*>::iterator originalItr = this->originalEntities.begin();
	QList<ShStretchData*>::iterator dataItr = this->stretchDataList.begin();
	
	for (itr = this->entitiesToStretch.begin(); itr != this->entitiesToStretch.end(); ++itr) {

		visitor.SetOriginal((*originalItr));
		visitor.SetStretchData((*dataItr));
		++originalItr;
		++dataItr;
		(*itr)->Accept(&visitor);
	}

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();


}


void ShStretchEntityCommand::UnExecute() {
	
	/*
	ShStretchVisitor visitor(this->current, this->base);

	QLinkedList<ShEntity*>::iterator itr;
	QLinkedList<VertexPoint>::iterator itrVertexPoint = this->vertexPoints.begin();
	QLinkedList<ShEntity*>::iterator originalItr = this->originalEntities.begin();

	for (itr = this->entities.begin(); itr != this->entities.end(); ++itr) {

		visitor.SetVertexPoint((*itrVertexPoint));
		//visitor.SetOriginalEntity((*originalItr));
		//++originalItr;
		visitor.SetOriginalEntity((*itr));
		++itrVertexPoint;
		(*itr)->Accept(&visitor);

		
	}
	*/

	ShEntityData *data;
	QList<ShEntity*>::iterator itr;
	QList<ShEntity*>::iterator originalItr = this->originalEntities.begin();
	for (itr = this->entitiesToStretch.begin(); itr != this->entitiesToStretch.end(); ++itr) {

		data = (*originalItr)->CreateData();
		(*itr)->SetData(data);
		delete data;
		++originalItr;
	}

	
	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();

}

void ShStretchEntityCommand::DeleteOriginalAll() {
	
	while (!this->originalEntities.empty())
		delete this->originalEntities.takeFirst();

}

void ShStretchEntityCommand::StoreOriginal() {
	
	QList <ShEntity*>::iterator itr;
	for (itr = this->entitiesToStretch.begin(); itr != this->entitiesToStretch.end(); ++itr)
		this->originalEntities.append((*itr)->Clone());
}
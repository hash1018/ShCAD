

#include "ShStretchEntityCommand.h"
#include "Interface\ShGraphicView.h"

ShStretchEntityCommand::ShStretchEntityCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& entities,
	const QLinkedList<VertexPoint>& vertexPoints, const ShPoint3d& base, const ShPoint3d& current)
	:ShCommand("Stretch Entity"), view(view), entities(entities), vertexPoints(vertexPoints),
	base(base), current(current) {

	this->StoreOriginal();
}

ShStretchEntityCommand::~ShStretchEntityCommand() {

	this->DeleteOriginalAll();
}


#include "Visitor Pattern\ShStretchVisitor.h"
#include "Entity\ShEntity.h"
void ShStretchEntityCommand::Execute() {

	ShStretchVisitor visitor(this->base, this->current);

	QLinkedList<ShEntity*>::iterator itr;
	QLinkedList<VertexPoint>::iterator itrVertexPoint = this->vertexPoints.begin();
	QLinkedList<ShEntity*>::iterator originalItr = this->originalEntities.begin();

	for (itr = this->entities.begin(); itr != this->entities.end(); ++itr) {

		visitor.SetVertexPoint((*itrVertexPoint));
		visitor.SetOriginalEntity((*originalItr));
		++originalItr;
		++itrVertexPoint;
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
	QLinkedList<ShEntity*>::iterator itr;
	QLinkedList<ShEntity*>::iterator originalItr = this->originalEntities.begin();
	for (itr = this->entities.begin(); itr != this->entities.end(); ++itr) {

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
	
	QLinkedList <ShEntity*>::iterator itr;
	for (itr = this->entities.begin(); itr != this->entities.end(); ++itr)
		this->originalEntities.append((*itr)->Clone());
}
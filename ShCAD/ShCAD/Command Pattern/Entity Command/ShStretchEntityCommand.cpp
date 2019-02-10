

#include "ShStretchEntityCommand.h"
#include "Interface\ShGraphicView.h"

ShStretchEntityCommand::ShStretchEntityCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& entities,
	const QLinkedList<HitPoint>& hitPoints, const ShPoint3d& previous, const ShPoint3d& current)
	:ShCommand("Stretch Entity"), view(view), entities(entities), hitPoints(hitPoints),
	previous(previous), current(current) {


}

ShStretchEntityCommand::~ShStretchEntityCommand() {


}


#include "Visitor Pattern\ShStretchVisitor.h"
#include "Entity\ShEntity.h"
void ShStretchEntityCommand::Execute() {

	ShStretchVisitor visitor(this->current.x, this->current.y);

	QLinkedList<ShEntity*>::iterator itr;
	QLinkedList<HitPoint>::iterator itrHitPoint = this->hitPoints.begin();

	for (itr = this->entities.begin(); itr != this->entities.end(); ++itr) {

		visitor.SetHitPoint((*itrHitPoint));
		++itrHitPoint;
		(*itr)->Accept(&visitor);
	}

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();


}


void ShStretchEntityCommand::UnExecute() {

	ShStretchVisitor visitor(this->previous.x, this->previous.y);

	QLinkedList<ShEntity*>::iterator itr;
	QLinkedList<HitPoint>::iterator itrHitPoint = this->hitPoints.begin();

	for (itr = this->entities.begin(); itr != this->entities.end(); ++itr) {

		visitor.SetHitPoint((*itrHitPoint));
		++itrHitPoint;
		(*itr)->Accept(&visitor);
	}

	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();

}
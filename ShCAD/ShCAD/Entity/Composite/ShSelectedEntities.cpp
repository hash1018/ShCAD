
#include "ShSelectedEntities.h"
#include "Interface\ShCADWidget.h"
#include "Event\ShNotifyEvent.h"
#include "Entity\Composite\Dim\ShDim.h"

ShSelectedEntities::ShSelectedEntities() {

}

ShSelectedEntities::~ShSelectedEntities() {

	this->list.clear();
}

bool ShSelectedEntities::add(ShEntity *entity) {

	if (entity->isSelected() == true)
		return false;

	entity->select();
	this->list.append(entity);

	this->justSelectedList.clear();
	this->justSelectedList.append(entity);

	if (dynamic_cast<ShDim*>(entity))
		this->dimSelectedList.append(dynamic_cast<ShDim*>(entity));

	this->selectedEntityCountChanged();

	return true;
}

bool ShSelectedEntities::add(const QLinkedList<ShEntity*> &list) {

	this->justSelectedList.clear();

	auto itr = const_cast<QLinkedList<ShEntity*>&>(list).begin();

	for (itr; itr != const_cast<QLinkedList<ShEntity*>&>(list).end(); ++itr) {
	
		if ((*itr)->isSelected() == false) {

			(*itr)->select();
			this->list.append((*itr));
			this->justSelectedList.append(*itr);

			if (dynamic_cast<ShDim*>((*itr)))
				this->dimSelectedList.append(dynamic_cast<ShDim*>((*itr)));
		}

	}

	this->selectedEntityCountChanged();
	return true;
}

bool ShSelectedEntities::deleteEntity(ShEntity *entity) {

	//igonore.
	return false;
}

bool ShSelectedEntities::remove(ShEntity *entity) {

	if (entity->isSelected() == false)
		return false;

	entity->unSelect();
	this->list.removeOne(entity);

	this->justSelectedList.clear();

	if (dynamic_cast<ShDim*>(entity))
		this->dimSelectedList.removeOne(dynamic_cast<ShDim*>(entity));

	this->selectedEntityCountChanged();

	return true;
}

bool ShSelectedEntities::remove(const QLinkedList<ShEntity*> &list) {

	this->justSelectedList.clear();

	auto itr = const_cast<QLinkedList<ShEntity*>&> (list).begin();

	for (itr; itr != const_cast<QLinkedList<ShEntity*>&>(list).end(); ++itr) {
	
		if ((*itr)->isSelected() == true) {
		
			(*itr)->unSelect();
			this->list.removeOne((*itr));

			if (dynamic_cast<ShDim*>((*itr)))
				this->dimSelectedList.removeOne(dynamic_cast<ShDim*>((*itr)));
		}
	}

	this->selectedEntityCountChanged();

	return true;
}

void ShSelectedEntities::unSelectAll() {

	this->justSelectedList.clear();

	auto itr = this->list.begin();

	for (itr; itr != this->list.end(); ++itr)
		(*itr)->unSelect();

	this->list.clear();
	this->dimSelectedList.clear();

	this->selectedEntityCountChanged();
}

ShSelectedEntities* ShSelectedEntities::clone() {

	return nullptr;
}

void ShSelectedEntities::accept(ShVisitor *visitor) {


}

void ShSelectedEntities::selectedEntityCountChanged() {

	ShSelectedEntityCountChangedEvent event(this->widget, this->list);
	this->widget->notify(&event);
}


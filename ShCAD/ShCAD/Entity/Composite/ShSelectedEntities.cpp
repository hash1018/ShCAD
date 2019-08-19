
#include "ShSelectedEntities.h"

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
		}

	}
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

	return true;
}

bool ShSelectedEntities::remove(const QLinkedList<ShEntity*> &list) {

	this->justSelectedList.clear();

	auto itr = const_cast<QLinkedList<ShEntity*>&> (list).begin();

	for (itr; itr != const_cast<QLinkedList<ShEntity*>&>(list).end(); ++itr) {
	
		if ((*itr)->isSelected() == true) {
		
			(*itr)->unSelect();
			this->list.removeOne((*itr));
		}
	}

	return true;
}

void ShSelectedEntities::unSelectAll() {

	this->justSelectedList.clear();

	auto itr = this->list.begin();

	for (itr; itr != this->list.end(); ++itr)
		(*itr)->unSelect();

	this->list.clear();
}

ShSelectedEntities* ShSelectedEntities::clone() {

	return nullptr;
}

void ShSelectedEntities::accept(ShVisitor *visitor) {


}
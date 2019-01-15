

#include "ShSelectedEntityManager.h"
#include "Entity\ShEntity.h"
ShSelectedEntityManager::ShSelectedEntityManager() {

}

ShSelectedEntityManager::~ShSelectedEntityManager() {

}

ShSelectedEntityManager::ShSelectedEntityManager(const ShSelectedEntityManager& other)
	:list(other.list) {

}

ShSelectedEntityManager& ShSelectedEntityManager::operator=(const ShSelectedEntityManager& other) {

	this->list = other.list;

	return *this;
}

bool ShSelectedEntityManager::Push(ShEntity *entity) {

	if (entity->IsSelected() == true)
		return false;

	entity->Select();
	this->list.append(entity);

	return true;
}

bool ShSelectedEntityManager::Pop(ShEntity *entity) {

	if (entity->IsSelected() == false)
		return false;

	entity->UnSelect();
	this->list.removeOne(entity);

	return true;
}

void ShSelectedEntityManager::UnSelectAll() {

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		(*itr)->UnSelect();


	this->list.empty();


}

int ShSelectedEntityManager::GetSize() {

	return this->list.size();
}

ShEntity* ShSelectedEntityManager::GetRecentSelected() {

	//if (this->list.isEmpty() == true)
		//return 0;


	return this->list.last();
}
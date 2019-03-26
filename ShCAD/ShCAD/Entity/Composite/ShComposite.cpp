

#include "ShComposite.h"


ShComposite::ShComposite() {

}

ShComposite::ShComposite(const ShPropertyData &propertyData, ShLayer *layer)
	:ShEntity(propertyData, layer) {

}

ShComposite::ShComposite(const ShComposite& other)
	: ShEntity(other) {

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = (const_cast<ShComposite&>(other)).list.begin(); itr != (const_cast<ShComposite&>(other)).list.end(); ++itr) {

		ShEntity *entity = (*itr)->Clone();
		this->list.append(entity);
	}

}

ShComposite::~ShComposite() {

	while (!this->list.isEmpty())
		delete this->list.takeFirst();

		
}

ShComposite& ShComposite::operator=(const ShComposite& other) {

	ShEntity::operator=(other);


	QLinkedList<ShEntity*>::iterator itr;

	for (itr = (const_cast<ShComposite&>(other)).list.begin(); itr != (const_cast<ShComposite&>(other)).list.end(); ++itr) {

		ShEntity *entity = (*itr)->Clone();
		this->list.append(entity);
	}


	return *this;
}

#include "ShLayer.h"
bool ShComposite::Add(ShEntity* shEntity) {

	if (shEntity == 0)
		return false;

	this->list.append(shEntity);
	
	return true;
}

bool ShComposite::Add(QLinkedList<ShEntity*> &list) {
	
	if (list.isEmpty())
		return false;

	
	QLinkedList<ShEntity*>::iterator itr;

	for (itr = list.begin(); itr != list.end(); ++itr) {
		this->list.append((*itr));
	}

	return true;

}

void ShComposite::Delete(ShEntity *shEntity) {

	shEntity->GetLayer()->Remove(shEntity);

	this->list.removeOne(shEntity);

	delete shEntity;
}

void ShComposite::Remove(ShEntity *shEntity) {

	this->list.removeOne(shEntity);

}

bool ShComposite::IsListEmpty() {

	return this->list.isEmpty();
}



void ShComposite::RemoveAll(QLinkedList<ShEntity*> &list) {

	while (!list.isEmpty())
		list.removeFirst();
	

}

ShEntity* ShComposite::GetEntity(int index) {

	if (index >= this->list.count())
		return 0;

	if (index < 0)
		return 0;

	QLinkedList<ShEntity*>::iterator itr = this->list.begin();
	int i = 0;
	while (i < index) {
	
		++itr;
		i++;
	}

	return (*itr);
}

int ShComposite::GetIndex(ShEntity* entity) {

	if (entity == 0)
		return -1;

	QLinkedList<ShEntity*>::iterator itr = this->Begin();

	int index = 0;
	while (itr != this->End() && (*itr) != entity) {

		index++;
		++itr;
	}

	if ((*itr) == entity)
		return index;

	return -1;
}

#include "ShComposite.h"
#include "Entity\Private\ShSearchEntityStrategy.h"


ShComposite::ShComposite() {

}

ShComposite::ShComposite(const ShPropertyData &propertyData, ShLayer *layer)
	:ShEntity(propertyData, layer) {

}

ShComposite::ShComposite(const ShComposite &other)
	:ShEntity(other) {

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = (const_cast<ShComposite&>(other)).list.begin();
		itr != (const_cast<ShComposite&>(other)).list.end();
		++itr) {

		ShEntity *entity = (*itr)->clone();
		this->list.append(entity);
	}
}

ShComposite::~ShComposite() {

	while (!this->list.isEmpty())
		delete this->list.takeFirst();
}

ShComposite& ShComposite::operator=(const ShComposite &other) {

	ShEntity::operator=(other);

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = (const_cast<ShComposite&>(other)).list.begin();
		itr != (const_cast<ShComposite&>(other)).list.end();
		++itr) {

		ShEntity *entity = (*itr)->clone();
		this->list.append(entity);
	}

	return *this;
}

bool ShComposite::add(ShEntity *entity) {

	if (entity == nullptr)
		return false;

	this->list.append(entity);
	return true;
}

bool ShComposite::add(const QLinkedList<ShEntity*> &list) {

	if (list.isEmpty())
		return false;

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = (const_cast<QLinkedList<ShEntity*>&>(list)).begin();
		itr != (const_cast<QLinkedList<ShEntity*>&>(list)).end();
		++itr) {

		this->list.append(*itr);
	}

	return true;
}

bool ShComposite::deleteEntity(ShEntity *entity) {

	bool result = this->list.removeOne(entity);

	if (result == false)
		return false;

	delete entity;
	return true;
}

bool ShComposite::remove(ShEntity *entity) {

	return this->list.removeOne(entity);
}

void ShComposite::search(ShSearchEntityStrategy &strategy) {

	strategy.setList(this->list);
	strategy.search();
}
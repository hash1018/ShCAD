
#include "ShSearchEntityStrategy.h"
#include "ShFinder.h"
#include "Entity\ShEntity.h"

ShSearchEntityStrategy::ShSearchEntityStrategy(double x, double y, double zoomRate)
	:x(x), y(y), zoomRate(zoomRate) {

}

ShSearchEntityStrategy::~ShSearchEntityStrategy() {

}

void ShSearchEntityStrategy::setList(const QLinkedList<ShEntity*> &list) {

	this->list = list;
}

/////////////////////////////////////////////////////////////



ShSearchEntityUniqueStrategy::ShSearchEntityUniqueStrategy(ShEntity* *foundEntity, double x, double y, double zoomRate)
	:ShSearchEntityStrategy(x, y, zoomRate), foundEntity(foundEntity) {

}

ShSearchEntityUniqueStrategy::~ShSearchEntityUniqueStrategy() {

}

void ShSearchEntityUniqueStrategy::search() {

	ShEntity *entity = nullptr;

	ShFinder finder(this->x, this->y, this->zoomRate, &entity);

	QLinkedList<ShEntity*>::iterator itr = this->list.begin();

	while (itr != this->list.end() && entity == nullptr) {

		(*itr)->accept(&finder);
		++itr;
	}

	*this->foundEntity = entity;

}
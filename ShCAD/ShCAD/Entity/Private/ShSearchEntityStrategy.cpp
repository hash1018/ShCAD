
#include "ShSearchEntityStrategy.h"
#include "ShFinder.h"
#include "Entity\ShEntity.h"
#include "Entity\Composite\ShComposite.h"

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


//////////////////////////////////////////////////////////////////////


ShSearchEntityCompositeChildIncludedStrategy::ShSearchEntityCompositeChildIncludedStrategy(ShEntity* *foundEntity, double x, double y, double zoomRate)
	:ShSearchEntityStrategy(x, y, zoomRate) {

}

ShSearchEntityCompositeChildIncludedStrategy::~ShSearchEntityCompositeChildIncludedStrategy() {

}


void ShSearchEntityCompositeChildIncludedStrategy::search() {

	*this->foundEntity = nullptr;

	ShFinder finder(x, y, zoomRate, this->foundEntity);

	QLinkedList<ShEntity*>::iterator itr = this->list.begin();

	while (itr != this->list.end() && *this->foundEntity == nullptr) {
		(*itr)->accept(&finder);
		++itr;
	}

	if (dynamic_cast<ShComposite*>((*this->foundEntity))) {
		ShSearchEntityCompositeChildIncludedStrategy strategy(this->foundEntity, this->x, this->y, this->zoomRate);
		dynamic_cast<ShComposite*>((*this->foundEntity))->search(strategy);

	}

	
}
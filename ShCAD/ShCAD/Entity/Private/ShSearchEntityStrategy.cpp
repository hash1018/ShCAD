
#include "ShSearchEntityStrategy.h"
#include "Algorithm\ShFinder.h"
#include "Entity\ShEntity.h"
#include "Entity\Composite\ShComposite.h"

ShSearchEntityStrategy::ShSearchEntityStrategy(double x, double y, double zoomRate, double tolerance)
	:x(x), y(y), zoomRate(zoomRate),tolerance(tolerance) {

}

ShSearchEntityStrategy::~ShSearchEntityStrategy() {

}

void ShSearchEntityStrategy::setList(const QLinkedList<ShEntity*> &list) {

	this->list = list;
}

/////////////////////////////////////////////////////////////



ShSearchEntityUniqueStrategy::ShSearchEntityUniqueStrategy(ShEntity* *foundEntity, double x, double y, double zoomRate, double tolerance)
	:ShSearchEntityStrategy(x, y, zoomRate, tolerance), foundEntity(foundEntity) {

}

ShSearchEntityUniqueStrategy::~ShSearchEntityUniqueStrategy() {

}

void ShSearchEntityUniqueStrategy::search() {

	ShEntity *entity = nullptr;

	ShFinder finder(this->x, this->y, this->zoomRate, &entity, this->tolerance);

	QLinkedList<ShEntity*>::iterator itr = this->list.begin();

	while (itr != this->list.end() && entity == nullptr) {

		(*itr)->accept(&finder);
		++itr;
	}

	*this->foundEntity = entity;

}


//////////////////////////////////////////////////////////////////////


ShSearchEntityCompositeChildIncludedStrategy::ShSearchEntityCompositeChildIncludedStrategy(ShEntity* *foundEntity, double x, double y, double zoomRate, double tolerance)
	:ShSearchEntityStrategy(x, y, zoomRate, tolerance), foundEntity(foundEntity) {

}

ShSearchEntityCompositeChildIncludedStrategy::~ShSearchEntityCompositeChildIncludedStrategy() {

}


void ShSearchEntityCompositeChildIncludedStrategy::search() {

	(*this->foundEntity) = nullptr;

	ShFinder finder(this->x, this->y, this->zoomRate, this->foundEntity, this->tolerance);

	QLinkedList<ShEntity*>::iterator itr = this->list.begin();

	while (itr != this->list.end() && (*this->foundEntity) == nullptr) {
		(*itr)->accept(&finder);
		++itr;
	}

	if (dynamic_cast<ShComposite*>((*this->foundEntity))) {
		ShSearchEntityCompositeChildIncludedStrategy strategy(this->foundEntity, this->x, this->y, this->zoomRate);
		dynamic_cast<ShComposite*>((*this->foundEntity))->search(strategy);

	}	
}

/////////////////////////////////////////////////////////////////////////


ShSearchEntityDuplicateStrategy::ShSearchEntityDuplicateStrategy(QLinkedList<ShEntity*> &foundEntities, const int max, double x, double y, double zoomRate, double tolerance)
	:ShSearchEntityStrategy(x, y, zoomRate, tolerance), foundEntities(foundEntities), max(max) {

}

ShSearchEntityDuplicateStrategy::~ShSearchEntityDuplicateStrategy() {

}

void ShSearchEntityDuplicateStrategy::search() {

	if (this->max == 0)
		return;

	ShEntity *foundEntity = nullptr;

	ShFinder finder(this->x, this->y, this->zoomRate, &foundEntity, this->tolerance);

	int count = 0;
	auto itr = this->list.begin();

	for (itr; itr != this->list.end(); ++itr) {
	
		foundEntity = nullptr;
		(*itr)->accept(&finder);

		if (foundEntity != nullptr) {
			count++;
			this->foundEntities.append(foundEntity);

			if (count >= this->max)
				return;

		}

	}
}

////////////////////////////////////////////////////////////////

ShSearchEntityDuplicateCompositeChildIncludedStrategy::ShSearchEntityDuplicateCompositeChildIncludedStrategy(QLinkedList<ShEntity*> &foundEntities,
	const int max, double x, double y, double zoomRate, double tolerance)
	:ShSearchEntityStrategy(x, y, zoomRate, tolerance), foundEntities(foundEntities), max(max) {

}

ShSearchEntityDuplicateCompositeChildIncludedStrategy::~ShSearchEntityDuplicateCompositeChildIncludedStrategy() {

}

void ShSearchEntityDuplicateCompositeChildIncludedStrategy::search() {

	if (this->max == 0)
		return;

	ShEntity *foundEntity = nullptr;

	ShFinder finder(this->x, this->y, this->zoomRate, &foundEntity, this->tolerance);

	int count = this->foundEntities.count();
	auto itr = this->list.begin();

	for (itr; itr != this->list.end(); ++itr) {

		foundEntity = nullptr;
		(*itr)->accept(&finder);

		if (foundEntity != nullptr) {

			if (dynamic_cast<ShComposite*>(foundEntity)) {
			
				ShSearchEntityDuplicateCompositeChildIncludedStrategy strategy(this->foundEntities, this->max, this->x, this->y,
					this->zoomRate, this->tolerance);

				dynamic_cast<ShComposite*>(foundEntity)->search(strategy);
			}
			else {
				count++;
				this->foundEntities.append(foundEntity);

				if (count >= this->max)
					return;

			}
		}
	}
}
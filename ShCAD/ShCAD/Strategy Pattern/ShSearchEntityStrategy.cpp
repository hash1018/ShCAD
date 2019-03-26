

#include "ShSearchEntityStrategy.h"
#include "Visitor Pattern\ShFinder.h"
#include "Entity\Composite\ShEntityTable.h"

ShSearchEntityStrategy::ShSearchEntityStrategy(double x, double y, double zoomRate)
	:x(x), y(y), zoomRate(zoomRate) {

}

ShSearchEntityStrategy::~ShSearchEntityStrategy() {

}

ShSearchEntityUniqueStrategy::ShSearchEntityUniqueStrategy(ShEntity* *foundEntity, double x, double y, double zoomRate)
	:ShSearchEntityStrategy(x, y, zoomRate), foundEntity(foundEntity) {

}

ShSearchEntityUniqueStrategy::~ShSearchEntityUniqueStrategy() {

}


void ShSearchEntityUniqueStrategy::Search() {


	ShEntity *entity = 0;

	ShFinder finder(x, y, zoomRate, &entity);

	QLinkedList<ShEntity*>::iterator itr = this->entityTable->TurnOnLayerBegin();

	while (itr != this->entityTable->TurnOnLayerEnd() && entity == 0) {

		(*itr)->Accept(&finder);
		++itr;
	}

	*foundEntity = entity;

}

////////////////////////////////////////////////////////////////////

ShSearchEntityCompositeChildIncludedStrategy::ShSearchEntityCompositeChildIncludedStrategy(ShEntity* *foundEntity,
	double x, double y, double zoomRate)
	:ShSearchEntityStrategy(x, y, zoomRate), foundEntity(foundEntity) {

}
ShSearchEntityCompositeChildIncludedStrategy::~ShSearchEntityCompositeChildIncludedStrategy() {

}

#include "Entity\Composite\ShPolyLine.h"
void ShSearchEntityCompositeChildIncludedStrategy::Search() {

	ShEntity *entity = 0;

	ShFinder finder(x, y, zoomRate, &entity);

	QLinkedList<ShEntity*>::iterator itr = this->entityTable->TurnOnLayerBegin();

	while (itr != this->entityTable->TurnOnLayerEnd() && entity == 0) {

		(*itr)->Accept(&finder);
		++itr;
	}

	
	if (dynamic_cast<ShPolyLine*>(entity)) {
		
		ShPolyLine* polyLine = dynamic_cast<ShPolyLine*>(entity);
		entity = 0;

		itr = polyLine->Begin();
		while (itr != polyLine->End() && entity == 0) {

			(*itr)->Accept(&finder);
			++itr;
		}
	}

	*foundEntity = entity;

}
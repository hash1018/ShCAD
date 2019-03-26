

#include "ShEntityTable.h"
#include "Visitor Pattern\ShVisitor.h"

//#include "Visitor Pattern\ShFinder.h"

ShEntityTable::ShEntityTable() {

}

ShEntityTable::ShEntityTable(const ShEntityTable& other) {

}

ShEntityTable::~ShEntityTable() {

}

ShEntityTable& ShEntityTable::operator=(const ShEntityTable &other) {

	ShComposite::operator=(other);

	return *this;
}

ShEntityTable* ShEntityTable::Clone() {

	return new ShEntityTable(*this);
}

void ShEntityTable::Accept(ShVisitor *shVisitor) {

	shVisitor->Visit(this);
}

bool ShEntityTable::Add(ShEntity *shEntity) {

	if (shEntity == 0)
		return false;

	this->RemoveAll(this->justAddedEntityList);

	shEntity->GetLayer()->Add(shEntity);
	
	if (shEntity->GetLayer()->IsTurnOn() == true) {
		this->layerTable.turnOnList.append(shEntity);
		this->justAddedEntityList.append(shEntity);
	}

	return ShComposite::Add(shEntity);
	
}

bool ShEntityTable::Add(QLinkedList<ShEntity*> &list) {

	this->RemoveAll(this->justAddedEntityList);

	if (list.isEmpty())
		return false;


	QLinkedList<ShEntity*>::iterator itr;

	for (itr = list.begin(); itr != list.end(); ++itr) {
		
		this->list.append((*itr));
		(*itr)->GetLayer()->Add((*itr));

		if ((*itr)->GetLayer()->IsTurnOn() == true) {
			this->layerTable.turnOnList.append((*itr));
			this->justAddedEntityList.append((*itr));
		}
	
	}

	return true;
}

void ShEntityTable::Remove(ShEntity *shEntity) {

	shEntity->GetLayer()->Remove(shEntity);

	if (shEntity->GetLayer()->IsTurnOn() == true) {
		this->layerTable.turnOnList.removeOne(shEntity);
	}

	ShComposite::Remove(shEntity);

}


/*
ShEntity* ShEntityTable::FindEntity(double x, double y, double zoomRate) {

	ShEntity *entity = 0;

	ShFinder finder(x, y, zoomRate, &entity);

	QLinkedList<ShEntity*>::iterator itr = this->TurnOnLayerBegin();

	while (itr != this->TurnOnLayerEnd() && entity == 0) {

		(*itr)->Accept(&finder);
		++itr;
	}

	return entity;

}

*/

#include "Strategy Pattern\ShSearchEntityStrategy.h"
void ShEntityTable::Search(ShSearchEntityStrategy& strategy) {

	strategy.entityTable = this;
	strategy.Search();
}
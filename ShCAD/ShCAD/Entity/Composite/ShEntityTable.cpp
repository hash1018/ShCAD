

#include "ShEntityTable.h"
#include "Visitor Pattern\ShFinder.h"
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


ShEntity* ShEntityTable::FindEntity(double x, double y, double zoomRate) {

	ShEntity *entity = 0;

	ShFinder finder(x, y, zoomRate, &entity);

	QLinkedList<ShEntity*>::iterator itr = this->list.begin();

	while (itr != this->list.end() && entity == 0) {

		(*itr)->Accept(&finder);
		++itr;
	}

	return entity;

}

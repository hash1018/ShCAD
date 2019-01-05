

#include "ShEntityTable.h"
#include "Visitor Pattern\ShVisitor.h"

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

	this->list.append(shEntity);
	this->length++;

	return true;
}
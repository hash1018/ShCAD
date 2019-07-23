
#include "ShEntityTable.h"

ShEntityTable::ShEntityTable() {

}

ShEntityTable::ShEntityTable(const ShEntityTable &other)
	:ShComposite(other) {

}

ShEntityTable::~ShEntityTable() {

}

ShEntityTable& ShEntityTable::operator=(const ShEntityTable &other) {

	ShComposite::operator=(other);
	
	return *this;
}

ShEntityTable* ShEntityTable::clone() {

	return new ShEntityTable(*this);
}

void ShEntityTable::accept(ShVisitor *visitor) {


}

bool ShEntityTable::add(ShEntity *entity) {

	if (entity == nullptr)
		return false;

	this->justAddedEntityList.clear();

	this->justAddedEntityList.append(entity);

	return ShComposite::add(entity);

}

bool ShEntityTable::add(const QLinkedList<ShEntity*> &list) {
	
	if (list.isEmpty())
		return false;

	this->justAddedEntityList.clear();

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = const_cast<QLinkedList<ShEntity*>&>(list).begin();
		itr != const_cast<QLinkedList<ShEntity*>&>(list).end();
		++itr) {
	
		this->justAddedEntityList.append((*itr));
	}

	return ShComposite::add(list);
}

bool ShEntityTable::remove(ShEntity *entity) {

	return ShComposite::remove(entity);
}
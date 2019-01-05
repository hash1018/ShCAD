

#include "ShComposite.h"


ShEntity* ShComposite::Iterator::Current() {

	return (*this->itr);
}

bool ShComposite::Iterator::IsLast() {

	if ((*this->itr) == (*this->last))
		return true;

	return false;
}

bool ShComposite::Iterator::IsFirst() {

	if ((*this->itr) == (*this->first))
		return true;

	return false;
}

void ShComposite::Iterator::Previous() {

	--this->itr;
}

void ShComposite::Iterator::Next() {

	++this->itr;
}


ShComposite::ShComposite()
	:length(0) {

}

ShComposite::ShComposite(const ShComposite& other)
	: length(other.length) {

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = (const_cast<ShComposite&>(other)).list.begin(); itr != (const_cast<ShComposite&>(other)).list.end(); ++itr) {
	
		ShEntity *entity = (*itr)->Clone();
		this->list.append(entity);
	}

}

ShComposite::~ShComposite() {

	while (!this->list.isEmpty()) {
		delete this->list.takeFirst();
		qDebug("asdasdasd");
	}
}

ShComposite& ShComposite::operator=(const ShComposite& other) {

	ShEntity::operator=(other);


	QLinkedList<ShEntity*>::iterator itr;

	for (itr = (const_cast<ShComposite&>(other)).list.begin(); itr != (const_cast<ShComposite&>(other)).list.end(); ++itr) {

		ShEntity *entity = (*itr)->Clone();
		this->list.append(entity);
	}

	this->length = other.length;



	return *this;
}

ShComposite::Iterator& ShComposite::GetIterator() {

	this->itr.itr = this->list.begin();
	this->itr.first = this->list.begin();
	this->itr.last = this->list.end();

	return this->itr;
}
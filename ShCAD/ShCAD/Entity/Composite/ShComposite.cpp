

#include "ShComposite.h"

ShComposite::Iterator::Iterator() {


}

ShComposite::Iterator::Iterator(const ShComposite::Iterator& other){
	
	this->itr = other.itr;
	this->first = other.first;
	this->last = other.last;

}

ShComposite::Iterator& ShComposite::Iterator::operator=(const ShComposite::Iterator& other) {

	this->itr = other.itr;
	this->first = other.first;
	this->last = other.last;
	return *this;
}

ShComposite::Iterator::~Iterator() {

}

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

	while (!this->list.isEmpty())
		delete this->list.takeFirst();
		
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

ShComposite::Iterator ShComposite::First() {

	ShComposite::Iterator itr;
	
	itr.first = this->list.begin();
	itr.last = this->list.end();
	itr.itr = this->list.begin();
	
	return itr;
}


ShComposite::Iterator ShComposite::Last() {

	ShComposite::Iterator itr;

	itr.first = this->list.begin();
	itr.last = this->list.end();
	itr.itr = this->list.end();

	return itr;

}
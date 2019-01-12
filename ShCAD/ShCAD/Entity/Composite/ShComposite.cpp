

#include "ShComposite.h"

ShComposite::Iterator::Iterator() {


}

ShComposite::Iterator::Iterator(const ShComposite::Iterator& other){
	
	this->itr = other.itr;
	this->begin = other.begin;
	this->end = other.end;

}

ShComposite::Iterator& ShComposite::Iterator::operator=(const ShComposite::Iterator& other) {

	this->itr = other.itr;
	this->begin = other.begin;
	this->end = other.end;
	return *this;
}

ShComposite::Iterator::~Iterator() {

}

ShEntity* ShComposite::Iterator::Current() {

	return (*this->itr);
}

bool ShComposite::Iterator::IsEnd() {

	if ((*this->itr) == (*this->end))
		return true;

	return false;
}

bool ShComposite::Iterator::IsBegin() {

	if ((*this->itr) == (*this->begin))
		return true;

	return false;
}

void ShComposite::Iterator::Previous() {

	--this->itr;
}

void ShComposite::Iterator::Next() {

	++this->itr;
}


ShComposite::ShComposite() {

}

ShComposite::ShComposite(const ShComposite& other) {

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


	return *this;
}

bool ShComposite::Add(ShEntity* shEntity) {

	if (shEntity == 0)
		return false;

	this->list.append(shEntity);
	

	return true;
}

void ShComposite::Delete(ShEntity *shEntity) {

	this->list.removeOne(shEntity);

	delete shEntity;
}

bool ShComposite::IsListEmpty() {

	return this->list.isEmpty();
}


ShComposite::Iterator ShComposite::Begin() {

	ShComposite::Iterator itr;
	
	itr.begin = this->list.begin();
	itr.end = this->list.end();
	itr.itr = this->list.begin();
	
	return itr;
}


ShComposite::Iterator ShComposite::End() {

	ShComposite::Iterator itr;

	itr.begin = this->list.begin();
	itr.end = this->list.end();
	itr.itr = this->list.end();

	return itr;

}




#include "ShMemento.h"

ShMemento::ShMemento()
	:type(MementoUnknown) {

	this->entity = 0;

}

ShMemento::~ShMemento() {
	
}

void ShMemento::SetType(MementoType type) {

	this->type = type;
}

ShLineMemento::ShLineMemento() {
	
	
}

ShLineMemento::~ShLineMemento() {
	
	if (this->data != 0)
		delete this->data;

}

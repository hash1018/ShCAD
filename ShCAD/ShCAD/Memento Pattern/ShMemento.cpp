

#include "ShMemento.h"
#include "ShUndoCommand.h"

ShMemento::ShMemento()
	:status(MementoUnknown) {

	this->entity = 0;

}

ShMemento::~ShMemento() {

}

void ShMemento::SetStatus(MementoStatus status) {

	this->status = status;
}

ShLineMemento::ShLineMemento() {

}

ShLineMemento::~ShLineMemento() {

}

void ShLineMemento::SetData(const ShLineData &data) {

	this->data = data;
}

ShLineData& ShLineMemento::GetData() {

	return this->data;
}

void ShLineMemento::Accept(ShUndoCommand *command) {
	
	command->Undo(this);
}


#include "ShUndoTaker.h"

ShUndoTaker::ShUndoTaker() {

}

ShUndoTaker::~ShUndoTaker() {

	while (!this->IsEmpty())
		delete this->pop();

}

void ShUndoTaker::Push(ShMemento *memento) {

	this->stack.push(memento);
}

ShMemento* ShUndoTaker::pop() {

	if (this->stack.isEmpty()) {
		qDebug("Stack is empty");
		return 0;
	}

	return this->stack.pop();
}

bool ShUndoTaker::IsEmpty() {

	return this->stack.isEmpty();
}
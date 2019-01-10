

#include "ShRedoTaker.h"
#include "Memento Pattern\ShMemento.h"
ShRedoTaker::ShRedoTaker() {

}

ShRedoTaker::~ShRedoTaker() {

	while (!this->IsEmpty())
		delete this->Pop();

}

void ShRedoTaker::Push(ShMemento *memento) {

	if (this->stack.size() > 30) {
		delete this->stack[0];
		this->stack.pop_front();
	}

	this->stack.push(memento);
}

ShMemento* ShRedoTaker::Pop() {

	if (this->stack.isEmpty()) {
		qDebug("Stack is empty");
		return 0;
	}

	return this->stack.pop();
}

bool ShRedoTaker::IsEmpty() {

	return this->stack.isEmpty();
}

void ShRedoTaker::DeleteAll() {

	while (!this->IsEmpty())
		delete this->Pop();

}

#include "ShTransactionStack.h"
#include "ShTransaction.h"
#include <qdebug.h>

ShTransactionStack::ShTransactionStack() {

}

ShTransactionStack::~ShTransactionStack() {

	while (!this->isEmpty())
		this->pop()->destroy();
}

void ShTransactionStack::push(ShTransaction *transaction) {

	if (this->stack.size() > 50) {
		this->stack[0]->destroy();
		this->stack.pop_front();
	}

	this->stack.push(transaction);
}

ShTransaction* ShTransactionStack::pop() {

	if (this->stack.isEmpty()) {
		qDebug() << "ShCommandStack::pop  stack is empty";
		return nullptr;
	}

	return this->stack.pop();
}

void ShTransactionStack::deleteAll() {

	while (!this->isEmpty())
		this->pop()->destroy();
}
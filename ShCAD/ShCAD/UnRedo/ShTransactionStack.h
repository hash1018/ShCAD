

#ifndef _SHTRANSACTIONSTACK_H
#define _SHTRANSACTIONSTACK_H

#include <qstack.h>
class ShTransaction;

// Command Pattern.

class ShTransactionStack {
	friend class ShCADWidget;
private:
	QStack<ShTransaction*> stack;

public:
	void push(ShTransaction *transaction);
	ShTransaction* pop();

	void deleteAll();

	inline bool isEmpty() const { return this->stack.isEmpty(); }
	inline int getSize() const { return this->stack.size(); }

private:
	ShTransactionStack();
	~ShTransactionStack();
};

#endif //_SHTRANSACTIONSTACK_H
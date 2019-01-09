

#ifndef _SHUNDOTAKER_H
#define _UNDOTAKER_H

#include <qstack.h>
class ShMemento;
class ShUndoTaker {

private:
	QStack<ShMemento*> stack;

public:
	ShUndoTaker();
	~ShUndoTaker();

	void Push(ShMemento *);
	ShMemento* pop();
	bool IsEmpty();

};

#endif //_SHUNDOTAKER_H
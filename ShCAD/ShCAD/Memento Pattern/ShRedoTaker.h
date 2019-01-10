

#ifndef _SHREDOTAKER_H
#define _SHREDOTAKER_H

#include <qstack.h>
class ShMemento;
class ShRedoTaker {

private:
	QStack<ShMemento*> stack;

public:
	ShRedoTaker();
	~ShRedoTaker();

	void Push(ShMemento *);
	ShMemento* Pop();
	bool IsEmpty();

	/* deallocate all items and set empty */
	void DeleteAll();

};

#endif //_SHREDOTAKER_H
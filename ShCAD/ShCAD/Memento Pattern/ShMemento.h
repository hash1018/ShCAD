


#ifndef _SHMEMENTO_H
#define _SHMEMENTO_H

#include "ShVariable.h"

class ShUndoCommand;
class ShRedoCommand;
class ShEntity;
class ShMemento {

	friend class ShUndoCommand;
	friend class ShRedoCommand;

public:
	ShMemento();
	virtual ~ShMemento() = 0;
	void SetType(MementoType type);

protected:
	MementoType type;
	ShEntity *entity;
	
};

class ShLine;
struct ShLineData;
class ShLineMemento : public ShMemento {
	
	friend class ShRedoCommand;
	friend class ShLine;

public:
	~ShLineMemento();
	ShLineMemento();
private:
	
	

private:
	ShLineData *data;


};


#endif //_SHMEMENTO_H
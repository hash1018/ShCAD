


#ifndef _SHMEMENTO_H
#define _SHMEMENTO_H
#include "ShVariable.h"
#include "Entity\ShEntity.h"

class ShUndoCommand;
class ShMemento {

public:
	friend class ShUndoCommand;

	ShMemento();
	virtual ~ShMemento() = 0;
	void SetStatus(MementoStatus status);

	virtual void Accept(ShUndoCommand *command) = 0;

protected:
	MementoStatus status;
	ShEntity *entity;


};


#include "Entity\Leaf\ShLine.h"
class ShLineMemento : public ShMemento {

public:
	~ShLineMemento();
	void Accept(ShUndoCommand *command);

private:

	friend class ShLine;
	ShLineMemento();
	void SetData(const ShLineData &data);
	ShLineData& GetData();


private:

	ShLineData data;

};


#endif //_SHMEMENTO_H
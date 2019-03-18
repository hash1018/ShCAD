

#ifndef _SHMOVEENTITYCOMMAND_H
#define _SHMOVEENTITYCOMMAND_H

#include "Command Pattern\ShCommand.h"
#include <qlinkedlist.h>
#include "ShPoint.h"
class ShGraphicView;
class ShEntity;
class ShMoveEntityCommand : public ShCommand {

private:
	ShGraphicView *view;
	QLinkedList<ShEntity*> list;
	ShPoint3d dis;

public:
	ShMoveEntityCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& list, const ShPoint3d& dis);
	

	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShMoveEntityCommand();
};


#endif //_SHMOVEENTITYCOMMAND_H
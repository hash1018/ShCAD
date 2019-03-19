

#ifndef _SHCOPYENTITYCOMMAND_H
#define _SHCOPYENTITYCOMMAND_H

#include "Command Pattern\ShCommand.h"
#include <qlinkedlist.h>
class ShGraphicView;
class ShEntity;
class ShCopyEntityCommand : public ShCommand {

private:
	ShGraphicView *view;
	QLinkedList<ShEntity*> copiedEntityList;
	bool mustDeallocateEntities;

public:
	ShCopyEntityCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& copiedEntityList);

	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShCopyEntityCommand();

};

#endif //_SHCOPYENTITYCOMMAND_H
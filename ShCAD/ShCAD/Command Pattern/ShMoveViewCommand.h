

#ifndef _SHMOVEVIEWCOMMAND_H
#define _SHMOVEVIEWCOMMAND_H

#include "ShCommand.h"

class ShGraphicView;
class ShMoveViewMemento;
class ShMoveViewCommand : public ShCommand {

private:
	ShGraphicView *view;

public:
	ShMoveViewCommand(ShGraphicView *view, ShMoveViewMemento *memento);
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShMoveViewCommand();



};

#endif //_SHMOVEVIEWCOMMAND_H
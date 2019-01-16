

#ifndef _SHDELETEENTITYCOMMAND_H
#define _SHDELETEENTITYCOMMAND_H

#include "ShCommand.h"

class ShGraphicView;
class ShDeletedEntitiesMemento;
class ShDeleteEntityCommand : public ShCommand {

private:
	ShGraphicView *graphicView;

public:
	ShDeleteEntityCommand(ShGraphicView *view, ShDeletedEntitiesMemento *memento);
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShDeleteEntityCommand();


};

#endif //_SHDELETEENTITYCOMMAND_H



#ifndef _SHREDOCOMMAND_H
#define _SHREDOCOMMAND_H

#include "ShCommand.h"
class ShGraphicView;
class ShMemento;
class ShRedoCommand :public ShCommand{

private:
	ShGraphicView *graphicView;
	ShMemento *memento;

public:
	ShRedoCommand(ShGraphicView *view, ShMemento *memento);
	~ShRedoCommand();

	virtual void Execute();

};

#endif //_SHREDOCOMMAND_H


#ifndef _SHUNDOCOMMAND_H
#define _SHUNDOCOMMAND_H

#include "ShCommand.h"

class ShGraphicView;
class ShMemento;
class ShUndoCommand : public ShCommand{

private:
	ShGraphicView *graphicView;
	ShMemento *memento;

public:
	ShUndoCommand(ShGraphicView *view, ShMemento *memento);
	~ShUndoCommand();

	virtual void Execute();

};

#endif //_SHUNDOCOMMAND_H
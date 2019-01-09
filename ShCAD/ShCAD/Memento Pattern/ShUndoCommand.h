

#ifndef _SHUNDOCOMMAND_H
#define _SHUNDOCOMMAND_H

class ShGraphicView;
class ShLineMemento;
class ShUndoCommand {

private:
	ShGraphicView *graphicView;

public:
	ShUndoCommand(ShGraphicView *view);
	~ShUndoCommand();

	void Undo(ShLineMemento *memento);

};

#endif //_SHUNDOCOMMAND_H
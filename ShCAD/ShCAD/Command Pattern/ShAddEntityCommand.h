

#ifndef _SHADDENTITYCOMMAND_H
#define _SHADDENTITYCOMMAND_H

#include "ShCommand.h"

class ShGraphicView;
class ShEntityMemento;
class ShAddEntityCommand : public ShCommand {

private:
	ShGraphicView *graphicView;

public:
	ShAddEntityCommand(ShGraphicView *view, ShEntityMemento *memento);
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShAddEntityCommand();

	
};

#endif //_SHADDENTITYCOMMAND_H
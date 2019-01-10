

#ifndef _SHADDENTITYCOMMAND_H
#define _SHADDENTITYCOMMAND_H

#include "ShCommand.h"

class ShGraphicView;
class ShEntity;
class ShAddEntityCommand : public ShCommand {

private:
	ShGraphicView *graphicView;
	ShEntity *newEntity;

public:
	ShAddEntityCommand(ShGraphicView *view, ShEntity *newEntity);
	~ShAddEntityCommand();

	virtual void Execute();
};

#endif //_SHADDENTITYCOMMAND_H
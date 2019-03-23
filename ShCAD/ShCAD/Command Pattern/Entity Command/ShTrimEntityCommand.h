
#ifndef _SHTRIMENTITYCOMMAND_H
#define _SHTRIMENTITYCOMMAND_H

#include "Command Pattern\ShCommand.h"
class ShEntity;
class ShGraphicView;
class ShTrimEntityCommand : public ShCommand {

private:
	ShGraphicView *view;
	ShEntity *original;
	ShEntity *trimedEntity;
	ShEntity *trimedEntity2;
	bool mustDeallocateOriginal;
	bool mustDeallocateTrimedEntity;

public:
	ShTrimEntityCommand(ShGraphicView *view, ShEntity *original, ShEntity *trimedEntity, ShEntity *trimedEntity2 = 0);
	
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShTrimEntityCommand();

};

#endif //_SHTRIMENTITYCOMMAND_H
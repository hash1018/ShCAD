
#ifndef _SHEXTENDENTITYCOMMAND_H
#define _SHEXTENDENTITYCOMMAND_H

#include "Command Pattern\ShCommand.h"
class ShEntity;
class ShGraphicView;
class ShExtendEntityCommand :public ShCommand {

private:
	ShGraphicView *view;
	ShEntity *original;
	ShEntity *extendedEntity;
	bool mustDeallocateOriginal;
	bool mustDeallocateExtended;
	

public:
	ShExtendEntityCommand(ShGraphicView *view, ShEntity *original, ShEntity *extendedEntity);
	
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShExtendEntityCommand();

};

#endif //_SHEXTENDENTITYCOMMAND_H
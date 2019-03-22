
#ifndef _SHEXTENDENTITYCOMMAND_H
#define _SHEXTENDENTITYCOMMAND_H

#include "Command Pattern\ShCommand.h"
class ShEntity;
class ShGraphicView;
class ShEntityData;
class ShExtendEntityCommand :public ShCommand {

private:
	ShGraphicView *view;
	ShEntity *entityToExtend;
	ShEntityData *original;
	ShEntityData *extendedData;

public:
	ShExtendEntityCommand(ShGraphicView *view, ShEntity *entityToExtend, ShEntityData *original, ShEntityData *extededData);
	
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShExtendEntityCommand();

};

#endif //_SHEXTENDENTITYCOMMAND_H
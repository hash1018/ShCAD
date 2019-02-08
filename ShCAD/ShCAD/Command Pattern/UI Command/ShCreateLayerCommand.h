

#ifndef _SHCREATELAYERCOMMAND_H
#define _SHCREATELAYERCOMMAND_H

#include "Command Pattern\ShCommand.h"
class ShGraphicView;
class ShLayerMemento;
class ShLayer;
class ShCreateLayerCommand : public ShCommand {

private:
	ShGraphicView *view;
	ShLayer *layer;
	bool mustDeallocateLayer;

public:
	ShCreateLayerCommand(ShGraphicView *view, ShLayer *layer);
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShCreateLayerCommand();

};

#endif //_SHCREATELAYERCOMMAND_H
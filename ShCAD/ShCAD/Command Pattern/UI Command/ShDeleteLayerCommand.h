

#ifndef _SHDELETELAYERCOMMAND_H
#define _SHDELETELAYERCOMMAND_H

#include "Command Pattern\ShCommand.h"
class ShGraphicView;
class ShLayer;
class ShDeleteLayerCommand : public ShCommand {

private:
	ShGraphicView *view;
	ShLayer *layer;
	bool mustDeallocateLayer;

public:
	ShDeleteLayerCommand(ShGraphicView *view, ShLayer *layer);
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShDeleteLayerCommand();

};

#endif //_SHCREATELAYERCOMMAND_H
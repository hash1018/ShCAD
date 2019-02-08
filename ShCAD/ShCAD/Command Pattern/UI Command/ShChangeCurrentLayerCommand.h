


#ifndef _SHCHANGECURRENTLAYERCOMMAND_H
#define _SHCHANGECURRENTLAYERCOMMAND_H

#include "Command Pattern\ShCommand.h"

class ShGraphicView;
class ShLayer;
class ShChangeCurrentLayerCommand : public ShCommand {

private:
	ShGraphicView *view;
	ShLayer *previousLayer;
	ShLayer *currentLayer;

public:
	ShChangeCurrentLayerCommand(ShGraphicView *view, ShLayer *previousLayer, ShLayer *currentLayer);
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShChangeCurrentLayerCommand();

};

#endif //_SHCHANGECURRENTLAYERCOMMAND_H
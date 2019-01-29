

#ifndef _SHCHANGELAYERDATACOMMAND_H
#define _SHCHANGELAYERDATACOMMAND_H

#include "ShCommand.h"

class ShGraphicView;
class ShLayer;
class ShLayerMemento;
class ShChangeLayerDataCommand : public ShCommand {

private:
	ShGraphicView *view;
	ShLayer *changedLayer;
	
public:
	ShChangeLayerDataCommand(ShGraphicView *view, ShLayer *changedLayer, ShLayerMemento *memento);
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShChangeLayerDataCommand();



};


#endif //_SHCHANGELAYERDATACOMMAND_H
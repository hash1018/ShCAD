

#ifndef _SHCHANGEENTITYLAYER_H
#define _SHCHANGEENTITYLAYER_H

#include "ShCommand.h"
class ShGraphicView;
class ShLayer;
class ShCompositeEntityMemento;
class ShChangeEntityLayerCommand : public ShCommand {

private:
	ShGraphicView *view;
	ShLayer *changedLayer;
	
public:
	ShChangeEntityLayerCommand(ShGraphicView *view, ShCompositeEntityMemento *memento, ShLayer *changedLayer);
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShChangeEntityLayerCommand();

};

#endif //_SHCHANGEENTITYLAYER_H
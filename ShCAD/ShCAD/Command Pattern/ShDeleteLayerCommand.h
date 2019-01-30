

#ifndef _SHDELETELAYERCOMMAND_H
#define _SHDELETELAYERCOMMAND_H

#include "ShCommand.h"
class ShGraphicView;
class ShLayerMemento;
class ShDeleteLayerCommand : public ShCommand {

private:
	ShGraphicView *view;

public:
	ShDeleteLayerCommand(ShGraphicView *view, ShLayerMemento* memento);
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShDeleteLayerCommand();

};

#endif //_SHCREATELAYERCOMMAND_H
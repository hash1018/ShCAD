

#ifndef _SHCREATELAYERCOMMAND_H
#define _SHCREATELAYERCOMMAND_H

#include "ShCommand.h"
class ShGraphicView;
class ShLayerMemento;
class ShCreateLayerCommand : public ShCommand {

private:
	ShGraphicView *view;

public:
	ShCreateLayerCommand(ShGraphicView *view, ShLayerMemento* memento);
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShCreateLayerCommand();

};

#endif //_SHCREATELAYERCOMMAND_H


#ifndef _SHCHANGELAYERDATACOMMAND_H
#define _SHCHANGELAYERDATACOMMAND_H

#include "ShCommand.h"

class ShGraphicView;
class ShLayer;
class ShLayerMemento;
class ShChangeLayerDataCommand : public ShCommand {

public:
	enum ChangedType {
		State = 0,
		Name = 1,
		TurnOnOff = 2,
		Color = 3,
		LineStyle = 4
	};


private:
	ShGraphicView *view;
	ShLayer *changedLayer;
	ChangedType type;
	
public:
	ShChangeLayerDataCommand(ShGraphicView *view, ShLayer *changedLayer, ShLayerMemento *memento, 
		ShChangeLayerDataCommand::ChangedType type);
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShChangeLayerDataCommand();



};


#endif //_SHCHANGELAYERDATACOMMAND_H
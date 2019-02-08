

#ifndef _SHCHANGEPROPERTYCOLORCOMMAND_H
#define _SHCHANGEPROPERTYCOLORCOMMAND_H

#include "Command Pattern\ShCommand.h"
#include "ShPropertyData.h"
class ShGraphicView;
class ShChangePropertyDataCommand : public ShCommand {

public:
	enum ChangedType {
		Color=0,
		LineStyle=1,
	};

private:
	ShGraphicView *view;
	ShPropertyData prev;
	ShPropertyData current;
	ChangedType type;

public:
	ShChangePropertyDataCommand(ShGraphicView *view, const ShPropertyData& prev, const ShPropertyData& current, ChangedType type);
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShChangePropertyDataCommand();



};

#endif //_SHCHANGEPROPERTYCOLORCOMMAND_H
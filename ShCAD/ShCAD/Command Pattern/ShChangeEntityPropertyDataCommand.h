

#ifndef _SHCHANGEENTITYPROPERTYDATACOMMAND_H
#define _SHCHANGEENTITYPROPERTYDATACOMMAND_H

#include "ShCommand.h"
#include "ShPropertyData.h"

class ShGraphicView;
class ShCompositeEntityMemento;
class ShChangeEntityPropertyDataCommand : public ShCommand {
public:
	enum ChangedType {
		Color=0,
		LineStyle=1,
	};

private:
	ChangedType type;
	ShGraphicView *view;
	ShColor color;
	ShLineStyle lineStyle;

public:
	ShChangeEntityPropertyDataCommand(ShGraphicView *view, ShCompositeEntityMemento *memento, const ShColor& color);
	ShChangeEntityPropertyDataCommand(ShGraphicView *view, ShCompositeEntityMemento *memento, const ShLineStyle& lineStyle);

	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShChangeEntityPropertyDataCommand();



};

#endif //_SHCHANGEENTITYPROPERTYDATACOMMAND_H
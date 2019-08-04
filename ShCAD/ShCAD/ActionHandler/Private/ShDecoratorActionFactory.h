
#ifndef _SHDECORATORACTIONFACTORY_H
#define _SHDECORATORACTIONFACTORY_H

#include "Base\ShVariable.h"

class ShDecoratorAction;
class ShActionHandler;
class ShCADWidget;
class DraftData;

class ShDecoratorActionFactory {

public:
	ShDecoratorActionFactory();
	~ShDecoratorActionFactory();

	static ShDecoratorAction* create(ShCADWidget *widget, ShActionHandler *actionHandler, const DraftData &draftData);

private:
	static ShDecoratorAction* createLineActionPerpendicular(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child);
};

#endif //_SHDECORATORACTIONFACTORY_H
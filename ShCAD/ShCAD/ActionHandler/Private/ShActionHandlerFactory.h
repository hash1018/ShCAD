
#ifndef _SHACTIONHANDLERFACTORY_H
#define _SHACTIONHANDLERFACTORY_H

#include "Base\ShVariable.h"

class ShActionHandler;
class ShCADWidget;

class ShActionHandlerFactory {

public:
	ShActionHandlerFactory();
	~ShActionHandlerFactory();

	static ShActionHandler* create(ActionType actionType, ShCADWidget *widget);

};

#endif //_SHACTIONHANDLERFACTORY_H
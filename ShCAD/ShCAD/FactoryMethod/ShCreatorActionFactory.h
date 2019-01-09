

#ifndef _SHCREATORACTIONFACTORY_H
#define _SHCREATORACTIONFACTORY_H

#include "ShVariable.h"

class ShActionHandler;
class ShGraphicView;
class ShCreatorActionFactory {

public:
	ShCreatorActionFactory();
	~ShCreatorActionFactory();

	static ShActionHandler* Create(ActionType actionType, ShGraphicView *graphicView);


};

#endif //_SHCREATORACTIONFACTORY_H
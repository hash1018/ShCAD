

#ifndef _SHCREATORACTIONDECORATORFACTORY_H
#define _SHCREATORACTIONDECORATORFACTORY_H

#include "ShVariable.h"

class ShActionHandlerDecorator;
class ShGraphicView;
class ShActionHandler;
class ShDraftFlag;
class ShCreatorActionDecoratorFactory {

public:
	ShCreatorActionDecoratorFactory();
	~ShCreatorActionDecoratorFactory();

	static ShActionHandlerDecorator* Create(ShGraphicView *graphicView, ShActionHandler *actionHandler, const ShDraftFlag& flag, ObjectSnap disposableSnap);

};

#endif //_SHCREATORACTIONDECORATORFACTORY_H

#ifndef _SHDECORATORACTIONFACTORY_H
#define _SHDECORATORACTIONFACTORY_H

#include "Base\ShVariable.h"

class ShDecoratorAction;
class ShActionHandler;
class ShCADWidget;
class ShDraftData;

class ShDecoratorActionFactory {

public:
	ShDecoratorActionFactory();
	~ShDecoratorActionFactory();

	static ShDecoratorAction* create(ShCADWidget *widget, ShActionHandler *actionHandler, const ShDraftData &draftData);

	static ShDecoratorAction* addOrthgonal(ShCADWidget *widget, ShActionHandler *actionHandler, 
		ShDecoratorAction *decoratorAction, const ShDraftData &draftData);

	static ShDecoratorAction* removeOrthgonal(ShCADWidget *widget, ShDecoratorAction *decoratorAction, const ShDraftData &draftData);

	static ShDecoratorAction* addDisposableSnap(ShCADWidget *widget, ShActionHandler *actionHandler, 
		ShDecoratorAction *decoratorAction, const ShDraftData &draftData);

	static ShDecoratorAction* removeDisposableSnap(ShCADWidget *widget, ShDecoratorAction *decoratorAction, const ShDraftData &draftData);

};

class ShDisposableSnapActionFactory {
	
	friend class ShDecoratorActionFactory;

private:
	ShDisposableSnapActionFactory();
	~ShDisposableSnapActionFactory();

	static ShDecoratorAction* create(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child, ObjectSnap objectSnap);

private:
	static ShDecoratorAction* createLineActionPerpendicular(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child);
	static ShDecoratorAction* createDisposableSnap(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child, ObjectSnap objectSnap);
};

#endif //_SHDECORATORACTIONFACTORY_H
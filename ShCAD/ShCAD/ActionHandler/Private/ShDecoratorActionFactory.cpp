
#include "ShDecoratorActionFactory.h"
#include "ActionHandler\DecoratorAction\ShDecoratorDefaultAction.h"
#include "ActionHandler\DecoratorAction\ShOrthogonalAction.h"
#include "Data\DraftData.h"
#include "ActionHandler\DecoratorAction\ShDisposableSnapAction.h"


ShDecoratorActionFactory::ShDecoratorActionFactory() {

}

ShDecoratorActionFactory::~ShDecoratorActionFactory() {

}

ShDecoratorAction* ShDecoratorActionFactory::create(ShCADWidget *widget, ShActionHandler *actionHandler, const DraftData &draftData) {

	ShDecoratorAction *decoratorAction = new ShDecoratorDefaultAction(widget, actionHandler);

	if (draftData.getOrthMode() == true)
		decoratorAction = new ShOrthogonalAction(widget, actionHandler, decoratorAction);


	if (draftData.getDisposableSnap() == ObjectSnap::ObjectSnapNothing) {
	
	}

	else if (draftData.getDisposableSnap() == ObjectSnap::ObjectSnapEndPoint) {
	
		decoratorAction = new ShDisposableSnapAction_General(widget, actionHandler, draftData.getDisposableSnap(), decoratorAction);
	}

	return decoratorAction;
}

#include "ShDecoratorActionFactory.h"
#include "ActionHandler\DecoratorAction\ShDecoratorDefaultAction.h"
#include "ActionHandler\DecoratorAction\ShOrthogonalAction.h"
#include "Data\DraftData.h"
#include "ActionHandler\DecoratorAction\ShDisposableSnapAction.h"
#include "ActionHandler\DrawAction\ShDrawLineAction.h"


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

	else if (draftData.getDisposableSnap() == ObjectSnap::ObjectSnapEndPoint ||
		draftData.getDisposableSnap() == ObjectSnap::ObjectSnapMidPoint ||
		draftData.getDisposableSnap() == ObjectSnap::ObjectSnapCenter ||
		draftData.getDisposableSnap() == ObjectSnap::ObjectSnapQuadrant) {

		decoratorAction = new ShDisposableSnapAction_General(widget, actionHandler, draftData.getDisposableSnap(), decoratorAction);
	}
	else if (draftData.getDisposableSnap() == ObjectSnap::ObjectSnapPerpendicular) {
	
		if (dynamic_cast<ShDrawLineAction*>(actionHandler)) {

			decoratorAction = ShDecoratorActionFactory::createLineActionPerpendicular(widget, actionHandler, decoratorAction);
		}
		else {

			decoratorAction = new ShDisposableSnapAction_Perpendicular(widget, actionHandler, decoratorAction);
		}
	}

	return decoratorAction;
}


ShDecoratorAction* ShDecoratorActionFactory::createLineActionPerpendicular(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *parent) {

	return nullptr;
}
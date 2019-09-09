
#include "ShDecoratorActionFactory.h"
#include "ActionHandler\DecoratorAction\ShDecoratorDefaultAction.h"
#include "ActionHandler\DecoratorAction\ShOrthogonalAction.h"
#include "Data\ShDraftData.h"
#include "ActionHandler\DecoratorAction\ShDisposableSnapAction.h"
#include "ActionHandler\DrawAction\ShDrawLineAction.h"
#include <qdebug.h>
#include "ActionHandler\DecoratorAction\UnusualDecoratorAction\ShDisposablePerSnapLineAction.h"
#include "ActionHandler\DecoratorAction\UnusualDecoratorAction\ShDisposableExtensionSnapAction.h"

ShDecoratorActionFactory::ShDecoratorActionFactory() {

}

ShDecoratorActionFactory::~ShDecoratorActionFactory() {

}

ShDecoratorAction* ShDecoratorActionFactory::create(ShCADWidget *widget, ShActionHandler *actionHandler, const ShDraftData &draftData) {

	ShDecoratorAction *decoratorAction = new ShDecoratorDefaultAction(widget, actionHandler);

	if (draftData.getOrthMode() == true)
		decoratorAction = new ShOrthogonalAction(widget, actionHandler, decoratorAction);

	if (draftData.getDisposableSnap() != ObjectSnap::ObjectSnapNothing) {

		decoratorAction = ShDisposableSnapActionFactory::create(widget, actionHandler, decoratorAction, draftData.getDisposableSnap());
	}


	return decoratorAction;
}


ShDecoratorAction* ShDecoratorActionFactory::addOrthgonal(ShCADWidget *widget, ShActionHandler *actionHandler,
	ShDecoratorAction *decoratorAction, const ShDraftData &draftData) {

	if (draftData.getOrthMode() == false)
		Q_ASSERT("ShDecoratorActionFactory::addOrthgonal() orthMode is not available.");

	if (draftData.getDisposableSnap() != ObjectSnap::ObjectSnapNothing) {
	
		ShDecoratorAction *child = decoratorAction->getChild();
		
		ShOrthogonalAction *orthAction = new ShOrthogonalAction(widget, actionHandler, child);
		orthAction->setParent(decoratorAction);
		decoratorAction->setChild(orthAction);

	}
	else {
	
		decoratorAction = new ShOrthogonalAction(widget, actionHandler, decoratorAction);
	}

	return decoratorAction;
}

ShDecoratorAction* ShDecoratorActionFactory::removeOrthgonal(ShCADWidget *widget, ShDecoratorAction *decoratorAction, const ShDraftData &draftData) {

	if (draftData.getOrthMode() == true)
		Q_ASSERT("ShDecoratorActionFactory::removeOrthgonal() orthMode is not available.");

	if (draftData.getDisposableSnap() != ObjectSnap::ObjectSnapNothing) {
	
		ShDecoratorAction *child = decoratorAction->getChild();
		ShDecoratorAction *descendant = child->getChild();

		descendant->setParent(decoratorAction);
		decoratorAction->setChild(descendant);

		if (!dynamic_cast<ShOrthogonalAction*>(child))
			Q_ASSERT("ShDecoratorActionFactory::removeOrthgonal() child is not orthAction");
		
		child->setChild(nullptr);
		delete child;
	
	}
	else {
	
		if(!dynamic_cast<ShOrthogonalAction*>(decoratorAction))
			Q_ASSERT("ShDecoratorActionFactory::removeOrthgonal() decoratorAction is not orthAction");

		ShDecoratorAction *parent = decoratorAction;
		ShDecoratorAction *child = parent->getChild();

		parent->setChild(nullptr);
		delete parent;

		decoratorAction = child;
	}

	return decoratorAction;
}

ShDecoratorAction* ShDecoratorActionFactory::addDisposableSnap(ShCADWidget *widget, ShActionHandler *actionHandler,
	ShDecoratorAction *decoratorAction, const ShDraftData &draftData) {

	if (draftData.getDisposableSnap() == ObjectSnap::ObjectSnapNothing)
		Q_ASSERT("ShDecoratorActionFactory::addDisposableSnap() DisposableSnap is not available.");

	return ShDisposableSnapActionFactory::create(widget, actionHandler, decoratorAction, draftData.getDisposableSnap());
}

ShDecoratorAction* ShDecoratorActionFactory::removeDisposableSnap(ShCADWidget *widget, ShDecoratorAction *decoratorAction, const ShDraftData &draftData) {

	if (draftData.getDisposableSnap() != ObjectSnap::ObjectSnapNothing)
		Q_ASSERT("ShDecoratorActionFactory::removeDisposableSnap() there'no disposableSnapAction to delete.");

	if(!dynamic_cast<ShDisposableSnapAction*>(decoratorAction))
		Q_ASSERT("ShDecoratorActionFactory::removeDisposableSnap() decoratorAction is not disposableSnapAction.");

	ShDecoratorAction *disposableSnap = decoratorAction;
	ShDecoratorAction *child = decoratorAction->getChild();

	disposableSnap->setChild(nullptr);
	delete disposableSnap;

	child->setParent(nullptr);

	return child;
}


///////////////////////////////////////////////////////////////////////////////////////////

ShDisposableSnapActionFactory::ShDisposableSnapActionFactory() {

}

ShDisposableSnapActionFactory::~ShDisposableSnapActionFactory() {

}

ShDecoratorAction* ShDisposableSnapActionFactory::create(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child, ObjectSnap objectSnap) {

	ShDecoratorAction *decoratorAction = child;

	if (objectSnap == ObjectSnap::ObjectSnapPerpendicular &&
		dynamic_cast<ShDrawLineAction*>(actionHandler)) {

		decoratorAction = ShDisposableSnapActionFactory::createLineActionPerpendicular(widget, actionHandler, decoratorAction);
	}
	else {

		decoratorAction = ShDisposableSnapActionFactory::createDisposableSnap(widget, actionHandler, decoratorAction, objectSnap);
	}

	return decoratorAction;
}



ShDecoratorAction* ShDisposableSnapActionFactory::createLineActionPerpendicular(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child) {

	ShDecoratorAction *decoratorAction;

	ShDrawLineAction *drawLineAction = dynamic_cast<ShDrawLineAction*>(actionHandler);
	ShDrawLineAction::Status status = drawLineAction->getStatus();
	ShDrawLineAction::SubAction subAction = drawLineAction->getSubAction();

	if (status == ShDrawLineAction::Status::PickedStart &&
		subAction == ShDrawLineAction::SubAction::Default) {

		decoratorAction = new ShDisposableSnapAction_Perpendicular(widget, actionHandler, child);
	}
	else if (status == ShDrawLineAction::Status::PickedNothing &&
		subAction == ShDrawLineAction::SubAction::Default) {

		decoratorAction = new ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing(widget, actionHandler, child);
	}
	else if (status == ShDrawLineAction::Status::PickedStart &&
		subAction == ShDrawLineAction::SubAction::Perpendicular) {

		decoratorAction = new ShDisposableSnapAction_DrawLineActionPerPer(widget, actionHandler, child);
	}
	else {

		Q_ASSERT("ShDecoratorActionFactory::createLineActionPerpendicular() this can't be happend.");
	}

	return decoratorAction;
}

ShDecoratorAction* ShDisposableSnapActionFactory::createDisposableSnap(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child, ObjectSnap objectSnap) {

	ShDecoratorAction *decoratorAction = nullptr;

	if (objectSnap == ObjectSnap::ObjectSnapEndPoint)
		decoratorAction = new ShDisposableSnapAction_End(widget, actionHandler, child);
	else if (objectSnap == ObjectSnap::ObjectSnapMidPoint)
		decoratorAction = new ShDisposableSnapAction_Mid(widget, actionHandler, child);
	else if (objectSnap == ObjectSnap::ObjectSnapCenter)
		decoratorAction = new ShDisposableSnapAction_Center(widget, actionHandler, child);
	else if (objectSnap == ObjectSnap::ObjectSnapQuadrant)
		decoratorAction = new ShDisposableSnapAction_Quadrant(widget, actionHandler, child);
	else if (objectSnap == ObjectSnap::ObjectSnapIntersection)
		decoratorAction = new ShDisposableSnapAction__Intersection(widget, actionHandler, child);
	else if (objectSnap == ObjectSnap::ObjectSnapAppraentIntersection)
		decoratorAction = new ShDisposableSnapAction_ApparentIntersection(widget, actionHandler, child);
	else if (objectSnap == ObjectSnap::ObjectSnapExtension)
		decoratorAction = new ShDisposableExtensionSnapAction(widget, actionHandler, child);

	if (decoratorAction == nullptr)
		Q_ASSERT("ShDisposableSnapActionFactory::createDisposableSnap() decoratorAction is nullptr.");

	return decoratorAction;
}
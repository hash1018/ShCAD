

#include "ShCreatorActionDecoratorFactory.h"
#include "ShDraft.h"
#include "ActionHandler\ShActionHandlerDecorator.h"
#include "ActionHandler\DrawAction\ShDrawLineAction.h"
ShCreatorActionDecoratorFactory::ShCreatorActionDecoratorFactory() {

}

ShCreatorActionDecoratorFactory::~ShCreatorActionDecoratorFactory() {

}

ShActionHandlerDecorator* ShCreatorActionDecoratorFactory::Create(ShGraphicView *view, ShActionHandler *actionHandler,
	const ShDraftFlag& flag, ObjectSnap disposableSnap) {

	ShActionHandlerDecorator *decorator = new ShActionHandlerDecorator_Default(view, actionHandler);

	if (flag.AcceptOrthogonal() == true)
		decorator = new ShActionHandlerDecorator_Orthogonal(view, actionHandler, decorator);
	
	
	if (disposableSnap == ObjectSnap::ObjectSnapNothing) {

	}

	else if (disposableSnap == ObjectSnap::ObjectSnapEndPoint ||
		disposableSnap == ObjectSnap::ObjectSnapMidPoint ||
		disposableSnap == ObjectSnap::ObjectSnapCenter ||
		disposableSnap == ObjectSnap::ObjectSnapQuadrant) {

		decorator = new ShActionHandlerDecorator_DisposableSnap_General(view,
			actionHandler, disposableSnap, decorator);
	}

	else if (disposableSnap == ObjectSnap::ObjectSnapPerpendicular) {
	
		if (dynamic_cast<ShDrawLineAction*>(actionHandler)) {
			
			ShDrawLineAction *drawLineAction = dynamic_cast<ShDrawLineAction*>(actionHandler);
			ShDrawLineAction::Status status = drawLineAction->GetStatus();
			ShDrawLineAction::DrawMethod method = drawLineAction->GetDrawMethod();

			if (status == ShDrawLineAction::Status::PickedStart &&
				method == ShDrawLineAction::DrawMethod::Default) {
				
				decorator = new ShActionHandlerDecorator_DisposableSnap_Perpendicular(view,
					actionHandler, decorator);
			}
			else if (status == ShDrawLineAction::Status::PickedNothing &&
				method == ShDrawLineAction::DrawMethod::Default) {
			
				decorator = new ShDrawLineAction_DisposableSnap_Perpendicular_PickedNothing(view,
					actionHandler, decorator);
			}
			else if (status == ShDrawLineAction::Status::PickedStart &&
				method == ShDrawLineAction::DrawMethod::Perpendicular) {
			
				decorator = new ShDrawLineAction_DisposableSnap_Per_Per(view, actionHandler, decorator);
			}
		}
		else {
			decorator = new ShActionHandlerDecorator_DisposableSnap_Perpendicular(view,
				actionHandler, decorator);
		}
	}


	return decorator;
}
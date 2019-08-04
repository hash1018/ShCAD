
#include "ShDisposableSnapAction.h"
#include "ObjectSnap\ShSearchSnapPointStrategy.h"
#include "ObjectSnap\ShSearchSnapPointStrategyFactory.h"
#include "ActionHandler\Private\ShDecorateActionStrategy.h"

ShDisposableSnapAction::ShDisposableSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ObjectSnap objectSnap, ShDecoratorAction *child)
	:ShDecoratorAction(widget, actionHandler, child), strategy(nullptr) {

	this->strategy = ShSearchSnapPointStrategyFactory::create(objectSnap, widget);

}

ShDisposableSnapAction::~ShDisposableSnapAction() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShDisposableSnapAction::keyPressEvent(ShActionData &data) {

	ShDecoratorAction::keyPressEvent(data);
}

void ShDisposableSnapAction::draw(QPainter *painter) {

	this->strategy->draw(painter);

	ShDecoratorAction::draw(painter);

}

void ShDisposableSnapAction::finishDisposableSnap() {

	ShDecorateDisposableSnapActionStrategy strategy(ObjectSnap::ObjectSnapNothing);
	this->widget->changeAction(strategy);
}


/////////////////////////////////////////////////////////////////

ShDisposableSnapAction_General::ShDisposableSnapAction_General(ShCADWidget *widget, ShActionHandler *actionHandler, ObjectSnap objectSnap, ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, objectSnap, child) {

}


ShDisposableSnapAction_General::~ShDisposableSnapAction_General() {


}

void ShDisposableSnapAction_General::mouseLeftPressEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
	
		if (this->strategy->search(data.point) == false) {
		
			this->finishDisposableSnap();
			return;
		}

		data.point = this->strategy->getSnap();
		dynamic_cast<ShDecoratorActionData&>(data).snapAccepted = true;

	}

	ShDisposableSnapAction::mouseLeftPressEvent(data);

	this->finishDisposableSnap();
}

void ShDisposableSnapAction_General::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->strategy->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction_General::invalidate(ShPoint3d point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->strategy->search(point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(point);
}

////////////////////////////////////////////////////////////////////////


ShDisposableSnapAction_Perpendicular::ShDisposableSnapAction_Perpendicular(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, ObjectSnap::ObjectSnapPerpendicular, child) {

}

ShDisposableSnapAction_Perpendicular::~ShDisposableSnapAction_Perpendicular() {

}


void ShDisposableSnapAction_Perpendicular::mouseLeftPressEvent(ShActionData &data) {

}

void ShDisposableSnapAction_Perpendicular::mouseMoveEvent(ShActionData &data) {

}

void ShDisposableSnapAction_Perpendicular::invalidate(ShPoint3d point) {


}


///////////////////////////////////////////////////////////////////


ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing(ShCADWidget *widget, ShActionHandler *actionHandler,
	ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, ObjectSnap::ObjectSnapPerpendicular, child) {

}

ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::~ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing() {

}

void ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::mouseLeftPressEvent(ShActionData &data) {

}

void ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::mouseMoveEvent(ShActionData &data) {

}

void ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::invalidate(ShPoint3d point) {

}


///////////////////////////////////////////////////////////////////////

ShDisposableSnapAction_DrawLineActionPerPer::ShDisposableSnapAction_DrawLineActionPerPer(ShCADWidget *widget, ShActionHandler *actionHandler,
	ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, ObjectSnap::ObjectSnapPerpendicular, child) {

}

ShDisposableSnapAction_DrawLineActionPerPer::~ShDisposableSnapAction_DrawLineActionPerPer() {

}

void ShDisposableSnapAction_DrawLineActionPerPer::mouseLeftPressEvent(ShActionData &data) {

}

void ShDisposableSnapAction_DrawLineActionPerPer::mouseMoveEvent(ShActionData &data) {

}

void ShDisposableSnapAction_DrawLineActionPerPer::invalidate(ShPoint3d point) {

}
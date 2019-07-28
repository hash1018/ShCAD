
#include "ShDisposableSnapAction.h"
#include "ObjectSnap\ShSearchSnapPointStrategy.h"

ShDisposableSnapAction::ShDisposableSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ObjectSnap objectSnap, ShDecoratorAction *child)
	:ShDecoratorAction(widget, actionHandler, child), strategy(nullptr) {

	if (objectSnap == ObjectSnap::ObjectSnapEndPoint)
		this->strategy = new ShSearchSnapPointStrategy_End(widget);


	//else if (objectSnap == ObjectSnap::ObjectSnapMidPoint)
	//	new ShObjectSnapStrategy_MidPoint(view);
	//else if (objectSnap == ObjectSnap::ObjectSnapPerpendicular)
	//	return new ShObjectSnapStrategy_Perpendicular(view);
	//else if (objectSnap == ObjectSnap::ObjectSnapCenter)
	//	return new ShObjectSnapStrategy_Center(view);
	//else if (objectSnap == ObjectSnap::ObjectSnapQuadrant)
	//	return new ShObjectSnapStrategy_Quadrant(view);


	//return new ShObjectSnapStrategy_Nothing(view);

	else
		this->strategy = new ShSearchSnapPointStrategy_Nothing(widget);

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
		
			return;
		}

		data.point = this->strategy->getSnap();

	}

	ShDecoratorAction::mouseLeftPressEvent(data);
}

void ShDisposableSnapAction_General::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->strategy->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDecoratorAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction_General::invalidate(ShPoint3d point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->strategy->search(point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDecoratorAction::invalidate(point);
}
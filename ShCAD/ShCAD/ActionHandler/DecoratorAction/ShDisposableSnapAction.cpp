
#include "ShDisposableSnapAction.h"
#include "ObjectSnap\ShSearchSnapPointStrategy.h"
#include "ObjectSnap\ShSearchSnapPointStrategyFactory.h"

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
		
			this->widget->setDisposableSnap(ObjectSnap::ObjectSnapNothing);
			return;
		}

		data.point = this->strategy->getSnap();
		dynamic_cast<ShDecoratorActionData&>(data).snapAccepted = true;

	}

	ShDisposableSnapAction::mouseLeftPressEvent(data);

	this->widget->setDisposableSnap(ObjectSnap::ObjectSnapNothing);
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
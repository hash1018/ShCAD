
#include "ShDisposableSnapAction.h"
#include "ObjectSnap\ShSearchSnapPointStrategy.h"
#include "ObjectSnap\ShSearchSnapPointStrategyFactory.h"
#include "ActionHandler\Private\ShDecorateActionStrategy.h"
#include "ActionHandler\DrawAction\ShDrawLineAction.h"
#include "Entity\Private\ShLineBothPerpendicularVisitor.h"

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

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {

		ShSearchSnapPointStrategy_Perpendicular *strategy = dynamic_cast<ShSearchSnapPointStrategy_Perpendicular*>(this->strategy);
		
		if (strategy->search(data.point, draft.getSnapBasePoint().x, draft.getSnapBasePoint().y) == false) {

			this->finishDisposableSnap();
			return;
		}

		data.point = strategy->getSnap();
		dynamic_cast<ShDecoratorActionData&>(data).snapAccepted = true;

	}

	ShDisposableSnapAction::mouseLeftPressEvent(data);

	this->finishDisposableSnap();
}

void ShDisposableSnapAction_Perpendicular::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {

		ShSearchSnapPointStrategy_Perpendicular *strategy = dynamic_cast<ShSearchSnapPointStrategy_Perpendicular*>(this->strategy);

		if (strategy->search(data.point, draft.getSnapBasePoint().x, draft.getSnapBasePoint().y) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction_Perpendicular::invalidate(ShPoint3d point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {

		ShSearchSnapPointStrategy_Perpendicular *strategy = dynamic_cast<ShSearchSnapPointStrategy_Perpendicular*>(this->strategy);

		if (strategy->search(point, draft.getSnapBasePoint().x, draft.getSnapBasePoint().y) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(point);
}


///////////////////////////////////////////////////////////////////


ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing(ShCADWidget *widget, ShActionHandler *actionHandler,
	ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, ObjectSnap::ObjectSnapPerpendicular, child) {

}

ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::~ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing() {

}

void ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::mouseLeftPressEvent(ShActionData &data) {

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


	ShDrawLineAction* drawLineAction = dynamic_cast<ShDrawLineAction*>(this->actionHandler);
	drawLineAction->changeSubAction(ShDrawLineAction::SubAction::Perpendicular);

	ShSubDrawLineAction_Perpendicular *subLineAction = dynamic_cast<ShSubDrawLineAction_Perpendicular*>(drawLineAction->getSubDrawLineAction());
	ShSearchSnapPointStrategy_Perpendicular *strategy = dynamic_cast<ShSearchSnapPointStrategy_Perpendicular*>(this->strategy);

	subLineAction->setPerpendicularBase(strategy->getPerpendicularBase());

	this->finishDisposableSnap();
}

void ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->strategy->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::invalidate(ShPoint3d point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->strategy->search(point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(point);
}


///////////////////////////////////////////////////////////////////////

ShDisposableSnapAction_DrawLineActionPerPer::ShDisposableSnapAction_DrawLineActionPerPer(ShCADWidget *widget, ShActionHandler *actionHandler,
	ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, ObjectSnap::ObjectSnapPerpendicular, child) {

}

ShDisposableSnapAction_DrawLineActionPerPer::~ShDisposableSnapAction_DrawLineActionPerPer() {

}

void ShDisposableSnapAction_DrawLineActionPerPer::mouseLeftPressEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {

		if (this->strategy->search(data.point) == false) {

			this->finishDisposableSnap();
			return;
		}

		dynamic_cast<ShDecoratorActionData&>(data).snapAccepted = true;
	}


	ShDrawLineAction *drawLineAction = dynamic_cast<ShDrawLineAction*>(this->actionHandler);
	ShSearchSnapPointStrategy_Perpendicular *strategy = dynamic_cast<ShSearchSnapPointStrategy_Perpendicular*>(this->strategy);
	ShSubDrawLineAction_Perpendicular *subDrawLineAction = dynamic_cast<ShSubDrawLineAction_Perpendicular*>(drawLineAction->getSubDrawLineAction());

	bool isValid = false;
	ShPoint3d point = strategy->getSnap();

	ShLineBothPerpendicularVisitor visitor(strategy->getPerpendicularBase(), point, isValid);
	subDrawLineAction->getPerpendicularBase()->accept(&visitor);

	if (isValid == true) {
		data.point = point;
		ShDisposableSnapAction::mouseLeftPressEvent(data);
		this->finishDisposableSnap();
	}
	else {
		//Fail.
	
	}
	
}

void ShDisposableSnapAction_DrawLineActionPerPer::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->strategy->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction_DrawLineActionPerPer::invalidate(ShPoint3d point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->strategy->search(point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(point);
}
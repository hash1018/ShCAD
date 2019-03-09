
#include "ShChangeCurrentActionStrategy.h"
#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
#include "ActionHandler\ShActionHandlerManager.h"
#include "Entity\Composite\ShPreview.h"
#include "ShSelectedEntityManager.h"

ShChangeCurrentActionStrategy::ShChangeCurrentActionStrategy(ActionType newActionType)
	:view(0), newActionType(newActionType) {

}

ShChangeCurrentActionStrategy::~ShChangeCurrentActionStrategy() {

}

ActionType ShChangeCurrentActionStrategy::Change() {

	if (this->newActionType == ActionType::ActionDefault &&
	
		this->view->actionHandlerManager->GetType() == ActionType::ActionDefault)
		return this->newActionType;


	DrawType drawType = DrawType::DrawCaptureImage;

	if (this->view->rubberBand != NULL) {
		delete this->view->rubberBand;
		this->view->rubberBand = NULL;
		drawType = (DrawType)(drawType | DrawType::DrawCaptureImage);
	}

	if (!this->view->preview.IsListEmpty()) {
		this->view->preview.DeleteAll();
		drawType = (DrawType)(drawType | DrawType::DrawCaptureImage);
	}

	if (this->view->selectedEntityManager.GetSize() > 0) {
		this->view->selectedEntityManager.UnSelectAll();
		drawType = (DrawType)(drawType | DrawType::DrawAll);
	}


	if ((drawType & DrawType::DrawAll) == DrawType::DrawAll) {
		this->view->update(DrawType::DrawAll);
		this->view->CaptureImage();
	}
	else if ((drawType & DrawType::DrawCaptureImage) == DrawType::DrawCaptureImage)
		this->view->update(DrawType::DrawCaptureImage);


	this->view->actionHandlerManager->ChangeAction(this->newActionType);
	this->view->setCursor(this->view->actionHandlerManager->GetCursorShape());


	ShCurrentActionChangedEvent event3(this->view->actionHandlerManager->GetType());
	this->view->Notify(&event3);

	return this->view->actionHandlerManager->GetType();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////


ShChangeCurrentActionCancelCurrent::ShChangeCurrentActionCancelCurrent(ActionType newActionType)
	:ShChangeCurrentActionStrategy(newActionType) {

}

ShChangeCurrentActionCancelCurrent::~ShChangeCurrentActionCancelCurrent() {

}

ActionType ShChangeCurrentActionCancelCurrent::Change() {

	if (this->view->GetCurrentActionType() != ActionType::ActionDefault) {
		ShUpdateListTextEvent event("<Cancel>");
		this->view->Notify(&event);
	}

	ShUpdateCommandEditHeadTitle event2(":: ");
	this->view->Notify(&event2);

	return ShChangeCurrentActionStrategy::Change();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////


ShChangeCurrentActionCurrentFinished::ShChangeCurrentActionCurrentFinished(ActionType newActionType)
	:ShChangeCurrentActionStrategy(newActionType) {

}

ShChangeCurrentActionCurrentFinished::~ShChangeCurrentActionCurrentFinished() {

}

ActionType ShChangeCurrentActionCurrentFinished::Change() {


	return ShChangeCurrentActionStrategy::Change();
}

#include "ShChangeCurrentActionStrategy.h"
#include "Interface\ShGraphicView.h"
#include "ShNotifyEvent.h"
#include "ActionHandler\ShActionHandler.h"
//#include "Entity\Leaf\ShRubberBand.h"
#include "Entity\Composite\ShPreview.h"
#include "ShSelectedEntityManager.h"
#include "FactoryMethod\ShCreatorActionFactory.h"
ShChangeCurrentActionStrategy::ShChangeCurrentActionStrategy(ActionType newActionType)
	:view(0), newActionType(newActionType) {

}

ShChangeCurrentActionStrategy::~ShChangeCurrentActionStrategy() {

}

ActionType ShChangeCurrentActionStrategy::Change() {

	if (this->newActionType == ActionType::ActionDefault &&
		this->view->currentAction->GetType() == ActionType::ActionDefault)
		return this->newActionType;



	if (this->view->currentAction != NULL)
		delete this->view->currentAction;


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



	this->view->currentAction = ShCreatorActionFactory::Create(this->newActionType, this->view);
	this->view->setCursor(this->view->currentAction->GetCursorShape());


	ShCurrentActionChangedEvent event3(this->view->currentAction->GetType());
	this->view->Notify(&event3);



	return this->view->currentAction->GetType();
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

#include "ShActionHandlerManager.h"
#include "FactoryMethod\ShCreatorActionFactory.h"
#include "ActionHandler\ShActionHandler.h"
#include "ActionHandler\TemporaryAction\ShTemporaryAction.h"
#include "FactoryMethod\ShCreatorActionDecoratorFactory.h"
#include "ActionHandler\ShActionHandlerDecorator.h"
#include "ShDraft.h"
#include <QMouseEvent>
#include "ShNotifyEvent.h"
ShActionHandlerManager::ShActionHandlerManager(ShGraphicView *graphicView, const ShDraftFlag& draftFlag)
	:graphicView(graphicView), draftFlag(draftFlag), disposableSnap(ObjectSnap::ObjectSnapNothing) {

	this->currentAction = ShCreatorActionFactory::Create(ActionType::ActionDefault, graphicView);
	this->actionDecorator = ShCreatorActionDecoratorFactory::Create(graphicView, this->currentAction, this->draftFlag, this->disposableSnap);
}

ShActionHandlerManager::~ShActionHandlerManager() {

	if (this->currentAction != 0)
		delete this->currentAction;

	if (this->actionDecorator != 0)
		delete this->actionDecorator;

}

void ShActionHandlerManager::LMousePressEvent(QMouseEvent *event) {

	ShActionData info;
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), info.point.x, info.point.y);
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), info.nextPoint.x, info.nextPoint.y);

	ShActionDecoratorData decoratorData;
	this->actionDecorator->LMousePressEvent(event, info, decoratorData);
	
	
	this->disposableSnap = ObjectSnap::ObjectSnapNothing;
	this->ChangeActionDecorator();
	
}

void ShActionHandlerManager::MMousePressEvent(QMouseEvent *event) {

	ShActionData info;
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), info.point.x, info.point.y);
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), info.nextPoint.x, info.nextPoint.y);

	ShActionDecoratorData decoratorData;
	this->actionDecorator->MMousePressEvent(event, info, decoratorData);
	
}

void ShActionHandlerManager::RMousePressEvent(QMouseEvent *event) {

	ShActionData info;
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), info.point.x, info.point.y);
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), info.nextPoint.x, info.nextPoint.y);

	ShActionDecoratorData decoratorData;
	this->actionDecorator->RMousePressEvent(event, info, decoratorData);
}

void ShActionHandlerManager::MouseMoveEvent(QMouseEvent *event) {

	ShActionData info;
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), info.point.x, info.point.y);

	ShActionDecoratorData decoratorData;
	this->actionDecorator->MouseMoveEvent(event, info, decoratorData);

	if ((info.drawType & ~DrawType::DrawNone) != DrawType::DrawNone)
		this->graphicView->update(info.drawType);
}

void ShActionHandlerManager::MouseReleaseEvent(QMouseEvent *event) {

	ShActionData info;
	ShActionDecoratorData decoratorData;
	this->actionDecorator->MouseReleaseEvent(event, info, decoratorData);
}

void ShActionHandlerManager::KeyPressEvent(QKeyEvent *event) {


	ShActionData info;
	ShActionDecoratorData decoratorData;
	this->actionDecorator->KeyPressEvent(event, info, decoratorData);
}

void ShActionHandlerManager::ChangeAction(ActionType actionType) {

	if (this->currentAction != 0)
		delete this->currentAction;

	this->currentAction = ShCreatorActionFactory::Create(actionType, this->graphicView);

	this->disposableSnap = ObjectSnap::ObjectSnapNothing;

	this->ChangeActionDecorator();
}

void ShActionHandlerManager::ReplaceAction(ShActionHandler *actionHandler) {

	this->currentAction = actionHandler;
	this->ChangeActionDecorator();
}

void ShActionHandlerManager::SetTemporaryAction(ShTemporaryAction *temporaryAction) {
	
	temporaryAction->SetPreviousAction(this->currentAction);
	this->currentAction = temporaryAction;
	this->ChangeActionDecorator();
	
}

QCursor ShActionHandlerManager::GetCursorShape() {

	return this->currentAction->GetCursorShape();
}

ActionType ShActionHandlerManager::GetType() {

	return this->currentAction->GetType();
}

void ShActionHandlerManager::Draw(QPainter *painter) {

	this->actionDecorator->Draw(painter);
}

void ShActionHandlerManager::SetDraftFlag(const ShDraftFlag& draftFlag) {

	this->draftFlag = draftFlag;
	this->ChangeActionDecorator();

	this->currentAction->ApplyOrthogonalShape(draftFlag.AcceptOrthogonal());
}

#include "FactoryMethod\ShCreatorObjectSnapFactory.h"
void ShActionHandlerManager::SetDisposableObjectSnap(ObjectSnap objectSnap) {

	
	ShAllowedDraftData data;
	this->currentAction->IsAllowedDraftOperation(data);

	QString str = ShCreatorObjectSnapCommandFactory::Create(objectSnap);

	if (data.AllowSnap() == false) {
	
		ShUpdateListTextEvent event(str + "Unknown command.", 
			ShUpdateListTextEvent::UpdateType::editTextWithText);
		this->graphicView->Notify(&event);

		return;
	}

	if (this->disposableSnap != ObjectSnap::ObjectSnapNothing) {
		
		this->disposableSnap = ObjectSnap::ObjectSnapNothing;

		ShUpdateListTextEvent event(str,
			ShUpdateListTextEvent::UpdateType::editTextWithText);
		this->graphicView->Notify(&event);

		ShUpdateListTextEvent event2("Invalid point.", 
			ShUpdateListTextEvent::UpdateType::TextWithoutAnything);
		this->graphicView->Notify(&event2);

		ShUpdateCommandEditHeadTitle event3(this->currentAction->GetActionHeadTitle());
		this->graphicView->Notify(&event3);
	}
	else {

		this->disposableSnap = objectSnap;

		ShUpdateCommandEditHeadTitle event(str, 
			ShUpdateCommandEditHeadTitle::UpdateType::AddHeadTitleToCurrent);
		this->graphicView->Notify(&event);
	
	}

	this->ChangeActionDecorator();

}

void ShActionHandlerManager::ChangeActionDecorator() {

	if (this->actionDecorator != 0)
		delete this->actionDecorator;

	this->actionDecorator = ShCreatorActionDecoratorFactory::Create(this->graphicView, this->currentAction,
		this->draftFlag, this->disposableSnap);
}
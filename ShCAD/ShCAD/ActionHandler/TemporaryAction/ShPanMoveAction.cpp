

#include "ShPanMoveAction.h"
#include "Memento Pattern\ShMemento.h"
#include "Command Pattern\ShMoveViewCommand.h"
#include <QMouseEvent>
ShPanMoveAction::ShPanMoveAction(ShGraphicView *graphicView, ShActionHandler *previousAction)
	:ShTemporaryAction(graphicView, previousAction), prevX(0), prevY(0) {

}

ShPanMoveAction::~ShPanMoveAction() {

}

//Pan Move Start here
void ShPanMoveAction::MousePressEvent(QMouseEvent *event) {
	qDebug("ShPanMoveAction->MousePressEvent");

	this->graphicView->setCursor(Qt::ClosedHandCursor);
	this->prevX = event->x();
	this->prevY = event->y();

	ShMoveViewMemento *memento = new ShMoveViewMemento;
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), memento->ex, memento->ey);
	memento->dx = event->x();
	memento->dy = event->y();
	memento->zoomRate = this->graphicView->GetZoomRate();

	this->graphicView->undoTaker.Push(new ShMoveViewCommand(this->graphicView, memento));

	if (!this->graphicView->redoTaker.IsEmpty())
		this->graphicView->redoTaker.DeleteAll();

}

void ShPanMoveAction::MouseMoveEvent(QMouseEvent *event) {

	double hPos = this->graphicView->GetHPos();
	hPos += this->prevX - event->x();
	double vPos = this->graphicView->GetVPos();
	vPos += this->prevY - event->y();

	this->graphicView->SetHPos(hPos);
	this->graphicView->SetVPos(vPos);


	this->prevX = event->x();
	this->prevY = event->y();
	this->graphicView->update(DrawType::DrawAll);

}

void ShPanMoveAction::KeyPressEvent(QKeyEvent *event) {

}

//Pan Move is finished
void ShPanMoveAction::MouseReleaseEvent(QMouseEvent *event) {
	qDebug("ShPanMoveAction->MouseReleaseEvent");

	this->graphicView->setCursor(this->previousAction->GetCursorShape());

	if (event->button()& Qt::MouseButton::MiddleButton) {
		this->graphicView->update(DrawType::DrawAll);
		this->graphicView->CaptureImage();
		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}

	this->ReturnToPrevious();

}


ActionType ShPanMoveAction::GetType() {
	
	return ActionType::ActionPanMove;
}


QCursor ShPanMoveAction::GetCursorShape() {
	
	QCursor cursor(Qt::ClosedHandCursor);
	
	return cursor;
}

#include "ShPanMoveAction.h"
#include <QMouseEvent>
#include "UnRedo\ShPanTransaction.h"

ShPanMoveAction::ShPanMoveAction(ShCADWidget *widget, ShActionHandler *previousAction)
	:ShTemporaryAction(widget, previousAction) {

}

ShPanMoveAction::~ShPanMoveAction() {

}

void ShPanMoveAction::mouseMidPressEvent(ShActionData &data) {

	this->widget->setCursor(Qt::ClosedHandCursor);

	int dx = data.mouseEvent->x();
	int dy = data.mouseEvent->y();
	this->prevX = dx;
	this->prevY = dy;

	ShPoint3d coordinate = data.point;

	this->widget->getUndoStack()->push(new ShPanTransaction(this->widget, coordinate, dx, dy));
	if (!this->widget->getRedoStack()->isEmpty())
		this->widget->getRedoStack()->deleteAll();
	
}

void ShPanMoveAction::mouseMoveEvent(ShActionData &data) {
	
	double hPos = this->widget->getScrollPosition().horizontal;
	double vPos = this->widget->getScrollPosition().vertical;
	hPos += this->prevX - data.mouseEvent->x();
	vPos += this->prevY - data.mouseEvent->y();

	this->widget->setScrollPosition(ShScrollPosition(vPos, hPos));

	this->prevX = data.mouseEvent->x();
	this->prevY = data.mouseEvent->y();

	this->widget->store(DrawType::DrawAll);
}

void ShPanMoveAction::mouseReleaseEvent(ShActionData &data) {
	
	if (data.mouseEvent->button() & Qt::MouseButton::MiddleButton) {

		this->widget->captureImage();
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}

	this->returnToPrevious();
}

ActionType ShPanMoveAction::getType() {

	return ActionType::ActionPanMove;
}

QCursor ShPanMoveAction::getCursorShape() {

	return QCursor(Qt::ClosedHandCursor);
}
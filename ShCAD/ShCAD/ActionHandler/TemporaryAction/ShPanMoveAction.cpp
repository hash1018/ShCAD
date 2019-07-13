
#include "ShPanMoveAction.h"
#include <QMouseEvent>


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

	
}

#include <qdebug.h>
void ShPanMoveAction::mouseMoveEvent(ShActionData &data) {
	qDebug() << "PanMoveAction::mouseMoveEvent";
	double hPos = this->widget->getScrollPosition().horizontal;
	double vPos = this->widget->getScrollPosition().vertical;
	hPos += this->prevX - data.mouseEvent->x();
	vPos += this->prevY - data.mouseEvent->y();

	this->widget->setScrollPosition(ShScrollPosition(vPos, hPos));

	this->prevX = data.mouseEvent->x();
	this->prevY = data.mouseEvent->y();

	this->widget->update();
}

void ShPanMoveAction::mouseReleaseEvent(ShActionData &data) {
	qDebug() << "PanMoveAction::mouseReleaseEvent";
	if (data.mouseEvent->button() & Qt::MouseButton::MiddleButton) {

		this->widget->captureImage();
		this->widget->updateImmediately((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}

	this->returnToPrevious();
}

ActionType ShPanMoveAction::getType() {

	return ActionType::ActionPanMove;
}

QCursor ShPanMoveAction::getCursorShape() {

	return QCursor(Qt::ClosedHandCursor);
}
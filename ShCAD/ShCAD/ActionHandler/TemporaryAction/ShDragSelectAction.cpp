

#include "ShDragSelectAction.h"
#include <QMouseEvent>
#include <qpainter.h>
ShDragSelectAction::ShDragSelectAction(ShGraphicView *graphicView, ShActionHandler *previousAction,
	double firstX, double firstY)
	:ShTemporaryAction(graphicView, previousAction), firstX(firstX), firstY(firstY), secondX(0), secondY(0) {

	this->graphicView->setCursor(QCursor(Qt::CursorShape::DragCopyCursor));
}

ShDragSelectAction::~ShDragSelectAction() {

}


//about to close dragRect , and back to previousAction
void ShDragSelectAction::MousePressEvent(QMouseEvent *event) {

	this->graphicView->setCursor(this->previousAction->GetCursorShape());
	this->graphicView->update(DrawType::DrawCaptureImage);

	this->ReturnToPrevious();
}

void ShDragSelectAction::MouseMoveEvent(QMouseEvent *event) {

	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), this->secondX, this->secondY);
	this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawActionHandler));
}

void ShDragSelectAction::KeyPressEvent(QKeyEvent *event) {

}



ActionType ShDragSelectAction::GetType() {

	return ActionType::ActionDragSelect;
}

QCursor ShDragSelectAction::GetCursorShape() {
	
	return QCursor(Qt::CursorShape::DragCopyCursor);
}

void ShDragSelectAction::Draw(QPainter *painter) {

	if (painter->isActive() == false)
		painter->begin(this->graphicView);

	int firstX, firstY, secondX, secondY;
	this->graphicView->ConvertEntityToDevice(this->firstX, this->firstY, firstX, firstY);
	this->graphicView->ConvertEntityToDevice(this->secondX, this->secondY, secondX, secondY);

	int width = abs(firstX - secondX);
	int height = abs(firstY - secondY);

	QPen oldPen = painter->pen();

	QPen pen;
	pen.setColor(QColor(255, 255, 255));
	painter->setPen(pen);

	//in this case, entity is selected when its all part is in dragRect.
	if (firstX <= secondX) {

		if (firstY >= secondY) {
			painter->drawRect(firstX, firstY - height, width, height);
			painter->fillRect(firstX, firstY - height, width, height, QColor(102, 102, 204, 125));
		}
		else {
			painter->drawRect(firstX, firstY, width, height);
			painter->fillRect(firstX, firstY, width, height, QColor(102, 102, 204, 125));
		}

	}
	//entity is selected when its any part of body is in dragRect.
	else {

		pen.setStyle(Qt::PenStyle::DotLine);
		painter->setPen(pen);
		if (firstY >= secondY) {
			painter->drawRect(secondX, secondY, width, height);
			painter->fillRect(secondX, secondY, width, height, QColor(102, 204, 102, 125));
		}
		else {
			painter->drawRect(secondX, firstY, width, height);
			painter->fillRect(secondX, firstY, width, height, QColor(102, 204, 102, 125));
		}

	}

	painter->setPen(oldPen);
	painter->end();
}
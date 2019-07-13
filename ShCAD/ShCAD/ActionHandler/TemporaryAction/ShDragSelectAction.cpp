
#include "ShDragSelectAction.h"
#include <qpainter.h>

ShDragSelectAction::ShDragSelectAction(ShCADWidget *widget, ShActionHandler *previousAction, double firstX, double firstY, Mode mode)
	:ShTemporaryAction(widget, previousAction), firstX(firstX), firstY(firstY), mode(mode) {

}

ShDragSelectAction::~ShDragSelectAction() {

}

void ShDragSelectAction::mouseLeftPressEvent(ShActionData &data) {

	if (this->mode == Mode::SelectMode) {

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
		this->widget->captureImage();

	}
	else if (this->mode == Mode::UnSelectMode) {

		this->widget->update(DrawType::DrawAll);
		this->widget->captureImage();
	}

	this->returnToPrevious();
}

void ShDragSelectAction::mouseMoveEvent(ShActionData &data) {

	this->secondX = data.point.x;
	this->secondY = data.point.y;

	this->widget->store((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawActionHandler));
}

void ShDragSelectAction::keyPressEvent(ShActionData &data) {

}

ActionType ShDragSelectAction::getType() {

	return ActionType::ActionDragSelect;
}

QCursor ShDragSelectAction::getCursorShape() {

	return QCursor(Qt::CursorShape::DragCopyCursor);
}

void ShDragSelectAction::draw(QPainter *painter) {

	if (painter->isActive() == false)
		painter->begin(this->widget);


	SelectMethod selectMethod;
	ShPoint3d topLeft, bottomRight;
	this->getDragRectPoint(ShPoint3d(this->firstX, this->firstY), ShPoint3d(this->secondX, this->secondY),
		topLeft, bottomRight, selectMethod);

	int topLeftX, topLeftY, bottomRightX, bottomRightY, width, height;
	this->widget->convertEntityToDevice(topLeft.x, topLeft.y, topLeftX, topLeftY);
	this->widget->convertEntityToDevice(bottomRight.x, bottomRight.y, bottomRightX, bottomRightY);
	width = abs(topLeftX - bottomRightX);
	height = abs(topLeftY - bottomRightY);


	QPen oldPen = painter->pen();
	QPen pen;
	pen.setColor(QColor(255, 255, 255));
	painter->setPen(pen);


	if (selectMethod == SelectMethod::OnePart) {
		pen.setStyle(Qt::PenStyle::DotLine);
		painter->setPen(pen);
		painter->drawRect(topLeftX, topLeftY, width, height);
		painter->fillRect(topLeftX, topLeftY, width, height, QColor(102, 204, 102, 125));
	}
	else {
		painter->drawRect(topLeftX, topLeftY, width, height);
		painter->fillRect(topLeftX, topLeftY, width, height, QColor(102, 102, 204, 125));

	}


	painter->setPen(oldPen);
	painter->end();
}

void ShDragSelectAction::getDragRectPoint(const ShPoint3d &first, const ShPoint3d &second, ShPoint3d &topLeft, ShPoint3d &bottomRight, SelectMethod &selectMethod) {

	if (first.x > second.x && first.y > second.y) {
		selectMethod = OnePart;
		topLeft.x = second.x;
		topLeft.y = first.y;
		bottomRight.x = first.x;
		bottomRight.y = second.y;
	}
	else if (first.x <= second.x && first.y > second.y) {
		selectMethod = AllPart;
		topLeft.x = first.x;
		topLeft.y = first.y;
		bottomRight.x = second.x;
		bottomRight.y = second.y;
	}
	else if (first.x > second.x && first.y <= second.y) {
		selectMethod = OnePart;
		topLeft.x = second.x;
		topLeft.y = second.y;
		bottomRight.x = first.x;
		bottomRight.y = first.y;
	}
	else if (first.x <= second.x && first.y <= second.y) {
		selectMethod = AllPart;
		topLeft.x = first.x;
		topLeft.y = second.y;
		bottomRight.x = second.x;
		bottomRight.y = first.y;
	}
}
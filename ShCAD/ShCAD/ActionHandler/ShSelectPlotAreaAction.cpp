
#include "ShSelectPlotAreaAction.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Interface\Dialog\ShPlotDialog.h"
#include "Command\ShAvailableCommands.h"
#include <qpainter.h>
#include "Base\ShCursorShape.h"

ShSelectPlotAreaAction::ShSelectPlotAreaAction(ShCADWidget *widget)
	:ShActionHandler(widget), status(PickedNothing), plotDialog(nullptr) {

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowInput().
		allowKey(KeyType::EscCancelCurrent).
		allowKey(KeyType::Enter).
		allowKey(KeyType::Return).
		build();

	this->availableCommands = ShAvailableCommands::ShBuilder(this->widget, this).
		addAvailableCommand(CommandType::AbsoluteCoordinate).
		addAvailableCommand(CommandType::Empty_Cancel).
		addAvailableCommand(CommandType::RelativeCoordinate).
		addAvailableCommand(CommandType::PolarCoordinate).
		addAvailableCommand(CommandType::DistanceFromBase).
		build();
}

ShSelectPlotAreaAction::~ShSelectPlotAreaAction() {

	this->plotDialog->setVisible(true);
}

void ShSelectPlotAreaAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShSelectPlotAreaAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShSelectPlotAreaAction::getType() {

	return ActionType::ActionSelectPlotArea;
}

QString ShSelectPlotAreaAction::getHeadTitle() {

	QString str;

	if (this->status == PickedNothing)
		str = "Plot >>"+ shGetLanValue_command("Command/Specify first corner") + ": ";
	else if (this->status == PickedFirstPoint)
		str = "Plot >>" + shGetLanValue_command("Command/Specify opposite corner") + ": ";

	return str;
}

QCursor ShSelectPlotAreaAction::getCursorShape() {

	return ShCursorShape::getCursor(ShCursorShape::Nothing);
}

void ShSelectPlotAreaAction::draw(QPainter *painter) {

	if (painter->isActive() == false)
		painter->begin(this->widget);

	int firstX, firstY, secondX, secondY;
	this->widget->convertEntityToDevice(this->firstX, this->firstY, firstX, firstY);
	this->widget->convertEntityToDevice(this->secondX, this->secondY, secondX, secondY);

	int width = abs(firstX - secondX);
	int height = abs(firstY - secondY);

	QPen oldPen = painter->pen();

	QPen pen;
	pen.setColor(QColor(255, 255, 255));
	painter->setPen(pen);

	pen.setStyle(Qt::PenStyle::DotLine);
	painter->setPen(pen);
	if (firstX <= secondX) {

		if (firstY >= secondY) {
			painter->drawRect(firstX, firstY - height, width, height);
		}
		else {
			painter->drawRect(firstX, firstY, width, height);
		}

	}
	else {

		if (firstY >= secondY) {
			painter->drawRect(secondX, secondY, width, height);
		}
		else {
			painter->drawRect(secondX, firstY, width, height);
		}
	}

	painter->setPen(oldPen);
	painter->end();
}

void ShSelectPlotAreaAction::invalidate(ShPoint3d &point) {

	if (this->status == PickedFirstPoint) {
	
		this->secondX = point.x;
		this->secondY = point.y;

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawActionHandler));
	}

}

void ShSelectPlotAreaAction::trigger(const ShPoint3d &point) {

	if (this->status == PickedNothing) {
	
		this->firstX = point.x;
		this->firstY = point.y;

		this->status = PickedFirstPoint;

		this->setLastBasePoint(point);
		this->triggerSucceeded();
	}
	else {
	
		this->plotDialog->setWindowPrevXY(this->firstX, this->firstY);
		this->plotDialog->setWindowCurrentXY(point.x, point.y);

		this->setLastBasePoint(point);
		this->actionFinished();
	}

}
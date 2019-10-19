
#include "ShDrawDimArcLengthAction.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Command\ShAvailableCommands.h"
#include "Base\ShCursorShape.h"
#include "Entity\Composite\Dim\ShDimArcLength.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Leaf\ShArc.h"
#include "Base\ShMath.h"

ShDrawDimArcLengthAction::ShDrawDimArcLengthAction(ShCADWidget *widget)
	:ShDrawDimAction(widget), status(Status::PickedNothing) {

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowKey(KeyType::Enter).
		allowKey(KeyType::Return).
		allowKey(KeyType::EscCancelCurrent).
		allowInput().
		build();

	this->availableCommands = ShAvailableCommands::ShBuilder(this->widget, this).
		addAvailableCommand(CommandType::Empty_Cancel).
		build();
}

ShDrawDimArcLengthAction::~ShDrawDimArcLengthAction() {

}

void ShDrawDimArcLengthAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShDrawDimArcLengthAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShDrawDimArcLengthAction::getType() {

	return ActionType::ActionDrawDimArcLength;
}

QString ShDrawDimArcLengthAction::getHeadTitle() {

	QString text;

	if (this->status == Status::PickedNothing)
		text = "DimArcLength >> " + shGetLanValue_command("Command/Select arc segment") + ": ";
	else if (this->status == Status::PickedShape)
		text = "DimArcLength >> " + shGetLanValue_command("Command/Specify dimension line location") + ": ";

	return text;
}

ShAvailableDraft ShDrawDimArcLengthAction::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->status == Status::PickedShape) {

		draft.setAvailableSnap(true);
		draft.setSnapBasePoint(this->widget->getMousePoint());
	}

	return draft;
}

QCursor ShDrawDimArcLengthAction::getCursorShape() {

	QCursor cursor;

	if (this->status == Status::PickedNothing)
		cursor = ShCursorShape::getCursor(ShCursorShape::Selecting);
	else if (this->status == Status::PickedShape)
		cursor = ShCursorShape::getCursor(ShCursorShape::Drawing);

	return cursor;
}

void ShDrawDimArcLengthAction::invalidate(ShPoint3d &point) {

	if (this->status == Status::PickedShape) {

		ShDimArcLengthData data;
		this->getDimArcLengthData(this->center, this->radius, this->start, this->end, point, data);

		ShDimArcLength *prevDimArcLength = dynamic_cast<ShDimArcLength*>(*this->widget->getPreview().begin());
		prevDimArcLength->setData(data);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

void ShDrawDimArcLengthAction::trigger(const ShPoint3d &point) {

	if (this->status == Status::PickedNothing) {

		ShEntity *entity = nullptr;
		ShSearchEntityUniqueStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
		this->widget->getEntityTable().search(strategy);

		if (entity != nullptr) {

			if (dynamic_cast<ShArc*>(entity)) {

				ShArc *arc = dynamic_cast<ShArc*>(entity);
				this->center = arc->getCenter();
				this->radius = arc->getRadius();
				this->start = arc->getStart();
				this->end = arc->getEnd();
				this->status = Status::PickedShape;

				ShDimArcLengthData data;
				this->getDimArcLengthData(this->center, this->radius, this->start, this->end, point, data);
				this->widget->getPreview().add(new ShDimArcLength(data, this->widget->getPropertyData(), this->widget->getCurrentLayer(),
					this->widget->getCurrentDimensionStyle()));

				this->availableCommands->add(CommandType::AbsoluteCoordinate);
				this->availableCommands->add(CommandType::RelativeCoordinate);
				this->availableCommands->add(CommandType::PolarCoordinate);
				this->availableCommands->add(CommandType::DistanceFromBase);

				this->widget->setCursor(this->getCursorShape());
				this->triggerSucceeded();
			}
			else {


				//
			}
		}
		else {

			//
		}
	}
	else {

		ShDimArcLengthData data;
		this->getDimArcLengthData(this->center, this->radius, this->start, this->end, point, data);

		ShDimArcLength *prevDimArcLength = dynamic_cast<ShDimArcLength*>(*this->widget->getPreview().begin());
		prevDimArcLength->setData(data);

		this->addEntity(prevDimArcLength->clone(), "DimArcLength");

		this->setLastBasePoint(point);
		this->actionFinished();
	}
}

void ShDrawDimArcLengthAction::getDimArcLengthData(const ShPoint3d &center, double radius, const ShPoint3d &start, const ShPoint3d &end,
	const ShPoint3d &point, ShDimArcLengthData &data) {

	data.center = center;
	data.boundary = point;
	data.radius = radius;
	data.start = start;
	data.end = end;

	double startAngle = math::getAbsAngle(center.x, center.y, start.x, start.y);
	double endAngle = math::getAbsAngle(center.x, center.y, end.x, end.y);
	double angle = math::getAbsAngle(center.x, center.y, point.x, point.y);

	if (math::checkAngleLiesOnAngleBetween(startAngle, endAngle, angle) == false) {

		data.start = end;
		data.end = start;
		double temp = startAngle;
		startAngle = endAngle;
		endAngle = temp;
	}
	
	double distance = math::getDistance(center.x, center.y, point.x, point.y);
	double angleDifference = math::getAngleDifference(startAngle, endAngle);

	math::rotate(startAngle + (angleDifference / 2.0), center.x, center.y, center.x + distance, center.y, data.text.x, data.text.y);
}
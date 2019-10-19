
#include "ShDrawDimAngularAction.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Command\ShAvailableCommands.h"
#include "Base\ShCursorShape.h"
#include "Entity\Composite\Dim\ShDimAngular.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Leaf\ShArc.h"
#include "Base\ShMath.h"

ShDrawDimAngularAction::ShDrawDimAngularAction(ShCADWidget *widget)
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

ShDrawDimAngularAction::~ShDrawDimAngularAction() {

}

void ShDrawDimAngularAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShDrawDimAngularAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShDrawDimAngularAction::getType() {

	return ActionType::ActionDrawDimAngular;
}

QString ShDrawDimAngularAction::getHeadTitle() {

	QString text;

	if (this->status == Status::PickedNothing)
		text = "DimAngular >> " + shGetLanValue_command("Command/Select arc segment") + ": ";
	else if (this->status == Status::PickedShape)
		text = "DimAngular >> " + shGetLanValue_command("Command/Specify dimension line location") + ": ";

	return text;
}

ShAvailableDraft ShDrawDimAngularAction::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->status == Status::PickedShape) {

		draft.setAvailableSnap(true);
		draft.setSnapBasePoint(this->widget->getMousePoint());
	}

	return draft;
}

QCursor ShDrawDimAngularAction::getCursorShape() {

	QCursor cursor;

	if (this->status == Status::PickedNothing)
		cursor = ShCursorShape::getCursor(ShCursorShape::Selecting);
	else if (this->status == Status::PickedShape)
		cursor = ShCursorShape::getCursor(ShCursorShape::Drawing);

	return cursor;
}

void ShDrawDimAngularAction::invalidate(ShPoint3d &point) {

	if (this->status == Status::PickedShape) {

		ShDimAngularData data;
		this->getDimAngularData(this->center, this->radius, this->start, this->end, point, data);

		ShDimAngular *prevDimAngular = dynamic_cast<ShDimAngular*>(*this->widget->getPreview().begin());
		prevDimAngular->setData(data);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

void ShDrawDimAngularAction::trigger(const ShPoint3d &point) {

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

				ShDimAngularData data;
				this->getDimAngularData(this->center, this->radius, this->start, this->end, point, data);
				this->widget->getPreview().add(new ShDimAngular(data, this->widget->getPropertyData(), this->widget->getCurrentLayer(),
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

		ShDimAngularData data;
		this->getDimAngularData(this->center, this->radius, this->start, this->end, point, data);

		ShDimAngular *prevDimAngular = dynamic_cast<ShDimAngular*>(*this->widget->getPreview().begin());
		prevDimAngular->setData(data);

		this->addEntity(prevDimAngular->clone(), "DimAngular");

		this->setLastBasePoint(point);
		this->actionFinished();
	}
}

void ShDrawDimAngularAction::getDimAngularData(const ShPoint3d &center, double radius, const ShPoint3d &start, const ShPoint3d &end,
	const ShPoint3d &point, ShDimAngularData &data) {

	data.center = center;
	data.boundary = point;
	data.start = start;
	data.end = end;

	double startAngle = math::getAbsAngle(center.x, center.y, start.x, start.y);
	double endAngle = math::getAbsAngle(center.x, center.y, end.x, end.y);
	double angle = math::getAbsAngle(center.x, center.y, point.x, point.y);

	if (math::checkAngleLiesOnAngleBetween(startAngle, endAngle, angle) == false) {

		data.start = end;
		data.end = start;
		math::swap(startAngle, endAngle);
	}

	double distance = math::getDistance(center.x, center.y, point.x, point.y);
	double angleDifference = math::getAngleDifference(startAngle, endAngle);

	math::rotate(startAngle + (angleDifference / 2.0), center.x, center.y, center.x + distance, center.y, data.text.x, data.text.y);
}
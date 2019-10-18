
#include "ShDrawDimDiameterAction.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Command\ShAvailableCommands.h"
#include "Base\ShMath.h"
#include "Entity\Composite\Dim\ShDimDiameter.h"
#include "Base\ShCursorShape.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity/Leaf/ShCircle.h"
#include "Entity\Leaf\ShArc.h"

ShDrawDimDiameterAction::ShDrawDimDiameterAction(ShCADWidget *widget)
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

ShDrawDimDiameterAction::~ShDrawDimDiameterAction() {

}

void ShDrawDimDiameterAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShDrawDimDiameterAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShDrawDimDiameterAction::getType() {

	return ActionType::ActionDrawDimDiameter;
}

QString ShDrawDimDiameterAction::getHeadTitle() {

	QString text;

	if (this->status == Status::PickedNothing)
		text = "DimDiameter >> " + shGetLanValue_command("Command/Select circle or arc segment") + ": ";
	else if (this->status == Status::PickedShape)
		text = "DimDiameter >> " + shGetLanValue_command("Command/Specify dimension line location") + ": ";

	return text;
}

ShAvailableDraft ShDrawDimDiameterAction::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->status == Status::PickedShape) {

		draft.setAvailableSnap(true);
		draft.setSnapBasePoint(this->widget->getMousePoint());
	}

	return draft;
}

QCursor ShDrawDimDiameterAction::getCursorShape() {

	QCursor cursor;

	if (this->status == Status::PickedNothing)
		cursor = ShCursorShape::getCursor(ShCursorShape::Selecting);
	else if (this->status == Status::PickedShape)
		cursor = ShCursorShape::getCursor(ShCursorShape::Drawing);

	return cursor;
}

void ShDrawDimDiameterAction::invalidate(ShPoint3d &point) {

	if (this->status == Status::PickedShape) {

		ShDimDiameterData data;
		this->getDimDiameterData(this->center, radius, point, data);

		ShDimDiameter *prevDimDiameter = dynamic_cast<ShDimDiameter*>(*this->widget->getPreview().begin());
		prevDimDiameter->setData(data);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

void ShDrawDimDiameterAction::trigger(const ShPoint3d &point) {

	if (this->status == Status::PickedNothing) {

		ShEntity *entity = nullptr;
		ShSearchEntityUniqueStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
		this->widget->getEntityTable().search(strategy);

		if (entity != nullptr) {

			if (dynamic_cast<ShCircle*>(entity)) {

				ShCircle *circle = dynamic_cast<ShCircle*>(entity);
				this->center = circle->getCenter();
				this->radius = circle->getRadius();
				this->status = Status::PickedShape;

				ShDimDiameterData data;
				this->getDimDiameterData(this->center, this->radius, point, data);
				this->widget->getPreview().add(new ShDimDiameter(data, this->widget->getPropertyData(), this->widget->getCurrentLayer(),
					this->widget->getCurrentDimensionStyle()));

				this->widget->setCursor(this->getCursorShape());
				this->triggerSucceeded();
			}
			else if (dynamic_cast<ShArc*>(entity)) {

				ShArc *arc = dynamic_cast<ShArc*>(entity);
				this->center = arc->getCenter();
				this->radius = arc->getRadius();
				this->status = Status::PickedShape;

				ShDimDiameterData data;
				this->getDimDiameterData(this->center, this->radius, point, data);
				this->widget->getPreview().add(new ShDimDiameter(data, this->widget->getPropertyData(), this->widget->getCurrentLayer(),
					this->widget->getCurrentDimensionStyle()));

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

		ShDimDiameterData data;
		this->getDimDiameterData(this->center, this->radius, point, data);

		ShDimDiameter *prevDimDiameter = dynamic_cast<ShDimDiameter*>(*this->widget->getPreview().begin());
		prevDimDiameter->setData(data);

		this->addEntity(prevDimDiameter->clone(), "DimDiameter");

		this->setLastBasePoint(point);
		this->actionFinished();
	}
}

void ShDrawDimDiameterAction::getDimDiameterData(const ShPoint3d &center, double radius, const ShPoint3d &point, ShDimDiameterData &data) {

	data.center = center;
	data.text = point;

	double angle = math::getAbsAngle(center.x, center.y, point.x, point.y);
	math::rotate(angle, center.x, center.y, center.x + radius, center.y, data.firstDim.x, data.firstDim.y);
	math::rotate(angle + 180, center.x, center.y, center.x + radius, center.y, data.secondDim.x, data.secondDim.y);
}
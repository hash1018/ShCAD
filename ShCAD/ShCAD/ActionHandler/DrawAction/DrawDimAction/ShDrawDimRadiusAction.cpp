
#include "ShDrawDimRadiusAction.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Command\ShAvailableCommands.h"
#include "Base\ShMath.h"
#include "Entity\Composite\Dim\ShDimRadius.h"
#include "Base\ShCursorShape.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity/Leaf/ShCircle.h"
#include "Entity\Leaf\ShArc.h"

ShDrawDimRadiusAction::ShDrawDimRadiusAction(ShCADWidget *widget)
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

ShDrawDimRadiusAction::~ShDrawDimRadiusAction() {

}

void ShDrawDimRadiusAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShDrawDimRadiusAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShDrawDimRadiusAction::getType() {

	return ActionType::ActionDrawDimRadius;
}

QString ShDrawDimRadiusAction::getHeadTitle() {

	QString text;

	if (this->status == Status::PickedNothing)
		text = "DimRadius >> " + shGetLanValue_command("Command/Select circle or arc segment") + ": ";
	else if (this->status == Status::PickedShape)
		text = "DimRadius >> " + shGetLanValue_command("Command/Specify dimension line location") + ": ";

	return text;
}

ShAvailableDraft ShDrawDimRadiusAction::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->status == Status::PickedShape) {
	
		draft.setAvailableSnap(true);
		draft.setSnapBasePoint(this->widget->getMousePoint());
	}

	return draft;
}

QCursor ShDrawDimRadiusAction::getCursorShape() {

	QCursor cursor;

	if (this->status == Status::PickedNothing)
		cursor = ShCursorShape::getCursor(ShCursorShape::Selecting);
	else if (this->status == Status::PickedShape)
		cursor = ShCursorShape::getCursor(ShCursorShape::Drawing);

	return cursor;
}

void ShDrawDimRadiusAction::invalidate(ShPoint3d &point) {

	if (this->status == Status::PickedShape) {

		ShDimRadiusData data;
		this->getDimRadiusData(this->center, radius, point, data);

		ShDimRadius *prevDimRadius = dynamic_cast<ShDimRadius*>(*this->widget->getPreview().begin());
		prevDimRadius->setData(data);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

void ShDrawDimRadiusAction::trigger(const ShPoint3d &point) {

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

				ShDimRadiusData data;
				this->getDimRadiusData(this->center, this->radius, point, data);
				this->widget->getPreview().add(new ShDimRadius(data, this->widget->getPropertyData(), this->widget->getCurrentLayer(),
					this->widget->getCurrentDimensionStyle()));

				this->widget->setCursor(this->getCursorShape());
				this->triggerSucceeded();
			}
			else if (dynamic_cast<ShArc*>(entity)) {

				ShArc *arc = dynamic_cast<ShArc*>(entity);
				this->center = arc->getCenter();
				this->radius = arc->getRadius();
				this->status = Status::PickedShape;

				ShDimRadiusData data;
				this->getDimRadiusData(this->center, this->radius, point, data);
				this->widget->getPreview().add(new ShDimRadius(data, this->widget->getPropertyData(), this->widget->getCurrentLayer(),
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
	
		ShDimRadiusData data;
		this->getDimRadiusData(this->center, this->radius, point, data);

		ShDimRadius *prevDimRadius = dynamic_cast<ShDimRadius*>(*this->widget->getPreview().begin());
		prevDimRadius->setData(data);

		this->addEntity(prevDimRadius->clone(), "DimRadius");

		this->setLastBasePoint(point);
		this->actionFinished();
	}
}

void ShDrawDimRadiusAction::getDimRadiusData(const ShPoint3d &center, double radius, const ShPoint3d &point, ShDimRadiusData &data) {

	data.center = center;
	data.text = point;

	double angle = math::getAbsAngle(center.x, center.y, point.x, point.y);
	math::rotate(angle, center.x, center.y, center.x + radius, center.y, data.dim.x, data.dim.y);
}
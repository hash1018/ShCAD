

#include "ShDrawDimLinearAction.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Command\ShAvailableCommands.h"
#include "Base\ShMath.h"
#include "Entity\Composite\Dim\ShDimLinear.h"

ShDrawDimLinearAction::ShDrawDimLinearAction(ShCADWidget *widget)
	:ShDrawDimAction(widget), status(Status::PickedNothing), direction(Direction::Nothing) {

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowKey(KeyType::Enter).
		allowKey(KeyType::Return).
		allowKey(KeyType::EscCancelCurrent).
		allowInput().
		build();

	this->availableCommands = ShAvailableCommands::ShBuilder(this->widget, this).
		addAvailableCommand(CommandType::Empty_Cancel).
		addAvailableCommand(CommandType::AbsoluteCoordinate).
		addAvailableCommand(CommandType::RelativeCoordinate).
		addAvailableCommand(CommandType::PolarCoordinate).
		addAvailableCommand(CommandType::DistanceFromBase).
		build();
}

ShDrawDimLinearAction::~ShDrawDimLinearAction() {

}

void ShDrawDimLinearAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShDrawDimLinearAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShDrawDimLinearAction::getType() {

	return ActionType::ActionDrawDimLinear;
}

QString ShDrawDimLinearAction::getHeadTitle() {

	QString text;

	if (this->status == Status::PickedNothing)
		text = "DimLinear >> " + shGetLanValue_command("Command/Specify first extension line origin") + ": ";
	else if(this->status == Status::PickedFirst)
		text = "DimLinear >> " + shGetLanValue_command("Command/Specify second extension line origin") + ": ";
	else if(this->status==Status::PickedSecond)
		text = "DimLinear >> " + shGetLanValue_command("Command/Specify dimension line location") + ": ";

	return text;
}

ShAvailableDraft ShDrawDimLinearAction::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->status == Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->status == Status::PickedFirst) {

		draft.setAvailableOrthogonal(true);
		draft.setOrthogonalBasePoint(this->first);
		draft.setAvailableSnap(true);
		draft.setSnapBasePoint(this->first);
	}
	else if (this->status == Status::PickedSecond) {
	
		draft.setAvailableSnap(true);
		draft.setSnapBasePoint(this->second);
	}

	return draft;
}

void ShDrawDimLinearAction::invalidate(ShPoint3d &point) {

	if (this->status == Status::PickedFirst) {
	
		this->widget->getRubberBand().setEnd(point);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->status == Status::PickedSecond) {
	
		ShDimLinearData data;
		this->getDimLinearData(this->first, this->second, point, this->direction, data);

		ShDimLinear *prevDimLinear = dynamic_cast<ShDimLinear*>(*this->widget->getPreview().begin());
		prevDimLinear->setData(data);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

void ShDrawDimLinearAction::trigger(const ShPoint3d &point) {

	if (this->status == Status::PickedNothing) {
	
		this->status = Status::PickedFirst;
		this->first = point;

		this->widget->getRubberBand().setData(ShLineData(point, point));
		
		this->setLastBasePoint(point);
		this->triggerSucceeded();
	}
	else if (this->status == Status::PickedFirst) {

		this->status = Status::PickedSecond;
		this->second = point;

		this->widget->getRubberBand().clear();

		ShDimLinearData data;
		this->getDimLinearData(this->first, this->second, point, this->direction, data);

		this->widget->getPreview().add(new ShDimLinear(data, this->widget->getPropertyData(), this->widget->getCurrentLayer(),
			this->widget->getCurrentDimensionStyle()));

		this->setLastBasePoint(point);
		this->triggerSucceeded();
	}
	else if (this->status == Status::PickedSecond) {
	
		ShDimLinearData data;
		this->getDimLinearData(this->first, this->second, point, this->direction, data);

		ShDimLinear *prevDimLinear = dynamic_cast<ShDimLinear*>(*this->widget->getPreview().begin());
		prevDimLinear->setData(data);

		this->addEntity(prevDimLinear->clone(), "DimLinear");

		this->setLastBasePoint(point);
		this->actionFinished();
	}
}


void ShDrawDimLinearAction::getDimLinearData(const ShPoint3d &first, const ShPoint3d &second, const ShPoint3d &point,
	Direction &direction, ShDimLinearData &data) {

	data.firstOrigin = first;
	data.secondOrigin = second;
	data.firstDim = first;
	data.secondDim = second;

	if (direction == Nothing) {

		direction = Horizontal;

		data.firstDim.y = point.y;
		data.secondDim.y = point.y;
	}
	else if (direction == Horizontal) {

		if (math::isBetween(point.y, first.y, second.y, 0) == true &&
			math::isBetween(point.x, first.x, second.x, 0) == false) {

			direction = Vertical;

			data.firstDim.x = point.x;
			data.secondDim.x = point.x;
		}
		else {

			data.firstDim.y = point.y;
			data.secondDim.y = point.y;
		}
	}
	else if (direction == Vertical) {

		if (math::isBetween(point.x, first.x, second.x, 0) == true &&
			math::isBetween(point.y, first.y, second.y, 0) == false) {

			direction = Horizontal;

			data.firstDim.y = point.y;
			data.secondDim.y = point.y;
		}
		else {

			data.firstDim.x = point.x;
			data.secondDim.x = point.x;
		}
	}

	
	double distance = math::getDistance(data.firstDim.x, data.firstDim.y, data.secondDim.x, data.secondDim.y);
	double angle = math::getAbsAngle(data.firstDim.x, data.firstDim.y, data.secondDim.x, data.secondDim.y);
	math::rotate(angle, data.firstDim.x, data.firstDim.y, data.firstDim.x + distance / 2.0, data.firstDim.y,
		data.text.x, data.text.y);
}
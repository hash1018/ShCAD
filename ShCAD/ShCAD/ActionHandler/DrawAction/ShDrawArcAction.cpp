
#include "ShDrawArcAction.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShArc.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Command\ShAvailableCommands.h"

ShDrawArcAction::ShDrawArcAction(ShCADWidget *widget, SubAction subAction)
	:ShDrawAction(widget), status(PickedNothing), subAction(subAction), subDrawArcAction(nullptr) {

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
		build();

	this->changeSubAction(subAction);
}

ShDrawArcAction::~ShDrawArcAction() {

	if (this->subDrawArcAction != nullptr)
		delete this->subDrawArcAction;
}


void ShDrawArcAction::mouseLeftPressEvent(ShActionData &data) {

	this->subDrawArcAction->mouseLeftPressEvent(data);
}

void ShDrawArcAction::mouseMoveEvent(ShActionData &data) {

	this->subDrawArcAction->mouseMoveEvent(data);
}

ActionType ShDrawArcAction::getType() {

	return this->subDrawArcAction->getType();
}

QString ShDrawArcAction::getHeadTitle() {

	return this->subDrawArcAction->getHeadTitle();
}

ShAvailableDraft ShDrawArcAction::getAvailableDraft() {

	return this->subDrawArcAction->getAvailableDraft();
}

void ShDrawArcAction::invalidate(ShPoint3d &point) {

	this->subDrawArcAction->invalidate(point);
}

ShPoint3d ShDrawArcAction::getLastBasePoint() {

	return this->subDrawArcAction->getLastBasePoint();
}


void ShDrawArcAction::trigger(const ShPoint3d &point) {

	this->subDrawArcAction->trigger(point);
}

void ShDrawArcAction::changeSubAction(SubAction subAction) {

	if (this->subDrawArcAction != nullptr)
		delete this->subDrawArcAction;

	if (subAction == SubAction::ThreePoint)
		this->subDrawArcAction = new ShSubDrawArcAction_ThreePoint(this, this->widget);

	else if (subAction == SubAction::StartCenterEnd)
		this->subDrawArcAction = new ShSubDrawArcAction_StartCenterEnd(this, this->widget);
	else if (subAction == SubAction::StartCenterAngle)
		this->subDrawArcAction = new ShSubDrawArcAction_StartCenterAngle(this, this->widget);
	else if (subAction == SubAction::StartCenterLength)
		this->subDrawArcAction = new ShSubDrawArcAction_StartCenterLength(this, this->widget);

	else if (subAction == SubAction::StartEndAngle)
		this->subDrawArcAction = new ShSubDrawArcAction_StartEndAngle(this, this->widget);
	else if (subAction == SubAction::StartEndDirection)
		this->subDrawArcAction = new ShSubDrawArcAction_StartEndDirection(this, this->widget);
	else if (subAction == SubAction::StartEndRadius)
		this->subDrawArcAction = new ShSubDrawArcAction_StartEndRadius(this, this->widget);

	else if (subAction == SubAction::CenterStartEnd)
		this->subDrawArcAction = new ShSubDrawArcAction_CenterStartEnd(this, this->widget);
	else if (subAction == SubAction::CenterStartAngle)
		this->subDrawArcAction = new ShSubDrawArcAction_CenterStartAngle(this, this->widget);
	else if (subAction == SubAction::CenterStartLength)
		this->subDrawArcAction = new ShSubDrawArcAction_CenterStartLength(this, this->widget);
	
	
}


////////////////////////////////////////////////////////////////////

ShSubDrawArcAction::ShSubDrawArcAction(ShDrawArcAction *drawArcAction, ShCADWidget *widget)
	:drawArcAction(drawArcAction), widget(widget) {

}

ShSubDrawArcAction::~ShSubDrawArcAction() {

}

void ShSubDrawArcAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShSubDrawArcAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ShDrawArcAction::Status& ShSubDrawArcAction::getStatus() {

	return this->drawArcAction->status;
}

void ShSubDrawArcAction::addEntity(ShEntity *newEntity, const QString &type) {

	this->drawArcAction->addEntity(newEntity, type);
}

void ShSubDrawArcAction::triggerSucceeded() {

	this->drawArcAction->triggerSucceeded();
}

void ShSubDrawArcAction::actionFinished() {

	this->drawArcAction->actionFinished();
}

void ShSubDrawArcAction::triggerFailed(ShActionTriggerFailureReason reason) {

	this->drawArcAction->triggerFailed(reason);
}

///////////////////////////////////////////////////////////////////////////////


ShSubDrawArcAction_ThreePoint::ShSubDrawArcAction_ThreePoint(ShDrawArcAction *drawArcAction, ShCADWidget *widget)
	:ShSubDrawArcAction(drawArcAction, widget) {

}

ShSubDrawArcAction_ThreePoint::~ShSubDrawArcAction_ThreePoint() {

}


ActionType ShSubDrawArcAction_ThreePoint::getType() {

	return ActionType::ActionDrawArcThreePoint;
}

QString ShSubDrawArcAction_ThreePoint::getHeadTitle() {

	ShDrawArcAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawArcAction::Status::PickedNothing)
		text = "Arc >> " + shGetLanValue_command("Command/Specify first point on arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedFirstPoint)
		text = "Arc >> " + shGetLanValue_command("Command/Specify second point on arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedSecondPoint)
		text = "Arc >> " + shGetLanValue_command("Command/Specify third point on arc") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawArcAction_ThreePoint::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedFirstPoint ||
		this->getStatus() == ShDrawArcAction::Status::PickedSecondPoint) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);

		ShPoint3d first = this->widget->getRubberBand().getStart();

		draft.setOrthogonalBasePoint(first);
		draft.setSnapBasePoint(first);
	}

	return draft;
}

void ShSubDrawArcAction_ThreePoint::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedFirstPoint) {

		this->widget->getRubberBand().setEnd(point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedSecondPoint) {

		this->widget->getRubberBand().setEnd(point);
		
		ShArcData data;
		this->getArcDataWithThreePoint(this->first, this->second, point, data);

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		prevArc->setData(data);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawArcAction_ThreePoint::getLastBasePoint() {

	ShPoint3d lastBasePoint;

	if (this->getStatus() == ShDrawArcAction::Status::PickedFirstPoint) {

		lastBasePoint = this->first;
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedSecondPoint) {

		lastBasePoint = this->second;
	}

	return lastBasePoint;
}

void ShSubDrawArcAction_ThreePoint::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {

		this->getStatus() = ShDrawArcAction::Status::PickedFirstPoint;

		this->first = point;
		this->widget->getRubberBand().create(ShLineData(point, point));
		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawArcAction::PickedFirstPoint) {

		this->getStatus() = ShDrawArcAction::Status::PickedSecondPoint;

		this->second = point;
		this->widget->getRubberBand().setData(ShLineData(this->second, this->second));

		ShArcData data;
		this->getArcDataWithThreePoint(this->first, this->second, point, data);

		this->widget->getPreview().add(new ShArc(this->widget->getPropertyData(), data, this->widget->getCurrentLayer()));

		this->triggerSucceeded();

	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedSecondPoint) {

		ShArcData data;
		if (this->getArcDataWithThreePoint(this->first,this->second,point,data) == false) {

			this->triggerFailed(ShActionTriggerFailureReason::InvalidPoint);
			return;
		}
		
		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		prevArc->setData(data);

		this->addEntity(prevArc->clone(), "Arc");
		this->actionFinished();
	}
}

bool ShSubDrawArcAction_ThreePoint::getArcDataWithThreePoint(const ShPoint3d &first, const ShPoint3d &second, const ShPoint3d &third, ShArcData &data) {

	if (math::getCenterWithThreePoint(first, second, third, data.center) == false) {
	
		data = ShArcData();
		return false;
	}

	data.radius = math::getDistance(data.center.x, data.center.y, first.x, first.y);

	double startAngle = math::getAbsAngle(data.center.x, data.center.y, third.x, third.y);
	double endAngle = math::getAbsAngle(data.center.x, data.center.y, first.x, first.y);
	double angle = math::getAbsAngle(data.center.x, data.center.y, second.x, second.y);

	if (math::checkAngleLiesOnAngleBetween(startAngle, endAngle, angle) == true) {
		data.startAngle = startAngle;
		data.endAngle = endAngle;
	}
	else {
		data.startAngle = endAngle;
		data.endAngle = startAngle;
	}

	return true;
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

ShSubDrawArcAction_StartCenterEnd::ShSubDrawArcAction_StartCenterEnd(ShDrawArcAction *drawArcAction, ShCADWidget *widget)
	:ShSubDrawArcAction(drawArcAction, widget) {

}

ShSubDrawArcAction_StartCenterEnd::~ShSubDrawArcAction_StartCenterEnd() {

}

ActionType ShSubDrawArcAction_StartCenterEnd::getType() {

	return ActionType::ActionDrawArcStartCenterEnd;
}

QString ShSubDrawArcAction_StartCenterEnd::getHeadTitle() {

	ShDrawArcAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawArcAction::Status::PickedNothing)
		text = "Arc >> " + shGetLanValue_command("Command/Specify start point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedStart)
		text = "Arc >> " + shGetLanValue_command("Command/Specify center point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedCenter)
		text = "Arc >> " + shGetLanValue_command("Command/Specify end point of arc") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawArcAction_StartCenterEnd::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->start);
		draft.setSnapBasePoint(this->start);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {
	
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->center);
		draft.setSnapBasePoint(this->center);
	}

	return draft;
}

void ShSubDrawArcAction_StartCenterEnd::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		this->widget->getRubberBand().setEnd(point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		this->widget->getRubberBand().setEnd(point);

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		ShPoint3d center = prevArc->getCenter();
		double endAngle = math::getAbsAngle(center.x, center.y, point.x, point.y);
		prevArc->setEndAngle(endAngle);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawArcAction_StartCenterEnd::getLastBasePoint() {

	ShPoint3d lastBasePoint;

	if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		lastBasePoint = this->start;
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		lastBasePoint = this->center;
	}

	return lastBasePoint;
}

void ShSubDrawArcAction_StartCenterEnd::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {

		this->getStatus() = ShDrawArcAction::Status::PickedStart;
		this->start = point;
		this->widget->getRubberBand().create(ShLineData(point, point));
		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawArcAction::PickedStart) {

		if (math::compare(point.x, this->start.x) == 0 &&
			math::compare(point.y, this->start.y) == 0) {
		
			this->triggerFailed(InvalidPoint);
			return;
		}

		ShArcData data;
		data.center = point;
		data.radius = math::getDistance(point.x, point.y, this->start.x, this->start.y);
		data.startAngle = math::getAbsAngle(point.x, point.y, this->start.x, this->start.y);
		data.endAngle = data.startAngle;


		this->getStatus() = ShDrawArcAction::Status::PickedCenter;

		this->center = point;
		this->widget->getRubberBand().setData(ShLineData(point, point));

		this->widget->getPreview().add(new ShArc(this->widget->getPropertyData(), data, this->widget->getCurrentLayer()));

		this->triggerSucceeded();

	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		if (math::compare(point.x, this->start.x) == 0 &&
			math::compare(point.y, this->start.y) == 0) {

			this->triggerFailed(InvalidPoint);
			return;
		}

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));

		double endAngle = math::getAbsAngle(this->center.x, this->center.y, point.x, point.y);

		prevArc->setEndAngle(endAngle);

		this->addEntity(prevArc->clone(), "Arc");
		this->actionFinished();
	}
}


////////////////////////////////////////////////////////////////////////////

ShSubDrawArcAction_StartCenterAngle::ShSubDrawArcAction_StartCenterAngle(ShDrawArcAction *drawArcAction, ShCADWidget *widget)
	:ShSubDrawArcAction(drawArcAction, widget) {

}

ShSubDrawArcAction_StartCenterAngle::~ShSubDrawArcAction_StartCenterAngle() {

}

ActionType ShSubDrawArcAction_StartCenterAngle::getType() {

	return ActionType::ActionDrawArcStartCenterAngle;
}

QString ShSubDrawArcAction_StartCenterAngle::getHeadTitle() {

	ShDrawArcAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawArcAction::Status::PickedNothing)
		text = "Arc >> " + shGetLanValue_command("Command/Specify start point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedStart)
		text = "Arc >> " + shGetLanValue_command("Command/Specify center point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedCenter)
		text = "Arc >> " + shGetLanValue_command("Command/Specify included angle") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawArcAction_StartCenterAngle::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->start);
		draft.setSnapBasePoint(this->start);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->center);
		draft.setSnapBasePoint(this->center);
	}

	return draft;
}

void ShSubDrawArcAction_StartCenterAngle::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		this->widget->getRubberBand().setEnd(point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		this->widget->getRubberBand().setEnd(point);

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		
		double angleCenterToPoint = math::getAbsAngle(this->center.x, this->center.y, point.x, point.y);
		double endAngle = math::addAngle(prevArc->getStartAngle(), angleCenterToPoint);
		
		prevArc->setEndAngle(endAngle);
		
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawArcAction_StartCenterAngle::getLastBasePoint() {

	ShPoint3d lastBasePoint;

	if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		lastBasePoint = this->start;
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		lastBasePoint = this->center;
	}

	return lastBasePoint;
}

void ShSubDrawArcAction_StartCenterAngle::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {

		this->getStatus() = ShDrawArcAction::Status::PickedStart;
		this->start = point;
		this->widget->getRubberBand().create(ShLineData(point, point));
		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawArcAction::PickedStart) {

		if (math::compare(point.x, this->start.x) == 0 &&
			math::compare(point.y, this->start.y) == 0) {

			this->triggerFailed(InvalidPoint);
			return;
		}

		ShArcData data;
		data.center = point;
		data.radius = math::getDistance(point.x, point.y, this->start.x, this->start.y);
		data.startAngle = math::getAbsAngle(point.x, point.y, this->start.x, this->start.y);
		data.endAngle = data.startAngle;


		this->getStatus() = ShDrawArcAction::Status::PickedCenter;

		this->center = point;
		this->widget->getRubberBand().setData(ShLineData(point, point));

		this->widget->getPreview().add(new ShArc(this->widget->getPropertyData(), data, this->widget->getCurrentLayer()));

		this->triggerSucceeded();

	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		ShArcData data = prevArc->getData();

		double angleCenterToPoint = math::getAbsAngle(this->center.x, this->center.y, point.x, point.y);
		data.endAngle = math::addAngle(data.startAngle, angleCenterToPoint);

		if (math::compare(data.startAngle, data.endAngle) == 0) {
			this->triggerFailed(InvalidPoint);
			return;
		}

		prevArc->setData(data);

		this->addEntity(prevArc->clone(), "Arc");
		this->actionFinished();
	}
}

///////////////////////////////////////////////////////////////

ShSubDrawArcAction_StartCenterLength::ShSubDrawArcAction_StartCenterLength(ShDrawArcAction *drawArcAction, ShCADWidget *widget)
	:ShSubDrawArcAction(drawArcAction, widget) {

}

ShSubDrawArcAction_StartCenterLength::~ShSubDrawArcAction_StartCenterLength() {

}

ActionType ShSubDrawArcAction_StartCenterLength::getType() {

	return ActionType::ActionDrawArcStartCenterLength;
}

QString ShSubDrawArcAction_StartCenterLength::getHeadTitle() {

	ShDrawArcAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawArcAction::Status::PickedNothing)
		text = "Arc >> " + shGetLanValue_command("Command/Specify start point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedStart)
		text = "Arc >> " + shGetLanValue_command("Command/Specify center point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedCenter)
		text = "Arc >> " + shGetLanValue_command("Command/Specify length of chord") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawArcAction_StartCenterLength::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->start);
		draft.setSnapBasePoint(this->start);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {
		//special case
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->start);
		draft.setSnapBasePoint(this->start);
	}

	return draft;
}

void ShSubDrawArcAction_StartCenterLength::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		this->widget->getRubberBand().setEnd(point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		this->widget->getRubberBand().setEnd(point);

		ShArcData data;
		this->getArcDataWithStartCenterLength(this->start, this->center, math::getDistance(this->start.x, this->start.y, point.x, point.y), data);

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		prevArc->setData(data);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawArcAction_StartCenterLength::getLastBasePoint() {

	ShPoint3d lastBasePoint;

	if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		lastBasePoint = this->start;
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {
		//special case
		lastBasePoint = this->start;
	}

	return lastBasePoint;
}

void ShSubDrawArcAction_StartCenterLength::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {

		this->getStatus() = ShDrawArcAction::Status::PickedStart;
		this->start = point;
		this->widget->getRubberBand().create(ShLineData(point, point));
		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawArcAction::PickedStart) {

		ShArcData data;
		this->getArcDataWithStartCenterLength(this->start, point, math::getDistance(this->start.x, this->start.y, point.x, point.y), data);

		this->getStatus() = ShDrawArcAction::Status::PickedCenter;

		this->center = point;
		this->widget->getRubberBand().setEnd(point);

		this->widget->getPreview().add(new ShArc(this->widget->getPropertyData(), data, this->widget->getCurrentLayer()));

		this->triggerSucceeded();

	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		ShArcData data;
		
		if (this->getArcDataWithStartCenterLength(this->start, this->center,
			math::getDistance(this->start.x, this->start.y, point.x, point.y), data) == false) {
		
			this->triggerFailed(InvalidPoint);
			return;
		}

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		prevArc->setData(data);

		this->addEntity(prevArc->clone(), "Arc");
		this->actionFinished();
	}
}

bool ShSubDrawArcAction_StartCenterLength::getArcDataWithStartCenterLength(const ShPoint3d &start, const ShPoint3d &center, double length, ShArcData &data) {

	double radius = math::getDistance(center.x, center.y, start.x, start.y);
	double height = length / 2;
	double angle = asin(height / radius) * 180 / 3.1415926535897;

	data.radius = radius;
	data.center = center;
	data.startAngle = math::getAbsAngle(center.x, center.y, start.x, start.y);

	if (math::compare(radius, length) == 1 || math::compare(radius, length) == 0) {
		data.endAngle = math::addAngle(data.startAngle, angle * 2);
		return true;
	}

	data.endAngle = data.startAngle;
	return false;

}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

ShSubDrawArcAction_StartEndAngle::ShSubDrawArcAction_StartEndAngle(ShDrawArcAction *drawArcAction, ShCADWidget *widget)
	:ShSubDrawArcAction(drawArcAction, widget) {

}

ShSubDrawArcAction_StartEndAngle::~ShSubDrawArcAction_StartEndAngle() {

}

ActionType ShSubDrawArcAction_StartEndAngle::getType() {

	return ActionType::ActionDrawArcStartEndAngle;
}

QString ShSubDrawArcAction_StartEndAngle::getHeadTitle() {

	ShDrawArcAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawArcAction::Status::PickedNothing)
		text = "Arc >> " + shGetLanValue_command("Command/Specify start point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedStart)
		text = "Arc >> " + shGetLanValue_command("Command/Specify end point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedEnd)
		text = "Arc >> " + shGetLanValue_command("Command/Specify included angle") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawArcAction_StartEndAngle::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->start);
		draft.setSnapBasePoint(this->start);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedEnd) {
		//special case
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->start);
		draft.setSnapBasePoint(this->start);
	}

	return draft;
}

void ShSubDrawArcAction_StartEndAngle::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		this->widget->getRubberBand().setEnd(point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedEnd) {

		this->widget->getRubberBand().setEnd(point);

		ShArcData data;
		this->getArcDataWithStartEndAnother(this->start, this->end, point, data);

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		prevArc->setData(data);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawArcAction_StartEndAngle::getLastBasePoint() {

	ShPoint3d lastBasePoint;

	if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		lastBasePoint = this->start;
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedEnd) {
		//special case
		lastBasePoint = this->start;
	}

	return lastBasePoint;
}

void ShSubDrawArcAction_StartEndAngle::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {

		this->getStatus() = ShDrawArcAction::Status::PickedStart;
		this->start = point;
		this->widget->getRubberBand().create(ShLineData(point, point));
		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawArcAction::PickedStart) {

		double dis = math::getDistance(this->start.x, this->start.y, point.x, point.y);
		
		if (math::compare(dis, 0) == 0) {
		
			this->triggerFailed(InvalidPoint);
			return;
		}

		this->getStatus() = ShDrawArcAction::Status::PickedEnd;

		this->end = point;
		this->widget->getRubberBand().setEnd(point);

		ShArcData data;
		this->getArcDataWithStartEndAnother(this->start, this->end, point, data);
		this->widget->getPreview().add(new ShArc(this->widget->getPropertyData(), data, this->widget->getCurrentLayer()));

		this->triggerSucceeded();

	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedEnd) {

		ShArcData data;
		this->getArcDataWithStartEndAnother(this->start, this->end, point, data);

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		prevArc->setData(data);

		this->addEntity(prevArc->clone(), "Arc");
		this->actionFinished();
	}
}

bool ShSubDrawArcAction_StartEndAngle::getArcDataWithStartEndAnother(const ShPoint3d &start, const ShPoint3d &end, const ShPoint3d &another, ShArcData &data) {

	double angle = math::getAbsAngle(start.x, start.y, another.x, another.y);

	double disStartToEnd = math::getDistance(start.x, start.y, end.x, end.y);
	double baseSide = disStartToEnd / 2;

	double angleBetweenBaseSideAndHypotenuse = 90 - angle / 2;

	double height = tan((angleBetweenBaseSideAndHypotenuse*3.1415926535897) / 180);

	double angleStartToEnd = math::getAbsAngle(start.x, start.y, end.x, end.y);

	math::rotate(angleStartToEnd, start.x, start.y, start.x + baseSide, start.y + height, data.center.x, data.center.y);

	data.startAngle = math::getAbsAngle(data.center.x, data.center.y, start.x, start.y);
	data.endAngle = math::getAbsAngle(data.center.x, data.center.y, end.x, end.y);
	data.radius = math::getDistance(data.center.x, data.center.y, start.x, start.y);

	return true;
}

//////////////////////////////////////////////////////////////////

ShSubDrawArcAction_StartEndDirection::ShSubDrawArcAction_StartEndDirection(ShDrawArcAction *drawArcAction, ShCADWidget *widget)
	:ShSubDrawArcAction(drawArcAction, widget) {

}

ShSubDrawArcAction_StartEndDirection::~ShSubDrawArcAction_StartEndDirection() {

}

ActionType ShSubDrawArcAction_StartEndDirection::getType() {

	return ActionType::ActionDrawArcStartEndDirection;
}

QString ShSubDrawArcAction_StartEndDirection::getHeadTitle() {

	ShDrawArcAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawArcAction::Status::PickedNothing)
		text = "Arc >> " + shGetLanValue_command("Command/Specify start point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedStart)
		text = "Arc >> " + shGetLanValue_command("Command/Specify end point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedEnd)
		text = "Arc >> " + shGetLanValue_command("Command/Specify tangent direction for the start point of arc") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawArcAction_StartEndDirection::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->start);
		draft.setSnapBasePoint(this->start);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedEnd) {
		//special case
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->start);
		draft.setSnapBasePoint(this->start);
	}

	return draft;
}

void ShSubDrawArcAction_StartEndDirection::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		this->widget->getRubberBand().setEnd(point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedEnd) {

		this->widget->getRubberBand().setEnd(point);

		ShArcData data = this->getArcDataWithTwoPointTangentLine(this->start, this->end,
			this->widget->getRubberBand().getStart(), this->widget->getRubberBand().getEnd());

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		prevArc->setData(data);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawArcAction_StartEndDirection::getLastBasePoint() {

	ShPoint3d lastBasePoint;

	if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		lastBasePoint = this->start;
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedEnd) {
		//special case
		lastBasePoint = this->start;
	}

	return lastBasePoint;
}

void ShSubDrawArcAction_StartEndDirection::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {

		this->getStatus() = ShDrawArcAction::Status::PickedStart;
		this->start = point;
		this->widget->getRubberBand().create(ShLineData(point, point));
		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawArcAction::PickedStart) {

		double dis = math::getDistance(this->start.x, this->start.y, point.x, point.y);

		if (math::compare(dis, 0) == 0) {
			
			this->triggerFailed(InvalidPoint);
			return;
		}

		this->getStatus() = ShDrawArcAction::Status::PickedEnd;

		this->end = point;
		this->widget->getRubberBand().setEnd(point);

		ShArcData data = this->getArcDataWithTwoPointTangentLine(this->start, this->end, 
			this->widget->getRubberBand().getStart(), this->widget->getRubberBand().getEnd());
		
		this->widget->getPreview().add(new ShArc(this->widget->getPropertyData(), data, this->widget->getCurrentLayer()));

		this->triggerSucceeded();

	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedEnd) {

		ShArcData data = this->getArcDataWithTwoPointTangentLine(this->start, this->end,
			this->widget->getRubberBand().getStart(), this->widget->getRubberBand().getEnd());

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		prevArc->setData(data);

		this->addEntity(prevArc->clone(), "Arc");
		this->actionFinished();
	}
}

ShArcData ShSubDrawArcAction_StartEndDirection::getArcDataWithTwoPointTangentLine(const ShPoint3d &first, const ShPoint3d &second, 
	const ShPoint3d &lineStart, const ShPoint3d &lineEnd) {

	double angleStartToEnd = math::getAbsAngle(lineStart.x, lineStart.y, lineEnd.x, lineEnd.y);
	ShPoint3d tempEnd;
	math::rotate(angleStartToEnd + 90, first.x, first.y, first.x + 10, first.y, tempEnd.x, tempEnd.y);


	double angleFirstToSecond = math::getAbsAngle(first.x, first.y, second.x, second.y);

	double difference = math::getAngleDifference(angleStartToEnd, angleFirstToSecond);
	ShPoint3d tempEnd2;
	math::rotate(angleFirstToSecond + 90 + difference, second.x, second.y, second.x + 10, second.y, tempEnd2.x, tempEnd2.y);

	ShPoint3d center;
	math::checkLineLineIntersect(first, tempEnd, second, tempEnd2, center);

	ShArcData data;

	data.center = center;
	data.radius = math::getDistance(data.center.x, data.center.y, first.x, first.y);

	double angleCenterToFirst = math::getAbsAngle(data.center.x, data.center.y, first.x, first.y);
	double angleCenterToSecond = math::getAbsAngle(data.center.x, data.center.y, second.x, second.y);

	if (math::checkAngleLiesOnAngleBetween(angleFirstToSecond, math::addAngle(angleFirstToSecond, 180), angleStartToEnd) == true) {
		data.startAngle = angleCenterToSecond;
		data.endAngle = angleCenterToFirst;
	}
	else {
		data.startAngle = angleCenterToFirst;
		data.endAngle = angleCenterToSecond;
	}


	return data;
}

/////////////////////////////////////////////////////////////////

ShSubDrawArcAction_StartEndRadius::ShSubDrawArcAction_StartEndRadius(ShDrawArcAction *drawArcAction, ShCADWidget *widget)
	:ShSubDrawArcAction(drawArcAction, widget) {

}

ShSubDrawArcAction_StartEndRadius::~ShSubDrawArcAction_StartEndRadius() {

}

ActionType ShSubDrawArcAction_StartEndRadius::getType() {

	return ActionType::ActionDrawArcStartEndRadius;
}

QString ShSubDrawArcAction_StartEndRadius::getHeadTitle() {

	ShDrawArcAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawArcAction::Status::PickedNothing)
		text = "Arc >> " + shGetLanValue_command("Command/Specify start point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedStart)
		text = "Arc >> " + shGetLanValue_command("Command/Specify end point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedEnd)
		text = "Arc >> " + shGetLanValue_command("Command/Specify radius of arc") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawArcAction_StartEndRadius::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->start);
		draft.setSnapBasePoint(this->start);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedEnd) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->end);
		draft.setSnapBasePoint(this->end);
	}

	return draft;
}

void ShSubDrawArcAction_StartEndRadius::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		this->widget->getRubberBand().setEnd(point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedEnd) {

		this->widget->getRubberBand().setEnd(point);

		ShArcData data;
		this->getArcDataWithStartEndAnother(this->start, this->end, point, data);

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		prevArc->setData(data);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawArcAction_StartEndRadius::getLastBasePoint() {

	ShPoint3d lastBasePoint;

	if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		lastBasePoint = this->start;
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedEnd) {

		lastBasePoint = this->end;
	}

	return lastBasePoint;
}

void ShSubDrawArcAction_StartEndRadius::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {

		this->getStatus() = ShDrawArcAction::Status::PickedStart;
		this->start = point;
		this->widget->getRubberBand().create(ShLineData(point, point));
		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawArcAction::PickedStart) {

		double dis = math::getDistance(this->start.x, this->start.y, point.x, point.y);

		if (math::compare(dis, 0) == 0) {

			this->triggerFailed(InvalidPoint);
			return;
		}

		this->getStatus() = ShDrawArcAction::Status::PickedEnd;

		this->end = point;
		this->widget->getRubberBand().setData(ShLineData(this->end, this->end));

		ShArcData data;
		this->getArcDataWithStartEndAnother(this->start, this->end, point, data);

		this->widget->getPreview().add(new ShArc(this->widget->getPropertyData(), data, this->widget->getCurrentLayer()));

		this->triggerSucceeded();

	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedEnd) {

		ShArcData data;
		this->getArcDataWithStartEndAnother(this->start, this->end, point, data);

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		prevArc->setData(data);

		this->addEntity(prevArc->clone(), "Arc");
		this->actionFinished();
	}
}

bool ShSubDrawArcAction_StartEndRadius::getArcDataWithStartEndAnother(const ShPoint3d &start, const ShPoint3d &end, const ShPoint3d &another, ShArcData &data) {

	double radius = math::getDistance(end.x, end.y, another.x, another.y);

	double angleStartToEnd = math::getAbsAngle(start.x, start.y, end.x, end.y);
	double disStartToEnd = math::getDistance(start.x, start.y, end.x, end.y);

	double baseSide = disStartToEnd / 2;
	double height = sqrt((radius*radius) - (baseSide*baseSide));

	if (math::compare(radius, baseSide) == 1) {

		math::rotate(angleStartToEnd, start.x, start.y, start.x + baseSide, start.y + height, data.center.x, data.center.y);
		data.radius = radius;
	}
	else {

		math::rotate(angleStartToEnd, start.x, start.y, start.x + baseSide, start.y, data.center.x, data.center.y);
		data.radius = baseSide;
	}

	data.startAngle = math::getAbsAngle(data.center.x, data.center.y, start.x, start.y);
	data.endAngle = math::getAbsAngle(data.center.x, data.center.y, end.x, end.y);

	return true;
}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


ShSubDrawArcAction_CenterStartEnd::ShSubDrawArcAction_CenterStartEnd(ShDrawArcAction *drawArcAction, ShCADWidget *widget)
	:ShSubDrawArcAction(drawArcAction, widget) {

}

ShSubDrawArcAction_CenterStartEnd::~ShSubDrawArcAction_CenterStartEnd() {

}

ActionType ShSubDrawArcAction_CenterStartEnd::getType() {

	return ActionType::ActionDrawArcCenterStartEnd;
}

QString ShSubDrawArcAction_CenterStartEnd::getHeadTitle() {

	ShDrawArcAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawArcAction::Status::PickedNothing)
		text = "Arc >> " + shGetLanValue_command("Command/Specify center point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedCenter)
		text = "Arc >> " + shGetLanValue_command("Command/Specify start point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedStart)
		text = "Arc >> " + shGetLanValue_command("Command/Specify end of arc") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawArcAction_CenterStartEnd::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->center);
		draft.setSnapBasePoint(this->center);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->center);
		draft.setSnapBasePoint(this->center);
	}

	return draft;
}

void ShSubDrawArcAction_CenterStartEnd::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		this->widget->getRubberBand().setEnd(point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		this->widget->getRubberBand().setEnd(point);

		double endAngle = math::getAbsAngle(this->center.x, this->center.y, point.x, point.y);

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		prevArc->setEndAngle(endAngle);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawArcAction_CenterStartEnd::getLastBasePoint() {

	ShPoint3d lastBasePoint;

	if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		lastBasePoint = this->center;
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		lastBasePoint = this->center;
	}

	return lastBasePoint;
}

void ShSubDrawArcAction_CenterStartEnd::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {

		this->getStatus() = ShDrawArcAction::Status::PickedCenter;
		this->center = point;
		this->widget->getRubberBand().create(ShLineData(point, point));
		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawArcAction::PickedCenter) {

		if (math::compare(point.x, this->center.x) == 0 &&
			math::compare(point.y, this->center.y) == 0) {

			this->triggerFailed(InvalidPoint);
			return;
		}

		ShArcData data;
		data.center = this->center;
		data.radius = math::getDistance(this->center.x, this->center.y, point.x, point.y);
		data.startAngle = math::getAbsAngle(this->center.x, this->center.y, point.x, point.y);
		data.endAngle = data.startAngle;

		this->getStatus() = ShDrawArcAction::Status::PickedStart;

		this->start = point;
		this->widget->getRubberBand().setEnd(point);

		this->widget->getPreview().add(new ShArc(this->widget->getPropertyData(), data, this->widget->getCurrentLayer()));

		this->triggerSucceeded();

	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		double endAngle = math::getAbsAngle(this->center.x, this->center.y, point.x, point.y);
		
		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));

		if (math::compare(prevArc->getStartAngle(), endAngle) == 0) {
		
			this->triggerFailed(InvalidPoint);
			return;
		}

		prevArc->setEndAngle(endAngle);

		this->addEntity(prevArc->clone(), "Arc");
		this->actionFinished();
	}
}


///////////////////////////////////////////////////////////


ShSubDrawArcAction_CenterStartAngle::ShSubDrawArcAction_CenterStartAngle(ShDrawArcAction *drawArcAction, ShCADWidget *widget)
	:ShSubDrawArcAction(drawArcAction, widget) {

}

ShSubDrawArcAction_CenterStartAngle::~ShSubDrawArcAction_CenterStartAngle() {

}

ActionType ShSubDrawArcAction_CenterStartAngle::getType() {

	return ActionType::ActionDrawArcCenterStartAngle;
}

QString ShSubDrawArcAction_CenterStartAngle::getHeadTitle() {

	ShDrawArcAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawArcAction::Status::PickedNothing)
		text = "Arc >> " + shGetLanValue_command("Command/Specify center point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedCenter)
		text = "Arc >> " + shGetLanValue_command("Command/Specify start point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedStart)
		text = "Arc >> " + shGetLanValue_command("Command/Specify included angle") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawArcAction_CenterStartAngle::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->center);
		draft.setSnapBasePoint(this->center);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->center);
		draft.setSnapBasePoint(this->center);
	}

	return draft;
}

void ShSubDrawArcAction_CenterStartAngle::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		this->widget->getRubberBand().setEnd(point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		this->widget->getRubberBand().setEnd(point);

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		
		double angleCenterToPoint = math::getAbsAngle(this->center.x, this->center.y, point.x, point.y);
		double endAngle = math::addAngle(prevArc->getStartAngle(), angleCenterToPoint);

		prevArc->setEndAngle(endAngle);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawArcAction_CenterStartAngle::getLastBasePoint() {

	ShPoint3d lastBasePoint;

	if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		lastBasePoint = this->center;
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		lastBasePoint = this->center;
	}

	return lastBasePoint;
}

void ShSubDrawArcAction_CenterStartAngle::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {

		this->getStatus() = ShDrawArcAction::Status::PickedCenter;
		this->center = point;
		this->widget->getRubberBand().create(ShLineData(point, point));
		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawArcAction::PickedCenter) {

		if (math::compare(point.x, this->center.x) == 0 &&
			math::compare(point.y, this->center.y) == 0) {

			this->triggerFailed(InvalidPoint);
			return;
		}

		ShArcData data;
		data.center = this->center;
		data.radius = math::getDistance(this->center.x, this->center.y, point.x, point.y);
		data.startAngle = math::getAbsAngle(this->center.x, this->center.y, point.x, point.y);
		data.endAngle = data.startAngle;

		this->getStatus() = ShDrawArcAction::Status::PickedStart;

		this->start = point;
		this->widget->getRubberBand().setEnd(point);

		this->widget->getPreview().add(new ShArc(this->widget->getPropertyData(), data, this->widget->getCurrentLayer()));

		this->triggerSucceeded();

	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		ShArcData data = prevArc->getData();

		double angleCenterToPoint = math::getAbsAngle(this->center.x, this->center.y, point.x, point.y);
		data.endAngle = math::addAngle(data.startAngle, angleCenterToPoint);

		if (math::compare(data.startAngle, data.endAngle) == 0) {
		
			this->triggerFailed(InvalidPoint);
			return;
		}

		prevArc->setData(data);

		this->addEntity(prevArc->clone(), "Arc");
		this->actionFinished();
	}
}


///////////////////////////////////////////////////////////////////


ShSubDrawArcAction_CenterStartLength::ShSubDrawArcAction_CenterStartLength(ShDrawArcAction *drawArcAction, ShCADWidget *widget)
	:ShSubDrawArcAction(drawArcAction, widget) {

}

ShSubDrawArcAction_CenterStartLength::~ShSubDrawArcAction_CenterStartLength() {

}

ActionType ShSubDrawArcAction_CenterStartLength::getType() {

	return ActionType::ActionDrawArcCenterStartLength;
}

QString ShSubDrawArcAction_CenterStartLength::getHeadTitle() {

	ShDrawArcAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawArcAction::Status::PickedNothing)
		text = "Arc >> " + shGetLanValue_command("Command/Specify center point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedCenter)
		text = "Arc >> " + shGetLanValue_command("Command/Specify start point of arc") + ": ";
	else if (status == ShDrawArcAction::Status::PickedStart)
		text = "Arc >> " + shGetLanValue_command("Command/Specify length of chord") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawArcAction_CenterStartLength::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->center);
		draft.setSnapBasePoint(this->center);
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->start);
		draft.setSnapBasePoint(this->start);
	}

	return draft;
}

void ShSubDrawArcAction_CenterStartLength::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		this->widget->getRubberBand().setEnd(point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		this->widget->getRubberBand().setEnd(point);

		ShArcData data;
		this->getArcDataWithCenterStartLength(this->center, this->start, math::getDistance(this->start.x, this->start.y, point.x, point.y), data);

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		prevArc->setData(data);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawArcAction_CenterStartLength::getLastBasePoint() {

	ShPoint3d lastBasePoint;

	if (this->getStatus() == ShDrawArcAction::Status::PickedCenter) {

		lastBasePoint = this->center;
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		lastBasePoint = this->start;
	}

	return lastBasePoint;
}

void ShSubDrawArcAction_CenterStartLength::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawArcAction::Status::PickedNothing) {

		this->getStatus() = ShDrawArcAction::Status::PickedCenter;
		this->center = point;
		this->widget->getRubberBand().create(ShLineData(point, point));
		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawArcAction::PickedCenter) {

		if (math::compare(point.x, this->center.x) == 0 &&
			math::compare(point.y, this->center.y) == 0) {

			this->triggerFailed(InvalidPoint);
			return;
		}

		this->getStatus() = ShDrawArcAction::Status::PickedStart;

		this->start = point;

		ShArcData data;
		this->getArcDataWithCenterStartLength(this->center, this->start, math::getDistance(this->start.x, this->start.y, point.x, point.y), data);
		
		this->widget->getRubberBand().setData(ShLineData(this->start, this->start));

		this->widget->getPreview().add(new ShArc(this->widget->getPropertyData(), data, this->widget->getCurrentLayer()));

		this->triggerSucceeded();

	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedStart) {

		ShArcData data;
		if (this->getArcDataWithCenterStartLength(this->center, this->start,
			math::getDistance(this->start.x, this->start.y, point.x, point.y), data) == false) {
		
			this->triggerFailed(InvalidPoint);
			return;
		}

		ShArc *prevArc = dynamic_cast<ShArc*>((*this->widget->getPreview().begin()));
		prevArc->setData(data);

		this->addEntity(prevArc->clone(), "Arc");
		this->actionFinished();
	}
}

bool ShSubDrawArcAction_CenterStartLength::getArcDataWithCenterStartLength(const ShPoint3d &center, const ShPoint3d &start, double length, ShArcData &data) {

	double radius = math::getDistance(center.x, center.y, start.x, start.y);
	double height = length / 2;
	double angle = asin(height / radius) * 180 / 3.1415926535897;


	data.radius = radius;
	data.center = center;
	data.startAngle = math::getAbsAngle(center.x, center.y, start.x, start.y);

	if (math::compare(radius, length) == 1 || math::compare(radius, length) == 0) {
		data.endAngle = math::addAngle(data.startAngle, angle * 2);
		return true;
	}

	data.endAngle = data.startAngle;
	return false;
}

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

ShPoint3d ShDrawArcAction::getLastPickedPoint() {

	return this->subDrawArcAction->getLastPickedPoint();
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

ShPoint3d ShSubDrawArcAction_ThreePoint::getLastPickedPoint() {

	ShPoint3d lastPickedPoint;

	if (this->getStatus() == ShDrawArcAction::Status::PickedFirstPoint) {

		lastPickedPoint = this->first;
	}
	else if (this->getStatus() == ShDrawArcAction::Status::PickedSecondPoint) {

		lastPickedPoint = this->second;
	}

	return lastPickedPoint;
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

			//Fail.
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

}

void ShSubDrawArcAction_StartCenterEnd::invalidate(ShPoint3d &point) {

}

ShPoint3d ShSubDrawArcAction_StartCenterEnd::getLastPickedPoint() {

}

void ShSubDrawArcAction_StartCenterEnd::trigger(const ShPoint3d &point) {


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

}

void ShSubDrawArcAction_StartCenterAngle::invalidate(ShPoint3d &point) {

}

ShPoint3d ShSubDrawArcAction_StartCenterAngle::getLastPickedPoint() {

}

void ShSubDrawArcAction_StartCenterAngle::trigger(const ShPoint3d &point) {


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

}

void ShSubDrawArcAction_StartCenterLength::invalidate(ShPoint3d &point) {

}

ShPoint3d ShSubDrawArcAction_StartCenterLength::getLastPickedPoint() {

}

void ShSubDrawArcAction_StartCenterLength::trigger(const ShPoint3d &point) {


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

}

void ShSubDrawArcAction_StartEndAngle::invalidate(ShPoint3d &point) {

}

ShPoint3d ShSubDrawArcAction_StartEndAngle::getLastPickedPoint() {

}

void ShSubDrawArcAction_StartEndAngle::trigger(const ShPoint3d &point) {


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

}

void ShSubDrawArcAction_StartEndDirection::invalidate(ShPoint3d &point) {

}

ShPoint3d ShSubDrawArcAction_StartEndDirection::getLastPickedPoint() {

}

void ShSubDrawArcAction_StartEndDirection::trigger(const ShPoint3d &point) {


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

}

void ShSubDrawArcAction_StartEndRadius::invalidate(ShPoint3d &point) {

}

ShPoint3d ShSubDrawArcAction_StartEndRadius::getLastPickedPoint() {

}

void ShSubDrawArcAction_StartEndRadius::trigger(const ShPoint3d &point) {


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

}

void ShSubDrawArcAction_CenterStartEnd::invalidate(ShPoint3d &point) {

}

ShPoint3d ShSubDrawArcAction_CenterStartEnd::getLastPickedPoint() {

}

void ShSubDrawArcAction_CenterStartEnd::trigger(const ShPoint3d &point) {


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

}

void ShSubDrawArcAction_CenterStartAngle::invalidate(ShPoint3d &point) {

}

ShPoint3d ShSubDrawArcAction_CenterStartAngle::getLastPickedPoint() {

}

void ShSubDrawArcAction_CenterStartAngle::trigger(const ShPoint3d &point) {


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

}

void ShSubDrawArcAction_CenterStartLength::invalidate(ShPoint3d &point) {

}

ShPoint3d ShSubDrawArcAction_CenterStartLength::getLastPickedPoint() {

}

void ShSubDrawArcAction_CenterStartLength::trigger(const ShPoint3d &point) {


}
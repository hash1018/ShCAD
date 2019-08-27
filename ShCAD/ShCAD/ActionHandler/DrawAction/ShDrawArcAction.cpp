
#include "ShDrawArcAction.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShArc.h"


ShDrawArcAction::ShDrawArcAction(ShCADWidget *widget, SubAction subAction)
	:ShDrawAction(widget), status(PickedNothing), subAction(subAction), subDrawArcAction(nullptr) {

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
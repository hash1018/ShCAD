
#include "ShDrawCircleAction.h"
#include "Entity\Leaf\ShCircle.h"
#include "Base\ShMath.h"

ShDrawCircleAction::ShDrawCircleAction(ShCADWidget *widget, SubAction subAction)
	:ShDrawAction(widget), status(PickedNothing), subAction(subAction), subDrawCircleAction(nullptr) {

	this->changeSubAction(subAction);
}

ShDrawCircleAction::~ShDrawCircleAction() {

	if (this->subDrawCircleAction != nullptr)
		delete this->subDrawCircleAction;
}

void ShDrawCircleAction::mouseLeftPressEvent(ShActionData &data) {

	this->subDrawCircleAction->mouseLeftPressEvent(data);
}

void ShDrawCircleAction::mouseMoveEvent(ShActionData &data) {

	this->subDrawCircleAction->mouseMoveEvent(data);
}

ActionType ShDrawCircleAction::getType() {

	return this->subDrawCircleAction->getType();
}

QString ShDrawCircleAction::getHeadTitle() {

	return this->subDrawCircleAction->getHeadTitle();
}

ShAvailableDraft ShDrawCircleAction::getAvailableDraft() {

	return this->subDrawCircleAction->getAvailableDraft();
}

void ShDrawCircleAction::invalidate(ShPoint3d &point) {

	this->subDrawCircleAction->invalidate(point);
}

ShPoint3d ShDrawCircleAction::getLastPickedPoint() {

	return this->subDrawCircleAction->getLastPickedPoint();
}


void ShDrawCircleAction::trigger(const ShPoint3d &point) {

	this->subDrawCircleAction->trigger(point);
}

void ShDrawCircleAction::changeSubAction(SubAction subAction) {

	if (this->subDrawCircleAction != nullptr)
		delete this->subDrawCircleAction;

	if (subAction == SubAction::CenterRadius)
		this->subDrawCircleAction = new ShSubDrawCircleAction_CenterRadius(this, this->widget);
	else if (subAction == SubAction::CenterDiameter)
		this->subDrawCircleAction = new ShSubDrawCircleAction_CenterDiameter(this, this->widget);
	else if (subAction == SubAction::TwoPoint)
		this->subDrawCircleAction = new ShSubDrawCircleAction_TwoPoint(this, this->widget);
}


////////////////////////////////////////////////////////////////////

ShSubDrawCircleAction::ShSubDrawCircleAction(ShDrawCircleAction *drawCircleAction, ShCADWidget *widget)
	:drawCircleAction(drawCircleAction), widget(widget) {

}

ShSubDrawCircleAction::~ShSubDrawCircleAction() {

}

ShDrawCircleAction::Status& ShSubDrawCircleAction::getStatus() {

	return this->drawCircleAction->status;
}

void ShSubDrawCircleAction::addEntity(ShEntity *newEntity, const QString &type) {

	this->drawCircleAction->addEntity(newEntity, type);
}

void ShSubDrawCircleAction::triggerSucceeded() {

	this->drawCircleAction->triggerSucceeded();
}

void ShSubDrawCircleAction::actionFinished() {

	this->drawCircleAction->actionFinished();
}

//////////////////////////////////////////////////////////////////////


ShSubDrawCircleAction_CenterRadius::ShSubDrawCircleAction_CenterRadius(ShDrawCircleAction *drawCircleAction, ShCADWidget *widget)
	:ShSubDrawCircleAction(drawCircleAction, widget) {

}

ShSubDrawCircleAction_CenterRadius::~ShSubDrawCircleAction_CenterRadius() {

}

void ShSubDrawCircleAction_CenterRadius::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShSubDrawCircleAction_CenterRadius::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShSubDrawCircleAction_CenterRadius::getType() {

	return ActionType::ActionDrawCircleCenterRadius;
}

QString ShSubDrawCircleAction_CenterRadius::getHeadTitle() {

	ShDrawCircleAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawCircleAction::Status::PickedNothing)
		text = "Circle >> " + shGetLanValue_command("Command/Specify center point") + ": ";
	else if(status== ShDrawCircleAction::Status::PickedCenter)
		text = "Circle >> " + shGetLanValue_command("Command/Specify radius of circle") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawCircleAction_CenterRadius::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawCircleAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawCircleAction::Status::PickedCenter) {
	
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);

		ShCircle *prevCircle = dynamic_cast<ShCircle*>((*this->widget->getPreview().begin()));
		ShPoint3d center = prevCircle->getCenter();

		draft.setOrthogonalBasePoint(center);
		draft.setSnapBasePoint(center);
	}

	return draft;
}

void ShSubDrawCircleAction_CenterRadius::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawCircleAction::Status::PickedCenter) {
	
		ShCircle *prevCircle = dynamic_cast<ShCircle*>((*this->widget->getPreview().begin()));
		ShPoint3d center = prevCircle->getCenter();

		double radius = math::getDistance(center.x, center.y, point.x, point.y);

		prevCircle->setRadius(radius);

		this->widget->getRubberBand().setEnd(point);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawCircleAction_CenterRadius::getLastPickedPoint() {

	ShPoint3d lastPickedPoint;

	if (this->getStatus() == ShDrawCircleAction::Status::PickedCenter) {
	
		ShCircle *prevCircle = dynamic_cast<ShCircle*>((*this->widget->getPreview().begin()));
		lastPickedPoint = prevCircle->getCenter();
		
	}

	return lastPickedPoint;
}
	
void ShSubDrawCircleAction_CenterRadius::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawCircleAction::Status::PickedNothing) {
	
		this->getStatus() = ShDrawCircleAction::Status::PickedCenter;

		this->widget->getPreview().add(new ShCircle(this->widget->getPropertyData(), ShCircleData(point, 0), this->widget->getCurrentLayer()));
		this->widget->getRubberBand().create(ShLineData(point, point));

		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawCircleAction::PickedCenter) {
	
		ShCircle *prevCircle = dynamic_cast<ShCircle*>((*this->widget->getPreview().begin()));
		ShCircleData data = prevCircle->getData();

		data.radius = math::getDistance(data.center.x, data.center.y, point.x, point.y);

		prevCircle->setData(data);

		this->addEntity(prevCircle->clone(), "Circle");
		this->actionFinished();
	}
}




////////////////////////////////////////////////////////////////////////////////////////////




ShSubDrawCircleAction_CenterDiameter::ShSubDrawCircleAction_CenterDiameter(ShDrawCircleAction *drawCircleAction, ShCADWidget *widget)
	:ShSubDrawCircleAction(drawCircleAction, widget) {

}

ShSubDrawCircleAction_CenterDiameter::~ShSubDrawCircleAction_CenterDiameter() {

}

void ShSubDrawCircleAction_CenterDiameter::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShSubDrawCircleAction_CenterDiameter::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShSubDrawCircleAction_CenterDiameter::getType() {

	return ActionType::ActionDrawCircleCenterDiameter;
}

QString ShSubDrawCircleAction_CenterDiameter::getHeadTitle() {

	ShDrawCircleAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawCircleAction::Status::PickedNothing)
		text = "Circle >> " + shGetLanValue_command("Command/Specify center point") + ": ";
	else if (status == ShDrawCircleAction::Status::PickedCenter)
		text = "Circle >> " + shGetLanValue_command("Command/Specify diameter of circle") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawCircleAction_CenterDiameter::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawCircleAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawCircleAction::Status::PickedCenter) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);

		ShCircle *prevCircle = dynamic_cast<ShCircle*>((*this->widget->getPreview().begin()));
		ShPoint3d center = prevCircle->getCenter();

		draft.setOrthogonalBasePoint(center);
		draft.setSnapBasePoint(center);
	}

	return draft;
}

void ShSubDrawCircleAction_CenterDiameter::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawCircleAction::Status::PickedCenter) {

		ShCircle *prevCircle = dynamic_cast<ShCircle*>((*this->widget->getPreview().begin()));
		ShPoint3d center = prevCircle->getCenter();

		double radius = math::getDistance(center.x, center.y, point.x, point.y) / 2.0;

		prevCircle->setRadius(radius);

		this->widget->getRubberBand().setEnd(point);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawCircleAction_CenterDiameter::getLastPickedPoint() {

	ShPoint3d lastPickedPoint;

	if (this->getStatus() == ShDrawCircleAction::Status::PickedCenter) {

		ShCircle *prevCircle = dynamic_cast<ShCircle*>((*this->widget->getPreview().begin()));
		lastPickedPoint = prevCircle->getCenter();

	}

	return lastPickedPoint;
}

void ShSubDrawCircleAction_CenterDiameter::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawCircleAction::Status::PickedNothing) {

		this->getStatus() = ShDrawCircleAction::Status::PickedCenter;

		this->widget->getPreview().add(new ShCircle(this->widget->getPropertyData(), ShCircleData(point, 0), this->widget->getCurrentLayer()));
		this->widget->getRubberBand().create(ShLineData(point, point));

		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawCircleAction::PickedCenter) {

		ShCircle *prevCircle = dynamic_cast<ShCircle*>((*this->widget->getPreview().begin()));
		ShCircleData data = prevCircle->getData();

		data.radius = math::getDistance(data.center.x, data.center.y, point.x, point.y) / 2.0;

		prevCircle->setData(data);

		this->addEntity(prevCircle->clone(), "Circle");
		this->actionFinished();
	}
}



//////////////////////////////////////////////////////////////////////////////////



ShSubDrawCircleAction_TwoPoint::ShSubDrawCircleAction_TwoPoint(ShDrawCircleAction *drawCircleAction, ShCADWidget *widget)
	:ShSubDrawCircleAction(drawCircleAction, widget) {

}

ShSubDrawCircleAction_TwoPoint::~ShSubDrawCircleAction_TwoPoint() {

}

void ShSubDrawCircleAction_TwoPoint::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShSubDrawCircleAction_TwoPoint::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

ActionType ShSubDrawCircleAction_TwoPoint::getType() {

	return ActionType::ActionDrawCircleTwoPoint;
}

QString ShSubDrawCircleAction_TwoPoint::getHeadTitle() {

	ShDrawCircleAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawCircleAction::Status::PickedNothing)
		text = "Circle >> " + shGetLanValue_command("Command/Specify first end point of circle's diameter") + ": ";
	else if (status == ShDrawCircleAction::Status::PickedFirstPoint)
		text = "Circle >> " + shGetLanValue_command("Command/Specify second end point of circle's diameter") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawCircleAction_TwoPoint::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawCircleAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawCircleAction::Status::PickedFirstPoint) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);

		ShPoint3d first = this->widget->getRubberBand().getStart();

		draft.setOrthogonalBasePoint(first);
		draft.setSnapBasePoint(first);
	}

	return draft;
}

void ShSubDrawCircleAction_TwoPoint::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawCircleAction::Status::PickedFirstPoint) {

		ShPoint3d first = this->widget->getRubberBand().getStart();

		ShCircle *prevCircle = dynamic_cast<ShCircle*>((*this->widget->getPreview().begin()));
		
		ShPoint3d center = this->getCenter(first, point);
		double radius = math::getDistance(first.x, first.y, point.x, point.y) / 2.0;

		prevCircle->setCenter(center);
		prevCircle->setRadius(radius);

		this->widget->getRubberBand().setEnd(point);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawCircleAction_TwoPoint::getLastPickedPoint() {

	ShPoint3d lastPickedPoint;

	if (this->getStatus() == ShDrawCircleAction::Status::PickedFirstPoint) {

		lastPickedPoint = this->widget->getRubberBand().getStart();

	}

	return lastPickedPoint;
}

void ShSubDrawCircleAction_TwoPoint::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawCircleAction::Status::PickedNothing) {

		this->getStatus() = ShDrawCircleAction::Status::PickedFirstPoint;

		ShPoint3d center = this->getCenter(point, point);

		this->widget->getPreview().add(new ShCircle(this->widget->getPropertyData(), ShCircleData(center, 0), this->widget->getCurrentLayer()));
		this->widget->getRubberBand().create(ShLineData(point, point));

		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawCircleAction::PickedFirstPoint) {

		ShPoint3d first = this->widget->getRubberBand().getStart();

		ShCircle *prevCircle = dynamic_cast<ShCircle*>((*this->widget->getPreview().begin()));
		ShCircleData data = prevCircle->getData();

		data.center = this->getCenter(first, point);
		data.radius = math::getDistance(first.x, first.y, point.x, point.y) / 2.0;

		prevCircle->setData(data);

		this->addEntity(prevCircle->clone(), "Circle");
		this->actionFinished();
	}
}

ShPoint3d ShSubDrawCircleAction_TwoPoint::getCenter(const ShPoint3d &first, const ShPoint3d &second) {

	double angle = math::getAbsAngle(first.x, first.y, second.x, second.y);
	double dis = math::getDistance(first.x, first.y, second.x, second.y);

	ShPoint3d center;
	math::rotate(angle, first.x, first.y, first.x + (dis / 2), first.y, center.x, center.y);

	return center;
}

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
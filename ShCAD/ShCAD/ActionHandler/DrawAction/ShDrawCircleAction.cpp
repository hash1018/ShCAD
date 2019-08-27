
#include "ShDrawCircleAction.h"
#include "Entity\Leaf\ShCircle.h"
#include "Base\ShMath.h"
#include "KeyHandler\ShKeyHandler.h"
#include "Command\ShAvailableCommands.h"
#include "Command\ShCustomCommand.h"

ShDrawCircleAction::ShDrawCircleAction(ShCADWidget *widget, SubAction subAction)
	:ShDrawAction(widget), status(PickedNothing), subAction(subAction), subDrawCircleAction(nullptr) {

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
		addAvailableCommand(new ShOnlyNumberCommand<ShDrawCircleAction>(this, &ShDrawCircleAction::temp)).
		build();


	this->changeSubAction(subAction);
}

ShDrawCircleAction::~ShDrawCircleAction() {

	if (this->subDrawCircleAction != nullptr)
		delete this->subDrawCircleAction;
}

#include <qmessagebox.h>
void ShDrawCircleAction::temp(void* number) {

	QMessageBox box;
	box.setText(QString::number(*(static_cast<double*>(number))));
	box.exec();
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
	else if (subAction == SubAction::ThreePoint)
		this->subDrawCircleAction = new ShSubDrawCircleAction_ThreePoint(this, this->widget);
}


////////////////////////////////////////////////////////////////////

ShSubDrawCircleAction::ShSubDrawCircleAction(ShDrawCircleAction *drawCircleAction, ShCADWidget *widget)
	:drawCircleAction(drawCircleAction), widget(widget) {

}

ShSubDrawCircleAction::~ShSubDrawCircleAction() {

}

void ShSubDrawCircleAction::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShSubDrawCircleAction::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
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



/////////////////////////////////////////////////////////////////////////////////


ShSubDrawCircleAction_ThreePoint::ShSubDrawCircleAction_ThreePoint(ShDrawCircleAction *drawCircleAction, ShCADWidget *widget)
	:ShSubDrawCircleAction(drawCircleAction, widget) {

}

ShSubDrawCircleAction_ThreePoint::~ShSubDrawCircleAction_ThreePoint() {

}


ActionType ShSubDrawCircleAction_ThreePoint::getType() {

	return ActionType::ActionDrawCircleThreePoint;
}

QString ShSubDrawCircleAction_ThreePoint::getHeadTitle() {

	ShDrawCircleAction::Status status = this->getStatus();
	QString text;

	if (status == ShDrawCircleAction::Status::PickedNothing)
		text = "Circle >> " + shGetLanValue_command("Command/Specify first point on circle") + ": ";
	else if (status == ShDrawCircleAction::Status::PickedFirstPoint)
		text = "Circle >> " + shGetLanValue_command("Command/Specify second point on circle") + ": ";
	else if(status==ShDrawCircleAction::Status::PickedSecondPoint)
		text= "Circle >> " + shGetLanValue_command("Command/Specify third point on circle") + ": ";

	return text;
}

ShAvailableDraft ShSubDrawCircleAction_ThreePoint::getAvailableDraft() {

	ShAvailableDraft draft;

	if (this->getStatus() == ShDrawCircleAction::Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else if (this->getStatus() == ShDrawCircleAction::Status::PickedFirstPoint ||
		this->getStatus() == ShDrawCircleAction::Status::PickedSecondPoint) {

		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);

		ShPoint3d first = this->widget->getRubberBand().getStart();

		draft.setOrthogonalBasePoint(first);
		draft.setSnapBasePoint(first);
	}

	return draft;
}

void ShSubDrawCircleAction_ThreePoint::invalidate(ShPoint3d &point) {

	if (this->getStatus() == ShDrawCircleAction::Status::PickedFirstPoint) {
	
		this->widget->getRubberBand().setEnd(point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (this->getStatus() == ShDrawCircleAction::Status::PickedSecondPoint) {
	
		this->widget->getRubberBand().setEnd(point);
		ShCircleData data;
		if (math::getCenterWithThreePoint(this->first, this->second, point, data.center) == false) {
		
			data = ShCircleData(ShPoint3d(0, 0), 0);
		}
		else {
			data.radius = math::getDistance(data.center.x, data.center.y, point.x, point.y);
		}

		ShCircle *prevCircle = dynamic_cast<ShCircle*>((*this->widget->getPreview().begin()));
		prevCircle->setData(data);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

ShPoint3d ShSubDrawCircleAction_ThreePoint::getLastPickedPoint() {

	ShPoint3d lastPickedPoint;

	if (this->getStatus() == ShDrawCircleAction::Status::PickedFirstPoint) {
	
		lastPickedPoint = this->first;
	}
	else if (this->getStatus() == ShDrawCircleAction::Status::PickedSecondPoint) {
	
		lastPickedPoint = this->second;
	}

	return lastPickedPoint;
}

void ShSubDrawCircleAction_ThreePoint::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawCircleAction::Status::PickedNothing) {

		this->getStatus() = ShDrawCircleAction::Status::PickedFirstPoint;

		this->first = point;
		this->widget->getRubberBand().create(ShLineData(point, point));
		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawCircleAction::PickedFirstPoint) {

		this->getStatus() = ShDrawCircleAction::Status::PickedSecondPoint;

		this->second = point;
		this->widget->getRubberBand().setData(ShLineData(this->second, this->second));
		
		ShCircleData data;
		math::getCenterWithThreePoint(this->first, this->second, this->second, data.center);

		this->widget->getPreview().add(new ShCircle(this->widget->getPropertyData(), data, this->widget->getCurrentLayer()));

		this->triggerSucceeded();

	}
	else if (this->getStatus() == ShDrawCircleAction::Status::PickedSecondPoint) {
	
		ShCircleData data;
		if (math::getCenterWithThreePoint(this->first, this->second, point, data.center) == false) {
		

			//Fail.
			return;
		}
		else {
		
			data.radius = math::getDistance(data.center.x, data.center.y, point.x, point.y);
		}
	
		ShCircle *prevCircle = dynamic_cast<ShCircle*>((*this->widget->getPreview().begin()));
		prevCircle->setData(data);

		this->addEntity(prevCircle->clone(), "Circle");
		this->actionFinished();
	}
}
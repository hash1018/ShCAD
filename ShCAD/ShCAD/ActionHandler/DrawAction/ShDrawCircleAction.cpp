

#include "ShDrawCircleAction.h"
#include "ShNotifyEvent.h"
#include <QKeyEvent>
#include "Entity\Leaf\ShCircle.h"
#include "ShMath.h"
#include "Entity\Leaf\ShRubberBand.h"

ShDrawCircleAction::ShDrawCircleAction(ShGraphicView *graphicView, ShDrawCircleAction::DrawMethod drawMethod)
	:ShDrawAction(graphicView), drawMethod(drawMethod), drawCircleMethod(0) {

	this->status = PickedNothing;


	ShUpdateListTextEvent event("_Circle", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	this->SetDrawMethod(this->drawMethod);

	QString headTitle = this->drawCircleMethod->GetActionHeadTitle();

	ShUpdateCommandEditHeadTitle event2(headTitle);
	this->graphicView->Notify(&event2);
}

ShDrawCircleAction::~ShDrawCircleAction() {

	if (this->drawCircleMethod != 0)
		delete this->drawCircleMethod;
}

void ShDrawCircleAction::MousePressEvent(QMouseEvent *event, ShActionData& data) {

	this->drawCircleMethod->MousePressEvent(event, data);
	
}

void ShDrawCircleAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	this->drawCircleMethod->MouseMoveEvent(event, data);
}

#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
void ShDrawCircleAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

	if (event->key() == Qt::Key::Key_Escape) {

		ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);
		
	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}


ActionType ShDrawCircleAction::GetType() {

	return ActionType::ActionDrawCircleCenterRadius;
}


void ShDrawCircleAction::ApplyOrthogonalShape(bool on) {

	this->drawCircleMethod->ApplyOrthogonalShape(on);
}

QString ShDrawCircleAction::GetActionHeadTitle() {

	return this->drawCircleMethod->GetActionHeadTitle();
}

void ShDrawCircleAction::IsAllowedDraftOperation(ShAllowedDraftData &data) {

	this->drawCircleMethod->IsAllowedDraftOperation(data);
}

void ShDrawCircleAction::SetDrawMethod(DrawMethod drawMethod) {

	if (this->drawCircleMethod != 0)
		delete this->drawCircleMethod;

	if (drawMethod == DrawMethod::CenterRadius)
		this->drawCircleMethod = new ShDrawCircleMethod_CenterRadius(this, this->graphicView);
	else if (drawMethod == DrawMethod::CenterDiameter)
		this->drawCircleMethod = new ShDrawCircleMethod_CenterDiameter(this, this->graphicView);
	else if (drawMethod == DrawMethod::TwoPoint)
		this->drawCircleMethod = new ShDrawCircleMethod_TwoPoint(this, this->graphicView);
	else if (drawMethod == DrawMethod::ThreePoint)
		this->drawCircleMethod = new ShDrawCircleMethod_ThreePoint(this, this->graphicView);

}

///////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////

ShDrawCircleMethod::ShDrawCircleMethod(ShDrawCircleAction *drawCircleAction, ShGraphicView *view)
	:drawCircleAction(drawCircleAction), view(view) {

}


ShDrawCircleMethod::~ShDrawCircleMethod() {


}

///////////////////////////////////////////////////////////////////////////////////////////

ShDrawCircleMethod_CenterRadius::ShDrawCircleMethod_CenterRadius(ShDrawCircleAction *drawCircleAction, ShGraphicView *view)
	:ShDrawCircleMethod(drawCircleAction, view) {

	
}


ShDrawCircleMethod_CenterRadius::~ShDrawCircleMethod_CenterRadius() {


}

void ShDrawCircleMethod_CenterRadius::MousePressEvent(QMouseEvent *event, ShActionData& data) {

	ShDrawCircleAction::Status &status = this->GetStatus();
	ShPoint3d point = data.GetPoint();
	ShPoint3d nextPoint = data.GetNextPoint();

	if (status == ShDrawCircleAction::Status::PickedNothing) {

		double radius = Math::GetDistance(point.x, point.y, nextPoint.x, nextPoint.y);

		status = ShDrawCircleAction::Status::PickedCenter;

		this->view->preview.Add(new ShCircle(ShPropertyData(*this->view->GetData()->GetPropertyData()),
			ShCircleData(point, radius), this->view->entityTable.GetLayerTable()->GetCurrentLayer()));

		this->view->rubberBand = new ShRubberBand(ShLineData(point, nextPoint));

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		ShUpdateListTextEvent event2("");
		this->view->Notify(&event2);

		ShUpdateCommandEditHeadTitle event3("Circle >> Specify radius of circle: ");
		this->view->Notify(&event3);

	}
	else if (status == ShDrawCircleAction::Status::PickedCenter) {
	
		ShCircle *previewCircle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));
		ShPoint3d center = previewCircle->GetCenter();

		double radius = Math::GetDistance(center.x, center.y, point.x, point.y);
		previewCircle->SetRadius(radius);


		ShUpdateListTextEvent event2("");
		this->view->Notify(&event2);

		this->AddEntityAndFinish(previewCircle->Clone(), "Circle");
		
	}

}

void ShDrawCircleMethod_CenterRadius::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	ShDrawCircleAction::Status &status = this->GetStatus();

	if (status == ShDrawCircleAction::Status::PickedCenter) {
	
		ShPoint3d point = data.GetPoint();
		
		ShCircle *previewCircle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));
		ShPoint3d center = previewCircle->GetCenter();

		double radius = Math::GetDistance(center.x, center.y, point.x, point.y);

		previewCircle->SetRadius(radius);

		this->view->rubberBand->SetEnd(point);

		data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}

}

void ShDrawCircleMethod_CenterRadius::ApplyOrthogonalShape(bool on) {
	
	if (this->GetStatus() == ShDrawCircleAction::Status::PickedNothing)
		return;

	ShCircle *circle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));
	ShCircleData data = circle->GetData();
	ShPoint3d mouse = this->view->GetCursorPoint();

	if (on == true) {
		ShPoint3d orth;
		this->GetOrthogonal(data.center.x, data.center.y, mouse.x, mouse.y, orth.x, orth.y);
		data.radius = Math::GetDistance(data.center.x, data.center.y, orth.x, orth.y);
		this->view->rubberBand->SetEnd(orth);
	}
	else {
		data.radius = Math::GetDistance(data.center.x, data.center.y, mouse.x, mouse.y);
		this->view->rubberBand->SetEnd(mouse);
	}

	circle->SetData(data);
	this->view->update((DrawType)(DrawCaptureImage | DrawPreviewEntities));

}

QString ShDrawCircleMethod_CenterRadius::GetActionHeadTitle() {

	ShDrawCircleAction::Status status = this->GetStatus();
	QString str;

	if (status == ShDrawCircleAction::Status::PickedNothing)
		str = "Circle >> Specify center point: ";
	else if (status == ShDrawCircleAction::Status::PickedCenter)
		str = "Circle >> Specify radius of circle: ";

	return str;
}

void ShDrawCircleMethod_CenterRadius::IsAllowedDraftOperation(ShAllowedDraftData &data) {
	
	ShDrawCircleAction::Status status = this->GetStatus();
	
	if (status == ShDrawCircleAction::Status::PickedNothing) {
	
		data.SetAllowOrthogonal(false);
		data.SetAllowtSnap(true);

		ShPoint3d mouse = this->view->GetCursorPoint();
		data.SetSnapBasePoint(mouse);
	}
	else if (status == ShDrawCircleAction::Status::PickedCenter) {
		data.SetAllowOrthogonal(true);
		data.SetAllowtSnap(true);

		ShCircle *previewCircle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));

		data.SetOrthogonalBasePoint(previewCircle->GetCenter());
		data.SetSnapBasePoint(previewCircle->GetCenter());
		
	}

}


//////////////////////////////////////////////////////////////////////////////////////////////////////


ShDrawCircleMethod_CenterDiameter::ShDrawCircleMethod_CenterDiameter(ShDrawCircleAction *drawCircleAction, ShGraphicView *view)
	:ShDrawCircleMethod(drawCircleAction, view) {

	
}


ShDrawCircleMethod_CenterDiameter::~ShDrawCircleMethod_CenterDiameter() {

}

void ShDrawCircleMethod_CenterDiameter::MousePressEvent(QMouseEvent *event, ShActionData& data) {

	ShDrawCircleAction::Status &status = this->GetStatus();
	ShPoint3d point = data.GetPoint();
	ShPoint3d nextPoint = data.GetNextPoint();

	if (status == ShDrawCircleAction::Status::PickedNothing) {

		double radius = Math::GetDistance(point.x, point.y, nextPoint.x, nextPoint.y) / 2.0;

		status = ShDrawCircleAction::Status::PickedCenter;

		this->view->preview.Add(new ShCircle(ShPropertyData(*this->view->GetData()->GetPropertyData()),
			ShCircleData(point, radius), this->view->entityTable.GetLayerTable()->GetCurrentLayer()));

		this->view->rubberBand = new ShRubberBand(ShLineData(point, nextPoint));

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		ShUpdateListTextEvent event2("");
		this->view->Notify(&event2);

		ShUpdateCommandEditHeadTitle event3("Circle >> Specify diameter of circle: ");
		this->view->Notify(&event3);

	}
	else if (status == ShDrawCircleAction::Status::PickedCenter) {

		ShCircle *previewCircle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));
		ShPoint3d center = previewCircle->GetCenter();

		double radius = Math::GetDistance(center.x, center.y, point.x, point.y) / 2.0;
		previewCircle->SetRadius(radius);


		ShUpdateListTextEvent event2("");
		this->view->Notify(&event2);

		this->AddEntityAndFinish(previewCircle->Clone(), "Circle");

	}
}

void ShDrawCircleMethod_CenterDiameter::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	ShDrawCircleAction::Status &status = this->GetStatus();

	if (status == ShDrawCircleAction::Status::PickedCenter) {

		ShPoint3d point = data.GetPoint();

		ShCircle *previewCircle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));
		ShPoint3d center = previewCircle->GetCenter();

		double radius = Math::GetDistance(center.x, center.y, point.x, point.y) / 2.0;

		previewCircle->SetRadius(radius);

		this->view->rubberBand->SetEnd(point);

		data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}

}

void ShDrawCircleMethod_CenterDiameter::ApplyOrthogonalShape(bool on) {

	if (this->GetStatus() == ShDrawCircleAction::Status::PickedNothing)
		return;

	ShCircle *circle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));
	ShCircleData data = circle->GetData();
	ShPoint3d mouse = this->view->GetCursorPoint();

	if (on == true) {
		ShPoint3d orth;
		this->GetOrthogonal(data.center.x, data.center.y, mouse.x, mouse.y, orth.x, orth.y);
		data.radius = Math::GetDistance(data.center.x, data.center.y, orth.x, orth.y) / 2.0;
		this->view->rubberBand->SetEnd(orth);
	}
	else {
		data.radius = Math::GetDistance(data.center.x, data.center.y, mouse.x, mouse.y) / 2.0;
		this->view->rubberBand->SetEnd(mouse);
	}

	circle->SetData(data);
	this->view->update((DrawType)(DrawCaptureImage | DrawPreviewEntities));
}

QString ShDrawCircleMethod_CenterDiameter::GetActionHeadTitle() {

	ShDrawCircleAction::Status status = this->GetStatus();
	QString str;

	if (status == ShDrawCircleAction::Status::PickedNothing)
		str = "Circle >> Specify center point: ";
	else if (status == ShDrawCircleAction::Status::PickedCenter)
		str = "Circle >> Specify diameter of circle: ";

	return str;
}

void ShDrawCircleMethod_CenterDiameter::IsAllowedDraftOperation(ShAllowedDraftData &data) {

	ShDrawCircleAction::Status status = this->GetStatus();

	if (status == ShDrawCircleAction::Status::PickedNothing) {

		data.SetAllowOrthogonal(false);
		data.SetAllowtSnap(true);

		ShPoint3d mouse = this->view->GetCursorPoint();
		data.SetSnapBasePoint(mouse);
	}
	else if (status == ShDrawCircleAction::Status::PickedCenter) {
		data.SetAllowOrthogonal(true);
		data.SetAllowtSnap(true);

		ShCircle *previewCircle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));

		data.SetOrthogonalBasePoint(previewCircle->GetCenter());
		data.SetSnapBasePoint(previewCircle->GetCenter());

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawCircleMethod_TwoPoint::ShDrawCircleMethod_TwoPoint(ShDrawCircleAction *drawCircleAction, ShGraphicView *view)
	:ShDrawCircleMethod(drawCircleAction, view) {

}


ShDrawCircleMethod_TwoPoint::~ShDrawCircleMethod_TwoPoint() {

}

void ShDrawCircleMethod_TwoPoint::MousePressEvent(QMouseEvent *event, ShActionData& data) {

	ShDrawCircleAction::Status &status = this->GetStatus();
	ShPoint3d point = data.GetPoint();
	ShPoint3d nextPoint = data.GetNextPoint();
	

	if (status == ShDrawCircleAction::Status::PickedNothing) {

		ShPoint3d center = this->GetCenter(point, nextPoint);
		double radius = Math::GetDistance(point.x, point.y, nextPoint.x, nextPoint.y) / 2.0;
	
		status = ShDrawCircleAction::Status::PickedFirstPoint;

		this->view->preview.Add(new ShCircle(ShPropertyData(*this->view->GetData()->GetPropertyData()),
			ShCircleData(center, radius), this->view->entityTable.GetLayerTable()->GetCurrentLayer()));

		this->view->rubberBand = new ShRubberBand(ShLineData(point, nextPoint));

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		ShUpdateListTextEvent event2("");
		this->view->Notify(&event2);

		ShUpdateCommandEditHeadTitle event3("Circle >> Specify second end point of circle's diameter: ");
		this->view->Notify(&event3);

	}
	else if (status == ShDrawCircleAction::Status::PickedFirstPoint) {

		ShPoint3d first = this->view->rubberBand->GetStart();
		ShPoint3d point = data.GetPoint();

		ShCircle *previewCircle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));

		ShPoint3d center = this->GetCenter(first, point);
		double radius = Math::GetDistance(first.x, first.y, point.x, point.y) / 2.0;

		previewCircle->SetCenter(center);
		previewCircle->SetRadius(radius);


		ShUpdateListTextEvent event2("");
		this->view->Notify(&event2);

		this->AddEntityAndFinish(previewCircle->Clone(), "Circle");

	}
}

void ShDrawCircleMethod_TwoPoint::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	ShDrawCircleAction::Status &status = this->GetStatus();

	if (status == ShDrawCircleAction::Status::PickedFirstPoint) {
		ShPoint3d first = this->view->rubberBand->GetStart();
		ShPoint3d point = data.GetPoint();


		ShCircle *previewCircle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));
		
		ShPoint3d center = this->GetCenter(first, point);
		double radius = Math::GetDistance(first.x, first.y, point.x, point.y) / 2.0;

		previewCircle->SetCenter(center);
		previewCircle->SetRadius(radius);

		this->view->rubberBand->SetEnd(point);

		data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

void ShDrawCircleMethod_TwoPoint::ApplyOrthogonalShape(bool on) {

	if (this->GetStatus() == ShDrawCircleAction::Status::PickedNothing)
		return;

	ShCircle *circle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));
	ShPoint3d first = this->view->rubberBand->GetStart();
	ShPoint3d mouse = this->view->GetCursorPoint();

	if (on == true) {
		ShPoint3d orth;
		this->GetOrthogonal(first.x, first.y, mouse.x, mouse.y, orth.x, orth.y);
		this->view->rubberBand->SetEnd(orth);
	}
	else {
		this->view->rubberBand->SetEnd(mouse);
	}

	ShPoint3d second = this->view->rubberBand->GetEnd();
	ShPoint3d center = this->GetCenter(first, second);
	double radius = Math::GetDistance(first.x, first.y, second.x, second.y) / 2.0;

	circle->SetCenter(center);
	circle->SetRadius(radius);

	this->view->update((DrawType)(DrawCaptureImage | DrawPreviewEntities));
}

QString ShDrawCircleMethod_TwoPoint::GetActionHeadTitle() {

	ShDrawCircleAction::Status status = this->GetStatus();
	QString str;

	if (status == ShDrawCircleAction::Status::PickedNothing)
		str = "Circle >> Specify first end point of circle's diameter: ";
	else if (status == ShDrawCircleAction::Status::PickedFirstPoint)
		str = "Circle >> Specify second end point of circle's diameter: ";

	return str;
}

void ShDrawCircleMethod_TwoPoint::IsAllowedDraftOperation(ShAllowedDraftData &data) {

	ShDrawCircleAction::Status status = this->GetStatus();

	if (status == ShDrawCircleAction::Status::PickedNothing) {

		data.SetAllowOrthogonal(false);
		data.SetAllowtSnap(true);

		ShPoint3d mouse = this->view->GetCursorPoint();
		data.SetSnapBasePoint(mouse);
	}
	else if (status == ShDrawCircleAction::Status::PickedFirstPoint) {
		data.SetAllowOrthogonal(true);
		data.SetAllowtSnap(true);

		ShPoint3d first = this->view->rubberBand->GetStart();

		data.SetOrthogonalBasePoint(first);
		data.SetSnapBasePoint(first);

	}
}

ShPoint3d ShDrawCircleMethod_TwoPoint::GetCenter(const ShPoint3d& first, const ShPoint3d& second) {

	double angle = Math::GetAbsAngle(first.x, first.y, second.x, second.y);
	double dis = Math::GetDistance(first.x, first.y, second.x, second.y);

	ShPoint3d center;
	Math::Rotate(angle, first.x, first.y, first.x + (dis / 2), first.y, center.x, center.y);

	return center;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawCircleMethod_ThreePoint::ShDrawCircleMethod_ThreePoint(ShDrawCircleAction *drawCircleAction, ShGraphicView *view)
	:ShDrawCircleMethod(drawCircleAction, view) {

}

ShDrawCircleMethod_ThreePoint::~ShDrawCircleMethod_ThreePoint() {

}

void ShDrawCircleMethod_ThreePoint::MousePressEvent(QMouseEvent *event, ShActionData& data) {

	ShDrawCircleAction::Status &status = this->GetStatus();
	ShPoint3d point = data.GetPoint();
	ShPoint3d nextPoint = data.GetNextPoint();


	if (status == ShDrawCircleAction::Status::PickedNothing) {

		this->first = point;

		status = ShDrawCircleAction::Status::PickedFirstPoint;

		this->view->rubberBand = new ShRubberBand(ShLineData(point, nextPoint));

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		ShUpdateListTextEvent event2("");
		this->view->Notify(&event2);

		ShUpdateCommandEditHeadTitle event3("Circle >> Specify second point on circle: ");
		this->view->Notify(&event3);

	}
	else if (status == ShDrawCircleAction::Status::PickedFirstPoint) {

		this->second = point;

		status = ShDrawCircleAction::Status::PickedSecondPoint;

		this->view->rubberBand->SetStart(this->second);
		this->view->rubberBand->SetEnd(nextPoint);
		
		ShCircleData data;
		if (Math::GetCenterWithThreePoint(this->first, this->second, nextPoint, data.center) == false) {
			data.center.x = 0;
			data.center.y = 0;
			data.radius = 0;
		}
		else {
			data.radius = Math::GetDistance(data.center.x, data.center.y, this->first.x, this->first.y);
		}


		this->view->preview.Add(new ShCircle(ShPropertyData(*this->view->GetData()->GetPropertyData()),
			data, this->view->entityTable.GetLayerTable()->GetCurrentLayer()));

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		ShUpdateListTextEvent event2("");
		this->view->Notify(&event2);

		ShUpdateCommandEditHeadTitle event3("Circle >> Specify third point on circle: ");
		this->view->Notify(&event3);
	}
	else if (status == ShDrawCircleAction::Status::PickedSecondPoint) {
	
		ShCircleData circleData;
		if (Math::GetCenterWithThreePoint(this->first, this->second, data.GetPoint(), circleData.center) == false) {
			ShUpdateListTextEvent event2("");
			this->view->Notify(&event2);
			ShUpdateListTextEvent event3("Circle does not exist.",
				ShUpdateListTextEvent::UpdateType::TextWithoutAnything);
			this->view->Notify(&event3);
			return;
		}
		else {
			circleData.radius = Math::GetDistance(circleData.center.x, circleData.center.y, this->first.x, this->first.y);
		}

		ShCircle *previewCircle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));
		previewCircle->SetData(circleData);

		ShUpdateListTextEvent event2("");
		this->view->Notify(&event2);

		this->AddEntityAndFinish(previewCircle->Clone(), "Circle");
	}
}

void ShDrawCircleMethod_ThreePoint::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	ShDrawCircleAction::Status &status = this->GetStatus();

	if (status == ShDrawCircleAction::Status::PickedFirstPoint) {
		
		ShPoint3d point = data.GetPoint();
		this->view->rubberBand->SetEnd(point);

		data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (status == ShDrawCircleAction::Status::PickedSecondPoint) {
	
		this->view->rubberBand->SetEnd(data.GetPoint());

		ShCircleData circleData;
		if (Math::GetCenterWithThreePoint(this->first, this->second, data.GetPoint(), circleData.center) == false) {
			circleData.center.x = 0;
			circleData.center.y = 0;
			circleData.radius = 0;
		}
		else {
			circleData.radius = Math::GetDistance(circleData.center.x, circleData.center.y, this->first.x, this->first.y);
		}

		ShCircle *previewCircle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));
		previewCircle->SetData(circleData);

		data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}

}

void ShDrawCircleMethod_ThreePoint::ApplyOrthogonalShape(bool on) {

	if (this->GetStatus() == ShDrawCircleAction::Status::PickedNothing)
		return;

	ShPoint3d mouse = this->view->GetCursorPoint();

	if (this->GetStatus() == ShDrawCircleAction::Status::PickedFirstPoint) {
	
		if (on == true) {
			ShPoint3d orth;
			this->GetOrthogonal(this->first.x, this->first.y, mouse.x, mouse.y, orth.x, orth.y);
			this->view->rubberBand->SetEnd(orth);
		}
		else {
			this->view->rubberBand->SetEnd(mouse);
		}
	}
	else if (this->GetStatus() == ShDrawCircleAction::Status::PickedSecondPoint) {
	
		if (on == true) {
			ShPoint3d orth;
			this->GetOrthogonal(this->second.x, this->second.y, mouse.x, mouse.y, orth.x, orth.y);
			this->view->rubberBand->SetEnd(orth);
		}
		else {
			this->view->rubberBand->SetEnd(mouse);
		}
		ShPoint3d third = this->view->rubberBand->GetEnd();

		ShCircleData circleData;
		if (Math::GetCenterWithThreePoint(this->first, this->second, third, circleData.center) == false) {
			circleData.center.x = 0;
			circleData.center.y = 0;
			circleData.radius = 0;
		}
		else {
			circleData.radius = Math::GetDistance(circleData.center.x, circleData.center.y, this->first.x, this->first.y);
		}

		ShCircle *previewCircle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));
		previewCircle->SetData(circleData);
	}
	

	this->view->update((DrawType)(DrawCaptureImage | DrawPreviewEntities));

}


QString ShDrawCircleMethod_ThreePoint::GetActionHeadTitle() {

	ShDrawCircleAction::Status status = this->GetStatus();
	QString str;

	if (status == ShDrawCircleAction::Status::PickedNothing)
		str = "Circle >> Specify first point on circle: ";
	else if (status == ShDrawCircleAction::Status::PickedFirstPoint)
		str = "Circle >> Specify second point on circle: ";
	else if (status == ShDrawCircleAction::Status::PickedSecondPoint)
		str = "Circle >> Specify third point on circle: ";

	return str;
}

void ShDrawCircleMethod_ThreePoint::IsAllowedDraftOperation(ShAllowedDraftData &data) {

	ShDrawCircleAction::Status status = this->GetStatus();

	if (status == ShDrawCircleAction::Status::PickedNothing) {

		data.SetAllowOrthogonal(false);
		data.SetAllowtSnap(true);

		ShPoint3d mouse = this->view->GetCursorPoint();
		data.SetSnapBasePoint(mouse);
	}
	else if (status == ShDrawCircleAction::Status::PickedFirstPoint ||
		status == ShDrawCircleAction::Status::PickedSecondPoint) {
		data.SetAllowOrthogonal(true);
		data.SetAllowtSnap(true);

		ShPoint3d first = this->view->rubberBand->GetStart();

		data.SetOrthogonalBasePoint(first);
		data.SetSnapBasePoint(first);

	}

}

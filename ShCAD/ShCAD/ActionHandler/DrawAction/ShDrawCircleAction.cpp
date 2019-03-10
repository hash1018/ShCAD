

#include "ShDrawCircleAction.h"
#include "ShNotifyEvent.h"
#include <QKeyEvent>
#include "Entity\Leaf\ShCircle.h"
#include "ShMath.h"
#include "Entity\Leaf\ShRubberBand.h"

ShDrawCircleAction::ShDrawCircleAction(ShGraphicView *graphicView)
	:ShDrawAction(graphicView) {

	this->status = PickedNothing;
	this->drawMethod = CenterRadius;

	ShUpdateListTextEvent event("_Circle", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	ShUpdateCommandEditHeadTitle event2("Circle >> Specify center point: ");
	this->graphicView->Notify(&event2);

	this->drawCircleMethod = new ShDrawCircleMethod_CenterRadius(this, this->graphicView);

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

	return ActionType::ActionDrawCircle;
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
	ShPoint3d mouse;
	QPoint pos = this->view->mapFromGlobal(QCursor::pos());
	this->view->ConvertDeviceToEntity(pos.x(), pos.y(), mouse.x, mouse.y);

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

		QPoint point = this->view->mapFromGlobal(QCursor::pos());
		ShPoint3d temp;
		this->view->ConvertDeviceToEntity(point.x(), point.y(), temp.x, temp.y);
		data.SetSnapBasePoint(temp);
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

}

void ShDrawCircleMethod_CenterDiameter::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {


}

void ShDrawCircleMethod_CenterDiameter::ApplyOrthogonalShape(bool on) {

}

QString ShDrawCircleMethod_CenterDiameter::GetActionHeadTitle() {

	return QString("");
}

void ShDrawCircleMethod_CenterDiameter::IsAllowedDraftOperation(ShAllowedDraftData &data) {


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawCircleMethod_TwoPoint::ShDrawCircleMethod_TwoPoint(ShDrawCircleAction *drawCircleAction, ShGraphicView *view)
	:ShDrawCircleMethod(drawCircleAction, view) {

}


ShDrawCircleMethod_TwoPoint::~ShDrawCircleMethod_TwoPoint() {

}

void ShDrawCircleMethod_TwoPoint::MousePressEvent(QMouseEvent *event, ShActionData& data) {

}

void ShDrawCircleMethod_TwoPoint::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

}

void ShDrawCircleMethod_TwoPoint::ApplyOrthogonalShape(bool on) {

}

QString ShDrawCircleMethod_TwoPoint::GetActionHeadTitle() {

	return QString("");
}

void ShDrawCircleMethod_TwoPoint::IsAllowedDraftOperation(ShAllowedDraftData &data) {


}

//////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawCircleMethod_ThreePoint::ShDrawCircleMethod_ThreePoint(ShDrawCircleAction *drawCircleAction, ShGraphicView *view)
	:ShDrawCircleMethod(drawCircleAction, view) {

}

ShDrawCircleMethod_ThreePoint::~ShDrawCircleMethod_ThreePoint() {

}

void ShDrawCircleMethod_ThreePoint::MousePressEvent(QMouseEvent *event, ShActionData& data) {

}

void ShDrawCircleMethod_ThreePoint::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

}

void ShDrawCircleMethod_ThreePoint::ApplyOrthogonalShape(bool on) {


}


QString ShDrawCircleMethod_ThreePoint::GetActionHeadTitle() {

	return QString("");
}

void ShDrawCircleMethod_ThreePoint::IsAllowedDraftOperation(ShAllowedDraftData &data) {


}

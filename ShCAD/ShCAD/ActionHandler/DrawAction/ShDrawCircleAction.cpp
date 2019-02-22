

#include "ShDrawCircleAction.h"
#include "ShNotifyEvent.h"
#include <QKeyEvent>
#include "Entity\Leaf\ShCircle.h"
#include "ShMath.h"
#include "Entity\Leaf\ShRubberBand.h"

ShDrawCircleAction::ShDrawCircleAction(ShGraphicView *graphicView)
	:ShDrawAction(graphicView) {

	this->status = PickedNothing;

	ShUpdateListTextEvent event("_Circle", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	ShUpdateCommandEditHeadTitle event2("Circle >> Specify center point: ");
	this->graphicView->Notify(&event2);

	this->subActionHandler = new ShDrawCircleProxy(this, this->graphicView);

	if (this->graphicView->GetDraftInfomation()->GetOrthogonalMode() == true)
		this->SetOrthogonal();

}

ShDrawCircleAction::~ShDrawCircleAction() {

}

void ShDrawCircleAction::MousePressEvent(QMouseEvent *event) {

	ShSubActionInfo info;
	this->subActionHandler->MousePressEvent(event, info);
	
}

void ShDrawCircleAction::MouseMoveEvent(QMouseEvent *event) {

	ShSubActionInfo info(DrawType::DrawCaptureImage);
	this->subActionHandler->MouseMoveEvent(event, info);

	this->graphicView->update(info.GetDrawType());
}

void ShDrawCircleAction::KeyPressEvent(QKeyEvent *event) {

	if (event->key() == Qt::Key::Key_Escape) {

		this->graphicView->ChangeCurrentAction(ActionType::ActionDefault);
	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}


ActionType ShDrawCircleAction::GetType() {

	return ActionType::ActionDrawCircle;
}

void ShDrawCircleAction::ApplyOrthogonalShape(bool isOrthogonalModeOn) {

}

void ShDrawCircleAction::SetActionHeadTitle() {


}


///////////////////////////////////////////////////////////////////////////////////////

ShDrawCircleProxy::ShDrawCircleProxy(ShDrawCircleAction *drawCircleAction, ShGraphicView *view)
	:ShSubIndividualAction(drawCircleAction, view) {

	this->drawCircleMethod = new ShDrawCircleMethod_CenterRadius(drawCircleAction, view);
}

ShDrawCircleProxy::~ShDrawCircleProxy() {

	if (this->drawCircleMethod != 0)
		delete this->drawCircleMethod;
}

void ShDrawCircleProxy::MousePressEvent(QMouseEvent *event, ShSubActionInfo &info) {
	
	if (info.IsSnapPointClicked() == false) {
		ShPoint3d point;
		this->view->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
		info.SetPoint(point);
	}

	this->drawCircleMethod->MousePressEvent(event, info);
}

void ShDrawCircleProxy::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info) {
	
	ShPoint3d point;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
	info.SetPoint(point);

	this->drawCircleMethod->MouseMoveEvent(event, info);
}


////////////////////////////////////////////////////////////////////////////////////////////

ShDrawCircleMethod::ShDrawCircleMethod(ShDrawCircleAction *drawCircleAction, ShGraphicView *view)
	:drawCircleAction(drawCircleAction), view(view) {

}


ShDrawCircleMethod::~ShDrawCircleMethod() {


}

///////////////////////////////////////////////////////////////////////////////////////////

ShDrawCircleMethod_CenterRadius::ShDrawCircleMethod_CenterRadius(ShDrawCircleAction *drawCircleAction, ShGraphicView *view)
	:ShDrawCircleMethod(drawCircleAction, view) {

	this->SetDrawMethod(ShDrawCircleAction::DrawMethod::CenterRadius);
}


ShDrawCircleMethod_CenterRadius::~ShDrawCircleMethod_CenterRadius() {


}

void ShDrawCircleMethod_CenterRadius::MousePressEvent(QMouseEvent *event, ShSubActionInfo& info) {

	ShDrawCircleAction::Status &status = this->GetStatus();
	ShPoint3d point = info.GetPoint();
	ShPoint3d cursor;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), cursor.x, cursor.y);

	if (status == ShDrawCircleAction::Status::PickedNothing) {

		double radius = Math::GetDistance(point.x, point.y, cursor.x, cursor.y);

		status = ShDrawCircleAction::Status::PickedCenter;

		this->view->preview.Add(new ShCircle(ShPropertyData(*this->view->GetData()->GetPropertyData()),
			ShCircleData(point, radius), this->view->entityTable.GetLayerTable()->GetCurrentLayer()));

		this->view->rubberBand = new ShRubberBand(ShLineData(point, cursor));

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

	}
	else if (status == ShDrawCircleAction::Status::PickedCenter) {
	
		ShCircle *previewCircle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));
		ShPoint3d center = previewCircle->GetCenter();

		double radius = Math::GetDistance(center.x, center.y, point.x, point.y);
		previewCircle->SetRadius(radius);

		this->AddEntity(previewCircle->Clone(), "Circle");
		this->view->ChangeCurrentAction(ActionType::ActionDefault);
	}

}

void ShDrawCircleMethod_CenterRadius::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info) {

	ShDrawCircleAction::Status &status = this->GetStatus();

	if (status == ShDrawCircleAction::Status::PickedCenter) {
	
		ShPoint3d point = info.GetPoint();
		
		ShCircle *previewCircle = dynamic_cast<ShCircle*>((*this->view->preview.Begin()));
		ShPoint3d center = previewCircle->GetCenter();

		double radius = Math::GetDistance(center.x, center.y, point.x, point.y);

		previewCircle->SetRadius(radius);

		this->view->rubberBand->SetEnd(point);

		DrawType drawType = info.GetDrawType();
		drawType = (DrawType)(drawType | DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities);
		info.SetDrawType(drawType);
	}

}


//////////////////////////////////////////////////////////////////////////////////////////////////////


ShDrawCircleMethod_CenterDiameter::ShDrawCircleMethod_CenterDiameter(ShDrawCircleAction *drawCircleAction, ShGraphicView *view)
	:ShDrawCircleMethod(drawCircleAction, view) {

	this->SetDrawMethod(ShDrawCircleAction::DrawMethod::CenterDiameter);
}


ShDrawCircleMethod_CenterDiameter::~ShDrawCircleMethod_CenterDiameter() {

}

void ShDrawCircleMethod_CenterDiameter::MousePressEvent(QMouseEvent *event, ShSubActionInfo& info) {

}

void ShDrawCircleMethod_CenterDiameter::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info) {


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawCircleMethod_TwoPoint::ShDrawCircleMethod_TwoPoint(ShDrawCircleAction *drawCircleAction, ShGraphicView *view)
	:ShDrawCircleMethod(drawCircleAction, view) {

	this->SetDrawMethod(ShDrawCircleAction::DrawMethod::TwoPoint);
}


ShDrawCircleMethod_TwoPoint::~ShDrawCircleMethod_TwoPoint() {

}

void ShDrawCircleMethod_TwoPoint::MousePressEvent(QMouseEvent *event, ShSubActionInfo& info) {

}

void ShDrawCircleMethod_TwoPoint::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info) {

}


//////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawCircleMethod_ThreePoint::ShDrawCircleMethod_ThreePoint(ShDrawCircleAction *drawCircleAction, ShGraphicView *view)
	:ShDrawCircleMethod(drawCircleAction, view) {

	this->SetDrawMethod(ShDrawCircleAction::DrawMethod::ThreePoint);
}

ShDrawCircleMethod_ThreePoint::~ShDrawCircleMethod_ThreePoint() {

}

void ShDrawCircleMethod_ThreePoint::MousePressEvent(QMouseEvent *event, ShSubActionInfo& info) {

}

void ShDrawCircleMethod_ThreePoint::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info) {

}

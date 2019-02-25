

#include "ShDrawArcAction.h"
#include "ShNotifyEvent.h"
#include <QKeyEvent>
#include "Entity\Leaf\ShArc.h"
#include "ShMath.h"
#include "Entity\Leaf\ShRubberBand.h"

ShDrawArcAction::ShDrawArcAction(ShGraphicView *graphicView)
	:ShDrawAction(graphicView) {

	this->status = PickedNothing;

	ShUpdateListTextEvent event("_Arc", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	ShUpdateCommandEditHeadTitle event2("Arc >> Specify center point: ");
	this->graphicView->Notify(&event2);

	this->subActionHandler = new ShDrawArcProxy(this, this->graphicView);

	if (this->graphicView->GetDraftInfomation()->GetOrthogonalMode() == true)
		this->SetOrthogonal();

}

ShDrawArcAction::~ShDrawArcAction() {

}

void ShDrawArcAction::MousePressEvent(QMouseEvent *event) {

	ShSubActionInfo info;
	this->subActionHandler->MousePressEvent(event, info);

}

void ShDrawArcAction::MouseMoveEvent(QMouseEvent *event) {

	ShSubActionInfo info(DrawType::DrawCaptureImage);
	this->subActionHandler->MouseMoveEvent(event, info);

	this->graphicView->update(info.GetDrawType());
}

#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
void ShDrawArcAction::KeyPressEvent(QKeyEvent *event) {

	if (event->key() == Qt::Key::Key_Escape) {

		ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);
		//this->graphicView->ChangeCurrentAction(ActionType::ActionDefault);
	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}


ActionType ShDrawArcAction::GetType() {

	return ActionType::ActionDrawArc;
}

void ShDrawArcAction::ApplyOrthogonalShape(bool isOrthogonalModeOn) {

}

void ShDrawArcAction::SetActionHeadTitle() {


}


///////////////////////////////////////////////////////////////////////////////////////

ShDrawArcProxy::ShDrawArcProxy(ShDrawArcAction *drawArcAction, ShGraphicView *view)
	:ShSubIndividualAction(drawArcAction, view) {

	this->drawArcMethod = new ShDrawArcMethod_CenterStartEnd(drawArcAction, view);
}

ShDrawArcProxy::~ShDrawArcProxy() {

	if (this->drawArcMethod != 0)
		delete this->drawArcMethod;
}

void ShDrawArcProxy::MousePressEvent(QMouseEvent *event, ShSubActionInfo &info) {

	if (info.IsSnapPointClicked() == false) {
		ShPoint3d point;
		this->view->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
		info.SetPoint(point);
	}

	this->drawArcMethod->MousePressEvent(event, info);
}

void ShDrawArcProxy::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info) {

	ShPoint3d point;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
	info.SetPoint(point);

	this->drawArcMethod->MouseMoveEvent(event, info);
}


////////////////////////////////////////////////////////////////////////////////////////////

ShDrawArcMethod::ShDrawArcMethod(ShDrawArcAction *drawArcAction, ShGraphicView *view)
	:drawArcAction(drawArcAction), view(view) {

}


ShDrawArcMethod::~ShDrawArcMethod() {


}

///////////////////////////////////////////////////////////////////////////////////////////

ShDrawArcMethod_CenterStartEnd::ShDrawArcMethod_CenterStartEnd(ShDrawArcAction *drawArcAction, ShGraphicView *view)
	:ShDrawArcMethod(drawArcAction, view) {

	this->SetDrawMethod(ShDrawArcAction::DrawMethod::CenterStartEnd);
}


ShDrawArcMethod_CenterStartEnd::~ShDrawArcMethod_CenterStartEnd() {


}

void ShDrawArcMethod_CenterStartEnd::MousePressEvent(QMouseEvent *event, ShSubActionInfo& info) {

	ShDrawArcAction::Status &status = this->GetStatus();
	ShPoint3d point = info.GetPoint();
	ShPoint3d cursor;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), cursor.x, cursor.y);

	if (status == ShDrawArcAction::Status::PickedNothing) {

		status = ShDrawArcAction::Status::PickedCenter;

		//this->view->preview.Add(new ShCircle(ShPropertyData(*this->view->GetData()->GetPropertyData()),
		//	ShCircleData(point, radius), this->view->entityTable.GetLayerTable()->GetCurrentLayer()));

		this->view->rubberBand = new ShRubberBand(ShLineData(point, cursor));

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

	}
	else if (status == ShDrawArcAction::Status::PickedCenter) {

		status = ShDrawArcAction::Status::PickedStart;

		ShPoint3d center = this->view->rubberBand->GetStart();
		double radius = Math::GetDistance(center.x, center.y, point.x, point.y);
		double startAngle = Math::GetAbsAngle(center.x, center.y, point.x, point.y);
		double endAngle = Math::GetAbsAngle(center.x, center.y, cursor.x, cursor.y);

		this->view->preview.Add(new ShArc(ShPropertyData(*this->view->GetData()->GetPropertyData()),
			ShArcData(center, radius, startAngle, endAngle), this->view->entityTable.GetLayerTable()->GetCurrentLayer()));

		//delete this->view->rubberBand;
		//this->view->rubberBand = 0;

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (status = ShDrawArcAction::Status::PickedStart) {
		
		ShArc *previewArc = dynamic_cast<ShArc*>((*this->view->preview.Begin()));
		ShPoint3d center = previewArc->GetCenter();
		double endAngle = Math::GetAbsAngle(center.x, center.y, point.x, point.y);

		previewArc->SetEndAngle(endAngle);

		this->AddEntity(previewArc->Clone(), "Arc");

		//this->view->ChangeCurrentAction(ActionType::ActionDefault);
		ShChangeCurrentActionCurrentFinished strategy(ActionType::ActionDefault);
		this->view->ChangeCurrentAction(strategy);

	}

}

void ShDrawArcMethod_CenterStartEnd::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info) {

	ShDrawArcAction::Status status = this->GetStatus();
	
	if (status == ShDrawArcAction::Status::PickedCenter) {
		
		ShPoint3d point = info.GetPoint();
		
		this->view->rubberBand->SetEnd(point);

		DrawType drawType = info.GetDrawType();
		drawType = (DrawType)(drawType | DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities);
		info.SetDrawType(drawType);
	}
	else if (status == ShDrawArcAction::Status::PickedStart) {
	
		ShPoint3d point = info.GetPoint();

		ShArc *previewArc = dynamic_cast<ShArc*>((*this->view->preview.Begin()));
		ShPoint3d center = previewArc->GetCenter();
		double endAngle = Math::GetAbsAngle(center.x, center.y, point.x, point.y);

		previewArc->SetEndAngle(endAngle);

		this->view->rubberBand->SetEnd(point);

		DrawType drawType = info.GetDrawType();
		drawType = (DrawType)(drawType | DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities);
		info.SetDrawType(drawType);
	}
	

}


//////////////////////////////////////////////////////////////////////////////////////////////////////


ShDrawArcMethod_StartEndRadius::ShDrawArcMethod_StartEndRadius(ShDrawArcAction *drawArcAction, ShGraphicView *view)
	:ShDrawArcMethod(drawArcAction, view) {

	this->SetDrawMethod(ShDrawArcAction::DrawMethod::StartEndRadius);
}


ShDrawArcMethod_StartEndRadius::~ShDrawArcMethod_StartEndRadius() {

}

void ShDrawArcMethod_StartEndRadius::MousePressEvent(QMouseEvent *event, ShSubActionInfo& info) {

}

void ShDrawArcMethod_StartEndRadius::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info) {


}



//////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawArcMethod_ThreePoint::ShDrawArcMethod_ThreePoint(ShDrawArcAction *drawArcAction, ShGraphicView *view)
	:ShDrawArcMethod(drawArcAction, view) {

	this->SetDrawMethod(ShDrawArcAction::DrawMethod::ThreePoint);
}

ShDrawArcMethod_ThreePoint::~ShDrawArcMethod_ThreePoint() {

}

void ShDrawArcMethod_ThreePoint::MousePressEvent(QMouseEvent *event, ShSubActionInfo& info) {

}

void ShDrawArcMethod_ThreePoint::MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info) {

}

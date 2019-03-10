

#include "ShDrawArcAction.h"
#include "ShNotifyEvent.h"
#include <QKeyEvent>
#include "Entity\Leaf\ShArc.h"
#include "ShMath.h"
#include "Entity\Leaf\ShRubberBand.h"

ShDrawArcAction::ShDrawArcAction(ShGraphicView *graphicView)
	:ShDrawAction(graphicView) {

	this->status = PickedNothing;
	this->drawMethod = CenterStartEnd;

	ShUpdateListTextEvent event("_Arc", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	ShUpdateCommandEditHeadTitle event2("Arc >> Specify center point: ");
	this->graphicView->Notify(&event2);

	this->drawArcMethod = new ShDrawArcMethod_CenterStartEnd(this, this->graphicView);

}

ShDrawArcAction::~ShDrawArcAction() {

	if (this->drawArcMethod != 0)
		delete this->drawArcMethod;
}

void ShDrawArcAction::MousePressEvent(QMouseEvent *event, ShActionData& data) {

	this->drawArcMethod->MousePressEvent(event, data);

}

void ShDrawArcAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	this->drawArcMethod->MouseMoveEvent(event, data);
}

#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
void ShDrawArcAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

	if (event->key() == Qt::Key::Key_Escape) {

		ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);
		
	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}


ActionType ShDrawArcAction::GetType() {

	return ActionType::ActionDrawArc;
}

void ShDrawArcAction::ApplyOrthogonalShape(bool on) {

	this->drawArcMethod->ApplyOrthogonalShape(on);
}

QString ShDrawArcAction::GetActionHeadTitle() {

	return this->drawArcMethod->GetActionHeadTitle();
}

void ShDrawArcAction::IsAllowedDraftOperation(ShAllowedDraftData &data) {

	this->drawArcMethod->IsAllowedDraftOperation(data);
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

	
}


ShDrawArcMethod_CenterStartEnd::~ShDrawArcMethod_CenterStartEnd() {


}

void ShDrawArcMethod_CenterStartEnd::MousePressEvent(QMouseEvent *event, ShActionData &data) {

	ShDrawArcAction::Status &status = this->GetStatus();
	ShPoint3d point = data.GetPoint();
	ShPoint3d nextPoint = data.GetNextPoint();

	if (status == ShDrawArcAction::Status::PickedNothing) {

		status = ShDrawArcAction::Status::PickedCenter;

		this->view->rubberBand = new ShRubberBand(ShLineData(point, nextPoint));

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		ShUpdateListTextEvent event2("");
		this->view->Notify(&event2);

		ShUpdateCommandEditHeadTitle event3("Arc >> Specify start point: ");
		this->view->Notify(&event3);

	}
	else if (status == ShDrawArcAction::Status::PickedCenter) {

		status = ShDrawArcAction::Status::PickedStart;

		ShPoint3d center = this->view->rubberBand->GetStart();
		double radius = Math::GetDistance(center.x, center.y, point.x, point.y);
		double startAngle = Math::GetAbsAngle(center.x, center.y, point.x, point.y);
		double endAngle = Math::GetAbsAngle(center.x, center.y, nextPoint.x, nextPoint.y);

		this->view->preview.Add(new ShArc(ShPropertyData(*this->view->GetData()->GetPropertyData()),
			ShArcData(center, radius, startAngle, endAngle), this->view->entityTable.GetLayerTable()->GetCurrentLayer()));

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		ShUpdateListTextEvent event2("");
		this->view->Notify(&event2);

		ShUpdateCommandEditHeadTitle event3("Arc >> Specify end point: ");
		this->view->Notify(&event3);

	}
	else if (status = ShDrawArcAction::Status::PickedStart) {
		
		ShArc *previewArc = dynamic_cast<ShArc*>((*this->view->preview.Begin()));
		ShPoint3d center = previewArc->GetCenter();
		double endAngle = Math::GetAbsAngle(center.x, center.y, point.x, point.y);

		previewArc->SetEndAngle(endAngle);

		ShUpdateListTextEvent event2("");
		this->view->Notify(&event2);

		this->AddEntityAndFinish(previewArc->Clone(), "Arc");

	}

}

void ShDrawArcMethod_CenterStartEnd::MouseMoveEvent(QMouseEvent *event, ShActionData &data) {

	ShDrawArcAction::Status status = this->GetStatus();
	
	if (status == ShDrawArcAction::Status::PickedCenter) {
		
		ShPoint3d point = data.GetPoint();
		
		this->view->rubberBand->SetEnd(point);

		data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
	else if (status == ShDrawArcAction::Status::PickedStart) {
	
		ShPoint3d point = data.GetPoint();

		ShArc *previewArc = dynamic_cast<ShArc*>((*this->view->preview.Begin()));
		ShPoint3d center = previewArc->GetCenter();
		double endAngle = Math::GetAbsAngle(center.x, center.y, point.x, point.y);

		previewArc->SetEndAngle(endAngle);

		this->view->rubberBand->SetEnd(point);

		data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}

}

void ShDrawArcMethod_CenterStartEnd::ApplyOrthogonalShape(bool on) {
	
	ShDrawArcAction::Status status = this->GetStatus();

	if (status == ShDrawArcAction::Status::PickedNothing)
		return;

	ShPoint3d mouse = this->view->GetCursorPoint();

	if (status == ShDrawArcAction::Status::PickedCenter) {
		
		if (on == true) {
			ShPoint3d center = this->view->rubberBand->GetStart();
			ShPoint3d orth;
			this->GetOrthogonal(center.x, center.y, mouse.x, mouse.y, orth.x, orth.y);
			this->view->rubberBand->SetEnd(orth);
		}
		else {
			this->view->rubberBand->SetEnd(mouse);
		}

	}
	else if (status == ShDrawArcAction::Status::PickedStart) {
		ShArc *arc = dynamic_cast<ShArc*>((*this->view->preview.Begin()));
		ShPoint3d center = arc->GetCenter();
		double endAngle;

		if (on == true) {
			
			ShPoint3d orth;
			this->GetOrthogonal(center.x, center.y, mouse.x, mouse.y, orth.x, orth.y);
			this->view->rubberBand->SetEnd(orth);
			endAngle = Math::GetAbsAngle(center.x, center.y, orth.x, orth.y);

		}
		else {
			this->view->rubberBand->SetEnd(mouse);
			endAngle = Math::GetAbsAngle(center.x, center.y, mouse.x, mouse.y);
		}

		arc->SetEndAngle(endAngle);
	}

	this->view->update((DrawType)(DrawCaptureImage | DrawPreviewEntities));

}

QString ShDrawArcMethod_CenterStartEnd::GetActionHeadTitle() {

	ShDrawArcAction::Status status = this->GetStatus();
	QString str = "";

	if (status == ShDrawArcAction::Status::PickedNothing)
		str = "Arc >> Specify center point: ";
	else if (status == ShDrawArcAction::Status::PickedCenter)
		str = "Arc >> Specify start point: ";
	else if (status == ShDrawArcAction::Status::PickedStart)
		str = "Arc >> Specify end point: ";

	return str;
	
}

void ShDrawArcMethod_CenterStartEnd::IsAllowedDraftOperation(ShAllowedDraftData &data) {

	ShDrawArcAction::Status status = this->GetStatus();

	if (status == ShDrawArcAction::Status::PickedNothing) {

		data.SetAllowOrthogonal(false);
		data.SetAllowtSnap(true);

		ShPoint3d mouse = this->view->GetCursorPoint();
		data.SetSnapBasePoint(mouse);
	}
	else if (status == ShDrawArcAction::Status::PickedCenter) {
		data.SetAllowOrthogonal(true);
		data.SetAllowtSnap(true);

		ShPoint3d point = this->view->rubberBand->GetStart();

		data.SetOrthogonalBasePoint(point);
		data.SetSnapBasePoint(point);

	}
	else if (status == ShDrawArcAction::Status::PickedStart) {
		data.SetAllowOrthogonal(true);
		data.SetAllowtSnap(true);

		ShArc *previewArc = dynamic_cast<ShArc*>((*this->view->preview.Begin()));

		data.SetOrthogonalBasePoint(previewArc->GetCenter());
		data.SetSnapBasePoint(previewArc->GetCenter());

	}

}


//////////////////////////////////////////////////////////////////////////////////////////////////////


ShDrawArcMethod_StartEndRadius::ShDrawArcMethod_StartEndRadius(ShDrawArcAction *drawArcAction, ShGraphicView *view)
	:ShDrawArcMethod(drawArcAction, view) {

	
}


ShDrawArcMethod_StartEndRadius::~ShDrawArcMethod_StartEndRadius() {

}

void ShDrawArcMethod_StartEndRadius::MousePressEvent(QMouseEvent *event, ShActionData &data) {

}

void ShDrawArcMethod_StartEndRadius::MouseMoveEvent(QMouseEvent *event, ShActionData &data) {


}

void ShDrawArcMethod_StartEndRadius::ApplyOrthogonalShape(bool on) {

}

QString ShDrawArcMethod_StartEndRadius::GetActionHeadTitle() {

	return QString("");
}

void ShDrawArcMethod_StartEndRadius::IsAllowedDraftOperation(ShAllowedDraftData &data) {


}

//////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawArcMethod_ThreePoint::ShDrawArcMethod_ThreePoint(ShDrawArcAction *drawArcAction, ShGraphicView *view)
	:ShDrawArcMethod(drawArcAction, view) {

	
}

ShDrawArcMethod_ThreePoint::~ShDrawArcMethod_ThreePoint() {

}

void ShDrawArcMethod_ThreePoint::MousePressEvent(QMouseEvent *event, ShActionData &data) {

}

void ShDrawArcMethod_ThreePoint::MouseMoveEvent(QMouseEvent *event, ShActionData &data) {

}

void ShDrawArcMethod_ThreePoint::ApplyOrthogonalShape(bool on) {

}

QString ShDrawArcMethod_ThreePoint::GetActionHeadTitle() {

	return QString("");
}

void ShDrawArcMethod_ThreePoint::IsAllowedDraftOperation(ShAllowedDraftData &data) {


}
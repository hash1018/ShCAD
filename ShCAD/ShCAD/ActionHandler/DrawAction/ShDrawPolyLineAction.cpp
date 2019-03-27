

#include "ShDrawPolyLineAction.h"
#include <QMouseEvent>
#include "ShNotifyEvent.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Composite\ShPolyLine.h"

ShDrawPolyLineAction::ShDrawPolyLineAction(ShGraphicView *graphicView)
	:ShDrawAction(graphicView), polyLine(0), status(PickedNothing),
	previous(PickedNothing) {

	ShUpdateListTextEvent event("_PLine", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	ShUpdateCommandEditHeadTitle event2("PLine >> Specify first point: ");
	this->graphicView->Notify(&event2);
}

ShDrawPolyLineAction::~ShDrawPolyLineAction() {

}

void ShDrawPolyLineAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {

	ShPoint3d point = data.GetPoint();
	ShPoint3d nextPoint = data.GetNextPoint();

	if (this->status == PickedNothing) {

		this->status = PickedStart;

		this->graphicView->preview.Add(new ShLine(ShPropertyData(*this->graphicView->GetData()->GetPropertyData()),
			ShLineData(point, nextPoint), this->graphicView->entityTable.GetLayerTable()->GetCurrentLayer()));

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		ShUpdateListTextEvent event2("");
		this->graphicView->Notify(&event2);

		ShUpdateCommandEditHeadTitle event3("PLine >> Specify next point: ");
		this->graphicView->Notify(&event3);

	}
	else if (this->status == PickedStart) {

		ShLine *prevLine = dynamic_cast<ShLine*>((*this->graphicView->preview.Begin()));
		ShLineData data = prevLine->GetData();
		data.end = point;

		prevLine->SetData(data);

		if (this->polyLine == 0) {
			this->polyLine = new ShPolyLine(ShPropertyData(*this->graphicView->GetData()->GetPropertyData()),
				this->graphicView->entityTable.GetLayerTable()->GetCurrentLayer());
			this->polyLine->SetStart(data.start);
		}

	
		this->polyLine->Add(prevLine->Clone());
		this->polyLine->SetEnd(data.end);

		if (this->previous == PickedNothing) {
			this->AddEntity(polyLine, "PLine");
			this->previous = PickedStart;
		}
		else {
			this->graphicView->update((DrawType)(DrawType::DrawAll));
			this->graphicView->CaptureImage();
			this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
		}

		data = ShLineData(point, nextPoint);
		prevLine->SetData(data);

		ShUpdateListTextEvent event2("");
		this->graphicView->Notify(&event2);

		ShUpdateCommandEditHeadTitle event3("PLine >> Specify next point: ");
		this->graphicView->Notify(&event3);
	}
}

void ShDrawPolyLineAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	if (this->status == PickedStart) {

		ShPoint3d point = data.GetPoint();

		ShLine *prevLine = dynamic_cast<ShLine*>((*this->graphicView->preview.Begin()));

		prevLine->SetEnd(point);

		data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

	}
}

#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
void ShDrawPolyLineAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {
	
	if (event->key() == Qt::Key::Key_Escape) {

		ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);

	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}

ActionType ShDrawPolyLineAction::GetType() {

	return ActionType::ActionDrawPolyLine;
}

void ShDrawPolyLineAction::ApplyOrthogonalShape(bool on) {

	if (this->status == ShDrawPolyLineAction::Status::PickedNothing)
		return;

	ShLine *line = dynamic_cast<ShLine*>((*this->graphicView->preview.Begin()));
	ShLineData data = line->GetData();
	ShPoint3d mouse;
	QPoint pos = this->graphicView->mapFromGlobal(QCursor::pos());
	this->graphicView->ConvertDeviceToEntity(pos.x(), pos.y(), mouse.x, mouse.y);

	if (on == true) {
		ShPoint3d orth;
		this->GetOrthogonal(data.start.x, data.start.y, mouse.x, mouse.y, orth.x, orth.y);
		data.end = orth;
	}
	else
		data.end = mouse;


	line->SetData(data);
	this->graphicView->update((DrawType)(DrawCaptureImage | DrawPreviewEntities));

}

QString ShDrawPolyLineAction::GetActionHeadTitle() {

	QString str;

	if (this->status == Status::PickedNothing)
		str = "PLine >> Specify first point: ";
	else
		str = "PLine >> Specify next point: ";

	return str;
}

void ShDrawPolyLineAction::IsAllowedDraftOperation(ShAllowedDraftData &data) {

	if (this->status == Status::PickedNothing) {
		data.SetAllowOrthogonal(true);
		data.SetAllowtSnap(true);

		ShPoint3d mouse = this->graphicView->GetCursorPoint();
		data.SetOrthogonalBasePoint(mouse);
		data.SetSnapBasePoint(mouse);
	}
	else {

		ShLine *prevLine = dynamic_cast<ShLine*>((*this->graphicView->preview.Begin()));

		
		data.SetAllowOrthogonal(true);
		data.SetOrthogonalBasePoint(prevLine->GetStart());
	
		data.SetAllowtSnap(true);
		data.SetSnapBasePoint(prevLine->GetStart());
	}
}
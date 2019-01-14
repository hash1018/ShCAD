

#include "ShDrawLineAction.h"
#include <QMouseEvent>
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShRubberBand.h"

ShDrawLineAction::ShDrawLineAction(ShGraphicView *graphicView)
	:ShDrawAction(graphicView) {

	this->status = PickedNothing;
}

ShDrawLineAction::~ShDrawLineAction() {

}


void ShDrawLineAction::MousePressEvent(QMouseEvent *event) {
	
	if (this->status == PickedNothing) {
	
		this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), this->start.x, this->start.y);
		this->status = PickedStart;

		this->graphicView->preview.Add(new ShLine(ShLineData(this->start, this->start)));
		this->graphicView->rubberBand = new ShRubberBand(ShLineData(this->start, this->start));
		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
		
	}
	else {
		this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), this->end.x, this->end.y);
		ShLineData data(start, end);

		dynamic_cast<ShLine*>(this->graphicView->preview.Begin().Current())->SetData(data);

		ShDrawAction::AddEntity(this->graphicView->preview.Begin().Current()->Clone());

		this->start = this->end;

		
	}
}

void ShDrawLineAction::MouseMoveEvent(QMouseEvent *event) {

	if (this->status == PickedStart) {
		this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), this->end.x, this->end.y);

		ShLineData data(this->start, this->end);

		dynamic_cast<ShLine*>(this->graphicView->preview.Begin().Current())->SetData(data);
		
		this->graphicView->rubberBand->SetData(data);

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
		
	}
}

void ShDrawLineAction::KeyPressEvent(QKeyEvent *event) {


}

ActionType ShDrawLineAction::GetType() {

	return ActionType::ActionDrawLine;
}
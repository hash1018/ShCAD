

#include "ShDrawLineAction.h"
#include <QMouseEvent>
#include "Entity\Leaf\ShLine.h"
#include "Command Pattern\ShAddEntityCommand.h"
#include "Entity\Leaf\ShRubberBand.h"

ShDrawLineAction::ShDrawLineAction(ShGraphicView *graphicView)
	:ShDrawAction(graphicView) {

	this->status = PickedNothing;
}

ShDrawLineAction::~ShDrawLineAction() {

}


void ShDrawLineAction::MousePressEvent(QMouseEvent *event) {
	
	if (this->status == PickedNothing) {
	
		this->start.x = event->x();
		this->start.y = event->y();
		this->status = PickedStart;

		this->graphicView->preview.Add(new ShLine(ShLineData(this->start, ShVector(event->x(), event->y()))));
		this->graphicView->rubberBand = new ShRubberBand(ShLineData(this->start, ShVector(event->x(), event->y())));
		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
		
	}
	else {
		this->end.x = event->x();		this->end.y = event->y();
		ShLineData data(start, end);

		dynamic_cast<ShLine*>(this->graphicView->preview.Begin().Current())->SetData(data);

		ShAddEntityCommand command(this->graphicView, this->graphicView->preview.Begin().Current()->Clone());
		command.Execute();

		this->start = this->end;

		
	}
}

void ShDrawLineAction::MouseMoveEvent(QMouseEvent *event) {

	if (this->status == PickedStart) {
		this->end.x = event->x();
		this->end.y = event->y();

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


#include "ShDrawLineAction.h"
#include <QMouseEvent>
#include "Entity\Leaf\ShLine.h"
#include "Command Pattern\ShAddEntityCommand.h"

#include "Command Pattern\ShDrawPreviewCommand.h"
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

		ShDrawPreviewCommand command(this->graphicView, ShVector(event->x(), event->y()), ShVector(event->x(), event->y()));
		command.Execute();
	}
	else {
		this->end.x = event->x();
		this->end.y = event->y();
		ShLineData data(start, end);


		ShLine *line = new ShLine(data);

		ShAddEntityCommand command(this->graphicView, line);
		command.Execute();

		this->start = this->end;

		
	}
}

void ShDrawLineAction::MouseMoveEvent(QMouseEvent *event) {

	if (this->status == PickedStart) {
	
		ShDrawPreviewCommand command(this->graphicView, ShVector(this->start.x, this->start.y), ShVector(event->x(), event->y()));
		command.Execute();
	}
}

void ShDrawLineAction::KeyPressEvent(QKeyEvent *event) {


}

ActionType ShDrawLineAction::GetType() {

	return ActionType::ActionDrawLine;
}
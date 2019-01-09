

#include "ShDrawLineAction.h"
#include <QMouseEvent>
#include "Entity\Leaf\ShLine.h"
#include "Entity\Composite\ShEntityTable.h"
ShDrawLineAction::ShDrawLineAction(ShGraphicView *graphicView)
	:ShDrawAction(graphicView) {

	this->status = PickedNothing;
}

ShDrawLineAction::~ShDrawLineAction() {

}

#include "Memento Pattern\ShMemento.h"
void ShDrawLineAction::MousePressEvent(QMouseEvent *event) {
	
	if (this->status == PickedNothing) {
	
		this->start.x = event->x();
		this->start.y = event->y();
		this->status = PickedStart;
	}
	else {
		this->end.x = event->x();
		this->end.y = event->y();
		ShLineData data(start, end);



		ShLine *line = new ShLine(data);


		ShLineMemento *memento = line->CreateMemento();
		memento->SetStatus(MementoStatus::MementoCreated);
		this->graphicView->GetUndoTaker()->Push(memento);



		this->graphicView->GetEntityTable()->Add(line);

		this->start = this->end;

		this->graphicView->update();
	}
}

void ShDrawLineAction::MouseMoveEvent(QMouseEvent *event) {

}

void ShDrawLineAction::KeyPressEvent(QKeyEvent *event) {


}

ActionType ShDrawLineAction::GetType() {

	return ActionType::ActionDrawLine;
}
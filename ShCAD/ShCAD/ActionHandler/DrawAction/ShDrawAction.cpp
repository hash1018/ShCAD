

#include "ShDrawAction.h"
#include "Command Pattern\ShAddEntityCommand.h"

ShDrawAction::ShDrawAction(ShGraphicView *graphicView)
	:ShActionHandler(graphicView) {


}

ShDrawAction::~ShDrawAction() {

}

QCursor ShDrawAction::GetCursorShape() {

	return QCursor(Qt::CursorShape::CrossCursor);
}

void ShDrawAction::AddEntity(ShEntity* newEntity) {

	ShAddEntityCommand *command = new ShAddEntityCommand(this->graphicView, newEntity->CreateMemento());

	command->Execute();

	this->graphicView->undoTaker.Push(command);

	if (!this->graphicView->redoTaker.IsEmpty())
		this->graphicView->redoTaker.DeleteAll();


}
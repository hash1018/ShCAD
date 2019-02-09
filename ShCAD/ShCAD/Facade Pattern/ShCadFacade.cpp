

#include "ShCadFacade.h"
#include "Interface\ShGraphicView.h"
#include <qstring.h>
#include "Command Pattern\ShCommand.h"
#include "ShNotifyEvent.h"
#include "ActionHandler\ShActionHandler.h"
#include "Command Pattern\Entity Command\ShDeleteEntityCommand.h"
//#include "Memento Pattern\ShMemento.h"


ShCadFacade::ShCadFacade() {

}

ShCadFacade::~ShCadFacade() {

}

void ShCadFacade::Undo(ShGraphicView *graphicView) {

	if (graphicView->currentAction->GetType() != ActionType::ActionDefault)
		return;


	if (graphicView->selectedEntityManager.GetSize() > 0) {
		graphicView->selectedEntityManager.UnSelectAll();
		graphicView->update(DrawType::DrawAll);
		graphicView->CaptureImage();
		return;
	}


	QString first, second;

	if (graphicView->undoTaker.IsEmpty() == false) {
		ShCommand *command = graphicView->undoTaker.Pop();
		command->UnExecute();

		graphicView->redoTaker.Push(command);

		first = "<Undo>";
		second = command->GetCommandText() + " UnExecuted.";
	}
	else {

		first = "<Undo>";
		second = "No remaining Undo Command.";
	}

	ShUpdateListTextEvent event(first,
		ShUpdateListTextEvent::editTextAndNewLineHeadTitleWithText);
	graphicView->Notify(&event);

	ShUpdateListTextEvent event2(second,
		ShUpdateListTextEvent::TextWithoutAnything);
	graphicView->Notify(&event2);

}

void ShCadFacade::Redo(ShGraphicView *graphicView) {

	if (graphicView->currentAction->GetType() != ActionType::ActionDefault)
		return;


	if (graphicView->selectedEntityManager.GetSize() > 0) {
		graphicView->selectedEntityManager.UnSelectAll();
		graphicView->update(DrawType::DrawAll);
		graphicView->CaptureImage();
		return;
	}

	QString first, second;

	if (graphicView->redoTaker.IsEmpty() == false) {

		ShCommand *command = graphicView->redoTaker.Pop();
		command->Execute();

		graphicView->undoTaker.Push(command);

		first = "<Redo>";
		second = command->GetCommandText() + " Executed.";
	}
	else {

		first = "<Redo>";
		second = "No remaining Redo Command.";
	}


	ShUpdateListTextEvent event(first,
		ShUpdateListTextEvent::editTextAndNewLineHeadTitleWithText);
	graphicView->Notify(&event);

	ShUpdateListTextEvent event2(second,
		ShUpdateListTextEvent::TextWithoutAnything);
	graphicView->Notify(&event2);

}

void ShCadFacade::SelectAll(ShGraphicView *graphicView) {

	graphicView->selectedEntityManager.SelectAll(&(graphicView->entityTable));

	graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
	graphicView->CaptureImage();

	ShUpdateListTextEvent event("<SelectAll>",
		ShUpdateListTextEvent::editTextAndNewLineHeadTitleWithText);
	graphicView->Notify(&event);

	int size = graphicView->selectedEntityManager.GetSize();

	ShUpdateListTextEvent event2("All Entities (" + QString::number(size) + ") is selected.",
		ShUpdateListTextEvent::TextWithoutAnything);
	graphicView->Notify(&event2);

}

void ShCadFacade::Delete(ShGraphicView *graphicView) {

	int size = graphicView->selectedEntityManager.GetSize();

	graphicView->selectedEntityManager.UnSelectAll();
	QLinkedList<ShEntity*>::iterator itr = graphicView->selectedEntityManager.GetJustUnSelectedBegin();
	QLinkedList<ShEntity*> entities;

	for (itr = graphicView->selectedEntityManager.GetJustUnSelectedBegin();
		itr != graphicView->selectedEntityManager.GetJustUnSelectedEnd();
		++itr) {

		entities.append((*itr));
	}


	ShDeleteEntityCommand *command = new ShDeleteEntityCommand(graphicView, entities);
	command->Execute();

	graphicView->undoTaker.Push(command);

	if (!graphicView->redoTaker.IsEmpty())
		graphicView->redoTaker.DeleteAll();




	ShUpdateListTextEvent event("<Delete>",
		ShUpdateListTextEvent::editTextAndNewLineHeadTitleWithText);
	graphicView->Notify(&event);

	ShUpdateListTextEvent event2("All Entities (" + QString::number(size) + ") is deleted.",
		ShUpdateListTextEvent::TextWithoutAnything);
	graphicView->Notify(&event2);

}

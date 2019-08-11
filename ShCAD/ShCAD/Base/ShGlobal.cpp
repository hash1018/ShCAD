
#include "ShGlobal.h"
#include "Interface\ShCADWidget.h"
#include "UnRedo\ShTransaction.h"
#include "UnRedo\ShTransactionStack.h"
#include "Event\ShNotifyEvent.h"
#include <qstring.h>
#include "Manager\ShLanguageManager.h"

ShGlobal::ShGlobal() {

}

ShGlobal::~ShGlobal() {

}

void ShGlobal::undo(ShCADWidget *widget) {

	QString first = shGetLanValue_command("Command/<Undo>");
	QString second;

	if (!widget->getUndoStack()->isEmpty()) {

		ShTransaction *transaction = widget->getUndoStack()->pop();
		transaction->undo();

		widget->getRedoStack()->push(transaction);

		second = transaction->getTransactionName();
	}
	else
		second = shGetLanValue_command("Command/No remaining Undo Command");

	ShUpdateTextToCommandListEvent notifyEvent(first, ShUpdateTextToCommandListEvent::EditTextAndNewLineHeadTitleWithText);
	widget->notify(&notifyEvent);

	ShUpdateTextToCommandListEvent notifyEvent2(second, ShUpdateTextToCommandListEvent::OnlyText);
	widget->notify(&notifyEvent2);

	ShTransactionStackSizeChangedEvent notifyEvent3(widget->getUndoStack()->getSize(), widget->getRedoStack()->getSize());
	widget->notify(&notifyEvent3);
}

void ShGlobal::redo(ShCADWidget *widget) {

	QString first = shGetLanValue_command("Command/<Redo>");
	QString second;

	if (!widget->getRedoStack()->isEmpty()) {

		ShTransaction *transaction = widget->getRedoStack()->pop();
		transaction->redo();

		widget->getUndoStack()->push(transaction);

		second = transaction->getTransactionName();
	}
	else 
		second = shGetLanValue_command("Command/No remaining Redo Command");
	
	ShUpdateTextToCommandListEvent notifyEvent(first, ShUpdateTextToCommandListEvent::EditTextAndNewLineHeadTitleWithText);
	widget->notify(&notifyEvent);

	ShUpdateTextToCommandListEvent notifyEvent2(second, ShUpdateTextToCommandListEvent::OnlyText);
	widget->notify(&notifyEvent2);

	ShTransactionStackSizeChangedEvent notifyEvent3(widget->getUndoStack()->getSize(), widget->getRedoStack()->getSize());
	widget->notify(&notifyEvent3);
}

void ShGlobal::selectAll(ShCADWidget *widget) {

}

void ShGlobal::deleteSelectedEntity(ShCADWidget *widget) {

}

void ShGlobal::pushNewTransaction(ShCADWidget *widget, ShTransaction *transaction) {

	widget->getUndoStack()->push(transaction);
	if (!widget->getRedoStack()->isEmpty())
		widget->getRedoStack()->deleteAll();

	ShTransactionStackSizeChangedEvent notifyEvent(widget->getUndoStack()->getSize(), widget->getRedoStack()->getSize());
	widget->notify(&notifyEvent);
}
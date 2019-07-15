
#include "ShGlobal.h"
#include "Interface\ShCADWidget.h"
#include "UnRedo\ShTransaction.h"
#include "UnRedo\ShTransactionStack.h"
#include "Event\ShNotifyEvent.h"
#include <qstring.h>

ShGlobal::ShGlobal() {

}

ShGlobal::~ShGlobal() {

}

void ShGlobal::undo(ShCADWidget *widget) {

	if (!widget->getUndoStack()->isEmpty()) {

		ShTransaction *transaction = widget->getUndoStack()->pop();
		transaction->undo();

		widget->getRedoStack()->push(transaction);
	}
}

void ShGlobal::redo(ShCADWidget *widget) {

	if (!widget->getRedoStack()->isEmpty()) {

		ShTransaction *transaction = widget->getRedoStack()->pop();
		transaction->redo();

		widget->getUndoStack()->push(transaction);
	}
}

void ShGlobal::selectAll(ShCADWidget *widget) {

}

void ShGlobal::deleteSelectedEntity(ShCADWidget *widget) {

}

void ShGlobal::pushNewTransaction(ShCADWidget *widget, ShTransaction *transaction) {

	widget->getUndoStack()->push(transaction);
	if (!widget->getRedoStack()->isEmpty())
		widget->getRedoStack()->deleteAll();
}
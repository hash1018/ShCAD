
#include "ShGlobal.h"
#include "Interface\ShCADWidget.h"
#include "UnRedo\ShTransaction.h"
#include "UnRedo\ShTransactionStack.h"
#include "Event\ShNotifyEvent.h"
#include <qstring.h>
#include "Manager\ShLanguageManager.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "Manager\ShCommandLogManager.h"

ShGlobal::ShGlobal() {

}

ShGlobal::~ShGlobal() {

}

void ShGlobal::undo(ShCADWidget *widget) {

	if (widget->getSelectedEntities()->getSize() > 0) {
		widget->getSelectedEntities()->unSelectAll();
		widget->update(DrawType::DrawAll);
		widget->captureImage();
		return;
	}

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

	shCommandLogManager->appendListEditTextAndNewLineWith(first);
	shCommandLogManager->appendList(second);

	ShTransactionStackSizeChangedEvent notifyEvent3(widget->getUndoStack()->getSize(), widget->getRedoStack()->getSize());
	widget->notify(&notifyEvent3);
}

void ShGlobal::redo(ShCADWidget *widget) {

	if (widget->getSelectedEntities()->getSize() > 0) {
		widget->getSelectedEntities()->unSelectAll();
		widget->update(DrawType::DrawAll);
		widget->captureImage();
		return;
	}

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
	

	shCommandLogManager->appendListEditTextAndNewLineWith(first);
	shCommandLogManager->appendList(second);


	ShTransactionStackSizeChangedEvent notifyEvent3(widget->getUndoStack()->getSize(), widget->getRedoStack()->getSize());
	widget->notify(&notifyEvent3);
}

void ShGlobal::selectAll(ShCADWidget *widget) {

	QLinkedList<ShEntity*> temp;
	auto itr = widget->getEntityTable().turnOnLayerBegin();

	for (itr; itr != widget->getEntityTable().turnOnLayerEnd(); ++itr)
		temp.append(*itr);
	
	widget->getSelectedEntities()->add(temp);

	widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
	widget->captureImage();

	shCommandLogManager->appendListEditTextAndNewLineWith(shGetLanValue_command("Command/<Select All>"));
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
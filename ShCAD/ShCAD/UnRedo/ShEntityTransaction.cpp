
#include "ShEntityTransaction.h"
#include "Entity\ShEntity.h"
#include "Interface\ShCADWidget.h"

ShAddEntityTransaction::ShAddEntityTransaction(ShCADWidget *widget, const QString &transactionName)
	:ShTransaction("Group " + transactionName), widget(widget), mustDeleteEntity(false) {

}

ShAddEntityTransaction::~ShAddEntityTransaction() {

	if (this->mustDeleteEntity == true) {
	
		while (!this->list.isEmpty())
			delete this->list.takeFirst();
	}
}


void ShAddEntityTransaction::redo() {

	this->widget->getEntityTable().add(this->list);
	this->mustDeleteEntity = false;

	this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawAddedEntities));
	this->widget->captureImage();
}

void ShAddEntityTransaction::undo() {

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		this->widget->getEntityTable().remove((*itr));


	this->mustDeleteEntity = true;

	this->widget->update();
	this->widget->captureImage();
}

void ShAddEntityTransaction::add(ShEntity *entity) {

	this->list.append(entity);
}
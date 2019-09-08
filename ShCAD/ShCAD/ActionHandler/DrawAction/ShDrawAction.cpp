
#include "ShDrawAction.h"
#include "UnRedo\ShEntityTransaction.h"
#include "Base\ShGlobal.h"
#include "Base\ShCursorShape.h"

ShDrawAction::ShDrawAction(ShCADWidget *widget)
	:ShActionHandler(widget), addTransaction(nullptr) {

}

ShDrawAction::~ShDrawAction() {

}

QCursor ShDrawAction::getCursorShape() {

	return ShCursorShape::getCursor(ShCursorShape::CursorType::Drawing);
}

void ShDrawAction::addEntity(ShEntity *newEntity, const QString &type) {

	if (this->addTransaction == nullptr) {
		this->addTransaction = new ShAddEntityTransaction(this->widget, type);
		ShGlobal::pushNewTransaction(this->widget, this->addTransaction);
	}

	this->widget->getEntityTable().add(newEntity);
	this->addTransaction->add(newEntity);

	this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawAddedEntities));
	this->widget->captureImage();
	
}
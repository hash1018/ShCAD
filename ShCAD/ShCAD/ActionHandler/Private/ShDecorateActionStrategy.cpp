
#include "ShDecorateActionStrategy.h"
#include <qdebug.h>
#include "Interface\ShCADWidget.h"
#include "ActionHandler\ShActionHandler.h"
#include "ActionHandler\ShActionHandlerProxy.h"
#include "ObjectSnap\ShObjectSnapCommandFactory.h"


ShDecorateActionStrategy::ShDecorateActionStrategy() {

}

ShDecorateActionStrategy::~ShDecorateActionStrategy() {

}


///////////////////////////////////////////////////////

ShDecorateOrthogonalActionStrategy::ShDecorateOrthogonalActionStrategy() {

}

ShDecorateOrthogonalActionStrategy::~ShDecorateOrthogonalActionStrategy() {

}

void ShDecorateOrthogonalActionStrategy::change() {

	if (this->widget == nullptr)
		Q_ASSERT("ShDecorateOrthogonalActionStrategy::change() >> widget is null ptr");

	if (this->widget->getDraftData().getOrthMode() == false) {

		if (this->widget->getActionHandlerProxy()->getType() != ActionType::ActionDefault) {
			
			shCommandLogManager->appendHeadTitle("<Ortho on> ");
		}

		this->widget->getDraftData().setOrthMode(true);
	}
	else {
		if (this->widget->getActionHandlerProxy()->getType() != ActionType::ActionDefault) {
			
			shCommandLogManager->appendHeadTitle("<Ortho off> ");

		}

		this->widget->getDraftData().setOrthMode(false);
	}

	this->widget->getActionHandlerProxy()->changeDecoratorAction();

	this->widget->getActionHandlerProxy()->invalidate();

}

//////////////////////////////////////////////////////////////

ShDecorateDisposableSnapActionStrategy::ShDecorateDisposableSnapActionStrategy(ObjectSnap objectSnap)
	:objectSnap(objectSnap) {

}

ShDecorateDisposableSnapActionStrategy::~ShDecorateDisposableSnapActionStrategy() {

}

void ShDecorateDisposableSnapActionStrategy::change() {

	if (this->widget == nullptr)
		Q_ASSERT("ShDecorateDisposableSnapActionStrategy::change() >> widget is null ptr");

	if (this->objectSnap == ObjectSnap::ObjectSnapNothing) {
		this->widget->getDraftData().setDisposableSnap(ObjectSnap::ObjectSnapNothing);
		this->widget->getActionHandlerProxy()->changeDecoratorAction();
		return;
	}

	ShAvailableDraft draft = this->widget->getActionHandlerProxy()->getCurrentAction()->getAvailableDraft();

	QString str = ShObjectSnapCommandFactory::create(objectSnap);

	if (draft.getAvailableSnap() == false) {

		shCommandLogManager->appendListEditTextWith(str + shGetLanValue_command("Command/Unknown command") + ".");

		return;
	}

	if (this->widget->getDraftData().getDisposableSnap() != ObjectSnap::ObjectSnapNothing) {

		this->widget->getDraftData().setDisposableSnap(ObjectSnap::ObjectSnapNothing);
		
		shCommandLogManager->appendListEditTextWith(str);
		shCommandLogManager->appendList(shGetLanValue_command("Command/Invalid point") + ".");
		shCommandLogManager->replaceHeadTitle(this->widget->getActionHandlerProxy()->getCurrentAction()->getHeadTitle());
	}
	else {

		this->widget->getDraftData().setDisposableSnap(objectSnap);

		shCommandLogManager->appendHeadTitle(str);
	}

	this->widget->getActionHandlerProxy()->changeDecoratorAction();
}
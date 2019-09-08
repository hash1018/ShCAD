
#include "ShDecorateActionStrategy.h"
#include <qdebug.h>
#include "Interface\ShCADWidget.h"
#include "ActionHandler\ShActionHandler.h"
#include "ActionHandler\ShActionHandlerProxy.h"
#include "ObjectSnap\ShObjectSnapCommandFactory.h"
#include "ActionHandler\Private\ShDecoratorActionFactory.h"


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

		ShDecoratorAction *decoratorAction = this->widget->getActionHandlerProxy()->getDecoratorAction();
		decoratorAction = ShDecoratorActionFactory::addOrthgonal(this->widget, decoratorAction, this->widget->getDraftData());
		this->widget->getActionHandlerProxy()->setDecoratorAction(decoratorAction);

	}
	else {
		if (this->widget->getActionHandlerProxy()->getType() != ActionType::ActionDefault) {
			
			shCommandLogManager->appendHeadTitle("<Ortho off> ");

		}

		this->widget->getDraftData().setOrthMode(false);

		ShDecoratorAction *decoratorAction = this->widget->getActionHandlerProxy()->getDecoratorAction();
		decoratorAction = ShDecoratorActionFactory::removeOrthgonal(this->widget, decoratorAction, this->widget->getDraftData());
		this->widget->getActionHandlerProxy()->setDecoratorAction(decoratorAction);
	}

	
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

		ShDecoratorAction *decoratorAction = this->widget->getActionHandlerProxy()->getDecoratorAction();
		decoratorAction = ShDecoratorActionFactory::removeDisposableSnap(this->widget, decoratorAction, this->widget->getDraftData());
		this->widget->getActionHandlerProxy()->setDecoratorAction(decoratorAction);
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

		ShDecoratorAction *decoratorAction = this->widget->getActionHandlerProxy()->getDecoratorAction();
		decoratorAction = ShDecoratorActionFactory::removeDisposableSnap(this->widget, decoratorAction, this->widget->getDraftData());
		this->widget->getActionHandlerProxy()->setDecoratorAction(decoratorAction);

	}
	else {

		this->widget->getDraftData().setDisposableSnap(objectSnap);

		shCommandLogManager->appendHeadTitle(str);

		ShDecoratorAction *decoratorAction = this->widget->getActionHandlerProxy()->getDecoratorAction();
		decoratorAction = ShDecoratorActionFactory::addDisposableSnap(this->widget, decoratorAction, this->widget->getDraftData());
		this->widget->getActionHandlerProxy()->setDecoratorAction(decoratorAction);
	}
}
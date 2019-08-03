
#include "ShDecorateActionStrategy.h"
#include <qdebug.h>
#include "Interface\ShCADWidget.h"
#include "Event\ShNotifyEvent.h"
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
		ShUpdateCommandHeadTitleEvent notifyEvent("<Ortho on> ", ShUpdateCommandHeadTitleEvent::UpdateType::AddHeadTitleToCurrent);
		this->widget->notify(&notifyEvent);

		this->widget->getDraftData().setOrthMode(true);
	}
	else {
		ShUpdateCommandHeadTitleEvent notifyEvent("<Ortho off> ", ShUpdateCommandHeadTitleEvent::UpdateType::AddHeadTitleToCurrent);
		this->widget->notify(&notifyEvent);

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

		ShUpdateTextToCommandListEvent notifyEvent(str + "Unknown command.",
			ShUpdateTextToCommandListEvent::UpdateType::EditTextWithText);
		this->widget->notify(&notifyEvent);

		return;
	}

	if (this->widget->getDraftData().getDisposableSnap() != ObjectSnap::ObjectSnapNothing) {

		this->widget->getDraftData().setDisposableSnap(ObjectSnap::ObjectSnapNothing);
		ShUpdateTextToCommandListEvent event(str,
			ShUpdateTextToCommandListEvent::UpdateType::EditTextWithText);
		this->widget->notify(&event);

		ShUpdateTextToCommandListEvent event2("Invalid point.",
			ShUpdateTextToCommandListEvent::UpdateType::OnlyText);
		this->widget->notify(&event2);

		ShUpdateCommandHeadTitleEvent event3(this->widget->getActionHandlerProxy()->getCurrentAction()->getHeadTitle());
		this->widget->notify(&event3);
	}
	else {

		this->widget->getDraftData().setDisposableSnap(objectSnap);

		ShUpdateCommandHeadTitleEvent event(str,
			ShUpdateCommandHeadTitleEvent::UpdateType::AddHeadTitleToCurrent);
		this->widget->notify(&event);
	}

	this->widget->getActionHandlerProxy()->changeDecoratorAction();
}
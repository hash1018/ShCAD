
#include "ShKeyHandler.h"
#include "Event\ShNotifyEvent.h"
#include "Interface\ShCADWidget.h"
#include "ShKey.h"
#include <QKeyEvent>

ShKeyHandler::ShBuilder::ShBuilder(ShCADWidget *widget, ShActionHandler *actionHandler)
	:widget(widget), actionHandler(actionHandler), allowedInput(false) {

}

ShKeyHandler::ShBuilder::~ShBuilder() {

}

ShKeyHandler::ShBuilder& ShKeyHandler::ShBuilder::allowEnter() {

	this->list.append(new ShReturnKey);
	this->list.append(new ShEnterKey);
	
	return *this;
}

ShKeyHandler::ShBuilder& ShKeyHandler::ShBuilder::allowEsc() {

	this->list.append(new ShEscKey);

	return *this;
}

ShKeyHandler::ShBuilder& ShKeyHandler::ShBuilder::allowInput() {

	this->allowedInput = true;
	return *this;
}

ShKeyHandler::ShBuilder& ShKeyHandler::ShBuilder::allowCustom(ShKey *key) {

	this->list.append(key);

	return *this;
}

ShKeyHandler* ShKeyHandler::ShBuilder::build() {

	return new ShKeyHandler(*this);
}


ShKeyHandler::ShKeyHandler(const ShKeyHandler::ShBuilder &builder)
	:widget(builder.widget), actionHandler(builder.actionHandler), list(builder.list), 
	allowedInput(builder.allowedInput) {

}

ShKeyHandler::~ShKeyHandler() {

	for (int i = 0; i < this->list.size(); i++)
		delete this->list.at(i);
}


void ShKeyHandler::keyPressEvent(QKeyEvent *event) {

	int i = 0;

	while (i < this->list.size()) {

		if (this->list.at(i)->compare((Qt::Key)event->key(), (event->modifiers())))
			break;

		i++;
	}
	
	
	if (i < this->list.size()) {
		this->list.at(i)->press();
		return;
	}
	

	if (this->allowedInput == true) {
		ShKeyPressedEvent notifyEvent(event);
		this->widget->notify(&notifyEvent);
	}
}
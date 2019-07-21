
#include "ShKeyHandler.h"
#include "Event\ShNotifyEvent.h"
#include "Interface\ShCADWidget.h"
#include "ShKey.h"
#include <QKeyEvent>
#include "ShCustomKey.h"
#include "ShKeyFlyWeight.h"

ShKeyHandler::ShBuilder::ShBuilder(ShCADWidget *widget, ShActionHandler *actionHandler)
	:widget(widget), actionHandler(actionHandler), allowedInput(false) {

}

ShKeyHandler::ShBuilder::~ShBuilder() {

}


ShKeyHandler::ShBuilder& ShKeyHandler::ShBuilder::allowKey(KeyType keyType) {

	if (keyType == KeyType::Custom)
		return *this;

	ShKeyFactory* factory = ShKeyFactory::getInstance();
	ShKey *key = factory->get(keyType);

	this->list.append(key);

	return *this;
}

ShKeyHandler::ShBuilder& ShKeyHandler::ShBuilder::allowInput() {

	this->allowedInput = true;
	return *this;
}

ShKeyHandler::ShBuilder& ShKeyHandler::ShBuilder::allowCustom(ShAbstractCustomKey *key) {

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

	for (int i = 0; i < this->list.size(); i++) {

		if (dynamic_cast<ShAbstractCustomKey*>(this->list.at(i)))
			delete this->list.at(i);
	}
}


void ShKeyHandler::keyPressEvent(QKeyEvent *event) {

	int i = 0;

	while (i < this->list.size()) {

		if (this->list.at(i)->compare((Qt::Key)event->key(), (event->modifiers())))
			break;

		i++;
	}
	
	
	if (i < this->list.size()) {
		this->list.at(i)->pressed(this->widget, this->actionHandler);
		return;
	}
	

	if (this->allowedInput == true) {
		ShKeyPressedEvent notifyEvent(event);
		this->widget->notify(&notifyEvent);
	}
}
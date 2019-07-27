
#include "ShDecoratorAction.h"


ShDecoratorAction::ShDecoratorAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShActionHandler(widget), actionHandler(actionHandler), parent(nullptr), child(child) {

	if (this->child != nullptr)
		this->child->setParent(this);
}

ShDecoratorAction::~ShDecoratorAction() {


}


void ShDecoratorAction::mouseLeftPressEvent(ShActionData &data) {

	if (this->child != nullptr)
		this->child->mouseLeftPressEvent(data);
	else
		this->actionHandler->mouseLeftPressEvent(data);
}

void ShDecoratorAction::mouseMidPressEvent(ShActionData &data) {

	if (this->child != nullptr)
		this->child->mouseMidPressEvent(data);
	else
		this->actionHandler->mouseMidPressEvent(data);
}

void ShDecoratorAction::mouseRightPressEvent(ShActionData &data) {

	if (this->child != nullptr)
		this->child->mouseRightPressEvent(data);
	else
		this->actionHandler->mouseRightPressEvent(data);
}

void ShDecoratorAction::mouseMoveEvent(ShActionData &data) {

	if (this->child != nullptr)
		this->child->mouseMoveEvent(data);
	else
		this->actionHandler->mouseMoveEvent(data);
}

void ShDecoratorAction::mouseReleaseEvent(ShActionData &data) {

	if (this->child != nullptr)
		this->child->mouseReleaseEvent(data);
	else
		this->actionHandler->mouseReleaseEvent(data);
}

void ShDecoratorAction::draw(QPainter *painter) {

	if (this->child != nullptr)
		this->child->draw(painter);
	else
		this->actionHandler->draw(painter);
}

ActionType ShDecoratorAction::getType() {

	if (this->child != nullptr)
		return this->child->getType();
	
	return this->actionHandler->getType();
}

QString ShDecoratorAction::getHeadTitle() {

	if (this->child != nullptr)
		return this->child->getHeadTitle();

	return this->actionHandler->getHeadTitle();
}
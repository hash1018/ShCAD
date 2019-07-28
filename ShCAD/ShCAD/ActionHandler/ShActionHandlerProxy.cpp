
#include "ShActionHandlerProxy.h"
#include "ShActionHandler.h"
#include "Private\ShActionHandlerFactory.h"
#include <QMouseEvent>
#include "Private\ShActionData.h"
#include "Interface\ShCADWidget.h"
#include "Private\ShDecoratorActionFactory.h"
#include "DecoratorAction\ShDecoratorAction.h"


ShActionHandlerProxy::ShActionHandlerProxy(ShCADWidget *widget)
	:widget(widget),currentAction(nullptr) {

	this->currentAction = ShActionHandlerFactory::create(ActionType::ActionDefault, widget);
	this->decoratorAction = ShDecoratorActionFactory::create(this->widget, this->currentAction, this->widget->getDraftData());
}

ShActionHandlerProxy::~ShActionHandlerProxy() {

	if (this->currentAction != nullptr)
		delete this->currentAction;

	if (this->decoratorAction != nullptr)
		delete this->decoratorAction;
}

void ShActionHandlerProxy::mouseLeftPressEvent(QMouseEvent *event) {

	//ShActionData data;
	//this->widget->convertDeviceToEntity(event->x(), event->y(), data.point.x, data.point.y);
	//data.nextPoint = data.point;
	//data.mouseEvent = event;

	//this->currentAction->mouseLeftPressEvent(data);

	ShDecoratorActionData data;
	data.point = this->widget->getMousePoint();
	data.nextPoint = data.point;
	data.mouseEvent = event;
	this->decoratorAction->mouseLeftPressEvent(data);
}

void ShActionHandlerProxy::mouseMidPressEvent(QMouseEvent *event) {

	//ShActionData data;
	//this->widget->convertDeviceToEntity(event->x(), event->y(), data.point.x, data.point.y);
	//data.nextPoint = data.point;
	//data.mouseEvent = event;

	//this->currentAction->mouseMidPressEvent(data);

	ShDecoratorActionData data;
	data.point = this->widget->getMousePoint();
	data.nextPoint = data.point;
	data.mouseEvent = event;
	this->decoratorAction->mouseMidPressEvent(data);
}

void ShActionHandlerProxy::mouseRightPressEvent(QMouseEvent *event) {

	//ShActionData data;
	//this->widget->convertDeviceToEntity(event->x(), event->y(), data.point.x, data.point.y);
	//data.nextPoint = data.point;
	//data.mouseEvent = event;

	//this->currentAction->mouseRightPressEvent(data);

	ShDecoratorActionData data;
	data.point = this->widget->getMousePoint();
	data.nextPoint = data.point;
	data.mouseEvent = event;
	this->decoratorAction->mouseRightPressEvent(data);
}

void ShActionHandlerProxy::mouseMoveEvent(QMouseEvent *event) {
	
	this->widget->getDrawBuffer().saveToBuffer = true;
	this->widget->getDrawBuffer().buffer = DrawType::DrawNone;



	//ShActionData data;
	//this->widget->convertDeviceToEntity(event->x(), event->y(), data.point.x, data.point.y);
	//data.mouseEvent = event;

	//this->currentAction->mouseMoveEvent(data);

	ShDecoratorActionData data;
	data.point = this->widget->getMousePoint();
	data.mouseEvent = event;
	this->decoratorAction->mouseMoveEvent(data);

	
	this->widget->getDrawBuffer().saveToBuffer = false;

	if ((this->widget->getDrawBuffer().buffer & ~DrawType::DrawNone) != DrawType::DrawNone)
		this->widget->update(this->widget->getDrawBuffer().buffer);

	this->widget->getDrawBuffer().buffer = DrawType::DrawNone;
}

void ShActionHandlerProxy::mouseReleaseEvent(QMouseEvent *event) {

	//ShActionData data;
	//this->widget->convertDeviceToEntity(event->x(), event->y(), data.point.x, data.point.y);
	//data.mouseEvent = event;

	//this->currentAction->mouseReleaseEvent(data);

	ShDecoratorActionData data;
	data.point = this->widget->getMousePoint();
	data.mouseEvent = event;
	this->decoratorAction->mouseReleaseEvent(data);
}

void ShActionHandlerProxy::keyPressEvent(QKeyEvent *event) {

	//ShActionData data;
	//data.keyEvent = event;

	//this->currentAction->keyPressEvent(data);

	ShDecoratorActionData data;
	data.keyEvent = event;
	this->decoratorAction->keyPressEvent(data);
}

void ShActionHandlerProxy::setCurrentAction(ShActionHandler *actionHandler) {

	this->currentAction = actionHandler;

	this->changeDecoratorAction();
}

QCursor ShActionHandlerProxy::getCursorShape() {

	return this->currentAction->getCursorShape();
}

ActionType ShActionHandlerProxy::getType() {

	return this->currentAction->getType();
}

void ShActionHandlerProxy::draw(QPainter *painter) {

	//this->currentAction->draw(painter);
	this->decoratorAction->draw(painter);
}

void ShActionHandlerProxy::changeDecoratorAction() {

	if (this->decoratorAction != nullptr)
		delete this->decoratorAction;

	this->decoratorAction = ShDecoratorActionFactory::create(this->widget, this->currentAction, this->widget->getDraftData());
}

void ShActionHandlerProxy::invalidate() {

	this->widget->getDrawBuffer().saveToBuffer = true;
	this->widget->getDrawBuffer().buffer = DrawType::DrawNone;


	this->decoratorAction->invalidate(this->widget->getMousePoint());

	this->widget->getDrawBuffer().saveToBuffer = false;

	if ((this->widget->getDrawBuffer().buffer & ~DrawType::DrawNone) != DrawType::DrawNone)
		this->widget->update(this->widget->getDrawBuffer().buffer);

	this->widget->getDrawBuffer().buffer = DrawType::DrawNone;

}
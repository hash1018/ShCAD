
#include "ShCADWidget.h"
#include <QMouseEvent>
#include "Manager\ShCADWidgetManager.h"
#include "Manager\ShChangeManager.h"
#include "Event\ShNotifyEvent.h"
#include <qdebug.h>
#include "Private\ShCADWidgetDrawStrategy.h"
#include <qpainter.h>
#include "Base\ShMath.h"
#include "ActionHandler\ShActionHandlerProxy.h"
#include "ActionHandler\TemporaryAction\ShPanMoveAction.h"

ShCADWidget::ShCADWidget(QWidget *parent)
	:QOpenGLWidget(parent),zoomRate(1.0){

	this->actionHandlerProxy = new ShActionHandlerProxy(this);
	this->setCursor(this->actionHandlerProxy->getCursorShape());

	this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	
	this->axis.setCenter(ShPoint3d(100, 500));

}

ShCADWidget::~ShCADWidget() {

	if (this->actionHandlerProxy != nullptr)
		delete this->actionHandlerProxy;

	ShCADWidgetManager::getInstance()->remove(this);
}


void ShCADWidget::initializeGL() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	this->captureImage();
}


void ShCADWidget::resizeGL(int width, int height) {

	QOpenGLWidget::resizeGL(width, height);
	this->updateImmediately();
	this->captureImage();

}

void ShCADWidget::paintGL() {
	qDebug() << "paintGL" << this->drawType;
	QPainter painter(this);

	ShCADWidgetDrawStrategy strategy(this, &painter, this->drawType);
	strategy.draw();

}

void ShCADWidget::mousePressEvent(QMouseEvent *event) {

	if (event->buttons() & Qt::MiddleButton)
		this->setTemporaryAction(new ShPanMoveAction(this, this->actionHandlerProxy->getCurrentAction()));

	if (event->buttons() & Qt::LeftButton)
		this->actionHandlerProxy->mouseLeftPressEvent(event);
	else if (event->buttons() & Qt::MiddleButton)
		this->actionHandlerProxy->mouseMidPressEvent(event);
	else if (event->buttons() & Qt::RightButton)
		this->actionHandlerProxy->mouseRightPressEvent(event);
}

void ShCADWidget::mouseMoveEvent(QMouseEvent *event) {

	if (this->hasFocus() == false)
		this->setFocus();

	this->actionHandlerProxy->mouseMoveEvent(event);
}

void ShCADWidget::mouseReleaseEvent(QMouseEvent *event) {

	this->actionHandlerProxy->mouseReleaseEvent(event);
}

void ShCADWidget::keyPressEvent(QKeyEvent *event) {

	this->actionHandlerProxy->keyPressEvent(event);
}

void ShCADWidget::wheelEvent(QWheelEvent *event) {

}

void ShCADWidget::focusInEvent(QFocusEvent *event) {

	qDebug() << "ShCADWidget::focusInEvent ";

	ShCADWidgetManager *manager = ShCADWidgetManager::getInstance();

	if (manager->getActivatedWidget() == this)
		return;

	ShActivatedWidgetChangedEvent notifyEvent(this, manager->getActivatedWidget());
	this->notify(&notifyEvent);

	manager->setActivatedWidget(this);

}


void ShCADWidget::notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::getInstance();

	manager->notify(this, event);
}

void ShCADWidget::update(ShNotifyEvent *event) {

}

void ShCADWidget::update(DrawType drawType) {
	qDebug() << "ShCADWidget::update" << drawType;
	this->drawType = (DrawType)(this->drawType | drawType);
	qDebug() << "ShCADWidget::update  this->drawType" << this->drawType;
	
}


void ShCADWidget::updateImmediately(DrawType drawType) {
	qDebug() << "ShCADWidget::updateImmediately" << drawType;
	this->drawType = drawType;

	if ((this->drawType & ~DrawType::DrawNone) != DrawType::DrawNone) {
		qDebug() << "ShCADWidget::aboutToDraw";
		QOpenGLWidget::update();
	}
}

void ShCADWidget::replaceAction(ShActionHandler *actionHandler) {

	this->actionHandlerProxy->replaceAction(actionHandler);
}

void ShCADWidget::setTemporaryAction(ShTemporaryAction *temporaryAction) {

	this->actionHandlerProxy->setTemporaryAction(temporaryAction);
	this->setCursor(this->actionHandlerProxy->getCursorShape());
}

void ShCADWidget::convertDeviceToEntity(const int &x, const int &y, double &ex, double &ey) {

	ex = (x + this->scroll.horizontal - (this->axis.getCenter().x*this->zoomRate))*1.000 / this->zoomRate;
	ey = (-1 * (y + this->scroll.vertical - (this->axis.getCenter().y)*this->zoomRate))*1.000 / this->zoomRate;
}

void ShCADWidget::convertEntityToDevice(const double &x, const double &y, int &dx, int &dy) {

	double tempX = ((x*this->zoomRate) - this->scroll.horizontal + (this->axis.getCenter().x*this->zoomRate));
	double tempY = (-1 * ((y*this->zoomRate) + this->scroll.vertical - (this->axis.getCenter().y*this->zoomRate)));

	dx = math::toInt(tempX);
	dy = math::toInt(tempY);
}

void ShCADWidget::captureImage() {
	qDebug() << "captureImage";
	this->capturedImage = this->grabFramebuffer();
}
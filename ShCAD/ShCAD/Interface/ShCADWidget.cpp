
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
	this->update();
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

	ShPoint3d point;
	this->convertDeviceToEntity(event->x(), event->y(), point.x, point.y);
	ShMousePositionChangedEvent notifyEvent(point);
	this->notify(&notifyEvent);

}

void ShCADWidget::mouseReleaseEvent(QMouseEvent *event) {

	this->actionHandlerProxy->mouseReleaseEvent(event);
}

void ShCADWidget::keyPressEvent(QKeyEvent *event) {

	this->actionHandlerProxy->keyPressEvent(event);
}

void ShCADWidget::wheelEvent(QWheelEvent *event) {

	this->convertDeviceToEntity(event->x(), event->y(), this->coordinate.x, this->coordinate.y);

	if (event->delta() > 0) {

		if (this->zoomRate < 15 && this->zoomRate >= 1)
			this->zoomRate++;
		else if (this->zoomRate < 1)
			this->zoomRate += 0.2;
		else
			return;
	}
	else {
		if (this->zoomRate > 2)
			this->zoomRate--;
		else if (this->zoomRate <= 2 && this->zoomRate > 1)
			this->zoomRate -= 0.5;
		else if (this->zoomRate <= 1 && math::compare(this->zoomRate, 0.2) == 1)
			this->zoomRate -= 0.2;
		else if ((math::compare(this->zoomRate, 0.2) == 0 || math::compare(this->zoomRate, 0.2) == -1) &&
			math::compare(this->zoomRate, 0.05) == 1)
			this->zoomRate -= 0.01;
		else
			return;
	}


	this->scroll.vertical = (-1 * (this->zoomRate*this->coordinate.y) -
		event->y() + (this->axis.getCenter().y*this->zoomRate));
	this->scroll.horizontal = (this->zoomRate*this->coordinate.x -
		event->x() + (this->axis.getCenter().x*this->zoomRate));

	this->update();

	ShZoomRateChangedEvent notifyEvent(this->zoomRate);
	this->notify(&notifyEvent);
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

void ShCADWidget::store(DrawType drawType) {
	
	this->drawType = (DrawType)(this->drawType | drawType);
}


void ShCADWidget::update(DrawType drawType) {
	
	this->drawType = drawType;

	if ((this->drawType & ~DrawType::DrawNone) != DrawType::DrawNone)
		QOpenGLWidget::update();
	
}

void ShCADWidget::clearDrawType() {

	this->drawType = DrawType::DrawNone;
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
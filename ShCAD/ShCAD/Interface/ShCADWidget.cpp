
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
#include "Event\ShCADWidgetEventFilter.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"



ShCADWidget::ShCADWidget(QWidget *parent)
	:QOpenGLWidget(parent),zoomRate(1.0){

	this->actionHandlerProxy = new ShActionHandlerProxy(this);
	this->setCursor(this->actionHandlerProxy->getCursorShape());

	this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	
	this->axis.setCenter(ShPoint3d(100, 500));

	this->undoStack = new ShTransactionStack;
	this->redoStack = new ShTransactionStack;

}

ShCADWidget::~ShCADWidget() {

	if (this->actionHandlerProxy != nullptr)
		delete this->actionHandlerProxy;

	if (this->undoStack != nullptr)
		delete this->undoStack;
	
	if (this->redoStack != nullptr)
		delete this->redoStack;

	this->rubberBand.clear();

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
	qDebug() << "paintGL";
	QPainter painter(this);

	ShCADWidgetDrawStrategy strategy(this, &painter, this->drawBuffer.drawType);
	strategy.draw();

}


void ShCADWidget::mousePressEvent(QMouseEvent *event) {

	if (event->buttons() & Qt::MiddleButton) {
		ShChangeTemporaryPanStrategy strategy(this->actionHandlerProxy->getCurrentAction());
		this->changeAction(strategy);
	}


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
	this->captureImage();

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

	ShCADWidgetEventFilter filter(this, event);
	filter.update();
}


void ShCADWidget::update(DrawType drawType) {
	
	if (this->drawBuffer.saveToBuffer == true) {
		this->drawBuffer.buffer = (DrawType)(this->drawBuffer.buffer | drawType);
	}
	else {
		this->drawBuffer.drawType = drawType;
		QOpenGLWidget::update();
	}
}

void ShCADWidget::changeAction(ShChangeActionStrategy &strategy) {

	strategy.widget = this;
	strategy.change();
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

void ShCADWidget::shiftViewport(const ShPoint3d &coordinate, int dx, int dy) {

	this->coordinate = coordinate;

	this->scroll.vertical = (-1 * (this->zoomRate*this->coordinate.y) - dy +
		(this->axis.getCenter().y*this->zoomRate));
	this->scroll.horizontal = (this->zoomRate*this->coordinate.x - dx +
		(this->axis.getCenter().x*this->zoomRate));

	this->update(DrawType::DrawAll);
	this->captureImage();

	QPoint pos = this->mapFromGlobal(QCursor::pos());
	this->convertDeviceToEntity(pos.x(), pos.y(), this->coordinate.x, this->coordinate.y);

	ShMousePositionChangedEvent notifyEvent(this->coordinate);
	this->notify(&notifyEvent);
}

ShPoint3d ShCADWidget::getMousePoint() {

	ShPoint3d mouse;
	QPoint pos = this->mapFromGlobal(QCursor::pos());
	this->convertDeviceToEntity(pos.x(), pos.y(), mouse.x, mouse.y);

	return mouse;
}

bool ShCADWidget::setOrthMode() {

	if (this->draftData.getOrthMode() == false) {
		ShUpdateCommandHeadTitleEvent notifyEvent("<Ortho on> ", ShUpdateCommandHeadTitleEvent::UpdateType::AddHeadTitleToCurrent);
		this->notify(&notifyEvent);

		this->draftData.setOrthMode(true);
	}
	else {
		ShUpdateCommandHeadTitleEvent notifyEvent("<Ortho off> ", ShUpdateCommandHeadTitleEvent::UpdateType::AddHeadTitleToCurrent);
		this->notify(&notifyEvent);

		this->draftData.setOrthMode(false);
	}

	this->actionHandlerProxy->changeDecoratorAction();

	this->actionHandlerProxy->invalidate();

	return this->draftData.getOrthMode();
}
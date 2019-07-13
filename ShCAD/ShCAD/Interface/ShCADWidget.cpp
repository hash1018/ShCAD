
#include "ShCADWidget.h"
#include <QMouseEvent>
#include "Manager\ShCADWidgetManager.h"
#include "Manager\ShChangeManager.h"
#include "Event\ShNotifyEvent.h"
#include <qdebug.h>
#include "Private\ShCADWidgetDrawStrategy.h"
#include <qpainter.h>
#include "Base\ShMath.h"

ShCADWidget::ShCADWidget(QWidget *parent)
	:QOpenGLWidget(parent),zoomRate(1.0),hPos(0),vPos(0),drawType(DrawAll) {

	this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	
	this->axis.setCenter(ShPoint3d(100, 500));

}

ShCADWidget::~ShCADWidget() {


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
	
	QPainter painter(this);

	ShCADWidgetDrawStrategy strategy(this, &painter, this->drawType);
	strategy.draw();

}

void ShCADWidget::mousePressEvent(QMouseEvent *event) {

}

void ShCADWidget::mouseMoveEvent(QMouseEvent *event) {

	if (this->hasFocus() == false)
		this->setFocus();

	//this->coordinate.point.x = event->x();
	//this->coordinate.point.y = event->y();

	//MousePositionChangedEvent notifyEvent(this->coordinate);

	//this->Notfiy(&notifyEvent);
}

void ShCADWidget::mouseReleaseEvent(QMouseEvent *event) {

}

void ShCADWidget::keyPressEvent(QKeyEvent *event) {

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

	this->drawType = drawType;
	QOpenGLWidget::update();
}

void ShCADWidget::convertDeviceToEntity(const int &x, const int &y, double &ex, double &ey) {


	ex = (x + this->hPos - (this->axis.getCenter().x*this->zoomRate))*1.000 / this->zoomRate;
	ey = (-1 * (y + this->vPos - (this->axis.getCenter().y)*this->zoomRate))*1.000 / this->zoomRate;
}

void ShCADWidget::convertEntityToDevice(const double &x, const double &y, int &dx, int &dy) {

	double tempX = ((x*this->zoomRate) - this->hPos + (this->axis.getCenter().x*this->zoomRate));
	double tempY = (-1 * ((y*this->zoomRate) + this->vPos - (this->axis.getCenter().y*this->zoomRate)));

	dx = math::toInt(tempX);
	dy = math::toInt(tempY);
}

void ShCADWidget::captureImage() {

	this->capturedImage = this->grabFramebuffer();
}
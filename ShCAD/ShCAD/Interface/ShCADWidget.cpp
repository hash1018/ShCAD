
#include "ShCADWidget.h"
#include <QMouseEvent>
#include "Manager\ShCADWidgetManager.h"

ShCADWidget::ShCADWidget(QWidget *parent)
	:QOpenGLWidget(parent) {

	this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);

}

ShCADWidget::~ShCADWidget() {


	ShCADWidgetManager::getInstance()->Remove(this);
}


void ShCADWidget::initializeGL() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

}


void ShCADWidget::resizeGL(int width, int height) {

	QOpenGLWidget::resizeGL(width, height);
	this->update();


}

void ShCADWidget::paintGL() {


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

	//ShCADWidgetManager *manager = ShCADWidgetManager::GetInstance();

	//if (manager->GetActivatedView() == this)
	//	return;

	//ActivatedViewChangedEvent notifyEvent(this, manager->GetActivatedView());
	//this->Notfiy(&notifyEvent);

	//manager->SetActivatedView(this);

}

/*
void ShCADWidget::Notfiy(NotifyEvent *event) {

	ChangeManager *manager = ChangeManager::GetInstance();

	manager->Notify(this, event);
}
*/

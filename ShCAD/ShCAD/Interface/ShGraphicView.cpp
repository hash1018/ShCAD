
/*--
**
**   This file is part of the ShCAD project, a 2D CAD Program
**
**    Copyright (C) 2019, Seungho Ha  (sh.ha1018@gmail.com)
**
**
**   This program is free software; you can redistribute it and/or modify it
**   under the terms of the GNU Lesser General Public License as published by
**   the Free Software Foundation; either version 2.1 of the License, or (at
**   your option) any later version.
**
**   This program is distributed in the hope that it will be useful, but
**   WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
**   General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
**
**
--*/


#include "ShGraphicView.h"
#include "ActionHandler\ShActionHandlerManager.h"
#include "ActionHandler\TemporaryAction\ShPanMoveAction.h"
#include <QMouseEvent>
#include "ShMath.h"
#include "ShNotifyEvent.h"
#include "Singleton Pattern\ShWidgetManager.h"

ShGraphicView::ShGraphicView(QWidget *parent)
	:QOpenGLWidget(parent){

	this->actionHandlerManager = new ShActionHandlerManager(this, this->draftFlag);
	this->setCursor(this->actionHandlerManager->GetCursorShape());

	this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	

	this->drawType = DrawType::DrawAll;
	
	this->rubberBand = NULL;

	this->axis.SetCenter(ShPoint3d(100, 500));

	this->selectedEntityManager.SetGraphicView(this);

}


ShGraphicView::~ShGraphicView() {

	if (this->actionHandlerManager != NULL)
		delete this->actionHandlerManager;

	if (this->rubberBand != NULL)
		delete this->rubberBand;
	
	ShWidgetManager::GetInstance()->Remove(this);
}


void ShGraphicView::initializeGL() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	this->CaptureImage();

}

void ShGraphicView::resizeGL(int width, int height) {

	QOpenGLWidget::resizeGL(width, height);
	this->update();
	this->CaptureImage();
}



void ShGraphicView::update(DrawType drawType) {

	this->drawType = drawType;

	QOpenGLWidget::update();
}



#include <qpainter.h>
#include "Strategy Pattern\ShViewDrawStrategy.h"
void ShGraphicView::paintGL() {


	QPainter painter(this);

	ShViewDrawStrategy strategy(this, &painter, this->drawType);
	strategy.Draw();
	
	
}


void ShGraphicView::mousePressEvent(QMouseEvent *event) {
	//qDebug("mousePressEvent in ShGraphicView");

	if (event->buttons() & Qt::MiddleButton)
		this->SetTemporaryAction(new ShPanMoveAction(this));
		
	this->actionHandlerManager->MousePressEvent(event);

}

void ShGraphicView::mouseMoveEvent(QMouseEvent *event) {
	//qDebug("mouseMoveEvent in ShGraphicView");
	
	if (this->hasFocus() == false)
		this->setFocus();
	
	this->ConvertDeviceToEntity(event->x(), event->y(), this->data.x, this->data.y);

	ShMousePositionChangedEvent notifyEvent(this->data.x, this->data.y, this->data.z, this->data.zoomRate);
	this->Notify(&notifyEvent);

	this->actionHandlerManager->MouseMoveEvent(event);
}

void ShGraphicView::mouseReleaseEvent(QMouseEvent *event) {

	this->actionHandlerManager->MouseReleaseEvent(event);
}

void ShGraphicView::keyPressEvent(QKeyEvent *event) {

	this->actionHandlerManager->KeyPressEvent(event);
}


void ShGraphicView::wheelEvent(QWheelEvent *event) {

	this->ConvertDeviceToEntity(event->x(), event->y(), this->data.x, this->data.y);

	if (event->delta() > 0) {
	
		if (this->data.zoomRate < 15 && this->data.zoomRate >= 1)
			this->data.zoomRate++;
		else if (this->data.zoomRate < 1)
			this->data.zoomRate += 0.2;
		else
			return;
	}
	else {
		if (this->data.zoomRate > 2)
			this->data.zoomRate--;
		else if (this->data.zoomRate <= 2 && this->data.zoomRate > 1)
			this->data.zoomRate -= 0.5;
		else if (this->data.zoomRate <= 1 && Math::Compare(this->data.zoomRate, 0.2) == 1)
			this->data.zoomRate -= 0.2;
		else if ((Math::Compare(this->data.zoomRate, 0.2) == 0 || Math::Compare(this->data.zoomRate, 0.2) == -1) &&
			Math::Compare(this->data.zoomRate, 0.05) == 1)
			this->data.zoomRate -= 0.01;
		else
			return;
	}


	this->data.vPos = (-1 * (this->data.zoomRate*this->data.y) - event->y() + (this->axis.GetCenter().y*this->data.zoomRate));
	this->data.hPos = (this->data.zoomRate*this->data.x - event->x() + (this->axis.GetCenter().x*this->data.zoomRate));

	this->update(DrawType::DrawAll);
	this->CaptureImage();

	ShZoomRateChangedEvent notifyEvent(this->data.x, this->data.y, this->data.z, this->data.zoomRate);
	this->Notify(&notifyEvent);

}

#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
ActionType ShGraphicView::ChangeCurrentAction(ShChangeCurrentActionStrategy& strategy) {

	strategy.SetView(this);
	return strategy.Change();
}

void ShGraphicView::CaptureImage() {

	this->captureImage = this->grabFramebuffer();
}


void ShGraphicView::focusInEvent(QFocusEvent *event) {

	ShWidgetManager *manager = ShWidgetManager::GetInstance();

	if (manager->GetActivatedWidget() == this)
		return;

	
	ShActivatedWidgetChangedEvent event2(this, manager->GetActivatedWidget());
	this->Notify(&event2);

	manager->SetActivatedWidget(this);


}

#include "Singleton Pattern\ShChangeManager.h"
void ShGraphicView::Notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, event);

}

#include "Strategy Pattern\ShViewNotifyEventUpdateStrategy.h"
void ShGraphicView::Update(ShNotifyEvent *event) {

	ShViewNotifyEventUpdateStrategy strategy(this, event);
	strategy.Update();

}

void ShGraphicView::ConvertDeviceToEntity(int x, int y, double &ex, double &ey) {

	ex = (x + this->data.hPos - (this->axis.GetCenter().x*this->data.zoomRate))*1.000f / this->data.zoomRate;
	ey = (-1 * (y + this->data.vPos - (this->axis.GetCenter().y)*this->data.zoomRate))*1.000f / this->data.zoomRate;
}

void ShGraphicView::ConvertEntityToDevice(double x, double y, int &dx, int &dy) {

	double tempX = ((x*this->data.zoomRate) - this->data.hPos + (this->axis.GetCenter().x*this->data.zoomRate));
	double tempY = (-1 * ((y*this->data.zoomRate) + this->data.vPos - (this->axis.GetCenter().y*this->data.zoomRate)));

	dx = Math::ToInt(tempX);
	dy = Math::ToInt(tempY);
	
}

void ShGraphicView::MoveView(double ex, double ey, double zoomRate, int dx, int dy) {
	qDebug("ShGraphicView->MoveView");
	this->data.x = ex;
	this->data.y = ey;
	this->data.zoomRate = zoomRate;
	

	this->data.vPos = (-1 * (zoomRate*ey) - dy + (this->axis.GetCenter().y*zoomRate));
	this->data.hPos = (zoomRate*ex - dx + (this->axis.GetCenter().x*zoomRate));

	this->update(DrawType::DrawAll);
	this->CaptureImage();

	QPoint pos = this->mapFromGlobal(QCursor::pos());
	this->ConvertDeviceToEntity(pos.x(), pos.y(), this->data.x, this->data.y);
	
	ShMousePositionChangedEvent notifyEvent(this->data.x, this->data.y, this->data.z, this->data.zoomRate);
	this->Notify(&notifyEvent);
}


void ShGraphicView::SetTemporaryAction(ShTemporaryAction *temporaryAction) {
	qDebug("ShGraphicView->SetTemporaryAction");
	
	this->actionHandlerManager->SetTemporaryAction(temporaryAction);
	this->setCursor(this->actionHandlerManager->GetCursorShape());

	ShCurrentActionChangedEvent event(this->actionHandlerManager->GetType());
	this->Notify(&event);
}


ActionType ShGraphicView::GetCurrentActionType() {

	return this->actionHandlerManager->GetType();
}

void ShGraphicView::SetOrthogonalMode() {

	if (this->draftFlag.acceptOrthogonal == false) {

		ShUpdateCommandEditHeadTitle event("<Ortho on> ", ShUpdateCommandEditHeadTitle::UpdateType::AddHeadTitleToCurrent);
		this->Notify(&event);

		this->draftFlag.acceptOrthogonal = true;
	}
	else {
		ShUpdateCommandEditHeadTitle event("<Ortho off> ", ShUpdateCommandEditHeadTitle::UpdateType::AddHeadTitleToCurrent);
		this->Notify(&event);

		this->draftFlag.acceptOrthogonal = false;
	}

	this->actionHandlerManager->SetDraftFlag(this->draftFlag);
}

ShPoint3d ShGraphicView::GetCursorPoint() {

	ShPoint3d mouse;
	QPoint pos = this->mapFromGlobal(QCursor::pos());
	this->ConvertDeviceToEntity(pos.x(), pos.y(), mouse.x, mouse.y);

	return mouse;
}
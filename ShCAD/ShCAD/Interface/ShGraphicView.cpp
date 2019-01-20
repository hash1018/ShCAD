
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
#include "FactoryMethod\ShCreatorActionFactory.h"
#include "ActionHandler\TemporaryAction\ShPanMoveAction.h"
#include "Entity\Leaf\ShRubberBand.h"
#include <QMouseEvent>
#include "ShMath.h"
#include "ShNotifyEvent.h"
#include "Singleton Pattern\ShWidgetManager.h"

ShGraphicView::ShGraphicView(QWidget *parent)
	:QOpenGLWidget(parent){

	this->currentAction = ShCreatorActionFactory::Create(ActionType::ActionDefault, this);

	this->setCursor(this->currentAction->GetCursorShape());

	this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	

	this->drawType = DrawType::DrawAll;
	
	this->rubberBand = NULL;

	this->axis.SetCenter(ShPoint3d(100, 500));

	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->zoomRate = 1;
	this->hPos = 0;
	this->vPos = 0;

}


ShGraphicView::~ShGraphicView() {

	if (this->currentAction != NULL)
		delete this->currentAction;

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


#include "Visitor Pattern\ShDrawer.h"
#include <qpainter.h>
void ShGraphicView::paintGL() {


	QPainter paint(this);
	

	if ((this->drawType & DrawType::DrawAll) == DrawType::DrawAll) {
		//qDebug("DrawAll");

		ShDrawer drawer(this, DrawType::DrawAll);

		this->axis.Draw(&paint, this);

		ShComposite::Iterator itr = this->entityTable.Begin();

		while (!itr.IsEnd()) {

			itr.Current()->Accept(&drawer);
			itr.Next();
		}
	}

	if ((this->drawType & DrawType::DrawCaptureImage) == DrawType::DrawCaptureImage) {
		//qDebug("DrawCaptureImage");

		if (paint.isActive() == false)
			paint.begin(this);

		paint.drawImage(0, 0, this->captureImage, 0, 0, 0, 0);
		paint.end();

	}

	if ((this->drawType & DrawType::DrawPreviewEntities) == DrawType::DrawPreviewEntities) {
		//qDebug("DrwaPreviewEntities");

		ShDrawer drawer(this, DrawType::DrawPreviewEntities);

		if (this->rubberBand != NULL) {
			this->rubberBand->Accept(&drawer);
		}

		ShComposite::Iterator itr = this->preview.Begin();

		while (!itr.IsEnd()) {
			itr.Current()->Accept(&drawer);
			itr.Next();
		}
	}


	if ((this->drawType & DrawType::DrawAddedEntities) == DrawType::DrawAddedEntities) {
		//qDebug("DrawAddedEntities");

		ShDrawer drawer(this, DrawType::DrawAddedEntities);

		ShComposite::Iterator itr = this->entityTable.GetJustAddedEntitiesBegin();

		while (!itr.IsEnd()) {
			itr.Current()->Accept(&drawer);
			itr.Next();
		}
	}


	if ((this->drawType & DrawType::DrawSelectedEntities) == DrawType::DrawSelectedEntities) {
		//qDebug("DrawSelectedEntities");

		ShDrawer drawer(this, DrawType::DrawSelectedEntities);

		ShSelectedEntityManager::Iterator itr = this->selectedEntityManager.GetJustSelectedBegin();

		while (!itr.IsEnd()) {
			itr.Current()->Accept(&drawer);
			itr.Next();
		}
	}

	if ((this->drawType & DrawType::DrawJustUnSelectedEntities) == DrawType::DrawJustUnSelectedEntities) {
		//qDebug("DrawJustUnSelectedEntities");

		ShDrawer drawer(this, DrawType::DrawJustUnSelectedEntities);

		ShSelectedEntityManager::Iterator itr = this->selectedEntityManager.GetJustUnSelectedBegin();

		while (!itr.IsEnd()) {
			itr.Current()->Accept(&drawer);
			itr.Next();
		}
	}



	if ((this->drawType & DrawType::DrawActionHandler) == DrawType::DrawActionHandler) {
		//qDebug("DrawActionHandler");
		this->currentAction->Draw(&paint);
	}



}


void ShGraphicView::mousePressEvent(QMouseEvent *event) {
	//qDebug("mousePressEvent in ShGraphicView");

	if (event->buttons() & Qt::MiddleButton)
		this->SetTemporaryAction(new ShPanMoveAction(this, this->currentAction));
		

	this->currentAction->MousePressEvent(event);

}

void ShGraphicView::mouseMoveEvent(QMouseEvent *event) {
	//qDebug("mouseMoveEvent in ShGraphicView");
	
	if (this->hasFocus() == false)
		this->setFocus();
	
	this->ConvertDeviceToEntity(event->x(), event->y(), this->x, this->y);

	ShMousePositionChangedEvent notifyEvent(this->x, this->y, this->z, this->zoomRate);
	this->Notify(&notifyEvent);


	this->currentAction->MouseMoveEvent(event);
}

void ShGraphicView::mouseReleaseEvent(QMouseEvent *event) {

	this->currentAction->MouseReleaseEvent(event);
}

void ShGraphicView::keyPressEvent(QKeyEvent *event) {

	this->currentAction->KeyPressEvent(event);

}


void ShGraphicView::wheelEvent(QWheelEvent *event) {

	this->ConvertDeviceToEntity(event->x(), event->y(), this->x, this->y);

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
		else if (this->zoomRate <= 1 && Math::Compare(this->zoomRate, 0.2) == 1)
			this->zoomRate -= 0.2;
		else if ((Math::Compare(this->zoomRate, 0.2) == 0 || Math::Compare(this->zoomRate, 0.2) == -1) &&
			Math::Compare(this->zoomRate, 0.05) == 1)
			this->zoomRate -= 0.01;
		else
			return;
	}


	this->vPos = (-1 * (this->zoomRate*this->y) - event->y() + (this->axis.GetCenter().y*this->zoomRate));
	this->hPos = (this->zoomRate*this->x - event->x() + (this->axis.GetCenter().x*this->zoomRate));

	this->update(DrawType::DrawAll);
	this->CaptureImage();

	ShZoomRateChangedEvent notifyEvent(this->x, this->y, this->z, this->zoomRate);
	this->Notify(&notifyEvent);

}




ActionType ShGraphicView::ChangeCurrentAction(ActionType actionType) {
	qDebug("ShGraphicView->ChangeCurrentAction");

	if (actionType == ActionType::ActionDefault &&
		this->currentAction->GetType() == ActionType::ActionDefault)
		return actionType;


	if (this->currentAction != NULL)
		delete this->currentAction;

	DrawType drawType = DrawType::DrawCaptureImage;


	if (this->rubberBand != NULL) {
		delete this->rubberBand;
		this->rubberBand = NULL;
		drawType = (DrawType)(drawType | DrawType::DrawCaptureImage);
	}

	if (!this->preview.IsListEmpty()) {
		this->preview.DeleteAll();
		drawType = (DrawType)(drawType | DrawType::DrawCaptureImage);
	}

	if (this->selectedEntityManager.GetSize() > 0) {
		this->selectedEntityManager.UnSelectAll();
		drawType = (DrawType)(drawType | DrawType::DrawAll);
	}


	if ((drawType & DrawType::DrawAll) == DrawType::DrawAll) {
		this->update(DrawType::DrawAll);
		this->CaptureImage();
	}
	else if ((drawType & DrawType::DrawCaptureImage) == DrawType::DrawCaptureImage)
		this->update(DrawType::DrawCaptureImage);



	this->currentAction = ShCreatorActionFactory::Create(actionType, this);
	this->setCursor(this->currentAction->GetCursorShape());

	return this->currentAction->GetType();


}


void ShGraphicView::CaptureImage() {

	this->captureImage = this->grabFramebuffer();
}


void ShGraphicView::focusInEvent(QFocusEvent *event) {

	ShWidgetManager *manager = ShWidgetManager::GetInstance();

	manager->SetActivatedWidget(this);
}

#include "Singleton Pattern\ShChangeManager.h"
void ShGraphicView::Notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, event);

}

void ShGraphicView::Update(ShNotifyEvent *event) {

	if (dynamic_cast<ShKeyPressedEvent*>(event)) {
		this->currentAction->KeyPressEvent(dynamic_cast<ShKeyPressedEvent*>(event)->GetEvent());
	}


}

void ShGraphicView::ConvertDeviceToEntity(int x, int y, double &ex, double &ey) {

	ex = (x + this->hPos - (this->axis.GetCenter().x*this->zoomRate))*1.000f / this->zoomRate;
	ey = (-1 * (y + this->vPos - (this->axis.GetCenter().y)*this->zoomRate))*1.000f / this->zoomRate;
}

void ShGraphicView::ConvertEntityToDevice(double x, double y, int &dx, int &dy) {

	double tempX = ((x*this->zoomRate) - this->hPos + (this->axis.GetCenter().x*this->zoomRate));
	double tempY = (-1 * ((y*this->zoomRate) + this->vPos - (this->axis.GetCenter().y*this->zoomRate)));

	dx = Math::ToInt(tempX);
	dy = Math::ToInt(tempY);
	
}

void ShGraphicView::MoveView(double ex, double ey, double zoomRate, int dx, int dy) {
	qDebug("ShGraphicView->MoveView");
	this->x = ex;
	this->y = ey;
	this->zoomRate = zoomRate;
	

	this->vPos = (-1 * (zoomRate*ey) - dy + (this->axis.GetCenter().y*zoomRate));
	this->hPos = (zoomRate*ex - dx + (this->axis.GetCenter().x*zoomRate));

	this->update(DrawType::DrawAll);
	this->CaptureImage();

	QPoint pos = this->mapFromGlobal(QCursor::pos());
	this->ConvertDeviceToEntity(pos.x(), pos.y(), this->x, this->y);
	
	ShMousePositionChangedEvent notifyEvent(this->x, this->y, this->z, this->zoomRate);
	this->Notify(&notifyEvent);
}

void ShGraphicView::SetTemporaryAction(ShTemporaryAction *temporaryAction) {
	qDebug("ShGraphicView->SetTemporaryAction");
	this->currentAction = temporaryAction;
}

void ShGraphicView::SetHPos(int hPos) {
	this->hPos = hPos;
}

void ShGraphicView::SetVPos(int vPos) {
	this->vPos = vPos;
}
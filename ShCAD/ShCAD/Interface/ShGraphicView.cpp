
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
#include "ActionHandler\ShActionHandler.h"
#include "Entity\Leaf\ShRubberBand.h"

ShGraphicView::ShGraphicView(QWidget *parent)
	:QOpenGLWidget(parent){

	this->currentAction = ShCreatorActionFactory::Create(ActionType::ActionDefault, this);

	this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	this->setMouseTracking(true);

	this->drawType = DrawType::DrawAll;
	
	this->rubberBand = NULL;

}


ShGraphicView::~ShGraphicView() {

	if (this->currentAction != NULL)
		delete this->currentAction;

	if (this->rubberBand != NULL)
		delete this->rubberBand;
	
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
	ShDrawer drawer(this->width(), this->height());

	if ((this->drawType & DrawType::DrawAll) == DrawType::DrawAll) {
		qDebug("DrawAll");


		ShComposite::Iterator itr = this->entityTable.Begin();

		while (!itr.IsEnd()) {

			itr.Current()->Accept(&drawer);
			itr.Next();
		}
	}

	if ((this->drawType & DrawType::DrawCaptureImage) == DrawType::DrawCaptureImage) {
		qDebug("DrawCaptureImage");

		if (paint.isActive() == false)
			paint.begin(this);

		paint.drawImage(0, 0, this->captureImage, 0, 0, 0, 0);
		paint.end();

	}

	if ((this->drawType & DrawType::DrawPreviewEntities) == DrawType::DrawPreviewEntities) {
		qDebug("DrwaPreviewEntities");

		if (this->rubberBand != NULL) {
			this->rubberBand->Accept(&drawer);
		}

		ShDrawer drawer(this->width(), this->height());

		ShComposite::Iterator itr = this->preview.Begin();

		while (!itr.IsEnd()) {
			itr.Current()->Accept(&drawer);
			itr.Next();
		}

	}

	if ((this->drawType & DrawType::DrawAddedEntities) == DrawType::DrawAddedEntities) {
		qDebug("DrawAddedEntities");


		ShComposite::Iterator itr = this->entityTable.End();
		itr.Previous();
		itr.Current()->Accept(&drawer);
	}


}


void ShGraphicView::mousePressEvent(QMouseEvent *event) {
	//qDebug("mousePressEvent in ShGraphicView");


	this->currentAction->MousePressEvent(event);


}

void ShGraphicView::mouseMoveEvent(QMouseEvent *event) {
	//qDebug("mouseMoveEvent in ShGraphicView");

	this->currentAction->MouseMoveEvent(event);
}

void ShGraphicView::keyPressEvent(QKeyEvent *event) {

	this->currentAction->KeyPressEvent(event);

}


void ShGraphicView::wheelEvent(QWheelEvent *event) {


}

void ShGraphicView::mouseReleaseEvent(QMouseEvent *event) {


}


ActionType ShGraphicView::ChangeCurrentAction(ActionType actionType) {
	qDebug("ShGraphicView->ChangeCurrentAction");

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

	if ((drawType& DrawType::DrawCaptureImage) == DrawType::DrawCaptureImage)
		this->update(DrawType::DrawCaptureImage);



	this->currentAction = ShCreatorActionFactory::Create(actionType, this);

	return this->currentAction->GetType();


}


void ShGraphicView::CaptureImage() {

	this->captureImage = this->grabFramebuffer();
}

#include "Singleton Pattern\ShWidgetManager.h"
void ShGraphicView::focusInEvent(QFocusEvent *event) {

	ShWidgetManager *manager = ShWidgetManager::GetInstance();

	manager->SetActivatedWidget(this);
}
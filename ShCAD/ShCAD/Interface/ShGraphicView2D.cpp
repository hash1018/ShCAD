
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


#include "ShGraphicView2D.h"
#include "ShCADWidget.h"
#include "FactoryMethod\ShCreatorActionFactory.h"
#include "ActionHandler\ShActionHandler.h"
ShGraphicView2D::ShGraphicView2D(QWidget *parent)
	:ShGraphicView(parent) {

	this->currentAction = ShCreatorActionFactory::Create(ActionType::ActionDefault, this);

}

ShGraphicView2D::~ShGraphicView2D() {

	if (this->currentAction != NULL)
		delete this->currentAction;

}



void ShGraphicView2D::initializeGL() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

#include "Visitor Pattern\ShDrawer.h"
void ShGraphicView2D::paintGL() {

	
	ShDrawer drawer(this->width(), this->height());

	ShComposite::Iterator itr = this->entityTable->First();

	while (!itr.IsLast()) {
	
		itr.Current()->Accept(&drawer);
		itr.Next();
	}
	
}


void ShGraphicView2D::mousePressEvent(QMouseEvent *event) {
	//qDebug("mousePressEvent in ShGraphicView2D");
	

	this->currentAction->MousePressEvent(event);
	

}

void ShGraphicView2D::mouseMoveEvent(QMouseEvent *event) {
	//qDebug("mouseMoveEvent in ShGraphicView2D");

	this->currentAction->MouseMoveEvent(event);
}

void ShGraphicView2D::keyPressEvent(QKeyEvent *event) {

	this->currentAction->KeyPressEvent(event);

}


ActionType ShGraphicView2D::ChangeCurrentAction(ActionType actionType) {

	if (this->currentAction != NULL)
		delete this->currentAction;

	this->currentAction = ShCreatorActionFactory::Create(actionType, this);

	return this->currentAction->GetType();


}
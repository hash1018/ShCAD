
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

#include "ShCommandDock.h"
#include <QResizeEvent>
#include "ShNotifyEvent.h"
#include "Singleton Pattern\ShChangeManager.h"

ShCommandList::ShCommandList(QWidget *parent)
	:QTextEdit(parent) {

	this->setReadOnly(true);
}

ShCommandList::~ShCommandList() {

}


ShCommandEdit::ShCommandEdit(QWidget *parent)
	:QLineEdit(parent), calledKeyPressEventByUpdate(false), headTitle(":: ") {

	this->setText(this->headTitle);
}

ShCommandEdit::~ShCommandEdit() {

}

void ShCommandEdit::keyPressEvent(QKeyEvent *event) {

	if (this->hasFocus() == false)
		this->setFocus();

	if (this->calledKeyPressEventByUpdate == true) {

		if(event->key() == Qt::Key_Left)
			if (this->cursorPosition() == this->headTitle.length())
				return;

		if (this->hasSelectedText() == false) {
			if (event->key() == Qt::Key::Key_Backspace)
				if (this->cursorPosition() == this->headTitle.length())
					return;
		}

		QLineEdit::keyPressEvent(event);

		if (event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key::Key_A) {
			this->setSelection(this->headTitle.length(), this->maxLength());
		}
	}
	else {
	
		ShKeyPressedEvent event2(event);
		dynamic_cast<ShCommandDock*>(this->parent()->parent())->Notify(&event2);
	}

	

}

ShCommandContainer::ShCommandContainer(QWidget *parent)
	:QWidget(parent) {

	this->edit = new ShCommandEdit(this);
	this->list = new ShCommandList(this);
}

ShCommandContainer::~ShCommandContainer() {

}

void ShCommandContainer::resizeEvent(QResizeEvent *event) {

	QWidget::resizeEvent(event);

	this->list->setGeometry(0, 0, event->size().width(), event->size().height() - 25);
	this->edit->setGeometry(0, event->size().height() - 25, event->size().width(), 25);
}

ShCommandDock::ShCommandDock(QWidget *parent)
	:QDockWidget(parent) {

	this->setMinimumHeight(200);

	this->setAllowedAreas(Qt::DockWidgetArea::BottomDockWidgetArea);
	


	this->container = new ShCommandContainer(this);
	this->setWidget(this->container);

	
}

ShCommandDock::~ShCommandDock() {

}

void ShCommandDock::Update(QKeyEvent *event) {

	

	this->container->edit->calledKeyPressEventByUpdate = true;
	this->container->edit->keyPressEvent(event);
	this->container->edit->calledKeyPressEventByUpdate = false;

}

void ShCommandDock::Notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, event);
}

void ShCommandDock::closeEvent(QCloseEvent *event) {

	event->ignore();
	this->hide();
}


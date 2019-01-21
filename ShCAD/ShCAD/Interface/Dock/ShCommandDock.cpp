
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

void ShCommandDock::Update(ShKeyPressedEvent *event) {

	this->container->edit->calledKeyPressEventByUpdate = true;
	this->container->edit->keyPressEvent(event->GetEvent());
	this->container->edit->calledKeyPressEventByUpdate = false;
}

void ShCommandDock::Update(ShUpdateListTextEvent *event) {

	if (event->GetUpdateType() == 
		ShUpdateListTextEvent::editTextWithText) {

		QString currentText = this->container->edit->text() + event->GetText();
		this->container->list->append(currentText);

		this->container->edit->clear();
		this->container->edit->setText(this->container->edit->headTitle);

	}
	else if (event->GetUpdateType() ==
		ShUpdateListTextEvent::editTextAndNewLineHeadTitleWithText) {

		QString currentText = this->container->edit->text();

		this->container->list->append(currentText);

		this->container->list->append(this->container->edit->headTitle + event->GetText());

		this->container->edit->clear();
		this->container->edit->setText(this->container->edit->headTitle);
	}

	else if (event->GetUpdateType() ==
		ShUpdateListTextEvent::TextWithoutAnything) {
	
		this->container->list->append(event->GetText());
	
	}


}

#include "Interface\ShGraphicView.h"
void ShCommandDock::Update(ShActivatedWidgetChangedEvent *event) {

	ShActivatedWidgetChangedEvent *event2 = dynamic_cast<ShActivatedWidgetChangedEvent*>(event);
	ShGraphicView *newWidget = event2->GetNewWidget();
	ShGraphicView *previousWidget = event2->GetPreviousWidget();

	if (previousWidget != 0) {
		//means there are two more widgets and focus changed each other.
		ShGraphicViewData* data = previousWidget->GetData();
		data->SetHeadTitle(this->GetHeadTitle());
		data->SetEdit(this->GetEdit());
		data->SetList(this->GetList());
	}

	ShGraphicViewData *data = newWidget->GetData();

	this->container->edit->headTitle = data->GetHeadTitle();
	this->container->edit->clear();
	this->container->edit->setText(data->GetHeadTitle() + data->GetEdit());
	
	this->container->list->clear();
	this->container->list->append(data->GetList());


}



void ShCommandDock::Notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, event);
}

QString ShCommandDock::GetList() {

	return this->container->list->toPlainText();
}

QString ShCommandDock::GetEdit() {

	QString text = this->container->edit->text();
	QString headTitle = this->container->edit->headTitle;

	return text.section(headTitle, 1);
}

QString ShCommandDock::GetHeadTitle() {

	return this->container->edit->headTitle;
}


void ShCommandDock::closeEvent(QCloseEvent *event) {

	event->ignore();
	this->hide();
}


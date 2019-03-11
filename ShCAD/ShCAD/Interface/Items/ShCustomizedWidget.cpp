
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

#include "ShCustomizedWidget.h"
#include <QResizeEvent>
#include <qpainter.h>


ShButtonWithMenuPopup::ShButton::ShButton(QWidget *parent)
	:QPushButton(parent), hoverMovedIn(false), hoverStayed(false) {


}

ShButtonWithMenuPopup::ShButton::~ShButton() {

}

void ShButtonWithMenuPopup::ShButton::paintEvent(QPaintEvent *event) {

	QPushButton::paintEvent(event);

	if (this->hoverMovedIn == true) {
		QPainter paint(this);
		paint.setPen(QColor(135, 206, 235, 255)); //sky blue
		paint.drawLine(0, 0, this->width(), 0);
		paint.drawLine(0, 0, 0, this->height());
		paint.drawLine(0, this->height()-1, this->width(), this->height()-1);

	}
	if (this->hoverStayed == true) {
	
		QPainter painter(this);
		painter.fillRect(0, 0, this->width(), this->height(), QColor(000, 153, 255, 60));

	}

}

ShButtonWithMenuPopup::ShMenuPopupButton::ShMenuPopupButton(QWidget *parent)
	:QPushButton(parent), hoverMovedIn(false), hoverStayed(false) {


}

ShButtonWithMenuPopup::ShMenuPopupButton::~ShMenuPopupButton() {

}

//void ShButtonWithMenuPopup::ShMenuPopupButton::mouseMoveEvent(QMouseEvent *event) {

//}

void ShButtonWithMenuPopup::ShMenuPopupButton::paintEvent(QPaintEvent *event) {

	QPushButton::paintEvent(event);

	if (this->hoverMovedIn == true) {
		QPainter paint(this);
		paint.setPen(QColor(135, 206, 235, 255)); //sky blue
		paint.drawLine(0, 0, this->width()-1, 0);
		
		paint.drawLine(0, this->height()-1, this->width()-1, this->height() - 1);
		paint.drawLine(this->width()-1, 0, this->width()-1, this->height() - 1);
	}
	if (this->hoverStayed == true) {
		QPainter painter(this);
		painter.fillRect(0, 0, this->width(), this->height(), QColor(000, 153, 255, 60));
	}
	
}



ShButtonWithMenuPopup::ShButtonWithMenuPopup(QWidget *parent)
	:QWidget(parent) {

	this->button = new ShButtonWithMenuPopup::ShButton(this);
	this->button->installEventFilter(this);

	this->button->setStyleSheet("QPushButton {background : transparent}");
	



	this->popupButton = new ShButtonWithMenuPopup::ShMenuPopupButton(this);
	this->popupButton->installEventFilter(this);

	this->popupButton->setStyleSheet(
		"QPushButton {background : transparent}"
		"QPushButton:menu-indicator {subcontrol-position:center; subcontrol-origin: padding}");

	connect(this->button, &QPushButton::pressed, this, &ShButtonWithMenuPopup::ButtonClicked);
	
}

ShButtonWithMenuPopup::~ShButtonWithMenuPopup() {

}

void ShButtonWithMenuPopup::SetIcon(const QIcon &icon) {
	
	this->button->setIcon(icon);
}

void ShButtonWithMenuPopup::SetMenu(QMenu *menu) {

	this->popupButton->setMenu(menu);
}



void ShButtonWithMenuPopup::resizeEvent(QResizeEvent *event) {

	QWidget::resizeEvent(event);


	int width = event->size().width();
	int height = event->size().height();

	this->button->setGeometry(0, 0, width / 10 * 8, height);
	this->popupButton->setGeometry(width / 10 * 8, 0, width / 10 * 2, height);



}


void ShButtonWithMenuPopup::ButtonClicked() {

	emit pressed();
}

void ShButtonWithMenuPopup::leaveEvent(QEvent *event) {

	this->button->hoverMovedIn = false;
	this->popupButton->hoverMovedIn = false;
	this->button->hoverStayed = false;
	this->popupButton->hoverStayed = false;
	this->button->update();
	this->popupButton->update();
}

bool ShButtonWithMenuPopup::eventFilter(QObject *obj, QEvent *event) {

	if ((event->type() == QEvent::HoverEnter || event->type()==QEvent::HoverMove) && (obj == this->button || obj == this->popupButton)) {
		this->button->hoverMovedIn = true;
		this->popupButton->hoverMovedIn = true;

		if (obj == this->button) {
			this->button->hoverStayed = true;
			this->popupButton->hoverStayed = false;
		}
		else {
			this->popupButton->hoverStayed = true;
			this->button->hoverStayed = false;
		}

		this->button->update();
		this->popupButton->update();
		
	}
	else if (event->type() == QEvent::HoverLeave && (obj == this->button || obj == this->popupButton)) {
		this->button->hoverMovedIn = false;
		this->popupButton->hoverMovedIn = false;
		this->button->hoverStayed = false;
		this->popupButton->hoverStayed = false;
		this->button->update();
		this->popupButton->update();
		
	}

	return QWidget::eventFilter(obj, event);
}




//////////////////////////////////////////////////////////////////////

ShButton::ShButton(QWidget *parent)
	:QPushButton(parent),hoverStayed(false) {

	this->setStyleSheet("QPushButton {background : transparent}");
}

ShButton::~ShButton() {


}

void ShButton::enterEvent(QEvent *event) {

	this->hoverStayed = true;
	this->update();

}

void ShButton::leaveEvent(QEvent *event) {

	this->hoverStayed = false;
	this->update();

}

void ShButton::paintEvent(QPaintEvent *event) {

	QPushButton::paintEvent(event);

	if (this->hoverStayed == true) {

		QPainter painter(this);
		painter.setPen(QColor(135, 206, 235, 255));
		painter.drawRect(0, 0, this->width()-1, this->height()-1);
		painter.fillRect(0, 0, this->width(), this->height(), QColor(000, 153, 255, 60));

	}

}
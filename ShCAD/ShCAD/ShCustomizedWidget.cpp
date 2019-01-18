

#include "ShCustomizedWidget.h"
#include <QResizeEvent>
#include <qpainter.h>


ShButtonWithMenuPopup::ShButton::ShButton(QWidget *parent)
	:QPushButton(parent),hoverMovedIn(false) {
	//this->setAttribute(Qt::WA_Hover, true);
}

ShButtonWithMenuPopup::ShButton::~ShButton() {

}

void ShButtonWithMenuPopup::ShButton::paintEvent(QPaintEvent *event) {

	QPushButton::paintEvent(event);

	if (this->hoverMovedIn == true) {
		QPainter paint(this);
		paint.setPen(QColor(135, 206, 235)); //sky blue
		paint.drawLine(0, 0, this->width(), 0);
		paint.drawLine(0, 0, 0, this->height());
		paint.drawLine(0, this->height()-1, this->width(), this->height()-1);
		//paint.drawLine(this->width(), 0, this->width(), this->height()-1);
	}

}

ShButtonWithMenuPopup::ShMenuPopupButton::ShMenuPopupButton(QWidget *parent)
	:QPushButton(parent), hoverMovedIn(false) {

}

ShButtonWithMenuPopup::ShMenuPopupButton::~ShMenuPopupButton() {

}


void ShButtonWithMenuPopup::ShMenuPopupButton::paintEvent(QPaintEvent *event) {

	QPushButton::paintEvent(event);

	if (this->hoverMovedIn == true) {
		QPainter paint(this);
		paint.setPen(QColor(135, 206, 235)); //sky blue
		paint.drawLine(0, 0, this->width()-1, 0);
		//paint.drawLine(0, 0, 0, this->height());
		paint.drawLine(0, this->height()-1, this->width()-1, this->height() - 1);
		paint.drawLine(this->width()-1, 0, this->width()-1, this->height() - 1);
	}
}



ShButtonWithMenuPopup::ShButtonWithMenuPopup(QWidget *parent)
	:QWidget(parent) {

	this->button = new ShButtonWithMenuPopup::ShButton(this);
	this->button->installEventFilter(this);

	this->button->setStyleSheet("QPushButton {background : transparent}"
		"QPushButton:hover {background :lightSkyBlue}"
		"QPushButton:pressed {background : steelBlue}");



	this->popupButton = new ShButtonWithMenuPopup::ShMenuPopupButton(this);
	this->popupButton->installEventFilter(this);

	this->popupButton->setStyleSheet(
		"QPushButton {background : transparent}"
		"QPushButton:hover {background:lightSkyBlue }"
		"QPushButton:pressed {background : steelBlue}"
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


bool ShButtonWithMenuPopup::eventFilter(QObject *obj, QEvent *event) {

	if ((event->type() == QEvent::HoverEnter || event->type()==QEvent::HoverMove) && (obj == this->button || obj == this->popupButton)) {
		this->button->hoverMovedIn = true;
		this->popupButton->hoverMovedIn = true;
		this->button->update();
		this->popupButton->update();
		
	}
	else if (event->type() == QEvent::HoverLeave && (obj == this->button || obj == this->popupButton)) {
		this->button->hoverMovedIn = false;
		this->popupButton->hoverMovedIn = false;
		this->button->update();
		this->popupButton->update();
		
	}

	return QWidget::eventFilter(obj, event);
}
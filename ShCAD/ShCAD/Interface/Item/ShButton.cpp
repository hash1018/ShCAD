

#include "ShButton.h"
#include <QResizeEvent>
#include <qpainter.h>
#include <qmenu.h>

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
		paint.drawLine(0, this->height() - 1, this->width(), this->height() - 1);

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


void ShButtonWithMenuPopup::ShMenuPopupButton::paintEvent(QPaintEvent *event) {

	QPushButton::paintEvent(event);

	if (this->hoverMovedIn == true) {
		QPainter paint(this);
		paint.setPen(QColor(135, 206, 235, 255)); //sky blue
		paint.drawLine(0, 0, this->width() - 1, 0);

		paint.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
		paint.drawLine(this->width() - 1, 0, this->width() - 1, this->height() - 1);
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

	connect(this->button, &QPushButton::pressed, this, &ShButtonWithMenuPopup::buttonClicked);

}

ShButtonWithMenuPopup::~ShButtonWithMenuPopup() {


}


void ShButtonWithMenuPopup::setIcon(const QIcon &icon) {

	this->button->setIcon(icon);
}


void ShButtonWithMenuPopup::setMenu(QMenu *menu) {

	this->popupButton->setMenu(menu);
}



void ShButtonWithMenuPopup::resizeEvent(QResizeEvent *event) {

	QWidget::resizeEvent(event);


	int width = event->size().width();
	int height = event->size().height();

	this->button->setGeometry(0, 0, width / 10 * 8, height);
	this->popupButton->setGeometry(width / 10 * 8, 0, width / 10 * 2, height);



}


void ShButtonWithMenuPopup::buttonClicked() {

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

	if ((event->type() == QEvent::HoverEnter || event->type() == QEvent::HoverMove) && (obj == this->button || obj == this->popupButton)) {
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
	:QPushButton(parent), hoverStayed(false) {

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

	if (this->isEnabled() == false)
		return;

	if (this->hoverStayed == true) {

		QPainter painter(this);
		painter.setPen(QColor(135, 206, 235, 255));
		painter.drawRect(0, 0, this->width() - 1, this->height() - 1);
		painter.fillRect(0, 0, this->width(), this->height(), QColor(000, 153, 255, 60));

	}

}

/////////////////////////////////////////////////////////////////////


ShButtonWithText::ShButton::ShButton(QWidget *parent)
	:QPushButton(parent), hoverStayed(false), direction(East) {


}

ShButtonWithText::ShButton::~ShButton() {

}

void ShButtonWithText::ShButton::paintEvent(QPaintEvent *event) {

	QPushButton::paintEvent(event);

	if (this->hoverStayed == true) {

		QPainter painter(this);
		painter.setPen(QColor(135, 206, 235, 255)); //sky blue

		if (this->direction == East) {

			painter.drawLine(0, 0, this->width(), 0);
			painter.drawLine(0, 0, 0, this->height());
			painter.drawLine(0, this->height() - 1, this->width(), this->height() - 1);
		}
		else if (this->direction == West) {
		
			painter.drawLine(0, 0, this->width() - 1, 0);
			painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
			painter.drawLine(this->width() - 1, 0, this->width() - 1, this->height() - 1);
		}
		else if (this->direction == South) {
		
			painter.drawLine(0, 0, this->width() - 1, 0);
			painter.drawLine(0, 0, 0, this->height());
			painter.drawLine(this->width() - 1, 0, this->width() - 1, this->height() - 1);
		}
		else if (this->direction == North) {
		
			painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
			painter.drawLine(0, this->height() - 1, 0, 0);
			painter.drawLine(this->width() - 1, this->height() - 1, this->width() - 1, 0);
		}


		painter.fillRect(0, 0, this->width(), this->height(), QColor(000, 153, 255, 60));

	}

}

ShButtonWithText::ShTextButton::ShTextButton(QWidget *parent)
	:QPushButton(parent), hoverStayed(false), direction(East) {


}

ShButtonWithText::ShTextButton::~ShTextButton() {

}


void ShButtonWithText::ShTextButton::paintEvent(QPaintEvent *event) {

	QPushButton::paintEvent(event);
	
	if (this->hoverStayed == true) {
		QPainter painter(this);

		painter.setPen(QColor(135, 206, 235, 255)); //sky blue

		if (this->direction == East) {
			
			painter.drawLine(0, 0, this->width() - 1, 0);
			painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
			painter.drawLine(this->width() - 1, 0, this->width() - 1, this->height() - 1);
		}
		else if (this->direction == West) {
		
			painter.drawLine(0, 0, this->width(), 0);
			painter.drawLine(0, 0, 0, this->height());
			painter.drawLine(0, this->height() - 1, this->width(), this->height() - 1);
		}
		else if (this->direction == South) {

			painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
			painter.drawLine(0, this->height() - 1, 0, 0);
			painter.drawLine(this->width() - 1, this->height() - 1, this->width() - 1, 0);
		}
		else if (this->direction == North) {

			painter.drawLine(0, 0, this->width() - 1, 0);
			painter.drawLine(0, 0, 0, this->height());
			painter.drawLine(this->width() - 1, 0, this->width() - 1, this->height() - 1);
		}

		painter.fillRect(0, 0, this->width(), this->height(), QColor(000, 153, 255, 60));
	}

}


ShButtonWithText::ShButtonWithText(QWidget *parent)
	:QWidget(parent), direction(East),rate(6) {

	this->button = new ShButtonWithText::ShButton(this);
	this->button->installEventFilter(this);

	this->button->setStyleSheet("QPushButton {background : transparent}");

	this->textButton = new ShButtonWithText::ShTextButton(this);
	this->textButton->installEventFilter(this);

	connect(this->button, &QPushButton::pressed, this, &ShButtonWithText::buttonClicked);
	connect(this->textButton, &QPushButton::pressed, this, &ShButtonWithText::buttonClicked);

}

ShButtonWithText::~ShButtonWithText() {


}


void ShButtonWithText::setIcon(const QIcon &icon) {

	this->button->setIcon(icon);
}


void ShButtonWithText::setText(const QString &text) {

	this->textButton->setText(text);
}

void ShButtonWithText::setTextDirection(const TextDirection &direction) {

	this->direction = direction;
	this->button->direction = direction;
	this->textButton->direction = direction;
	this->button->update();
	this->textButton->update();
	this->updateGeometry();
}

void ShButtonWithText::setIconSize(const QSize &size) {

	this->button->setIconSize(size);
}

void ShButtonWithText::setIconSizeRate(int rate) {

	this->rate = rate;
	this->updateGeometry();
}

void ShButtonWithText::resizeEvent(QResizeEvent *event) {

	QWidget::resizeEvent(event);


	int width = event->size().width();
	int height = event->size().height();

	if (this->direction == West) {
	
		this->button->setGeometry(width / 10 * 6, 0, width / 10 * 4, height);
		this->textButton->setGeometry(0, 0, width / 10 * 6, height);
		this->textButton->setStyleSheet("QPushButton {background : transparent}"
			"QPushButton {text-align : right}");
		
	}
	else if (this->direction == East) {
		this->button->setGeometry(0, 0, width / 10 * 4, height);
		this->textButton->setGeometry(width / 10 * 4, 0, width / 10 * 6, height);	
		this->textButton->setStyleSheet("QPushButton {background : transparent}"
			"QPushButton {text-align : left}");
	}
	else if (this->direction == South) {
		this->button->setGeometry(0, 0, width, height / 10 * 6);
		this->textButton->setGeometry(0, height / 10 * 6, width, height / 10 * 4);
		this->textButton->setStyleSheet("QPushButton {background : transparent}"
			"QPushButton {text-align : top}");
	}
	else if (this->direction == North) {
		this->button->setGeometry(0, height / 10 * 6, width, height / 10 * 4);
		this->textButton->setGeometry(0, 0, width, height / 10 * 6);
		this->textButton->setStyleSheet("QPushButton {background : transparent}"
			"QPushButton {text-align : bottom}");

	}

	

}


void ShButtonWithText::buttonClicked() {

	emit pressed();
}

void ShButtonWithText::leaveEvent(QEvent *event) {

	this->button->hoverStayed = false;
	this->textButton->hoverStayed = false;
	this->button->update();
	this->textButton->update();
	
}


bool ShButtonWithText::eventFilter(QObject *obj, QEvent *event) {

	if ((event->type() == QEvent::HoverEnter || event->type() == QEvent::HoverMove) && (obj == this->button || obj == this->textButton)) {
		
		this->textButton->hoverStayed = true;
		this->button->hoverStayed = true;

		this->button->update();
		this->textButton->update();	

	}
	else if (event->type() == QEvent::HoverLeave && (obj == this->button || obj == this->textButton)) {
		
		this->button->hoverStayed = false;
		this->textButton->hoverStayed = false;
		this->button->update();
		this->textButton->update();
		
	}

	return QWidget::eventFilter(obj, event);
}


///////////////////////////////////////////////////////////////////////////



ShButtonWithMenuPopupWithText::ShButton::ShButton(QWidget *parent)
	:QPushButton(parent), hoverMovedIn(false), hoverStayed(false), direction(East) {


}

ShButtonWithMenuPopupWithText::ShButton::~ShButton() {

}

void ShButtonWithMenuPopupWithText::ShButton::paintEvent(QPaintEvent *event) {

	QPushButton::paintEvent(event);

	if (this->hoverMovedIn == true) {

		QPainter painter(this);
		painter.setPen(QColor(135, 206, 235, 255)); //sky blue

		if (this->direction == East) {

			painter.drawLine(0, 0, this->width(), 0);
			painter.drawLine(0, 0, 0, this->height());
			painter.drawLine(0, this->height() - 1, this->width(), this->height() - 1);
		}
		else if (this->direction == West) {

			painter.drawLine(0, 0, this->width() - 1, 0);
			painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
			painter.drawLine(this->width() - 1, 0, this->width() - 1, this->height() - 1);
		}
		else if (this->direction == South) {

			painter.drawLine(0, 0, this->width() - 1, 0);
			painter.drawLine(0, 0, 0, this->height());
			painter.drawLine(this->width() - 1, 0, this->width() - 1, this->height() - 1);
		}
		else if (this->direction == North) {

			painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
			painter.drawLine(0, this->height() - 1, 0, 0);
			painter.drawLine(this->width() - 1, this->height() - 1, this->width() - 1, 0);
		}

	}
	if (this->hoverStayed == true) {

		QPainter painter(this);
		painter.fillRect(0, 0, this->width(), this->height(), QColor(000, 153, 255, 60));

	}

}

ShButtonWithMenuPopupWithText::ShMenuPopupButton::ShMenuPopupButton(QWidget *parent)
	:QPushButton(parent), hoverMovedIn(false), hoverStayed(false), direction(East) {


}

ShButtonWithMenuPopupWithText::ShMenuPopupButton::~ShMenuPopupButton() {

}


void ShButtonWithMenuPopupWithText::ShMenuPopupButton::paintEvent(QPaintEvent *event) {

	QPushButton::paintEvent(event);
	QPainter painter(this);

	if (this->hoverMovedIn == true) {
		
		painter.setPen(QColor(135, 206, 235, 255)); //sky blue

		if (this->direction == East) {

			painter.drawLine(0, 0, this->width() - 1, 0);
			painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
			painter.drawLine(this->width() - 1, 0, this->width() - 1, this->height() - 1);
		}
		else if (this->direction == West) {

			painter.drawLine(0, 0, this->width(), 0);
			painter.drawLine(0, 0, 0, this->height());
			painter.drawLine(0, this->height() - 1, this->width(), this->height() - 1);
		}
		else if (this->direction == South) {

			painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
			painter.drawLine(0, this->height() - 1, 0, 0);
			painter.drawLine(this->width() - 1, this->height() - 1, this->width() - 1, 0);

		}
		else if (this->direction == North) {

			painter.drawLine(0, 0, this->width() - 1, 0);
			painter.drawLine(0, 0, 0, this->height());
			painter.drawLine(this->width() - 1, 0, this->width() - 1, this->height() - 1);
		}
	}

	if (this->hoverStayed == true)
		painter.fillRect(0, 0, this->width(), this->height(), QColor(000, 153, 255, 60));
	

	QPainterPath path;

	if (this->direction == East) {

		path.moveTo(this->width() - 10, this->height() / 2 - 2);
		path.lineTo(this->width() - 2, this->height() / 2 - 2);
		path.lineTo(this->width() - 6, this->height() / 2 + 2);
		path.lineTo(this->width() - 10, this->height() / 2 - 2);
	}
	else if (this->direction == West) {

		
	}
	else if (this->direction == South) {
		
		path.moveTo(this->width() / 2 - 4, this->height() - 10);
		path.lineTo(this->width() / 2 + 4, this->height() - 10);
		path.lineTo(this->width() / 2, this->height() - 6);
		path.lineTo(this->width() / 2 - 4, this->height() - 10);
	}
	else if (this->direction == North) {

		
	}

	painter.fillPath(path, QBrush(QColor(0, 0, 0)));
}


ShButtonWithMenuPopupWithText::ShButtonWithMenuPopupWithText(QWidget *parent)
	:QWidget(parent), direction(East) {

	this->button = new ShButtonWithMenuPopupWithText::ShButton(this);
	this->button->installEventFilter(this);

	this->button->setStyleSheet("QPushButton {background : transparent}");

	this->popupButton = new ShButtonWithMenuPopupWithText::ShMenuPopupButton(this);
	this->popupButton->installEventFilter(this);

	connect(this->button, &QPushButton::pressed, this, &ShButtonWithMenuPopupWithText::buttonClicked);

}

ShButtonWithMenuPopupWithText::~ShButtonWithMenuPopupWithText() {


}


void ShButtonWithMenuPopupWithText::setIcon(const QIcon &icon) {

	this->button->setIcon(icon);
}


void ShButtonWithMenuPopupWithText::setMenu(QMenu *menu) {

	this->popupButton->setMenu(menu);
}

void ShButtonWithMenuPopupWithText::setTextDirection(const TextDirection &direction) {

	this->direction = direction;
	this->button->direction = direction;
	this->popupButton->direction = direction;
	this->button->update();
	this->popupButton->update();
	this->updateGeometry();
}

void ShButtonWithMenuPopupWithText::setText(const QString &text) {

	this->popupButton->setText(text);
}

void ShButtonWithMenuPopupWithText::setIconSize(const QSize &size) {

	this->button->setIconSize(size);
}

void ShButtonWithMenuPopupWithText::resizeEvent(QResizeEvent *event) {

	QWidget::resizeEvent(event);


	int width = event->size().width();
	int height = event->size().height();

	if (this->direction == West) {

		this->button->setGeometry(width / 10 * 6, 0, width / 10 * 4, height);
		this->popupButton->setGeometry(0, 0, width / 10 * 6, height);
		this->popupButton->setStyleSheet("QPushButton {background : transparent}"
			"QPushButton {text-align : right}"
			"QPushButton:menu-indicator {width:0px;}");

	}
	else if (this->direction == East) {
		this->button->setGeometry(0, 0, width / 10 * 4, height);
		this->popupButton->setGeometry(width / 10 * 4, 0, width / 10 * 6, height);
		this->popupButton->setStyleSheet("QPushButton {background : transparent}"
			"QPushButton {text-align : left}"
			"QPushButton:menu-indicator {width:0px;}");

		
	}
	else if (this->direction == South) {
		this->button->setGeometry(0, 0, width, height / 10 * 6);
		this->popupButton->setGeometry(0, height / 10 * 6, width, height / 10 * 4);
		this->popupButton->setStyleSheet("QPushButton {background : transparent}"
			"QPushButton {text-align : top center}"
			"QPushButton:menu-indicator {width:0px;}");
	}
	else if (this->direction == North) {
		this->button->setGeometry(0, height / 10 * 6, width, height / 10 * 4);
		this->popupButton->setGeometry(0, 0, width, height / 10 * 6);
		this->popupButton->setStyleSheet("QPushButton {background : transparent}"
			"QPushButton {text-align : bottom}"
			"QPushButton:menu-indicator {width:0px;}");

	}



}


void ShButtonWithMenuPopupWithText::buttonClicked() {

	emit pressed();


}

void ShButtonWithMenuPopupWithText::leaveEvent(QEvent *event) {

	this->button->hoverMovedIn = false;
	this->popupButton->hoverMovedIn = false;
	this->button->hoverStayed = false;
	this->popupButton->hoverStayed = false;
	this->button->update();
	this->popupButton->update();
}

bool ShButtonWithMenuPopupWithText::eventFilter(QObject *obj, QEvent *event) {

	if ((event->type() == QEvent::HoverEnter || event->type() == QEvent::HoverMove) && (obj == this->button || obj == this->popupButton)) {
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




///////////////////////////////////////////////////////////////////////////



ShStateButton::ShStateButton(const QString &text, QWidget *parent)
	:QPushButton(text, parent), state(false) {

	connect(this, &QPushButton::pressed, this, &ShStateButton::buttonPressed);
}

ShStateButton::ShStateButton(QWidget *parent)
	: QPushButton(parent), state(false) {

	connect(this, &QPushButton::pressed, this, &ShStateButton::buttonPressed);
}

ShStateButton::~ShStateButton() {

}

void ShStateButton::setState(bool on) {

	this->state = on;
	this->update();
}

void ShStateButton::buttonPressed() {

	if (this->state == true)
		this->state = false;
	else
		this->state = true;

	this->update();

	emit pressed();

}

void ShStateButton::paintEvent(QPaintEvent *event) {

	QPushButton::paintEvent(event);

	if (state == false)
		return;

	QPainter painter(this);
	painter.fillRect(0, 0, this->width(), this->height(), QColor(000, 153, 255, 125));
}


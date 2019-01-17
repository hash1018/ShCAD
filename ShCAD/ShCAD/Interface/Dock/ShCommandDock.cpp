
#include "ShCommandDock.h"
#include <QResizeEvent>

ShCommandList::ShCommandList(QWidget *parent)
	:QTextEdit(parent) {

	this->setReadOnly(true);
}

ShCommandList::~ShCommandList() {

}


ShCommandEdit::ShCommandEdit(QWidget *parent)
	:QLineEdit(parent) {

}

ShCommandEdit::~ShCommandEdit() {

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


void ShCommandDock::closeEvent(QCloseEvent *event) {

	event->ignore();
	this->hide();
}
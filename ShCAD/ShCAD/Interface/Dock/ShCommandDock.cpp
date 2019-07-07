
#include "ShCommandDock.h"
#include <QResizeEvent>
#include <qaction.h>

ShCommandList::ShCommandList(QWidget *parent)
	:QTextEdit(parent) {

	this->setReadOnly(true);
}

ShCommandList::~ShCommandList() {

}

//////////////////////////////////////////////////

ShCommandEdit::ShCommandEdit(QWidget *parent)
	:QLineEdit(parent) {


}

ShCommandEdit::~ShCommandEdit() {

}


/////////////////////////////////////////////////////

ShCommandContainer::ShCommandContainer(QWidget *parent)
	:QWidget(parent) {

	this->edit = new ShCommandEdit(this);
	this->list = new ShCommandList(this);

	this->setMinimumHeight(40);

}

ShCommandContainer::~ShCommandContainer() {

}


void ShCommandContainer::resizeEvent(QResizeEvent *event) {


	QWidget::resizeEvent(event);

	this->list->setGeometry(0, 0, event->size().width(), event->size().height() - 25);
	this->edit->setGeometry(0, event->size().height() - 25, event->size().width(), 25);
}

QSize ShCommandContainer::sizeHint() const {

	return QSize(0, 300);
}

/////////////////////////////////////////////////////

ShCommandDock::ShCommandDock(QWidget *parent)
	:QDockWidget(parent), menuActionChecked(true) {

	this->setAllowedAreas(Qt::DockWidgetArea::BottomDockWidgetArea);


	this->container = new ShCommandContainer(this);
	this->setWidget(this->container);

	this->menuAction = new QAction("CommandDock");
	this->menuAction->setCheckable(true);
	this->menuAction->setChecked(true);

	connect(this->menuAction, &QAction::triggered, this, &ShCommandDock::menuActionClicked);

}

ShCommandDock::~ShCommandDock() {

	if (this->menuAction != 0)
		delete this->menuAction;
}

void ShCommandDock::closeEvent(QCloseEvent *event) {

	event->ignore();
	this->menuActionChecked = false;
	this->hide();
	this->menuAction->setChecked(false);

}

void ShCommandDock::menuActionClicked() {

	if (this->menuActionChecked == false) {

		this->menuActionChecked = true;
		this->show();
		this->menuAction->setChecked(true);
	}
	else {

		this->menuActionChecked = false;
		this->hide();
		this->menuAction->setChecked(false);
	}
}

void ShCommandDock::activate() {

	if (this->menuActionChecked == true)
		this->show();
}

void ShCommandDock::deactivate() {

	if (this->menuActionChecked == true)
		this->hide();
}
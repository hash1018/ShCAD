
#include "ShCommandDock.h"
#include <QResizeEvent>
#include <qaction.h>
#include "Manager\ShLanguageManager.h"
#include "Event\ShNotifyEvent.h"
#include "Manager\ShChangeManager.h"
#include "Event\ShCommandDockEventFilter.h"

ShCommandList::ShCommandList(QWidget *parent)
	:QTextEdit(parent) {

	this->setReadOnly(true);
}

ShCommandList::~ShCommandList() {

}

//////////////////////////////////////////////////

ShCommandEdit::ShCommandEdit(QWidget *parent)
	:QLineEdit(parent),calledKeyPressEventByNotify(false) {

	this->headTitle = shGetLanValue_command("Command/Command");

	this->setText(this->headTitle);
}

ShCommandEdit::~ShCommandEdit() {

}

void ShCommandEdit::keyPressEvent(QKeyEvent *event) {

	if (this->hasFocus() == false)
		this->setFocus();

	if (this->calledKeyPressEventByNotify == true) {

		if (event->key() == Qt::Key_Left)
			if (this->cursorPosition() == this->headTitle.length())
				return;

		if (this->hasSelectedText() == false) {
			if (event->key() == Qt::Key::Key_Backspace)
				if (this->cursorPosition() == this->headTitle.length())
					return;
		}

		QLineEdit::keyPressEvent(event);

		if (event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key::Key_A)
			this->setSelection(this->headTitle.length(), this->maxLength());
	
	}
	else {
		ShKeyPressedEvent notifyEvent(event);
		dynamic_cast<ShCommandDock*>(this->parent()->parent())->notify(&notifyEvent);
	
	}

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
	this->setWindowTitle(shGetLanValue_ui("Command/Command"));

	this->container = new ShCommandContainer(this);
	this->setWidget(this->container);
	this->menuAction = new QAction(shGetLanValue_ui("Command/CommandDock"));
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

void ShCommandDock::update(ShNotifyEvent *event) {

	ShCommandDockEventFilter filter(this, event);
	filter.update();

}

void ShCommandDock::notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::getInstance();

	manager->notify(this, event);
}

void ShCommandDock::setCalledKeyPressedEventByNotify(bool on) {

	this->container->edit->calledKeyPressEventByNotify = on;
}

void ShCommandDock::keyPressEvent(QKeyEvent *event) {

	this->container->edit->keyPressEvent(event);
}

void ShCommandDock::appendTextToList(const QString &text) {

	this->container->list->append(text);
}

void ShCommandDock::clearEditText() {

	this->container->edit->clear();
	this->container->edit->setText(this->container->edit->headTitle);
}

void ShCommandDock::setHeadTitle(const QString &headTitle) {

	QString text = this->getEditText();
	this->container->edit->headTitle = headTitle;
	this->container->edit->clear();
	this->container->edit->setText(headTitle + text);
}

void ShCommandDock::setListText(const QString &text) {

	this->container->list->clear();
	this->container->list->append(text);
}

void ShCommandDock::setEditText(const QString &text) {

	this->container->edit->clear();
	this->container->edit->setText(this->getHeadTitle() + text);
}


QString ShCommandDock::getEditText() {

	QString text = this->container->edit->text();
	QString headTitle = this->container->edit->headTitle;

	return text.section(headTitle, 1);
}
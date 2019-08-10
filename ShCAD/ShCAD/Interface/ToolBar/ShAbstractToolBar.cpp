

#include "ShAbstractToolBar.h"

ShAbstractToolBar::ShAbstractToolBar(const QString &title, ShChain *chain, QWidget *parent)
	:QToolBar(title, parent), ShChain(chain), menuActionChecked(false) {

	this->menuAction = new QAction(title);
	this->menuAction->setCheckable(true);
	this->menuAction->setChecked(this->menuActionChecked);

	connect(this->menuAction, &QAction::triggered, this, &ShAbstractToolBar::menuActionClicked);
}

ShAbstractToolBar::~ShAbstractToolBar() {

	if (this->menuAction != nullptr)
		delete this->menuAction;
}


void ShAbstractToolBar::menuActionClicked() {

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

void ShAbstractToolBar::activate() {

	if (this->menuActionChecked == true)
		this->show();
}

void ShAbstractToolBar::deactivate() {

	this->hide();
}

void ShAbstractToolBar::setMenuActionChecked(bool checked) {

	this->menuActionChecked = checked;
	this->menuAction->setChecked(checked);
}
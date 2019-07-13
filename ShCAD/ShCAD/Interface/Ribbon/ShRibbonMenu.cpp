
#include "ShRibbonMenu.h"
#include "ShHomeTab.h"
#include "Manager\ShLanguageManager.h"

ShRibbonMenu::ShRibbonMenu(int height, QWidget *parent)
	:ShRibbon(height, parent), menuActionChecked(true) {

	this->setWindowTitle(shGetLanValue_ui("Ribbon/RibbonMenu"));

	this->homeTab = new ShHomeTab(shGetLanValue_ui("Home/Home"), this);
	this->addTab(this->homeTab);

	this->insertTab = new ShInsertTab(shGetLanValue_ui("Insert/Insert"), this);
	this->addTab(this->insertTab);

	this->annotateTab = new ShAnnotateTab(shGetLanValue_ui("Annotate/Annotate"), this);
	this->addTab(this->annotateTab);

	this->parametricTab = new ShParametricTab(shGetLanValue_ui("Parametric/Parametric"), this);
	this->addTab(this->parametricTab);

	this->viewTab = new ShViewTab(shGetLanValue_ui("View/View"), this);
	this->addTab(this->viewTab);

	this->manageTab = new ShManageTab(shGetLanValue_ui("Manage/Manage"), this);
	this->addTab(this->manageTab);

	this->menuAction = new QAction(shGetLanValue_ui("Ribbon/RibbonMenu"));
	this->menuAction->setCheckable(true);
	this->menuAction->setChecked(true);

	connect(this->menuAction, &QAction::triggered, this, &ShRibbonMenu::menuActionClicked);

}

ShRibbonMenu::~ShRibbonMenu() {

	if (this->menuAction != nullptr)
		delete this->menuAction;

}

void ShRibbonMenu::menuActionClicked() {

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

void ShRibbonMenu::activate() {

	if (this->menuActionChecked == true)
		this->show();
}

void ShRibbonMenu::deactivate() {

	if (this->menuActionChecked == true)
		this->hide();
}



////////////////////////////////////////////////////////////////////////////////////

ShInsertTab::ShInsertTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

}

ShInsertTab::~ShInsertTab() {

}

/////////////////////////////////////////////////////////////////////////////////////////

ShAnnotateTab::ShAnnotateTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

}

ShAnnotateTab::~ShAnnotateTab() {

}


//////////////////////////////////////////////////////////////////////////////////////////

ShParametricTab::ShParametricTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

}

ShParametricTab::~ShParametricTab() {

}


///////////////////////////////////////////////////////////////////////////////////////////

ShViewTab::ShViewTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

}

ShViewTab::~ShViewTab() {

}

///////////////////////////////////////////////////////////////////////////////////////////

ShManageTab::ShManageTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

}

ShManageTab::~ShManageTab() {

}

/////////////////////////////////////////////////////////////////////////////////////////////

#include "ShRibbonMenu.h"
#include "ShHomeTab.h"
#include "Manager\ShLanguageManager.h"
#include <qsettings.h>

ShRibbonMenu::ShRibbonMenu(int height, ShChain *chain, QWidget *parent)
	:ShRibbon(chain, height, parent), menuActionChecked(true) {

	this->setWindowTitle(shGetLanValue_ui("Ribbon/RibbonMenu"));
	this->setObjectName("RibbonMenu");

	this->homeTab = new ShHomeTab(this, shGetLanValue_ui("Home/Home"), this);
	this->addTab(this->homeTab);

	this->insertTab = new ShInsertTab(shGetLanValue_ui("Insert/Insert"), this, this);
	this->addTab(this->insertTab);

	this->annotateTab = new ShAnnotateTab(shGetLanValue_ui("Annotate/Annotate"), this, this);
	this->addTab(this->annotateTab);

	this->parametricTab = new ShParametricTab(shGetLanValue_ui("Parametric/Parametric"), this, this);
	this->addTab(this->parametricTab);

	this->viewTab = new ShViewTab(shGetLanValue_ui("View/View"), this, this);
	this->addTab(this->viewTab);

	this->manageTab = new ShManageTab(shGetLanValue_ui("Manage/Manage"), this, this);
	this->addTab(this->manageTab);

	this->menuAction = new QAction(shGetLanValue_ui("Ribbon/RibbonMenu"));
	this->menuAction->setCheckable(true);
	this->menuAction->setChecked(this->menuActionChecked);

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

	this->hide();
}

void ShRibbonMenu::update(ShNotifyEvent *event) {

	this->homeTab->update(event);
}

void ShRibbonMenu::readSettings() {

	QSettings settings("SeungHo Ha", "ShCAD");

	settings.beginGroup("Ribbon");

	bool checked = settings.value("isRibbonShown").toBool();

	this->menuActionChecked = checked;
	this->menuAction->setChecked(checked);
	
	settings.endGroup();
}

void ShRibbonMenu::writeSettings() {

	QSettings settings("SeungHo Ha", "ShCAD");

	settings.beginGroup("Ribbon");

	settings.setValue("isRibbonShown", this->menuActionChecked);

	settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////////

ShInsertTab::ShInsertTab(const QString &title, ShChain *chain, QWidget *parent)
	:ShRibbonTab(title, chain, parent) {

}

ShInsertTab::~ShInsertTab() {

}

/////////////////////////////////////////////////////////////////////////////////////////

ShAnnotateTab::ShAnnotateTab(const QString &title, ShChain *chain, QWidget *parent)
	:ShRibbonTab(title, chain, parent) {

}

ShAnnotateTab::~ShAnnotateTab() {

}


//////////////////////////////////////////////////////////////////////////////////////////

ShParametricTab::ShParametricTab(const QString &title, ShChain *chain, QWidget *parent)
	:ShRibbonTab(title, chain, parent) {

}

ShParametricTab::~ShParametricTab() {

}


///////////////////////////////////////////////////////////////////////////////////////////

ShViewTab::ShViewTab(const QString &title, ShChain *chain, QWidget *parent)
	:ShRibbonTab(title, chain, parent) {

}

ShViewTab::~ShViewTab() {

}

///////////////////////////////////////////////////////////////////////////////////////////

ShManageTab::ShManageTab(const QString &title, ShChain *chain, QWidget *parent)
	:ShRibbonTab(title, chain, parent) {

}

ShManageTab::~ShManageTab() {

}

/////////////////////////////////////////////////////////////////////////////////////////////
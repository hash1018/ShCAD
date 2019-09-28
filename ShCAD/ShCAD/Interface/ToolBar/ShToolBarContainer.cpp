

#include "ShToolBarContainer.h"
#include "Interface\ShCAD.h"
#include <qmenu.h>
#include "ShDrawToolBar.h"
#include "ShLayerToolBar.h"
#include "ShPropertyToolBar.h"
#include "ShModifyToolBar.h"
#include "ShObjectSnapToolBar.h"
#include "ShQuickAccessToolBar.h"
#include "Manager\ShLanguageManager.h"
#include <qsettings.h>
#include "ShDimensionToolBar.h"


ShToolBarContainer::ShToolBarContainer(ShCAD *parent, ShChain *chain)
	:parent(parent), ShChain(chain) {

	this->toolBarMenu = new QMenu(shGetLanValue_ui("ToolBar/ToolBars"));

	this->createToolBars();

	QList<ShAbstractToolBar*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr) {

		this->parent->addToolBar(Qt::ToolBarArea::TopToolBarArea, (*itr));
		this->toolBarMenu->addAction((*itr)->getMenuAction());
		(*itr)->hide();
	}


}

ShToolBarContainer::~ShToolBarContainer() {

	if (this->toolBarMenu != nullptr)
		delete this->toolBarMenu;

}

void ShToolBarContainer::createToolBars() {

	this->quickAccessToolBar = new ShQuickAccessToolBar(shGetLanValue_ui("Quick Access/Quick Access"), this->parent, this->parent);
	this->list.append(this->quickAccessToolBar);

	this->drawToolBar = new ShDrawToolBar(shGetLanValue_ui("Draw/Draw"), this->parent, this->parent);
	this->list.append(this->drawToolBar);

	this->propertyToolBar = new ShPropertyToolBar(shGetLanValue_ui("Property/Property"), this->parent, this->parent);
	this->list.append(this->propertyToolBar);

	this->modifyToolBar = new ShModifyToolBar(shGetLanValue_ui("Modify/Modify"), this->parent, this->parent);
	this->list.append(this->modifyToolBar);

	this->layerToolBar = new ShLayerToolBar(shGetLanValue_ui("Layer/Layer"), this->parent, this->parent);
	this->list.append(this->layerToolBar);

	this->objectSnapToolBar = new ShObjectSnapToolBar(shGetLanValue_ui("ObjectSnap/ObjectSnap"), this->parent, this->parent);
	this->list.append(this->objectSnapToolBar);

	this->dimensionToolBar = new ShDimensionToolBar(shGetLanValue_ui("Dim/Dim"), this->parent, this->parent);
	this->list.append(this->dimensionToolBar);

}

void ShToolBarContainer::activate() {

	QList<ShAbstractToolBar*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		(*itr)->activate();

}

void ShToolBarContainer::deactivate() {

	QList<ShAbstractToolBar*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		(*itr)->deactivate();

}

void ShToolBarContainer::update(ShNotifyEvent *event) {

	this->quickAccessToolBar->update(event);
	this->propertyToolBar->update(event);
	this->layerToolBar->update(event);
}

void ShToolBarContainer::readSettings() {

	QSettings settings("ShCAD", "ShCAD Apps");

	settings.beginGroup("ToolBars");

	this->quickAccessToolBar->setMenuActionChecked(settings.value("isQuickAccessShown").toBool());
	this->drawToolBar->setMenuActionChecked(settings.value("isDrawShown").toBool());
	this->propertyToolBar->setMenuActionChecked(settings.value("isPropertyShown").toBool());
	this->modifyToolBar->setMenuActionChecked(settings.value("isModifyShown").toBool());
	this->layerToolBar->setMenuActionChecked(settings.value("isLayerShown").toBool());
	this->objectSnapToolBar->setMenuActionChecked(settings.value("isObjectSnapShown").toBool());
	this->dimensionToolBar->setMenuActionChecked(settings.value("isDimensionShown").toBool());
	
	settings.endGroup();
}

void ShToolBarContainer::writeSettings() {

	QSettings settings("ShCAD", "ShCAD Apps");

	settings.beginGroup("ToolBars");

	settings.setValue("isQuickAccessShown", this->quickAccessToolBar->isMenuActionChecked());
	settings.setValue("isDrawShown", this->drawToolBar->isMenuActionChecked());
	settings.setValue("isPropertyShown", this->propertyToolBar->isMenuActionChecked());
	settings.setValue("isModifyShown", this->modifyToolBar->isMenuActionChecked());
	settings.setValue("isLayerShown", this->layerToolBar->isMenuActionChecked());
	settings.setValue("isObjectSnapShown", this->objectSnapToolBar->isMenuActionChecked());
	settings.setValue("isDimensionShown", this->dimensionToolBar->isMenuActionChecked());

	settings.endGroup();
}
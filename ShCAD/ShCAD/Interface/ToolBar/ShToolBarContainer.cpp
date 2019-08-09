

#include "ShToolBarContainer.h"
#include "Interface\ShCAD.h"
#include <qmenu.h>
#include "ShDrawToolBar.h"
#include "ShLayerToolBar.h"
#include "ShPropertyToolBar.h"
#include "ShModifyToolBar.h"
#include "ShObjectSnapToolBar.h"
#include "Manager\ShLanguageManager.h"

ShToolBarContainer::ShToolBarContainer(ShCAD *parent, ShChain *chain)
	:parent(parent), ShChain(chain) {

	this->toolBarMenu = new QMenu(shGetLanValue_ui("ToolBar/ToolBars"));

	this->createToolBars();

	QList<ShAbstractToolBar*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr) {

		this->parent->addToolBar(Qt::ToolBarArea::TopToolBarArea, (*itr));
		this->toolBarMenu->addAction((*itr)->GetMenuAction());
		(*itr)->hide();
	}


}

ShToolBarContainer::~ShToolBarContainer() {

	if (this->toolBarMenu != nullptr)
		delete this->toolBarMenu;

}

void ShToolBarContainer::createToolBars() {

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
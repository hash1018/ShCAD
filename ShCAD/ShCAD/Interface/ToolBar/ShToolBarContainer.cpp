

#include "ShToolBarContainer.h"
#include "Interface\shcad.h"
#include <qmenu.h>
#include "Interface\ToolBar\ShDrawToolBar.h"
#include "Interface\ToolBar\ShPropertyToolBar.h"
#include "Interface\ToolBar\ShModifyToolBar.h"
#include "Interface\ToolBar\ShLayerToolBar.h"
#include "Interface\ToolBar\ShObjectSnapToolBar.h"

ShToolBarContainer::ShToolBarContainer(ShCAD *shCAD)
	:shCAD(shCAD) {

	this->toolBarMenu = new QMenu("ToolBars");

	this->CreateToolBars();

	QList<ShAbstractToolBar*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr) {

		this->shCAD->addToolBar(Qt::ToolBarArea::TopToolBarArea, (*itr));
		this->toolBarMenu->addAction((*itr)->GetMenuAction());
		(*itr)->hide();
	}

	
}

ShToolBarContainer::~ShToolBarContainer() {

	if (this->toolBarMenu != 0)
		delete this->toolBarMenu;

}

void ShToolBarContainer::CreateToolBars() {

	this->drawToolBar = new ShDrawToolBar("Draw", this->shCAD);
	this->list.append(this->drawToolBar);

	this->propertyToolBar = new ShPropertyToolBar("Property", this->shCAD);
	this->list.append(this->propertyToolBar);

	this->modifyToolBar = new ShModifyToolBar("Modify", this->shCAD);
	this->list.append(this->modifyToolBar);

	this->layerToolBar = new ShLayerToolBar("Layer", this->shCAD);
	this->list.append(this->layerToolBar);

	this->objectSnapToolBar = new ShObjectSnapToolBar("ObjectSnap", this->shCAD);
	this->list.append(this->objectSnapToolBar);


}

void ShToolBarContainer::Activate() {

	QList<ShAbstractToolBar*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		(*itr)->Activate();

}

void ShToolBarContainer::DeActivate() {
	
	QList<ShAbstractToolBar*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		(*itr)->DeActivate();

}
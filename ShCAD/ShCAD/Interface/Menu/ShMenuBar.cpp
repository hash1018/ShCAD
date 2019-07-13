
#include "ShMenuBar.h"
#include "ShMenu.h"
#include "Interface/ShCAD.h"
#include <qdebug.h>
#include "Manager\ShLanguageManager.h"

ShMenuBar::ShMenuBar(ShCAD *parent)
	:QMenuBar(parent),parent(parent) {

	this->emptyFileMenu = new ShEmptyDrawingFileMenu(shGetLanValue_ui("File/File"), this);
	this->fileMenu = new ShFileMenu(shGetLanValue_ui("File/File"), this);
	this->editMenu = new ShEditMenu(shGetLanValue_ui("Edit/Edit"), this);
	this->drawMenu = new ShDrawMenu(shGetLanValue_ui("Draw/Draw"), this);
	this->modifyMenu = new ShModifyMenu(shGetLanValue_ui("Modify/Modify"), this);

}

ShMenuBar::~ShMenuBar() {

}

void ShMenuBar::activateMenu() {

	this->clear();
	this->addMenu(this->fileMenu);
	this->addMenu(this->editMenu);
	this->addMenu(this->drawMenu);
	this->addMenu(this->modifyMenu);
}

void ShMenuBar::deactivateMenu() {

	this->clear();
	this->addMenu(this->emptyFileMenu);
}

void ShMenuBar::newActionClicked() {

	if (this->parent == nullptr) {
		qDebug() << " ShMenuBar::newActionClicked  parent is nullptr";
		return;
	}
	
	this->parent->createCADWidget();
}

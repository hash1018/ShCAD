
#include "ShMenuBar.h"
#include "ShMenu.h"
#include <qdebug.h>
#include "Manager\ShLanguageManager.h"

ShMenuBar::ShMenuBar(ShChain *chain, QWidget *parent)
	:QMenuBar(parent), ShChain(chain) {

	this->emptyFileMenu = new ShEmptyDrawingFileMenu(shGetLanValue_ui("File/File"), this, this);
	this->fileMenu = new ShFileMenu(shGetLanValue_ui("File/File"), this, this);
	this->editMenu = new ShEditMenu(shGetLanValue_ui("Edit/Edit"), this, this);
	this->drawMenu = new ShDrawMenu(shGetLanValue_ui("Draw/Draw"), this, this);
	this->modifyMenu = new ShModifyMenu(shGetLanValue_ui("Modify/Modify"), this, this);
	this->windowMenu = new ShWindowMenu(shGetLanValue_ui("Window/Window"), this, this);

}

ShMenuBar::~ShMenuBar() {

}

void ShMenuBar::activateMenu() {

	this->clear();
	this->addMenu(this->fileMenu);
	this->addMenu(this->editMenu);
	this->addMenu(this->drawMenu);
	this->addMenu(this->modifyMenu);
	this->addMenu(this->windowMenu);
}

void ShMenuBar::deactivateMenu() {

	this->clear();
	this->addMenu(this->emptyFileMenu);
}


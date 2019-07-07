
#include "ShMenuBar.h"
#include "ShMenu.h"
#include "Interface/ShCAD.h"
#include <qdebug.h>

ShMenuBar::ShMenuBar(ShCAD *parent)
	:QMenuBar(parent),parent(parent) {

	this->emptyFileMenu = new ShEmptyDrawingFileMenu("File", this);
	this->fileMenu = new ShFileMenu("File", this);
	this->editMenu = new ShEditMenu("Edit", this);
	this->drawMenu = new ShDrawMenu("Draw", this);
	this->modifyMenu = new ShModifyMenu("Modify", this);

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

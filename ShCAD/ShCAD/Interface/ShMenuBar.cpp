

#include "ShMenuBar.h"

ShMenuBar::ShMenuBar(QWidget *parent)
	:QMenuBar(parent) {

	this->fileMenu = new ShFileMenu("File", this);
	this->addMenu(this->fileMenu);

}

ShMenuBar::~ShMenuBar() {


}


ShFileMenu::ShFileMenu(const QString &title, QWidget *parent)
	:QMenu(title, parent) {

	this->newAction = new QAction("New", this);

	this->addAction(this->newAction);
}

ShFileMenu::~ShFileMenu() {


}
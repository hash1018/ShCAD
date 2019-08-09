
#include "ShChangeManager.h"
#include "Interface/StatusBar/ShStatusBar.h"
#include "Interface/Dock/ShCommandDock.h"
#include "Interface\Ribbon\ShRibbonMenu.h"
#include "Interface\ToolBar\ShToolBarContainer.h"

ShChangeManager ShChangeManager::instance;

ShChangeManager::ShChangeManager() {

}

ShChangeManager::~ShChangeManager() {

}

ShChangeManager* ShChangeManager::getInstance() {

	return &(ShChangeManager::instance);
}

void ShChangeManager::registerObserver(ShStatusBar *statusBar) {

	this->statusBar = statusBar;
}

void ShChangeManager::registerObserver(ShCommandDock *commandDock) {

	this->commandDock = commandDock;
}

void ShChangeManager::registerObserver(ShRibbonMenu *ribbonMenu) {

	this->ribbonMenu = ribbonMenu;
}
void ShChangeManager::registerObserver(ShToolBarContainer *toolBarContainer) {

	this->toolBarContainer = toolBarContainer;
}

void ShChangeManager::notify(ShCADWidget *widget, ShNotifyEvent *event) {

	this->statusBar->update(event);
	this->commandDock->update(event);
	this->ribbonMenu->update(event);
	this->toolBarContainer->update(event);
}


#include "ShChangeManager.h"
#include "Interface/StatusBar/ShStatusBar.h"
#include "Interface/Dock/ShCommandDock.h"
#include "Manager\ShCADWidgetManager.h"
#include "Interface\ShCADWidget.h"

ShChangeManager ShChangeManager::instance;

ShChangeManager::ShChangeManager() {

}

ShChangeManager::~ShChangeManager() {

}

ShChangeManager* ShChangeManager::getInstance() {

	return &(ShChangeManager::instance);
}

void ShChangeManager::Register(ShStatusBar *statusBar) {

	this->statusBar = statusBar;
}

void ShChangeManager::Register(ShCommandDock *commandDock) {

	this->commandDock = commandDock;
}

void ShChangeManager::notify(ShCADWidget *widget, ShNotifyEvent *event) {

	this->statusBar->update(event);
	this->commandDock->update(event);

}

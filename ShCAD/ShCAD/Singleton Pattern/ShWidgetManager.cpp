

#include "ShWidgetManager.h"

ShWidgetManager ShWidgetManager::instance;

ShWidgetManager::ShWidgetManager() {

}

ShWidgetManager::~ShWidgetManager() {

}

ShWidgetManager* ShWidgetManager::GetInstance() {

	return &instance;
}

ShCADWidget* ShWidgetManager::GetActivatedWidget() {
	
	return GetInstance()->activatedWidget;
}

void ShWidgetManager::SetActivatedWidget(ShCADWidget *activated) {

	this->activatedWidget = activated;
}
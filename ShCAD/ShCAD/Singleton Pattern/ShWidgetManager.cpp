

#include "ShWidgetManager.h"

ShWidgetManager ShWidgetManager::instance;

ShWidgetManager::ShWidgetManager() {

	this->activatedWidget = 0;
}

ShWidgetManager::~ShWidgetManager() {

}

ShWidgetManager* ShWidgetManager::GetInstance() {

	return &instance;
}

ShGraphicView* ShWidgetManager::GetActivatedWidget() {
	
	return this->activatedWidget;
}

void ShWidgetManager::SetActivatedWidget(ShGraphicView *activated) {

	this->activatedWidget = activated;
}
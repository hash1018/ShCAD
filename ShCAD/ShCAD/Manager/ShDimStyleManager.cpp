
#include "ShDimStyleManager.h"
#include "Manager\ShCADWidgetManager.h"
#include "Interface\ShCADWidget.h"

ShDimStyleManager ShDimStyleManager::instance;


ShDimStyleManager::ShDimStyleManager()
	:arrowSize(10), intervalFromBase(10), textHeight(10) {

}

ShDimStyleManager::~ShDimStyleManager() {

}

ShDimStyleManager* ShDimStyleManager::getInstance() {

	return &(ShDimStyleManager::instance);
}

void ShDimStyleManager::setArrowSize(double arrowSize) {

	this->arrowSize = arrowSize;
	this->updateWidget();
}

void ShDimStyleManager::setIntervalFromBase(double intervalFromBase) {

	this->intervalFromBase = intervalFromBase;
	this->updateWidget();
}

void ShDimStyleManager::setTextHeight(double textHeight) {

	this->textHeight = textHeight;
	this->updateWidget();
}

void ShDimStyleManager::updateWidget() {

	ShCADWidgetManager *manager = ShCADWidgetManager::getInstance();

	if (manager->getActivatedWidget() == 0)
		return;

	manager->getActivatedWidget()->update();
	manager->getActivatedWidget()->captureImage();
}
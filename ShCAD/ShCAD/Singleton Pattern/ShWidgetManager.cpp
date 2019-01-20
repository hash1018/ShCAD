

#include "ShWidgetManager.h"
#include "Interface\ShGraphicView.h"

ShWidgetManager ShWidgetManager::instance;

ShWidgetManager::ShWidgetManager() {
	this->nameIndex = 0;
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

void ShWidgetManager::Add(ShGraphicView *view) {

	this->list.append(view);
	
	view->setWindowTitle("Unknown" + QString::number(this->nameIndex++));
}

void ShWidgetManager::Remove(ShGraphicView *view) {

	this->list.removeOne(view);

	if (this->list.isEmpty() == true) {
		this->activatedWidget = 0;
	}
}

void ShWidgetManager::SetActivatedWidget(ShGraphicView *activated) {

	this->activatedWidget = activated;

	for (int i = 0; i < this->list.size(); i++)
		this->list.at(i)->setMouseTracking(false);

	this->activatedWidget->setMouseTracking(true);
}
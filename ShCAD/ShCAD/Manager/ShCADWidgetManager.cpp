
#include "ShCADWidgetManager.h"
#include "Interface\ShCADWidget.h"
#include <qdebug.h>

ShCADWidgetManager::ShCADWidgetManager() {

	this->nameIndex = 0;
	this->activatedWidget = nullptr;
}

ShCADWidgetManager::~ShCADWidgetManager() {


}

ShCADWidget* ShCADWidgetManager::getActivatedWidget() {

	if (this->activatedWidget == nullptr)
		qDebug() << "ShCADWidgetManager::GEtActivatedWidget  -> activatedWidget is null ptr";

	return this->activatedWidget;
}

void ShCADWidgetManager::add(ShCADWidget *widget) {

	this->list.append(widget);
	widget->setWindowTitle("Unknown" + QString::number(this->nameIndex++));
}

void ShCADWidgetManager::remove(ShCADWidget *widget) {

	this->list.removeOne(widget);

	if (this->list.isEmpty() == true)
		this->activatedWidget = 0;

}

void ShCADWidgetManager::setActivatedWidget(ShCADWidget *widget) {

	this->activatedWidget = widget;

	for (int i = 0; i < this->list.size(); i++)
		this->list.at(i)->setMouseTracking(false);

	this->activatedWidget->setMouseTracking(true);
}
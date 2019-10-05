
#include "ShChangeManager.h"
#include "Event\ShObserver.h"

ShChangeManager::ShChangeManager() {

}

ShChangeManager::~ShChangeManager() {

}

void ShChangeManager::registerObserver(ShObserver *observer) {

	this->observers.append(observer);
}

void ShChangeManager::notify(ShCADWidget *widget, ShNotifyEvent *event) {

	for (int i = 0; i < this->observers.size(); i++)
		this->observers.at(i)->update(event);
}



#include "ShChangeManager.h"
#include "Interface\ShGraphicView.h"
#include "Interface\ShStatusBar.h"
ShChangeManager ShChangeManager::instance;

ShChangeManager::ShChangeManager() {

}

ShChangeManager::~ShChangeManager() {

}

ShChangeManager* ShChangeManager::GetInstance() {

	return &(ShChangeManager::instance);
}

void ShChangeManager::Register(ShStatusBar *statusBar) {

	this->statusBar = statusBar;
}



void ShChangeManager::Notify(ShGraphicView *view, NotifyEvent event) {

	if (event == NotifyEvent::NotifyMousePositionChanged ||
		event == NotifyEvent::NotifyZoomRateChanged) {

		this->statusBar->Update(view->GetX(), view->GetY(), view->GetZ(), view->GetZoomRate());
	}
	
}
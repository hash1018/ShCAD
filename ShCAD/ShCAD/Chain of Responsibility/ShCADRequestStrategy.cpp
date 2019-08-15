
#include "ShCADRequestStrategy.h"
#include "Interface\ShCAD.h"
#include "Manager\ShCADWidgetManager.h"
#include "ShRequest.h"
#include "Interface\ShCADWidget.h"
#include "Base\ShGlobal.h"
#include <qmdiarea.h>

ShCADRequestStrategy::ShCADRequestStrategy(ShCAD *shCAD, ShRequest *request)
	:shCAD(shCAD), request(request) {

}

ShCADRequestStrategy::~ShCADRequestStrategy() {

}

///////////////////////////////////////////

ShCADRequestCreateNewWidgetStrategy::ShCADRequestCreateNewWidgetStrategy(ShCAD *shCAD, ShRequest *request)
	:ShCADRequestStrategy(shCAD, request) {

}

ShCADRequestCreateNewWidgetStrategy::~ShCADRequestCreateNewWidgetStrategy() {

}

void ShCADRequestCreateNewWidgetStrategy::response() {

	this->shCAD->createCADWidget();
}

//////////////////////////////////////////////

ShCADRequestChangeActionStrategy::ShCADRequestChangeActionStrategy(ShCAD *shCAD, ShRequest *request)
	:ShCADRequestStrategy(shCAD, request) {

}
	
ShCADRequestChangeActionStrategy::~ShCADRequestChangeActionStrategy() {

}

void ShCADRequestChangeActionStrategy::response() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShRequestChangeActionHandler *request = dynamic_cast<ShRequestChangeActionHandler*>(this->request);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(*(request->getStrategy()));
}

////////////////////////////////////////////////

ShCADRequestSendNotifyEventStrategy::ShCADRequestSendNotifyEventStrategy(ShCAD *shCAD, ShRequest *request)
	:ShCADRequestStrategy(shCAD, request) {

}
ShCADRequestSendNotifyEventStrategy::~ShCADRequestSendNotifyEventStrategy() {

}

void ShCADRequestSendNotifyEventStrategy::response() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShRequestSendNotifyEvent *request = dynamic_cast<ShRequestSendNotifyEvent*>(this->request);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->update(request->getNotifyEvent());
}

///////////////////////////////////////////////////


ShCADRequestUndoStrategy::ShCADRequestUndoStrategy(ShCAD *shCAD, ShRequest *request)
	:ShCADRequestStrategy(shCAD, request) {

}

ShCADRequestUndoStrategy::~ShCADRequestUndoStrategy() {

}

void ShCADRequestUndoStrategy::response() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShGlobal::undo(ShCADWidgetManager::getInstance()->getActivatedWidget());
}

/////////////////////////////////////////////////////

ShCADRequestRedoStrategy::ShCADRequestRedoStrategy(ShCAD *shCAD, ShRequest *request)
	:ShCADRequestStrategy(shCAD, request) {

}

ShCADRequestRedoStrategy::~ShCADRequestRedoStrategy() {

}

void ShCADRequestRedoStrategy::response() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShGlobal::redo(ShCADWidgetManager::getInstance()->getActivatedWidget());
}

///////////////////////////////////////////////////////

ShCADRequestChangeViewModeStrategy::ShCADRequestChangeViewModeStrategy(ShCAD *shCAD, ShRequest *request)
	:ShCADRequestStrategy(shCAD, request) {

}

ShCADRequestChangeViewModeStrategy::~ShCADRequestChangeViewModeStrategy() {

}

void ShCADRequestChangeViewModeStrategy::response() {

	ShRequestChangeViewMode *request = dynamic_cast<ShRequestChangeViewMode*>(this->request);
	
	if (request->getViewMode() == ShRequestChangeViewMode::ViewMode::SubWindowView)
		this->shCAD->getMdiArea()->setViewMode(QMdiArea::ViewMode::SubWindowView);
	else if (request->getViewMode() == ShRequestChangeViewMode::ViewMode::TabbedView)
		this->shCAD->getMdiArea()->setViewMode(QMdiArea::ViewMode::TabbedView);
	else if (request->getViewMode() == ShRequestChangeViewMode::ViewMode::Cascade)
		this->shCAD->getMdiArea()->cascadeSubWindows();
	else if (request->getViewMode() == ShRequestChangeViewMode::Tile)
		this->shCAD->getMdiArea()->tileSubWindows();
		
}
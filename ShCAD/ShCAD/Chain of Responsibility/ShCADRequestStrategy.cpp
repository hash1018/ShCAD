
#include "ShCADRequestStrategy.h"
#include "Interface\ShCAD.h"
#include "Manager\ShCADWidgetManager.h"
#include "ShRequest.h"
#include "Interface\ShCADWidget.h"
#include "Base\ShGlobal.h"

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
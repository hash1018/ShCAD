
#include "ShRequest.h"

ShRequest::ShRequest(ShRequest::RequestType type)
	:type(type) {

}

ShRequest::~ShRequest() {

}

////////////////////////////////

ShRequestCreateNewCADWidget::ShRequestCreateNewCADWidget()
	:ShRequest(ShRequest::RequestCreateNewCADWidget) {

}

ShRequestCreateNewCADWidget::~ShRequestCreateNewCADWidget() {

}

//////////////////////////////

ShRequestChangeActionHandler::ShRequestChangeActionHandler(ShChangeActionStrategy *strategy)
	:ShRequest(ShRequest::RequestChangeActionHandler), strategy(strategy) {

}

ShRequestChangeActionHandler::~ShRequestChangeActionHandler() {

}

///////////////////////////////

ShRequestSendNotifyEvent::ShRequestSendNotifyEvent(ShNotifyEvent *notifyEvent)
	:ShRequest(ShRequest::RequestSendNotifyEvent), notifyEvent(notifyEvent) {

}

ShRequestSendNotifyEvent::~ShRequestSendNotifyEvent() {

}

///////////////////////////////

ShRequestUndo::ShRequestUndo()
	:ShRequest(ShRequest::RequestUndo) {

}

ShRequestUndo::~ShRequestUndo() {

}

///////////////////////////////

ShRequestRedo::ShRequestRedo()
	:ShRequest(ShRequest::RequestRedo) {

}

ShRequestRedo::~ShRequestRedo() {

}

///////////////////////////////

ShRequestChangeViewMode::ShRequestChangeViewMode(ViewMode viewMode)
	:ShRequest(ShRequest::RequestChangeViewMode), viewMode(viewMode) {

}

ShRequestChangeViewMode::~ShRequestChangeViewMode() {

}
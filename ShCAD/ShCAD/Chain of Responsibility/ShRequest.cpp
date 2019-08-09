
#include "ShRequest.h"

ShRequest::ShRequest(ShRequest::RequestType type)
	:type(type) {

}

ShRequest::~ShRequest() {

}

////////////////////////////////

ShCreateNewCADWidgetRequest::ShCreateNewCADWidgetRequest()
	:ShRequest(ShRequest::RequestCreateNewCADWidget) {

}

ShCreateNewCADWidgetRequest::~ShCreateNewCADWidgetRequest() {

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
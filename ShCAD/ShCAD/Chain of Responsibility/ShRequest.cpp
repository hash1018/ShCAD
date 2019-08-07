
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
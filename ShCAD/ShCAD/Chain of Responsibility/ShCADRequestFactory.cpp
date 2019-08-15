
#include "ShCADRequestFactory.h"
#include "ShRequest.h"
#include "ShCADRequestStrategy.h"

ShCADRequestFactory::ShCADRequestFactory() {

}

ShCADRequestFactory::~ShCADRequestFactory() {

}

ShCADRequestStrategy* ShCADRequestFactory::create(ShCAD *shCAD, ShRequest *request) {

	ShCADRequestStrategy *strategy = nullptr;

	if (request->getType() == ShRequest::RequestType::RequestCreateNewCADWidget)
		strategy = new ShCADRequestCreateNewWidgetStrategy(shCAD, request);
	else if (request->getType() == ShRequest::RequestChangeActionHandler)
		strategy = new ShCADRequestChangeActionStrategy(shCAD, request);
	else if (request->getType() == ShRequest::RequestSendNotifyEvent)
		strategy = new ShCADRequestSendNotifyEventStrategy(shCAD, request);
	else if (request->getType() == ShRequest::RequestUndo)
		strategy = new ShCADRequestUndoStrategy(shCAD, request);
	else if (request->getType() == ShRequest::RequestRedo)
		strategy = new ShCADRequestRedoStrategy(shCAD, request);
	else if (request->getType() == ShRequest::RequestChangeViewMode)
		strategy = new ShCADRequestChangeViewModeStrategy(shCAD, request);
		

	return strategy;
}

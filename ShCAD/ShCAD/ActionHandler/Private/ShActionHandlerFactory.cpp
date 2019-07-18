
#include "ShActionHandlerFactory.h"
#include "ActionHandler\ShDefaultAction.h"


ShActionHandlerFactory::ShActionHandlerFactory() {

}

ShActionHandlerFactory::~ShActionHandlerFactory() {

}

ShActionHandler* ShActionHandlerFactory::create(ActionType actionType, ShCADWidget *widget) {

	if (actionType == ActionType::ActionDefault)
		return new ShDefaultAction(widget);
	

	return new ShDefaultAction(widget);
}


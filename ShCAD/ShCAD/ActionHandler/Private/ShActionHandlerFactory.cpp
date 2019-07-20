
#include "ShActionHandlerFactory.h"
#include "ActionHandler\ShDefaultAction.h"
#include "ActionHandler\DrawAction\ShDrawLineAction.h"


ShActionHandlerFactory::ShActionHandlerFactory() {

}

ShActionHandlerFactory::~ShActionHandlerFactory() {

}

ShActionHandler* ShActionHandlerFactory::create(ActionType actionType, ShCADWidget *widget) {

	if (actionType == ActionType::ActionDefault)
		return new ShDefaultAction(widget);
	else if (actionType == ActionType::ActionDrawLine)
		return new ShDrawLineAction(widget);

	return new ShDefaultAction(widget);
}



#include "ShActionHandlerFactory.h"
#include "ActionHandler\ShDefaultAction.h"
#include "ActionHandler\DrawAction\ShDrawLineAction.h"
#include "ActionHandler\ModifyAction\ShModifyMoveAction.h"
#include "ActionHandler\ModifyAction\ShModifyCopyAction.h"


ShActionHandlerFactory::ShActionHandlerFactory() {

}

ShActionHandlerFactory::~ShActionHandlerFactory() {

}

ShActionHandler* ShActionHandlerFactory::create(ActionType actionType, ShCADWidget *widget) {

	if (actionType == ActionType::ActionDefault)
		return new ShDefaultAction(widget);
	else if (actionType == ActionType::ActionDrawLine)
		return new ShDrawLineAction(widget);

	else if (actionType == ActionType::ActionModifyMove)
		return new ShModifyMoveAction(widget);
	else if (actionType == ActionType::ActionModifyCopy)
		return new ShModifyCopyAction(widget);

	return new ShDefaultAction(widget);
}


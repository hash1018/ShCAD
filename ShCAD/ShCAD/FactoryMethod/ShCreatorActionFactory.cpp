

#include "ShCreatorActionFactory.h"
#include "ActionHandler\ShDefaultAction.h"
#include "ActionHandler\DrawAction\ShDrawLineAction.h"

ShCreatorActionFactory::ShCreatorActionFactory(){

}

ShCreatorActionFactory::~ShCreatorActionFactory() {

}

ShActionHandler* ShCreatorActionFactory::Create(ActionType actionType, ShGraphicView *graphicView) {

	if (actionType == ActionType::ActionDefault)
		return new ShDefaultAction(graphicView);

	if (actionType == ActionType::ActionDrawLine)
		return new ShDrawLineAction(graphicView);


	return new ShDefaultAction(graphicView);
}
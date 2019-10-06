
#include "ShActionHandlerFactory.h"
#include "ActionHandler\ShDefaultAction.h"
#include "ActionHandler\DrawAction\ShDrawLineAction.h"
#include "ActionHandler\DrawAction\ShDrawCircleAction.h"
#include "ActionHandler\DrawAction\ShDrawArcAction.h"
#include "ActionHandler\ModifyAction\ShModifyMoveAction.h"
#include "ActionHandler\ModifyAction\ShModifyCopyAction.h"
#include "ActionHandler\ModifyAction\ShModifyRotateAction.h"
#include "ActionHandler\ModifyAction\ShModifyMirrorAction.h"
#include "ActionHandler\ModifyAction\ShModifyEraseAction.h"
#include "ActionHandler\ModifyAction\ShModifyExtendAction.h"
#include "ActionHandler\ModifyAction\ShModifyTrimAction.h"
#include "ActionHandler\ModifyAction\ShModifyStretchAction.h"
#include "ActionHandler\DrawAction\DimAction\ShDimLinearAction.h"
#include "ActionHandler\DrawAction\ShDrawPointAction.h"
#include "ActionHandler\ShSelectPlotAreaAction.h"

ShActionHandlerFactory::ShActionHandlerFactory() {

}

ShActionHandlerFactory::~ShActionHandlerFactory() {

}

ShActionHandler* ShActionHandlerFactory::create(ActionType actionType, ShCADWidget *widget) {

	if (actionType == ActionType::ActionDefault)
		return new ShDefaultAction(widget);
	else if (actionType == ActionType::ActionDrawLine)
		return new ShDrawLineAction(widget);
	else if (actionType == ActionType::ActionDrawCircleCenterRadius)
		return new ShDrawCircleAction(widget, ShDrawCircleAction::SubAction::CenterRadius);
	else if (actionType == ActionType::ActionDrawCircleCenterDiameter)
		return new ShDrawCircleAction(widget, ShDrawCircleAction::SubAction::CenterDiameter);
	else if (actionType == ActionType::ActionDrawCircleTwoPoint)
		return new ShDrawCircleAction(widget, ShDrawCircleAction::SubAction::TwoPoint);
	else if (actionType == ActionType::ActionDrawCircleThreePoint)
		return new ShDrawCircleAction(widget, ShDrawCircleAction::SubAction::ThreePoint);

	else if (actionType == ActionType::ActionDrawArcThreePoint)
		return new ShDrawArcAction(widget, ShDrawArcAction::SubAction::ThreePoint);

	else if (actionType == ActionType::ActionDrawArcStartCenterEnd)
		return new ShDrawArcAction(widget, ShDrawArcAction::SubAction::StartCenterEnd);
	else if (actionType == ActionType::ActionDrawArcStartCenterAngle)
		return new ShDrawArcAction(widget, ShDrawArcAction::SubAction::StartCenterAngle);
	else if (actionType == ActionType::ActionDrawArcStartCenterLength)
		return new ShDrawArcAction(widget, ShDrawArcAction::SubAction::StartCenterLength);

	else if (actionType == ActionType::ActionDrawArcStartEndAngle)
		return new ShDrawArcAction(widget, ShDrawArcAction::SubAction::StartEndAngle);
	else if (actionType == ActionType::ActionDrawArcStartEndDirection)
		return new ShDrawArcAction(widget, ShDrawArcAction::SubAction::StartEndDirection);
	else if (actionType == ActionType::ActionDrawArcStartEndRadius)
		return new ShDrawArcAction(widget, ShDrawArcAction::SubAction::StartEndRadius);

	else if (actionType == ActionType::ActionDrawArcCenterStartEnd)
		return new ShDrawArcAction(widget, ShDrawArcAction::SubAction::CenterStartEnd);
	else if (actionType == ActionType::ActionDrawArcCenterStartAngle)
		return new ShDrawArcAction(widget, ShDrawArcAction::SubAction::CenterStartAngle);
	else if (actionType == ActionType::ActionDrawArcCenterStartLength)
		return new ShDrawArcAction(widget, ShDrawArcAction::SubAction::CenterStartLength);


	else if (actionType == ActionType::ActionModifyMove)
		return new ShModifyMoveAction(widget);
	else if (actionType == ActionType::ActionModifyCopy)
		return new ShModifyCopyAction(widget);
	else if (actionType == ActionType::ActionModifyRotate)
		return new ShModifyRotateAction(widget);
	else if (actionType == ActionType::ActionModifyMirror)
		return new ShModifyMirrorAction(widget);
	else if (actionType == ActionType::ActionModifyErase)
		return new ShModifyEraseAction(widget);
	else if (actionType == ActionType::ActionModifyExtend)
		return new ShModifyExtendAction(widget);
	else if (actionType == ActionType::ActionModifyTrim)
		return new ShModifyTrimAction(widget);
	else if (actionType == ActionType::ActionModifyStretch)
		return new ShModifyStretchAction(widget);



	else if (actionType == ActionType::ActionDrawDimLinear)
		return new ShDimLinearAction(widget);


	else if (actionType == ActionType::ActionDrawPoint)
		return new ShDrawPointAction(widget);


	else if (actionType == ActionType::ActionSelectPlotArea)
		return new ShSelectPlotAreaAction(widget);

	return new ShDefaultAction(widget);
}


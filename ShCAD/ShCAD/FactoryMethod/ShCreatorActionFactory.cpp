
/*--
**
**   This file is part of the ShCAD project, a 2D CAD Program
**
**    Copyright (C) 2019, Seungho Ha  (sh.ha1018@gmail.com)
**
**
**   This program is free software; you can redistribute it and/or modify it
**   under the terms of the GNU Lesser General Public License as published by
**   the Free Software Foundation; either version 2.1 of the License, or (at
**   your option) any later version.
**
**   This program is distributed in the hope that it will be useful, but
**   WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
**   General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
**
**
--*/

#include "ShCreatorActionFactory.h"
#include "ActionHandler\ShDefaultAction.h"
#include "ActionHandler\DrawAction\ShDrawLineAction.h"
#include "ActionHandler\DrawAction\ShDrawCircleAction.h"
#include "ActionHandler\DrawAction\ShDrawArcAction.h"
#include "ActionHandler\ModifyAction\ShModifyMoveAction.h"
#include "ActionHandler\ModifyAction\ShModifyCopyAction.h"
#include "ActionHandler\ModifyAction\ShModifyRotateAction.h"
#include "ActionHandler\ModifyAction\ShModifyMirrorAction.h"
#include "ActionHandler\ModifyAction\ShModifyEraseAction.h"
#include "ActionHandler\ModifyAction\ShModifyStretchAction.h"
#include "ActionHandler\ModifyAction\ShModifyExtendAction.h"
ShCreatorActionFactory::ShCreatorActionFactory(){

}

ShCreatorActionFactory::~ShCreatorActionFactory() {

}

ShActionHandler* ShCreatorActionFactory::Create(ActionType actionType, ShGraphicView *graphicView) {

	if (actionType == ActionType::ActionDefault)
		return new ShDefaultAction(graphicView);
	if (actionType == ActionType::ActionDrawLine)
		return new ShDrawLineAction(graphicView);

	if (actionType == ActionType::ActionDrawCircleCenterRadius)
		return new ShDrawCircleAction(graphicView);
	if (actionType == ActionType::ActionDrawCircleCenterDiameter)
		return new ShDrawCircleAction(graphicView, ShDrawCircleAction::DrawMethod::CenterDiameter);
	if (actionType == ActionType::ActionDrawCircleTwoPoint)
		return new ShDrawCircleAction(graphicView, ShDrawCircleAction::DrawMethod::TwoPoint);
	if (actionType == ActionType::ActionDrawCircleThreePoint)
		return new ShDrawCircleAction(graphicView, ShDrawCircleAction::DrawMethod::ThreePoint);


	if (actionType == ActionType::ActionDrawArcThreePoint)
		return new ShDrawArcAction(graphicView, ShDrawArcAction::DrawMethod::ThreePoint);
	if (actionType == ActionType::ActionDrawArcStartCenterEnd)
		return new ShDrawArcAction(graphicView, ShDrawArcAction::DrawMethod::StartCenterEnd);
	if (actionType == ActionType::ActionDrawArcStartCenterAngle)
		return new ShDrawArcAction(graphicView, ShDrawArcAction::DrawMethod::StartCenterAngle);
	if (actionType == ActionType::ActionDrawArcStartCenterLength)
		return new ShDrawArcAction(graphicView, ShDrawArcAction::DrawMethod::StartCenterLength);
	if (actionType == ActionType::ActionDrawArcStartEndAngle)
		return new ShDrawArcAction(graphicView, ShDrawArcAction::DrawMethod::StartEndAngle);
	if (actionType == ActionType::ActionDrawArcStartEndDirection)
		return new ShDrawArcAction(graphicView, ShDrawArcAction::DrawMethod::StartEndDirection);
	if (actionType == ActionType::ActionDrawArcStartEndRadius)
		return new ShDrawArcAction(graphicView, ShDrawArcAction::DrawMethod::StartEndRadius);
	if(actionType==ActionType::ActionDrawArcCenterStartEnd)
		return new ShDrawArcAction(graphicView,ShDrawArcAction::DrawMethod::CenterStartEnd);
	if (actionType == ActionType::ActionDrawArcCenterStartAngle)
		return new ShDrawArcAction(graphicView, ShDrawArcAction::DrawMethod::CenterStartAngle);
	if (actionType == ActionType::ActionDrawArcCenterStartLength)
		return new ShDrawArcAction(graphicView, ShDrawArcAction::DrawMethod::CenterStartLength);
	if (actionType == ActionType::ActionModifyMove)
		return new ShModifyMoveAction(graphicView);
	if (actionType == ActionType::ActionModifyCopy)
		return new ShModifyCopyAction(graphicView);
	if (actionType == ActionType::ActionModifyRotate)
		return new ShModifyRotateAction(graphicView);
	if (actionType == ActionType::ActionModifyMirror)
		return new ShModifyMirrorAction(graphicView);
	if (actionType == ActionType::ActionModifyErase)
		return new ShModifyEraseAction(graphicView);
	if (actionType == ActionType::ActionModifyStretch)
		return new ShModifyStretchAction(graphicView);
	if (actionType == ActionType::ActionModifyExtend)
		return new ShModifyExtendAction(graphicView);

	return new ShDefaultAction(graphicView);
}
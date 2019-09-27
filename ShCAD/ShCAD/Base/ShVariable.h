
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

#ifndef _SHVARIABLE_H
#define _SHVARIABLE_H


enum ActionType {
	ActionUnknown,
	ActionDefault,
	ActionTempPan,
	ActionTempDragSelect,
	ActionTempStretch,
	ActionDrawLine,
	ActionDrawCircleCenterRadius,
	ActionDrawCircleCenterDiameter,
	ActionDrawCircleTwoPoint,
	ActionDrawCircleThreePoint,
	ActionDrawArcThreePoint,
	ActionDrawArcStartCenterEnd,
	ActionDrawArcStartCenterAngle,
	ActionDrawArcStartCenterLength,
	ActionDrawArcStartEndAngle,
	ActionDrawArcStartEndDirection,
	ActionDrawArcStartEndRadius,
	ActionDrawArcCenterStartEnd,
	ActionDrawArcCenterStartAngle,
	ActionDrawArcCenterStartLength,

	ActionDrawRectangle,
	ActionDrawPolygon,
	ActionDrawPolyLine,



	ActionModifyMove,
	ActionModifyCopy,
	ActionModifyStretch,
	ActionModifyMirror,
	ActionModifyRotate,
	ActionModifyScale,
	ActionModifyErase,
	ActionModifyExtend,
	ActionModifyTrim,

	ActionDrawDimLinear,
	ActionDrawDimAligned,
	ActionDrawDimRadius,
	ActionDrawDimDiameter,
	ActionDrawDimAngular,
	ActionDrawDimArcLength,

	ActionPlotAreaSelect,
};


enum DrawType {
	DrawNone = 0x0000000,
	DrawCaptureImage = 0x0000001,
	DrawPreviewEntities = 0x0000002,
	DrawAddedEntities = 0x0000004,
	DrawActionHandler = 0x00000008,
	DrawSelectedEntities = 0x00000010,
	DrawJustTurnOnLayer = 0x00000020,
	DrawAll = 0x0001000

};


enum VertexType {
	VertexNothing= 0x0000000,
	VertexStart= 0x0000001,
	VertexEnd= 0x0000002,
	VertexMid= 0x0000004,
	VertexOther= 0x0000008,
	VertexCenter= 0x0000010,
	VertexLeft= 0x0000020,
	VertexRight= 0x0000040,
	VertexTop= 0x0000080,
	VertexBottom= 0x0000100,

};

enum ObjectSnap {
	ObjectSnapNothing = 0x00000000,
	ObjectSnapEndPoint = 0x00000001,
	ObjectSnapMidPoint = 0x00000002,
	ObjectSnapIntersection = 0x00000004,
	ObjectSnapAppraentIntersection = 0x00000008,
	ObjectSnapExtension = 0x00000010,
	ObjectSnapCenter = 0x00000020,
	ObjectSnapQuadrant = 0x00000040,
	ObjectSnapTangent = 0x00000080,
	ObjectSnapPerpendicular = 0x00000100,

};


enum WhatToPlot {
	PlotDisplay,
	PlotWindow,
};



#endif //_SHVARIABLE_H
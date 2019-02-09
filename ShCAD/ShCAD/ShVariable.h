
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
	ActionPanMove,
	ActionDragSelect,
	ActionDrawLine,
	ActionSelectionMove,


};


enum DrawType {
	DrawNone = 0x0000000,
	DrawCaptureImage = 0x0000001,
	DrawPreviewEntities = 0x0000002,
	DrawAddedEntities = 0x0000004,
	DrawActionHandler = 0x00000008,
	DrawSelectedEntities = 0x00000010,
	DrawJustTurnOnLayer=0x00000020,
	DrawAll = 0x0001000

};

//speicfic area ( mouse hovered or something)  of entity object.
enum HitPoint {
	HitNothing,
	HitStart,
	HitEnd,
	HitMid,
	HitOther,


};

#endif //_SHVARIABLE_H
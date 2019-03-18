
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

#ifndef _SHDRAGSELECTACTION_H
#define _SHDRAGSELECTACTION_H

#include "ShTemporaryAction.h"

class ShDragSelectAction : public ShTemporaryAction {

public:
	enum Mode {
		SelectMode,
		UnSelectMode,
	};

	enum SelectMethod {
		AllPart,
		OnePart,
	};

protected:
	double firstX;
	double firstY;
	double secondX;
	double secondY;
	Mode mode;

public:
	ShDragSelectAction(ShGraphicView *graphicView, double firstX, double firstY, Mode mode = SelectMode);
	~ShDragSelectAction();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data);
	

	virtual ActionType GetType();

	virtual QCursor GetCursorShape();
	virtual void Draw(QPainter *painter);

	virtual QString GetActionHeadTitle();

protected:
	void GetDragRectPoint(const ShPoint3d& first, const ShPoint3d& second, ShPoint3d &topLeft, ShPoint3d &bottomRight,
		SelectMethod &selectMethod);
	void FindEntities(const ShPoint3d& first, const ShPoint3d& second, QLinkedList<ShEntity*>& foundList);
	

};

class ShModifyDragSelectAction : public ShDragSelectAction {

public:
	ShModifyDragSelectAction(ShGraphicView *graphicView, double firstX, double firstY, Mode mode = SelectMode);
	~ShModifyDragSelectAction();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data);


};

#endif //_SHDRAGSELECTACTION_H
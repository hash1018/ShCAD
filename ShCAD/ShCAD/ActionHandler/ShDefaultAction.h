

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

#ifndef _SHDEFAULTACTION_H
#define _SHDEFAULTACTION_H

#include "ShActionHandler.h"

class ShSubDefaultAction;
class ShDefaultAction : public ShActionHandler {

private:
	ShSubDefaultAction *subDefaultAction;

public:
	ShDefaultAction(ShGraphicView *graphicView);
	~ShDefaultAction();

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data);

	virtual ActionType GetType();

	void ChangeSubAction(ShSubDefaultAction *subDefaultAction);
	virtual void SetActionHeadTitle();
};


////////////////////////////////////////////////////////////////////////////

#include "ShPoint.h"
class ShSubDefaultAction {

protected:
	ShDefaultAction *defaultAction;
	ShGraphicView *view;

public:
	ShSubDefaultAction(ShDefaultAction *defaultAction, ShGraphicView *view);
	virtual ~ShSubDefaultAction() = 0;


	virtual void MousePressEvent(QMouseEvent *event) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event) = 0;

};

class ShSubDefaultAction_Default : public ShSubDefaultAction {

public:
	ShSubDefaultAction_Default(ShDefaultAction *defaultAction, ShGraphicView *view);
	~ShSubDefaultAction_Default();

	void MousePressEvent(QMouseEvent *event);
	void MouseMoveEvent(QMouseEvent *event);

};


// This is the class for preparing for stretching entity.
class ShSubDefaultAction_MouseIsInEntityVertex : public ShSubDefaultAction {

private:
	ShPoint3d vertex;

public:
	ShSubDefaultAction_MouseIsInEntityVertex(ShDefaultAction *defaultAction, ShGraphicView *view,
		const ShPoint3d& vertex);
	~ShSubDefaultAction_MouseIsInEntityVertex();

	void MousePressEvent(QMouseEvent *event);
	void MouseMoveEvent(QMouseEvent *event);

private:
	void DrawVertex();
	void EraseVertex();

};


#endif //_SHDEFAULTACTION_H
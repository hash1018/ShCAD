
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

#ifndef _SHDRAWLINEACTION_H
#define _SHDRAWLINEACTION_H


#include "ShDrawAction.h"

//class ShSubDrawLineAction;
class ShLine;
class ShDrawLineAction : public ShDrawAction{
	
	friend class ShDrawLineMethod;
	friend class ShSubLineDecorator_SnapMode_Perpendicular;
public:
	enum Status {
		PickedNothing, // no point picked. About to pick start.
		PickedStart    // start point already picked. About to pick end.
	};

	enum DrawMethod {
		Default,
		Perpendicular,
	};

	
private:
	Status status;
	DrawMethod drawMethod;

public:
	ShDrawLineAction(ShGraphicView *graphicView);
	~ShDrawLineAction();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event);
	virtual void KeyPressEvent(QKeyEvent *event);

	virtual void SetObjectSnap(ObjectSnap objectSnap);
	
	virtual ActionType GetType();
	inline ShDrawLineAction::Status GetStatus() const { return this->status; }
	inline ShDrawLineAction::DrawMethod GetDrawMethod() const { return this->drawMethod; }

	virtual void ApplyOrthogonalShape(bool isOrthogonalModeOn);

	
	void ApplyLineEndPointToOrthogonal(ShLine *line);
	void ApplyLineEndPointToMouse(ShLine *line);

	virtual void SetActionHeadTitle();
};


#include "ActionHandler\SubActionHandler\ShSubActionHandler.h"
class ShDrawLineMethod;
class ShDrawLineProxy : public ShSubIndividualAction {

private:
	ShDrawLineMethod *drawLineMethod;

public:
	ShDrawLineProxy(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	~ShDrawLineProxy();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo &info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info);

	void ChangeDrawMethodToPerpendicular(ShEntity *perpendicularBaseEntity);
	ShEntity* GetPerpendicularBaseEntity();
};

class ShDrawLineMethod {

protected:
	ShDrawLineAction *drawLineAction;
	ShGraphicView *view;

public:
	ShDrawLineMethod(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	virtual ~ShDrawLineMethod() = 0;

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info) = 0;

protected:
	inline ShDrawLineAction::Status& GetStatus() const { return this->drawLineAction->status; }
	void AddEntity(ShEntity *newEntity, const QString& commandText) {
		this->drawLineAction->AddEntity(newEntity, commandText);
	}
	void SetDrawMethod(ShDrawLineAction::DrawMethod drawMethod) { this->drawLineAction->drawMethod = drawMethod; }

};

class ShDrawLineMethod_Default : public ShDrawLineMethod {

public:
	ShDrawLineMethod_Default(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	~ShDrawLineMethod_Default();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info);

};


class ShDrawLineMethod_Perpendicular : public ShDrawLineMethod {

private:
	ShEntity* perpendicularBaseEntity;

public:
	ShDrawLineMethod_Perpendicular(ShDrawLineAction *drawLineAction, ShGraphicView *view,
		ShEntity *perpendicularBaseEntity);
	~ShDrawLineMethod_Perpendicular();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info);

	inline ShEntity* GetPerpendicularBaseEntity() const { return this->perpendicularBaseEntity; }

};




class ShSubLineDecorator_SnapMode_Perpendicular : public ShSubActionDecorator_SnapMode {

public:
	ShSubLineDecorator_SnapMode_Perpendicular(ShActionHandler *actionHandler,
		ShGraphicView *view, ObjectSnap objectSnap);
	~ShSubLineDecorator_SnapMode_Perpendicular();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo &info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info);

};

#endif //_SHDRAWLINEACTION_H
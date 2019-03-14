
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
	ShDrawLineMethod *drawLineMethod;

public:
	ShDrawLineAction(ShGraphicView *graphicView);
	~ShDrawLineAction();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data);

	virtual ActionType GetType();

	virtual void ApplyOrthogonalShape(bool on);
	

	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

	inline Status GetStatus() const { return this->status; }
	inline DrawMethod GetDrawMethod() const { return this->drawMethod; }

	void ChangeDrawMethod(DrawMethod drawMethod);
	ShDrawLineMethod *GetDrawLineMethod() const { return this->drawLineMethod; }


};

////////////////////////////////////////////////////////////////////////////////////////////////

class ShDrawLineMethod {

protected:
	ShDrawLineAction *drawLineAction;
	ShGraphicView *view;
public:
	ShDrawLineMethod(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	virtual ~ShDrawLineMethod() = 0;

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data) = 0;
	
protected:
	inline ShDrawLineAction::Status& GetStatus() const { return this->drawLineAction->status; }
	void AddEntity(ShEntity *newEntity, const QString& commandText) {
		this->drawLineAction->AddEntity(newEntity, commandText);
	}
};

class ShDrawLineMethod_Default : public ShDrawLineMethod {

public:
	ShDrawLineMethod_Default(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	~ShDrawLineMethod_Default();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

};

class ShDrawLineMethod_Perpendicular : public ShDrawLineMethod {

private:
	ShEntity* perpendicularBaseEntity;

public:
	ShDrawLineMethod_Perpendicular(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	~ShDrawLineMethod_Perpendicular();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	inline ShEntity* GetPerpendicularBaseEntity() const { return this->perpendicularBaseEntity; }
	void SetPerpendicularBaseEntity(ShEntity *entity) { this->perpendicularBaseEntity = entity; }

};


#endif //_SHDRAWLINEACTION_H
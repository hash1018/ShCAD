
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
class ShDrawLineAction : public ShDrawAction{
	
	friend class ShDrawLineMethod;
public:
	enum Status {
		PickedNothing, // no point picked. About to pick start.
		PickedStart    // start point already picked. About to pick end.
	};

	//enum DrawMethod {
	//	Default,
	//	Perpendicular,
	//};

	//friend class ShSubDrawLineAction;
private:
	Status status;
	//DrawMethod drawMethod;
	//ShSubDrawLineAction *subDrawLineAction;
	

public:
	ShDrawLineAction(ShGraphicView *graphicView);
	~ShDrawLineAction();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event);
	virtual void KeyPressEvent(QKeyEvent *event);

	virtual void SetObjectSnap(ObjectSnap objectSnap);
	//Temp
	void SetOrthogonal();

	virtual void Draw(QPainter *painter);
	virtual ActionType GetType();


	//void ChangeSubAction(ShSubDrawLineAction *current);
};


#include "ActionHandler\SubActionHandler\ShSubActionHandler.h"
class ShDrawLineMethod;
class ShDrawLineProxy : public ShSubActionHandler {

private:
	ShDrawLineMethod *drawLineMethod;

public:
	ShDrawLineProxy(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	ShDrawLineProxy(const ShDrawLineProxy& other);
	~ShDrawLineProxy();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo &info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info);
	virtual void Draw(QPainter *painter);
	virtual void Decorate(ShSubActionDecorator *decorator);
	virtual ShDrawLineProxy* Clone();

};

class ShDrawLineMethod {

protected:
	ShDrawLineAction *drawLineAction;
	ShGraphicView *view;

public:
	ShDrawLineMethod(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	ShDrawLineMethod(const ShDrawLineMethod& other);
	virtual ~ShDrawLineMethod() = 0;

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info) = 0;

	virtual ShDrawLineMethod* Clone() = 0;

protected:
	inline ShDrawLineAction::Status& GetStatus() const { return this->drawLineAction->status; }
	void AddEntity(ShEntity *newEntity, const QString& commandText) {
		this->drawLineAction->AddEntity(newEntity, commandText);
	}

};

class ShDrawLineMethod_Default : public ShDrawLineMethod {

public:
	ShDrawLineMethod_Default(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	ShDrawLineMethod_Default(const ShDrawLineMethod_Default& other);
	~ShDrawLineMethod_Default();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info);

	virtual ShDrawLineMethod_Default* Clone();

};


//class ShDrawLineMethod_Perpendicular : public ShDrawLineMethod {

//public:


//};

#endif //_SHDRAWLINEACTION_H
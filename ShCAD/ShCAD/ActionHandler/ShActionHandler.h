

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


/*  This class is the base class that handles all actions such as drawing entities,
**  modifying entities .. or something 
*/

#ifndef _SHACTIONMODE_H
#define _SHACTIONMODE_H

#include "ShVariable.h"
#include <qobject.h>
#include "Interface\ShGraphicView.h"
#include "ShPoint.h"
#include "ShDraft.h"

class ShActionData {
	friend class ShActionHandlerManager;

private:
	ShPoint3d point;
	ShPoint3d nextPoint;
	DrawType drawType;
	bool allowActionHandler;

private:
	ShActionData() :drawType(DrawType::DrawNone), allowActionHandler(true) {}
	~ShActionData() {}

public:

	void SetPoint(const ShPoint3d& point) { this->point = point; }
	void SetNextPoint(const ShPoint3d& point) { this->nextPoint = point; }
	void SetDrawType(DrawType drawType) { this->drawType = drawType; }
	void AppendDrawType(DrawType drawType) { this->drawType = (DrawType)(this->drawType | drawType); }
	void SetAllowActionHandler(bool on) { this->allowActionHandler = on; }


	inline ShPoint3d GetPoint() const { return this->point; }
	inline ShPoint3d GetNextPoint() const { return this->nextPoint; }
	inline DrawType GetDrawType() const { return this->drawType; }
	inline bool AllowActionHandler() const { return this->allowActionHandler; }
	
};


class QMouseEvent;
class QKeyEvent;
class ShActionHandler : public QObject {

protected:
	ShGraphicView *graphicView;
	

public:
	ShActionHandler(ShGraphicView *graphicView);
	virtual ~ShActionHandler() = 0;

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data) = 0;
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data) = 0;
	virtual void MouseReleaseEvent(QMouseEvent *event, ShActionData& data) {}

	virtual ActionType GetType() = 0;
	virtual QCursor GetCursorShape();
	virtual void Draw(QPainter *painter);
	
	//command Edit headtitle based on specific individual currentAction status.
	virtual QString GetActionHeadTitle() { return ":: "; }

	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

	//change individual items when orthogonalMode turned on/off.
	virtual void ApplyOrthogonalShape(bool on) {}

protected:
	bool UnSelectSelectedEntities();
	void GetOrthogonal(double x, double y, double mouseX, double mouseY, double &orthX, double &orthY);

};

#endif //_SHACTIONMODE_H


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

class QMouseEvent;
class QKeyEvent;
class ShSubActionHandler;
class ShActionHandler : public QObject {

protected:
	ShGraphicView *graphicView;
	ShSubActionHandler *subActionHandler;

public:
	ShActionHandler(ShGraphicView *graphicView);
	virtual ~ShActionHandler() = 0;

	virtual void MousePressEvent(QMouseEvent *event) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event) = 0;
	virtual void KeyPressEvent(QKeyEvent *event) = 0;
	virtual void MouseReleaseEvent(QMouseEvent *event) {}

	virtual ActionType GetType() = 0;
	virtual QCursor GetCursorShape();
	virtual void Draw(QPainter *painter);

	virtual void SetObjectSnap(ObjectSnap objectSnap) {}
	virtual void SetOrthogonal();
	virtual void ChangeSubActionHandler(ShSubActionHandler *subActionHandler);
	virtual void ApplyOrthogonalShape(bool isOrthogonalModeOn) {}
	void GetOrthogonal(double x, double y, double mouseX, double mouseY, double &orthX, double &orthY);
	
	//set command Edit headtitle based on specific individual currentAction status.
	virtual void SetActionHeadTitle() {}


protected:
	bool UnSelectSelectedEntities();

};

#endif //_SHACTIONMODE_H
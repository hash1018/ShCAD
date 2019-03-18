
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

#ifndef _SHTEMPORARYACTION_H
#define _SHTEMPORARYACTION_H

/*  Base class that is used only temporary period.
    graphicView is currently set to origianl Action such as default, drawing Line , modifying something , etc,
	This class help origianl Action to do something expansion without changing current original Action.
	For example) zoomAction or panAction can be used while defaultAction is on.

*/

#include "ActionHandler\ShActionHandler.h"
class ShTemporaryAction : public ShActionHandler {

protected:
	ShActionHandler *previousAction;

public:
	ShTemporaryAction(ShGraphicView *graphicView);
	virtual ~ShTemporaryAction() = 0;
	void SetPreviousAction(ShActionHandler *previousAction) { this->previousAction = previousAction; }

	virtual bool EnabledDrawEntityVertex() { return this->previousAction->EnabledDrawEntityVertex(); }

protected:
	void ReturnToPrevious();
};

#endif //_SHTEMPORARYACTION_H

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


#ifndef _SHGRAPHICVIEW_H
#define _SHGRAPHICVIEW_H

#include <qopenglwidget.h>
#include "ShVariable.h"
#include "Memento Pattern\ShUndoTaker.h"

class ShEntityTable;
class ShGraphicView : public QOpenGLWidget {

	friend class ShCADWidget;

protected:
	//this points to class ShCADWidget's var.
	ShEntityTable *entityTable;

	//undo controller.
	ShUndoTaker undoTaker;

public:
	ShGraphicView(QWidget *parent = 0);
	virtual ~ShGraphicView() = 0;

	virtual ActionType ChangeCurrentAction(ActionType actionType) = 0;

	ShEntityTable* GetEntityTable() const;
	ShUndoTaker* GetUndoTaker();
};

inline ShEntityTable* ShGraphicView::GetEntityTable() const {

	return this->entityTable;
}

inline ShUndoTaker* ShGraphicView::GetUndoTaker(){

	return &(this->undoTaker);
}

#endif //_SHGRAPHICVIEW_H
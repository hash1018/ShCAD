
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
#include "Memento Pattern\ShRedoTaker.h"
#include "Entity\Composite\ShPreview.h"
#include "Entity\Composite\ShEntityTable.h"


class ShRubberBand;
class ShActionHandler;
class ShGraphicView : public QOpenGLWidget {

public:

	/* class that maintains a container of entity object */
	ShEntityTable entityTable;

	//undo controller.
	ShUndoTaker undoTaker;
	//redo controller.
	ShRedoTaker redoTaker;

	DrawType drawType;

	QImage captureImage;

	ShActionHandler *currentAction;

	ShRubberBand *rubberBand;

	ShPreview preview;

	

public:
	ShGraphicView(QWidget *parent = 0);
	~ShGraphicView();

	ActionType ChangeCurrentAction(ActionType actionType);

	
	virtual void update(DrawType drawType = DrawType::DrawAll);
	
	void CaptureImage();

protected:
	virtual void initializeGL();
	virtual void paintGL();
	virtual void resizeGL(int width, int height);

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void wheelEvent(QWheelEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void focusInEvent(QFocusEvent *event);
};


#endif //_SHGRAPHICVIEW_H
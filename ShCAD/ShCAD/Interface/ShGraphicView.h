
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
#include "ShAxis.h"

class ShRubberBand;
class ShActionHandler;
class ShGraphicView : public QOpenGLWidget {

private:
	double x;
	double y;
	double z;
	double zoomRate;
	double hPos;
	double vPos;
	double prevX;
	double prevY;

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
	ShAxis axis;

public:
	ShGraphicView(QWidget *parent = 0);
	~ShGraphicView();

	ActionType ChangeCurrentAction(ActionType actionType);
	virtual void update(DrawType drawType = DrawType::DrawAll);
	void CaptureImage();
	void Notify(NotifyEvent event);
	double GetX() const;
	double GetY() const;
	double GetZ() const;
	double GetZoomRate() const;
	double GetHPos() const;
	double GetVPos() const;
	void ConvertDeviceToEntity(int x, int y, double &ex, double &ey);
	void ConvertEntityToDevice(double x, double y, int &dx, int &dy);



protected:
	virtual void initializeGL();
	virtual void paintGL();
	virtual void resizeGL(int width, int height);

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void wheelEvent(QWheelEvent *event);
	virtual void focusInEvent(QFocusEvent *event);
};

inline double ShGraphicView::GetX() const {
	return this->x;
}

inline double ShGraphicView::GetY() const {
	return this->y;
}

inline double ShGraphicView::GetZ() const {
	return this->z;
}

inline double ShGraphicView::GetZoomRate() const {
	return this->zoomRate;
}

inline double ShGraphicView::GetHPos() const {
	return this->hPos;
}

inline double ShGraphicView::GetVPos() const {
	return this->vPos;
}

#endif //_SHGRAPHICVIEW_H